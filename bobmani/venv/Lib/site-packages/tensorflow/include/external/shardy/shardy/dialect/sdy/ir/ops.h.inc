/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ops.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::sdy {

/// Performs an all-gather communication along axes
/// Gathers chunks of a tensor along axes specified in `gathering_axes`.
/// 
///     The `gathering_axes` is a list of lists of axes. The outer list is over the
///     dimensions of the tensor. Each inner list specifies the axes along which a
///     separate gather should be performed on the respective dimension. It will be
///     applied to the sharding of the operand (`tensor`) to obtain the sharding of
///     the result (`out_sharding`).
/// 
///     Note that `out_sharding` is not used to determine the sharding of the
///     result. Instead, the sharding of the result is determined by the sharding of
///     the operand and the `gathering_axes`, and `out_sharding` must match this
///     inferred sharding.
/// 
///     Example:
///     ```mlir
///     %1 = stablehlo.tanh(%0) {sdy.sharding = #sdy.sharding_per_value<[<@mesh, [{"a", "b", "c"}, {}, {"d"}\]>]>} : tensor<8x8x8xf32>
///     %2 = sdy.all_gather [{"b", "c"}, {}, {"d"}\] %1 out_sharding=<@mesh, [{"a"}, {}, {}\]> : tensor<8x8x8xf32>
///     ```
/// 
///     **Constraints:**
///     - Must satisfy the constraints listed in `Sdy_CollectiveOpInterface`.
///     - Elements in `gathering_axes` must satisfy the constraints listed in
///       `AxisRefListAttr`.
///     - Applying `gathering_axes` to the operand sharding gets `out_sharding`.
class AllGatherOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Perform an all-reduce comunication along axes
/// Reduces chunks of a tensor along axes specified in `reduction_axes`.
///     The order of `reduction_axes` is not important for the result, but can
///     affect the order of the corresponding replica groups.
/// 
///     **Constraints:**
///     - Must satisfy the constraints listed in `Sdy_CollectiveOpInterface`.
///     - `reduction_axes` must satisfy the constraints listed in `AxisRefListAttr`.
///     - `reduction_axes` must be sorted w.r.t. the mesh.
///     - The operand sharding and `out_sharding` must have equivalent dimension
///       shardings.
///     - `reduction_axes` must not overlap with the operand dimension sharding and
///       replicated axes (it can overlap with unreduced axes).
///     - `reduction_axes` must not overlap with the unreduced axes of
///       `out_sharding`. In other words, `out_sharding` must be be replicated along
///       `reduction_axes` (implicitly or explicitly).
class AllReduceOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Performs a dynamic-slice operation along axes
/// Slices chunks of a tensor along axes specified in `slicing_axes`. There is
///     an algebric duality between `sdy.all_slice` and `sdy.all_gather`.
/// 
///     The `slicing_axes` is a list of lists of axes. The outer list is over the
///     dimensions of the tensor. Each inner list specifies the axes along which a
///     slice should be performed on the respective dimension. It will be applied to
///     the sharding of the operand (`tensor`) to obtain the sharding of the result
///     (`out_sharding`).
/// 
///     Note that `out_sharding` is not used to determine the sharding of the
///     result. Instead, the sharding of the result is determined by the sharding of
///     the operand and the `slicing_axes`, and `out_sharding` must match this
///     inferred sharding.
/// 
///     Example:
///     ```mlir
///     %1 = stablehlo.tanh(%0) {sdy.sharding = #sdy.sharding_per_value<[<@mesh, [{"a"}, {}, {}\]>]>} : tensor<8x8x8xf32>
///     %2 = sdy.all_slice [{"b", "c"}, {}, {"d"}\] %1 out_sharding=<@mesh, [{"a", "b", "c"}, {}, {"d"}\]> : tensor<8x8x8xf32>
///     ```
/// 
///     **Constraints:**
///     - Must satisfy the constraints listed in `Sdy_CollectiveOpInterface`.
///     - Elements in `slicing_axes` must satisfy the constraints listed in
///       `AxisRefListAttr`.
///     - Applying `slicing_axes` to the operand sharding gets `out_sharding`.
class AllSliceOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Performs an all-to-all communication along axes
/// For each (axes, src_dim, tgt_dim) tuple in the parameter list, this
///     operation slices chunks of a tensor along dimension `tgt_dim` and axes
///     specified in `axes`, scatteres those chunks along the axes, and concatenates
///     them along dimension `src_dim`.
/// 
///     This operation is essentially a combination of an all-gather along `src_dim`
///     and `axes`, followed by an all-slice along `tgt_dim` and `axes`, i.e., a
///     suffix of the axes sharding dimension `src_dim` on the input tensor is
///     appended to the axes sharding dimension `tgt_dim` on the output tensor.
/// 
///     The all-to-all will be applied to the sharding of the operand (`tensor`) to
///     obtain the sharding of the result (`out_sharding`).
/// 
///     Note that `out_sharding` is not used to determine the sharding of the
///     result. Instead, the sharding of the result is determined by the sharding of
///     the operand, `src_dim`, `tgt_dim`, and `axes`, and `out_sharding` must match
///     this inferred sharding.
/// 
///     Example:
///     ```mlir
///     %1 = stablehlo.tanh(%0) {sdy.sharding = #sdy.sharding_per_value<[<@mesh, [{"a", "b"}, {"c"}, {}, {}\]>]>} : tensor<8x8x4x4x32>
///     %2 = sdy.all_to_all [{"b"}: 0->2, {"c"}: 1->3] %1 out_sharding=<@mesh, [{"a"}, {}, {"b"}, {"c"}\]> : tensor<8x8x4x4x32>
///     ```
/// 
///     **Constraints:**
///     - Must satisfy the constraints listed in `Sdy_CollectiveOpInterface`.
///     - The parameter list must not be empty.
///     - For each parameter in `params`:
///       - Elements in `axes` must satisfy the constraints of `AxisRefAttr`.
///       - `src_dim` and `tgt_dim` must be valid dimensions (non-negative and less
///       than rank of tensor).
///       - Any `src_dim` or `tgt_dim` must be unique across all parameters.
///       - `src_dim` must be sorted in ascending order across all parameters.
///     - Moving `axes` from `src_dim` to `tgt_dim` in the operand sharding gets
///       `out_sharding`.
class AllToAllOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Performs a collective-permute communication to replace axes
/// Sends a chunk of the input tensor from each device to another to
///     reorder/replace the axes that shard the tensor.
/// 
///     A collective permute can transform the input sharding such that each
///     dimension must be as sharded as it was before, i.e., it must be sharded
///     along axes whose product of sizes matches that of the axes that previously
///     sharded the tensor.
/// 
///     This is useful for reordering axes in a single dimension or across different
///     dimensions, and swapping sharded axes with replicated ones.
/// 
///     In the below example, the sharded tensor size is `tensor<1x4x2xf32>`, and
///     that is preserved by the collective permute.
/// 
///     Example:
///     ```mlir
///     sdy.mesh @mesh = <["a"=2, "b"=2, "c"=4, "d"=2, "e"=2, "f"=2]>
///     %1 = stablehlo.tanh(%0) {sdy.sharding = #sdy.sharding_per_value<[<@mesh, [{"a", "c"}, {"f"}, {"d", "e"}\]>]>} : tensor<8x8x8xf32>
///     %2 = sdy.collective_permute %1 out_sharding=<@mesh, [{"c":(1)2, "b", "f"}, {"a"}, {"e", "d"}\]> : tensor<8x8x8xf32>
///     ```
/// 
///     **Constraints:**
///     - Must satisfy the constraints listed in `Sdy_CollectiveOpInterface`.
///     - If input and output sharding have different meshes, then those meshes must
///       have exactly the same axes and different order of device ids.
///     - For each dimension, the product of sharding axis sizes in `out_sharding`
///       must match that of the corresponding operand dimension sharding.
class CollectivePermuteOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Constant operation
/// Produces an `output` tensor from a constant `value`.
/// 
///     See:
///     https://github.com/openxla/stablehlo/blob/main/docs/spec.md#constant
/// 
///     NOTE: SDY defines its own constant op that isn't ConstantLike and doesn't
///     have a folder, so that we'll be able to duplicate constants without any
///     greedy pattern rewriter folding them back into a single constant. In this
///     way, constants can be sharded differently for every use, and no propagation
///     is done between constants (or constant expressions).
/// 
///     Example:
///     ```mlir
///     %output = sdy.constant dense<[[0.0, 1.0], [2.0, 3.0]]> : tensor<2x2xf32>
///     ```
class ConstantOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// data flow edge op.
/// A data flow edge of some op X defines a bridge between a set of sources
///     (each is either an operand of X or an operand of X's block terminator) and
///     a set of targets (each is either a result of X or a block argument of X),
///     such that all sources and targets should be sharded in the same way.
/// 
///     An op can have multiple data flow edges that are orthogonal to one another.
/// 
///     For example:
/// 
///     ```mlir
///       y_0, ..., y_n = while (x_0, ..., x_n)
///                       ((pred_arg_0,... , pred_arg_n) { ... })
///                       ((body_arg_0,..., body_arg_n) {
///                         ...
///                         return return_value_0, ..., return_value_n
///                       })
///     ```
/// 
///     This while op has n data flow edges, the i-th data flow edges is between
///     sources `x_i`, `return_value_i` and targets `y_i`, `pred_arg_i`,
///     `body_arg_i`.
/// 
///     An `sdy.data_flow_edge` takes as input the owner of an edge (can be
///     any of the targets, but preferably an op result rather than a block
///     argument), which shouldn't have any other uses. This op isn't pure because
///     it can take an input that originally didn't have any uses.
/// 
///     The `sdy.data_flow_edge` also holds an optional sharding for all targets of
///     the edge, and that sharding should be updated instead of the targets'
///     sharding (if can be attached) during propagation. This is useful when an op
///     has many edges, as it's much more efficient to:
///     - propagate through each edge separately.
///     - update the sharding of each edge separately instead of all targets at once
///       (e.g. an op has a single immutable `TensorShardingPerValueAttr` for result
///       shardings).
///     - add each edge to the worklist separately when the sharding of a source has
///       changed.
/// 
///     Propagation will propagate shardings between all sources and targets of a
///     `sdy.data_flow_edge` as if it was a regular op with the sources as operands
///     and targets as results, and an identity `sdy.op_sharding_rule`. That means
///     that forward propagation is from sources to targets and backwards
///     propagation is from targets to sources.
/// 
///     We don't allow the input of a `sdy.data_flow_edge` to be defined by an
///     `SdyDialect` op, so we can assume that it's defined by an op that has
///     unregistered `sdy.sharding` attribute.
/// 
///     NOTE: it's NOT the responsibility of the `sdy.data_flow_edge` to link
///     between sources and targets, it's simply attached to the owner of the edge.
///     The op that this edge is bound to (while in the example above) is
///     responsible for providing this information.
class DataFlowEdgeOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Multi-device parallelism operation with manual collectives
/// Jump into a region written in terms of per-device local code with explicit
///     collectives, where logical shapes match local per-device physical buffer
///     shapes and collectives correspond exactly to physical cross-device
///     communication.
/// 
///     The body is local wrt the manual_axes. Propagation will occur through
///     the body on any free axes - those not in the manual_axes list.
/// 
///     Note that any unranked tensors are expected to have a sharding with rank 0,
///     i.e. fully replicated.
/// 
///     **Constraints:**
///     - Elements in `in_shardings` and `out_shardings` must satisfy the constraints listed in `TensorShardingAttr`.
///     - The number of global and local tensor inputs/outputs of the op region must match.
///     - The manual axes must come before any free axes in each dim sharding.
///     - The manual axes cannot introduce padding. Namely, the dimension size must be divisible by the corresponding manual axes size.
///     - The global and local shapes of the op regions arguments/results must match.
class ManualComputationOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Named mesh
/// Defines a new named mesh. All meshes in a module must have the same number
///     of devices (except for meshes with a single device_id).
///     The mesh is a `Symbol` operation that appears in the module's
///     `SymbolTable` and can be referenced by its `name`.
class MeshOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// named computation operation
/// Groups a computation, i.e. a block of operations, and gives it a name.
///     Propagation will flow in/out of the region as if everything was inlined.
/// 
///     This can be used to handle propagating through call instructions to other
///     functions. Any users of Shardy should write an import/export pass that
///     converts their call ops to `sdy.named_computation` ops, duplicating/copying
///     the body of the called function into the body of the `named_computation`.
/// 
///     The type of each block arguments and returned values in the region must be
///     the same as the type of the operands and results type of the op.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = sdy.named_computation<"foo">(%0) (%arg1: tensor<16x32xf32>) {
///       sdy.return %arg1 : tensor<16x32xf32>
///     } : (tensor<16x32xf32>) -> tensor<16x32xf32>
///     ```
class NamedComputationOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Propagation barrier operation
/// This op operates like an identity op, outputting the same value it took as
///     input. But in terms of propagation, this will only allow propagation to flow
///     through it in a certain direction.
/// 
///     This prevents shardings from being propagated between the uses of the result
///     of the barrier op and its operand.
/// 
///     - `FORWARD` means shardings can only flow from the operand to the result.
///     - `BACKWARD` means shardings can only flow from the result to the operand.
///     - `NONE` means no sharding can propagate through this op.
///     - Cannot specify `BOTH`, as this op would be redundant.
class PropagationBarrierOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Performs a reduce-scatter communication along axes
/// Reduces chunks of a tensor along axes specified in `reduce_scatter_axes`,
///     and then scatters the result along the same axes. This operation is
///     essentially a combination of an `sdy.all_reduce` followed by an
///     `sdy.all_slice` along the same `reduce_scatter_axes`.
/// 
///     **Constraints:**
///     - Must satisfy the constraints listed in `Sdy_CollectiveOpInterface`.
///     - Elements in `reduce_scatter_axes` must satisfy the constraints listed in
///       `AxisRefListAttr`.
///     - Applying `reduce_scatter_axes` to the operand sharding gets
///       `out_sharding`.
class ReduceScatterOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Move implicitly or explicitly replicated axes to unreduced axes.
/// The `axes` should be implicitly or explicitly replicated in the operand.
///     This operation makes them unreduced in the result. We have the following
///     relationship:
/// 
///     all-reduce(replicated-to-unreduced(x, axes), axes) = x
/// 
///     Example:
///     ```mlir
///     %1 = stablehlo.tanh(%0) {sdy.sharding = #sdy.sharding_per_value<[<@mesh, [{"b"}, {}, {}\], replicated={"c", "d"}, unreduced={"e"}>]>} : tensor<8x8x8xf32>
///     %2 = sdy.replicated_to_unreduced {"a", "c", "f"} %1 out_sharding=<@mesh, [{"b"}, {}, {}\], replicated={"d"}, unreduced={"a", "c", "e", "f"}> : tensor<8x8x8xf32>
///     ```
/// 
///     **Constraints:**
///     - Must satisfy the constraints listed in `Sdy_CollectiveOpInterface`.
///     - `axes` must satisfy the constraints listed in `AxisRefListAttr`.
///     - `axes` must be sorted w.r.t. the mesh.
///     - `axes` are not empty.
///     - The input and output sharding must have the same dimension shardings.
///     - `axes` must be implicitly or explicitly replicated in the operand sharding.
///     - inUnreducedAxes + axes = outUnreducedAxes.
class ReplicatedToUnreducedOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Reshards a tensor to a different sharding
/// Reshards the input tensor with the specified sharding, which is different
///     from the input tensor's existing sharding.
/// 
///     Both ShardingConstraintOp and ReshardOp attach a sharding to a tensor. Their
///     lifespan is:
///     1. Before sharding propagation, ShardingConstraintOp is added by users.
///     2. Sharding propagation consumes ShardingConstraintOp. There is no
///        ShardingConstraintOp in the results of sharding propagation. Instead,
///        ReshardOp may be added if needed.
///     3. A partitioner converts a ReshardOp into a collective op (or an identity
///        op). There should be no ReshardOp in the results of the partitioner.
class ReshardOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// The `sdy.return` operation terminates the regions attached to
///     `sdy` region-based ops and any other Shardy region-based ops. It is
///     variadic: it takes as arguments a list of values whose types can be any (but
///     of the same kind, e.g. `AnyTensor`) and therefore can be reused at various
///     levels of the Shardy IR stack.
class ReturnOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Move some sharded axes of the operand to unreduced axes of the result.
/// The `axes` should be used to shard the operand. This operation makes them
///     unreduced in the result. We have the following relationship:
/// 
///     all-gather(x, axes) = all-reduce(sharded-to-unreduced(x, axes), axes), where
///     all-gather, sharded-to-unreduced, all-reduce are applied on the same axes.
/// 
///     Example:
///     ```mlir
///     %1 = stablehlo.tanh(%0) {sdy.sharding = #sdy.sharding_per_value<[<@mesh, [{"a", "b", "c"}, {}, {"d"}\], unreduced={"e"}>]>} : tensor<8x8x8xf32>
///     %2 = sdy.sharded_to_unreduced [{"b", "c"}, {}, {"d"}\] %1 out_sharding=<@mesh, [{"a"}, {}, {}\], unreduced={"b", "c", "d", "e"}> : tensor<8x8x8xf32>
///     ```
/// 
///     **Constraints:**
///     - Must satisfy the constraints listed in `Sdy_CollectiveOpInterface`.
///     - Elements in `axes` must satisfy the constraints listed in `AxisRefListAttr`.
///     - Applying `axes` to the operand sharding gets `out_sharding`.
class ShardedToUnreducedOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Constrains a tensor to the specified sharding
/// Attaches a sharding to an intermediate tensor (e.g. the result of a matmul)
///     to indicate that this is how that tensor, or a subset of its uses, should be
///     sharded.
/// 
///     If the sharding has open dimensions and unconstraint axes, it means the
///     tensor can be further sharded along the open dimensions.
/// 
///     This op can either:
///     - Have no uses (dangling) - which means the attached sharding is how the
///       input tensor itself should be sharded.
///     - Have uses - which means the attached sharding is how the uses of the
///       sharding constraint op should be sharded, while other uses of the input
///       tensor might have a different sharding (if the input tensor has no other
///       uses then the behavior is the same as the no uses case).
class ShardingConstraintOp;

} // namespace mlir::sdy
namespace mlir::sdy {

/// Constrains tensors in the group to have the same sharding.
/// This op provides an interface to assign tensors to sharding groups (
///     groups of tensors that will be enforced to have identical shardings).
///     During propagation, as soon as one group element is sharded, all other
///     members will be sharded in exactly the same way. This operation takes the
///     argument group ID and returns no result, but instead modifies the internal
///     sharding group representation to add the input tensor to the group with the
///     given ID.
class ShardingGroupOp;

} // namespace mlir::sdy
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::AllGatherOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllGatherOpGenericAdaptorBase {
public:
  struct Properties {
    using gathering_axesTy = ::mlir::sdy::ListOfAxisRefListsAttr;
    gathering_axesTy gathering_axes;

    auto getGatheringAxes() const {
      auto &propStorage = this->gathering_axes;
      return ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(propStorage);
    }
    void setGatheringAxes(const ::mlir::sdy::ListOfAxisRefListsAttr &propValue) {
      this->gathering_axes = propValue;
    }
    using out_shardingTy = ::mlir::sdy::TensorShardingAttr;
    out_shardingTy out_sharding;

    auto getOutSharding() const {
      auto &propStorage = this->out_sharding;
      return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setOutSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->out_sharding = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.gathering_axes == this->gathering_axes &&
        rhs.out_sharding == this->out_sharding &&
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
      odsOpName.emplace("sdy.all_gather", odsAttrs.getContext());
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

  ::mlir::sdy::ListOfAxisRefListsAttr getGatheringAxesAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(getProperties().gathering_axes);
    return attr;
  }

  ::llvm::ArrayRef<AxisRefListAttr> getGatheringAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
    return attr;
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
};

} // namespace detail
template <typename RangeT>
class AllGatherOpGenericAdaptor : public detail::AllGatherOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllGatherOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
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

  ValueT getTensor() {
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
class AllGatherOp : public ::mlir::Op<AllGatherOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait, ::mlir::sdy::CollectiveOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllGatherOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllGatherOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("gathering_axes"), ::llvm::StringRef("out_sharding")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGatheringAxesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGatheringAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOutShardingAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getOutShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.all_gather");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::ListOfAxisRefListsAttr getGatheringAxesAttr() {
    return ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(getProperties().gathering_axes);
  }

  ::llvm::ArrayRef<AxisRefListAttr> getGatheringAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
  void setGatheringAxesAttr(::mlir::sdy::ListOfAxisRefListsAttr attr) {
    getProperties().gathering_axes = attr;
  }

  void setGatheringAxes(::llvm::ArrayRef<AxisRefListAttr> attrValue);
  void setOutShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().out_sharding = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> gathering_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::AllGatherOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::AllReduceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllReduceOpGenericAdaptorBase {
public:
  struct Properties {
    using out_shardingTy = ::mlir::sdy::TensorShardingAttr;
    out_shardingTy out_sharding;

    auto getOutSharding() const {
      auto &propStorage = this->out_sharding;
      return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setOutSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->out_sharding = propValue;
    }
    using reduction_axesTy = ::mlir::sdy::AxisRefListAttr;
    reduction_axesTy reduction_axes;

    auto getReductionAxes() const {
      auto &propStorage = this->reduction_axes;
      return ::llvm::cast<::mlir::sdy::AxisRefListAttr>(propStorage);
    }
    void setReductionAxes(const ::mlir::sdy::AxisRefListAttr &propValue) {
      this->reduction_axes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.out_sharding == this->out_sharding &&
        rhs.reduction_axes == this->reduction_axes &&
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
      odsOpName.emplace("sdy.all_reduce", odsAttrs.getContext());
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

  ::mlir::sdy::AxisRefListAttr getReductionAxesAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::AxisRefListAttr>(getProperties().reduction_axes);
    return attr;
  }

  ::llvm::ArrayRef<AxisRefAttr> getReductionAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
    return attr;
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
};

} // namespace detail
template <typename RangeT>
class AllReduceOpGenericAdaptor : public detail::AllReduceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllReduceOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
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

  ValueT getTensor() {
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
class AllReduceOp : public ::mlir::Op<AllReduceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::sdy::CollectiveOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllReduceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllReduceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::sdy::CollectiveOpInterface::Trait<AllReduceOp>::allowDifferentMeshes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("out_sharding"), ::llvm::StringRef("reduction_axes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOutShardingAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOutShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getReductionAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getReductionAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.all_reduce");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::AxisRefListAttr getReductionAxesAttr() {
    return ::llvm::cast<::mlir::sdy::AxisRefListAttr>(getProperties().reduction_axes);
  }

  ::llvm::ArrayRef<AxisRefAttr> getReductionAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
  void setReductionAxesAttr(::mlir::sdy::AxisRefListAttr attr) {
    getProperties().reduction_axes = attr;
  }

  void setReductionAxes(::llvm::ArrayRef<AxisRefAttr> attrValue);
  void setOutShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().out_sharding = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> reduction_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
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
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  ::mlir::Type getType();
  bool allowMissingInputSharding();
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::AllReduceOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::AllSliceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllSliceOpGenericAdaptorBase {
public:
  struct Properties {
    using out_shardingTy = ::mlir::sdy::TensorShardingAttr;
    out_shardingTy out_sharding;

    auto getOutSharding() const {
      auto &propStorage = this->out_sharding;
      return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setOutSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->out_sharding = propValue;
    }
    using slicing_axesTy = ::mlir::sdy::ListOfAxisRefListsAttr;
    slicing_axesTy slicing_axes;

    auto getSlicingAxes() const {
      auto &propStorage = this->slicing_axes;
      return ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(propStorage);
    }
    void setSlicingAxes(const ::mlir::sdy::ListOfAxisRefListsAttr &propValue) {
      this->slicing_axes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.out_sharding == this->out_sharding &&
        rhs.slicing_axes == this->slicing_axes &&
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
      odsOpName.emplace("sdy.all_slice", odsAttrs.getContext());
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

  ::mlir::sdy::ListOfAxisRefListsAttr getSlicingAxesAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(getProperties().slicing_axes);
    return attr;
  }

  ::llvm::ArrayRef<AxisRefListAttr> getSlicingAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
    return attr;
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
};

} // namespace detail
template <typename RangeT>
class AllSliceOpGenericAdaptor : public detail::AllSliceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllSliceOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
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

  ValueT getTensor() {
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
class AllSliceOp : public ::mlir::Op<AllSliceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::sdy::CollectiveOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllSliceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllSliceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::sdy::CollectiveOpInterface::Trait<AllSliceOp>::allowDifferentMeshes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("out_sharding"), ::llvm::StringRef("slicing_axes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOutShardingAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOutShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSlicingAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSlicingAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.all_slice");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::ListOfAxisRefListsAttr getSlicingAxesAttr() {
    return ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(getProperties().slicing_axes);
  }

  ::llvm::ArrayRef<AxisRefListAttr> getSlicingAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
  void setSlicingAxesAttr(::mlir::sdy::ListOfAxisRefListsAttr attr) {
    getProperties().slicing_axes = attr;
  }

  void setSlicingAxes(::llvm::ArrayRef<AxisRefListAttr> attrValue);
  void setOutShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().out_sharding = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> slicing_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  ::mlir::Type getType();
  bool allowMissingInputSharding();
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::AllSliceOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::AllToAllOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllToAllOpGenericAdaptorBase {
public:
  struct Properties {
    using out_shardingTy = ::mlir::sdy::TensorShardingAttr;
    out_shardingTy out_sharding;

    auto getOutSharding() const {
      auto &propStorage = this->out_sharding;
      return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setOutSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->out_sharding = propValue;
    }
    using paramsTy = ::mlir::sdy::AllToAllParamListAttr;
    paramsTy params;

    auto getParams() const {
      auto &propStorage = this->params;
      return ::llvm::cast<::mlir::sdy::AllToAllParamListAttr>(propStorage);
    }
    void setParams(const ::mlir::sdy::AllToAllParamListAttr &propValue) {
      this->params = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.out_sharding == this->out_sharding &&
        rhs.params == this->params &&
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
      odsOpName.emplace("sdy.all_to_all", odsAttrs.getContext());
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

  ::mlir::sdy::AllToAllParamListAttr getParamsAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::AllToAllParamListAttr>(getProperties().params);
    return attr;
  }

  ::llvm::ArrayRef<AllToAllParamAttr> getParams();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
    return attr;
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
};

} // namespace detail
template <typename RangeT>
class AllToAllOpGenericAdaptor : public detail::AllToAllOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllToAllOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
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

  ValueT getTensor() {
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
class AllToAllOp : public ::mlir::Op<AllToAllOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait, ::mlir::sdy::CollectiveOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllToAllOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllToAllOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("out_sharding"), ::llvm::StringRef("params")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOutShardingAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOutShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getParamsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getParamsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.all_to_all");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::AllToAllParamListAttr getParamsAttr() {
    return ::llvm::cast<::mlir::sdy::AllToAllParamListAttr>(getProperties().params);
  }

  ::llvm::ArrayRef<AllToAllParamAttr> getParams();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
  void setParamsAttr(::mlir::sdy::AllToAllParamListAttr attr) {
    getProperties().params = attr;
  }

  void setParams(::llvm::ArrayRef<AllToAllParamAttr> attrValue);
  void setOutShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().out_sharding = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::AllToAllParamListAttr params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::AllToAllParamListAttr params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::AllToAllParamListAttr params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::sdy::AllToAllParamListAttr params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::sdy::AllToAllParamListAttr params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::sdy::AllToAllParamListAttr params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::AllToAllParamListAttr params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::AllToAllParamListAttr params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::AllToAllParamListAttr params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AllToAllParamAttr> params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AllToAllParamAttr> params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AllToAllParamAttr> params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::llvm::ArrayRef<AllToAllParamAttr> params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::llvm::ArrayRef<AllToAllParamAttr> params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::llvm::ArrayRef<AllToAllParamAttr> params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AllToAllParamAttr> params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AllToAllParamAttr> params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AllToAllParamAttr> params, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::AllToAllOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::CollectivePermuteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CollectivePermuteOpGenericAdaptorBase {
public:
  struct Properties {
    using out_shardingTy = ::mlir::sdy::TensorShardingAttr;
    out_shardingTy out_sharding;

    auto getOutSharding() const {
      auto &propStorage = this->out_sharding;
      return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setOutSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->out_sharding = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.out_sharding == this->out_sharding &&
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
  CollectivePermuteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.collective_permute", odsAttrs.getContext());
  }

  CollectivePermuteOpGenericAdaptorBase(CollectivePermuteOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
    return attr;
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
};

} // namespace detail
template <typename RangeT>
class CollectivePermuteOpGenericAdaptor : public detail::CollectivePermuteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CollectivePermuteOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  CollectivePermuteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CollectivePermuteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CollectivePermuteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CollectivePermuteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CollectivePermuteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CollectivePermuteOpGenericAdaptor(RangeT values, const CollectivePermuteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CollectivePermuteOp, typename = std::enable_if_t<std::is_same_v<LateInst, CollectivePermuteOp>>>
  CollectivePermuteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CollectivePermuteOpAdaptor : public CollectivePermuteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CollectivePermuteOpGenericAdaptor::CollectivePermuteOpGenericAdaptor;
  CollectivePermuteOpAdaptor(CollectivePermuteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CollectivePermuteOp : public ::mlir::Op<CollectivePermuteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::sdy::CollectiveOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CollectivePermuteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CollectivePermuteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::sdy::CollectiveOpInterface::Trait<CollectivePermuteOp>::allowMissingInputSharding;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("out_sharding")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOutShardingAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOutShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.collective_permute");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
  void setOutShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().out_sharding = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::TensorShardingAttr out_sharding);
  static CollectivePermuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::TensorShardingAttr out_sharding);
  static CollectivePermuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::sdy::TensorShardingAttr out_sharding);
  static CollectivePermuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::sdy::TensorShardingAttr out_sharding);
  static CollectivePermuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::TensorShardingAttr out_sharding);
  static CollectivePermuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::TensorShardingAttr out_sharding);
  static CollectivePermuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CollectivePermuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CollectivePermuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CollectivePermuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CollectivePermuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CollectivePermuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CollectivePermuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CollectivePermuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CollectivePermuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  ::mlir::Type getType();
  bool allowDifferentMeshes();
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::CollectivePermuteOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::ConstantOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConstantOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::mlir::ElementsAttr;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::ElementsAttr>(propStorage);
    }
    void setValue(const ::mlir::ElementsAttr &propValue) {
      this->value = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.value == this->value &&
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
  ConstantOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.constant", odsAttrs.getContext());
  }

  ConstantOpGenericAdaptorBase(ConstantOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ElementsAttr getValueAttr() {
    auto attr = ::llvm::cast<::mlir::ElementsAttr>(getProperties().value);
    return attr;
  }

  ::mlir::ElementsAttr getValue();
};

} // namespace detail
template <typename RangeT>
class ConstantOpGenericAdaptor : public detail::ConstantOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConstantOpGenericAdaptorBase;
public:
  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ConstantOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConstantOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConstantOpGenericAdaptor(RangeT values, const ConstantOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConstantOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConstantOp>>>
  ConstantOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ConstantOpAdaptor : public ConstantOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConstantOpGenericAdaptor::ConstantOpGenericAdaptor;
  ConstantOpAdaptor(ConstantOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConstantOp : public ::mlir::Op<ConstantOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConstantOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConstantOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<ConstantOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("value")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getValueAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getValueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.constant");
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

  ::mlir::TypedValue<::mlir::RankedTensorType> getOutput() {
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
  ::mlir::ElementsAttr getValueAttr() {
    return ::llvm::cast<::mlir::ElementsAttr>(getProperties().value);
  }

  ::mlir::ElementsAttr getValue();
  void setValueAttr(::mlir::ElementsAttr attr) {
    getProperties().value = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::ElementsAttr value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::ElementsAttr value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::ElementsAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ElementsAttr value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ElementsAttr value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ElementsAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ElementsAttr value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ElementsAttr value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ElementsAttr value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
  static bool isCompatibleReturnTypes(TypeRange l, TypeRange r);
};

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ConstantOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::DataFlowEdgeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DataFlowEdgeOpGenericAdaptorBase {
public:
  struct Properties {
    using shardingTy = ::mlir::sdy::TensorShardingAttr;
    shardingTy sharding;

    auto getSharding() const {
      auto &propStorage = this->sharding;
      return ::llvm::dyn_cast_or_null<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->sharding = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sharding == this->sharding &&
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
  DataFlowEdgeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.data_flow_edge", odsAttrs.getContext());
  }

  DataFlowEdgeOpGenericAdaptorBase(DataFlowEdgeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sdy::TensorShardingAttr getShardingAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::sdy::TensorShardingAttr>(getProperties().sharding);
    return attr;
  }

  ::std::optional<::mlir::sdy::TensorShardingAttr> getSharding();
};

} // namespace detail
template <typename RangeT>
class DataFlowEdgeOpGenericAdaptor : public detail::DataFlowEdgeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DataFlowEdgeOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  DataFlowEdgeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DataFlowEdgeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DataFlowEdgeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DataFlowEdgeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DataFlowEdgeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DataFlowEdgeOpGenericAdaptor(RangeT values, const DataFlowEdgeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DataFlowEdgeOp, typename = std::enable_if_t<std::is_same_v<LateInst, DataFlowEdgeOp>>>
  DataFlowEdgeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DataFlowEdgeOpAdaptor : public DataFlowEdgeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DataFlowEdgeOpGenericAdaptor::DataFlowEdgeOpGenericAdaptor;
  DataFlowEdgeOpAdaptor(DataFlowEdgeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DataFlowEdgeOp : public ::mlir::Op<DataFlowEdgeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::SymbolUserOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DataFlowEdgeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DataFlowEdgeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sharding")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getShardingAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.data_flow_edge");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::TensorShardingAttr getShardingAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::sdy::TensorShardingAttr>(getProperties().sharding);
  }

  ::std::optional<::mlir::sdy::TensorShardingAttr> getSharding();
  void setShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().sharding = attr;
  }

  ::mlir::Attribute removeShardingAttr() {
      auto attr = getProperties().sharding;
      getProperties().sharding = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input);
  static DataFlowEdgeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input);
  static DataFlowEdgeOp create(::mlir::ImplicitLocOpBuilder &builder, Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::sdy::TensorShardingAttr sharding);
  static DataFlowEdgeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::sdy::TensorShardingAttr sharding);
  static DataFlowEdgeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::sdy::TensorShardingAttr sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, /*optional*/::mlir::sdy::TensorShardingAttr sharding);
  static DataFlowEdgeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, /*optional*/::mlir::sdy::TensorShardingAttr sharding);
  static DataFlowEdgeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, /*optional*/::mlir::sdy::TensorShardingAttr sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::sdy::TensorShardingAttr sharding);
  static DataFlowEdgeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::sdy::TensorShardingAttr sharding);
  static DataFlowEdgeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::sdy::TensorShardingAttr sharding);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DataFlowEdgeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DataFlowEdgeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DataFlowEdgeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DataFlowEdgeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DataFlowEdgeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DataFlowEdgeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DataFlowEdgeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DataFlowEdgeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
  // If `target` is a target of a data-flow edge, returns the corresponding
  // `DataFlowEdgeOp`, otherwise returns `nullptr`.
  static DataFlowEdgeOp lookup(Value target);

  // If `source` is a source of a data-flow edge, returns the corresponding
  // `DataFlowEdgeOp`, otherwise returns `nullptr`.
  static DataFlowEdgeOp lookup(OpOperand& source);

  // Transforms the `sharding` of a target depending on `transformType`.
  //
  // See `DataFlowShardingTransformType` for more information.
  TensorShardingAttr transformTargetSharding(
      TensorShardingAttr sharding,
      DataFlowShardingTransformType transformType);

  // Returns all sources of this `DataFlowEdgeOp`.
  SmallVector<Value> getSources();

  // Returns all non-edge-owner targets of this `DataFlowEdgeOp`.
  SmallVector<Value> getNonOwnerTargets();
};

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::DataFlowEdgeOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::ManualComputationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ManualComputationOpGenericAdaptorBase {
public:
  struct Properties {
    using in_shardingsTy = ::mlir::sdy::TensorShardingPerValueAttr;
    in_shardingsTy in_shardings;

    auto getInShardings() const {
      auto &propStorage = this->in_shardings;
      return ::llvm::cast<::mlir::sdy::TensorShardingPerValueAttr>(propStorage);
    }
    void setInShardings(const ::mlir::sdy::TensorShardingPerValueAttr &propValue) {
      this->in_shardings = propValue;
    }
    using manual_axesTy = ::mlir::sdy::ManualAxesAttr;
    manual_axesTy manual_axes;

    auto getManualAxes() const {
      auto &propStorage = this->manual_axes;
      return ::llvm::cast<::mlir::sdy::ManualAxesAttr>(propStorage);
    }
    void setManualAxes(const ::mlir::sdy::ManualAxesAttr &propValue) {
      this->manual_axes = propValue;
    }
    using out_shardingsTy = ::mlir::sdy::TensorShardingPerValueAttr;
    out_shardingsTy out_shardings;

    auto getOutShardings() const {
      auto &propStorage = this->out_shardings;
      return ::llvm::cast<::mlir::sdy::TensorShardingPerValueAttr>(propStorage);
    }
    void setOutShardings(const ::mlir::sdy::TensorShardingPerValueAttr &propValue) {
      this->out_shardings = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.in_shardings == this->in_shardings &&
        rhs.manual_axes == this->manual_axes &&
        rhs.out_shardings == this->out_shardings &&
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
  ManualComputationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.manual_computation", odsAttrs.getContext());
  }

  ManualComputationOpGenericAdaptorBase(ManualComputationOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sdy::TensorShardingPerValueAttr getInShardingsAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingPerValueAttr>(getProperties().in_shardings);
    return attr;
  }

  ::mlir::sdy::TensorShardingPerValueAttr getInShardings();
  ::mlir::sdy::TensorShardingPerValueAttr getOutShardingsAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingPerValueAttr>(getProperties().out_shardings);
    return attr;
  }

  ::mlir::sdy::TensorShardingPerValueAttr getOutShardings();
  ::mlir::sdy::ManualAxesAttr getManualAxesAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::ManualAxesAttr>(getProperties().manual_axes);
    return attr;
  }

  ::llvm::ArrayRef<StringAttr> getManualAxes();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ManualComputationOpGenericAdaptor : public detail::ManualComputationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ManualComputationOpGenericAdaptorBase;
  static constexpr int odsIndex_tensors = 0;
public:
  ManualComputationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ManualComputationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ManualComputationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ManualComputationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ManualComputationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ManualComputationOpGenericAdaptor(RangeT values, const ManualComputationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ManualComputationOp, typename = std::enable_if_t<std::is_same_v<LateInst, ManualComputationOp>>>
  ManualComputationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getTensors() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ManualComputationOpAdaptor : public ManualComputationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ManualComputationOpGenericAdaptor::ManualComputationOpGenericAdaptor;
  ManualComputationOpAdaptor(ManualComputationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ManualComputationOp : public ::mlir::Op<ManualComputationOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<ReturnOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::SymbolUserOpInterface::Trait, ::mlir::sdy::ShardableDataFlowOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ManualComputationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ManualComputationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensors = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::sdy::ShardableDataFlowOpInterface::Trait<ManualComputationOp>::getNonEdgeOwnerTargets;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("in_shardings"), ::llvm::StringRef("manual_axes"), ::llvm::StringRef("out_shardings")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInShardingsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInShardingsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getManualAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getManualAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOutShardingsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getOutShardingsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.manual_computation");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getTensors() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getTensorsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
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
  ::mlir::sdy::TensorShardingPerValueAttr getInShardingsAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingPerValueAttr>(getProperties().in_shardings);
  }

  ::mlir::sdy::TensorShardingPerValueAttr getInShardings();
  ::mlir::sdy::TensorShardingPerValueAttr getOutShardingsAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingPerValueAttr>(getProperties().out_shardings);
  }

  ::mlir::sdy::TensorShardingPerValueAttr getOutShardings();
  ::mlir::sdy::ManualAxesAttr getManualAxesAttr() {
    return ::llvm::cast<::mlir::sdy::ManualAxesAttr>(getProperties().manual_axes);
  }

  ::llvm::ArrayRef<StringAttr> getManualAxes();
  void setInShardingsAttr(::mlir::sdy::TensorShardingPerValueAttr attr) {
    getProperties().in_shardings = attr;
  }

  void setOutShardingsAttr(::mlir::sdy::TensorShardingPerValueAttr attr) {
    getProperties().out_shardings = attr;
  }

  void setManualAxesAttr(::mlir::sdy::ManualAxesAttr attr) {
    getProperties().manual_axes = attr;
  }

  void setManualAxes(::llvm::ArrayRef<StringAttr> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange results, ValueRange tensors, ArrayRef<TensorShardingAttr> in_shardings, ArrayRef<TensorShardingAttr> out_shardings, ArrayRef<StringAttr> manual_axes);
  static ManualComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange results, ValueRange tensors, ArrayRef<TensorShardingAttr> in_shardings, ArrayRef<TensorShardingAttr> out_shardings, ArrayRef<StringAttr> manual_axes);
  static ManualComputationOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange results, ValueRange tensors, ArrayRef<TensorShardingAttr> in_shardings, ArrayRef<TensorShardingAttr> out_shardings, ArrayRef<StringAttr> manual_axes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ValueRange tensors, ::mlir::sdy::TensorShardingPerValueAttr in_shardings, ::mlir::sdy::TensorShardingPerValueAttr out_shardings, ::mlir::sdy::ManualAxesAttr manual_axes);
  static ManualComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ValueRange tensors, ::mlir::sdy::TensorShardingPerValueAttr in_shardings, ::mlir::sdy::TensorShardingPerValueAttr out_shardings, ::mlir::sdy::ManualAxesAttr manual_axes);
  static ManualComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ValueRange tensors, ::mlir::sdy::TensorShardingPerValueAttr in_shardings, ::mlir::sdy::TensorShardingPerValueAttr out_shardings, ::mlir::sdy::ManualAxesAttr manual_axes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ValueRange tensors, ::mlir::sdy::TensorShardingPerValueAttr in_shardings, ::mlir::sdy::TensorShardingPerValueAttr out_shardings, ::llvm::ArrayRef<StringAttr> manual_axes);
  static ManualComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ValueRange tensors, ::mlir::sdy::TensorShardingPerValueAttr in_shardings, ::mlir::sdy::TensorShardingPerValueAttr out_shardings, ::llvm::ArrayRef<StringAttr> manual_axes);
  static ManualComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ValueRange tensors, ::mlir::sdy::TensorShardingPerValueAttr in_shardings, ::mlir::sdy::TensorShardingPerValueAttr out_shardings, ::llvm::ArrayRef<StringAttr> manual_axes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ManualComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ManualComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ManualComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ManualComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  mlir::SmallVector<mlir::sdy::TensorShardingAttr> getBlockArgumentEdgeOwnerShardings();
  void setBlockArgumentEdgeOwnerShardings(mlir::ArrayRef<mlir::sdy::TensorShardingAttr> shardings);
  mlir::SmallVector<mlir::sdy::TensorShardingAttr> getOpResultEdgeOwnerShardings();
  void setOpResultEdgeOwnerShardings(mlir::ArrayRef<mlir::sdy::TensorShardingAttr> shardings);
  mlir::sdy::TensorShardingAttr transformTargetSharding(mlir::Value target, mlir::sdy::TensorShardingAttr sharding, mlir::sdy::DataFlowShardingTransformType transformType);
  mlir::ArrayRef<mlir::BlockArgument> getBlockArgumentEdgeOwners();
  mlir::ResultRange getOpResultEdgeOwners();
  mlir::SmallVector<mlir::OpOperand*> getEdgeSources(mlir::Value owner);
  mlir::Value getEdgeOwnerFromTarget(mlir::Value target);
  mlir::Value getEdgeOwnerFromSource(mlir::OpOperand&source);
  bool shouldKeepEdgeOwnerShardingsDivisible();
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
  TensorShardingAttr getInSharding(int64_t operandIndex) {
    return getInShardings().getSharding(operandIndex);
  }
  TensorShardingAttr getOutSharding(int64_t resultIndex) {
    return getOutShardings().getSharding(resultIndex);
  }

  void setInShardings(ArrayRef<TensorShardingAttr> shardings);
  void setOutShardings(ArrayRef<TensorShardingAttr> shardings);

  void setInSharding(int64_t operandIndex, TensorShardingAttr sharding);
  void setOutSharding(int64_t resultIndex, TensorShardingAttr sharding);
};

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ManualComputationOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::MeshOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MeshOpGenericAdaptorBase {
public:
  struct Properties {
    using meshTy = ::mlir::sdy::MeshAttr;
    meshTy mesh;

    auto getMesh() const {
      auto &propStorage = this->mesh;
      return ::llvm::cast<::mlir::sdy::MeshAttr>(propStorage);
    }
    void setMesh(const ::mlir::sdy::MeshAttr &propValue) {
      this->mesh = propValue;
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
        rhs.mesh == this->mesh &&
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
  MeshOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.mesh", odsAttrs.getContext());
  }

  MeshOpGenericAdaptorBase(MeshOp op);

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
  ::mlir::sdy::MeshAttr getMeshAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::MeshAttr>(getProperties().mesh);
    return attr;
  }

  ::mlir::sdy::MeshAttr getMesh();
};

} // namespace detail
template <typename RangeT>
class MeshOpGenericAdaptor : public detail::MeshOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MeshOpGenericAdaptorBase;
public:
  MeshOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MeshOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MeshOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MeshOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MeshOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MeshOpGenericAdaptor(RangeT values, const MeshOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MeshOp, typename = std::enable_if_t<std::is_same_v<LateInst, MeshOp>>>
  MeshOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MeshOpAdaptor : public MeshOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MeshOpGenericAdaptor::MeshOpGenericAdaptor;
  MeshOpAdaptor(MeshOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MeshOp : public ::mlir::Op<MeshOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MeshOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MeshOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("mesh"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMeshAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMeshAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.mesh");
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
  ::mlir::sdy::MeshAttr getMeshAttr() {
    return ::llvm::cast<::mlir::sdy::MeshAttr>(getProperties().mesh);
  }

  ::mlir::sdy::MeshAttr getMesh();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setMeshAttr(::mlir::sdy::MeshAttr attr) {
    getProperties().mesh = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::sdy::MeshAttr mesh);
  static MeshOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::sdy::MeshAttr mesh);
  static MeshOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::sdy::MeshAttr mesh);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::sdy::MeshAttr mesh);
  static MeshOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::sdy::MeshAttr mesh);
  static MeshOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::sdy::MeshAttr mesh);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::sdy::MeshAttr mesh);
  static MeshOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::sdy::MeshAttr mesh);
  static MeshOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::sdy::MeshAttr mesh);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::sdy::MeshAttr mesh);
  static MeshOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::sdy::MeshAttr mesh);
  static MeshOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::sdy::MeshAttr mesh);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MeshOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MeshOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MeshOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MeshOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::MeshOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::NamedComputationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NamedComputationOpGenericAdaptorBase {
public:
  struct Properties {
    using in_shardingsTy = ::mlir::sdy::TensorShardingPerValueAttr;
    in_shardingsTy in_shardings;

    auto getInShardings() const {
      auto &propStorage = this->in_shardings;
      return ::llvm::dyn_cast_or_null<::mlir::sdy::TensorShardingPerValueAttr>(propStorage);
    }
    void setInShardings(const ::mlir::sdy::TensorShardingPerValueAttr &propValue) {
      this->in_shardings = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using out_shardingsTy = ::mlir::sdy::TensorShardingPerValueAttr;
    out_shardingsTy out_shardings;

    auto getOutShardings() const {
      auto &propStorage = this->out_shardings;
      return ::llvm::dyn_cast_or_null<::mlir::sdy::TensorShardingPerValueAttr>(propStorage);
    }
    void setOutShardings(const ::mlir::sdy::TensorShardingPerValueAttr &propValue) {
      this->out_shardings = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.in_shardings == this->in_shardings &&
        rhs.name == this->name &&
        rhs.out_shardings == this->out_shardings &&
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
  NamedComputationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.named_computation", odsAttrs.getContext());
  }

  NamedComputationOpGenericAdaptorBase(NamedComputationOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
  ::mlir::sdy::TensorShardingPerValueAttr getInShardingsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::sdy::TensorShardingPerValueAttr>(getProperties().in_shardings);
    return attr;
  }

  ::std::optional<::mlir::sdy::TensorShardingPerValueAttr> getInShardings();
  ::mlir::sdy::TensorShardingPerValueAttr getOutShardingsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::sdy::TensorShardingPerValueAttr>(getProperties().out_shardings);
    return attr;
  }

  ::std::optional<::mlir::sdy::TensorShardingPerValueAttr> getOutShardings();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class NamedComputationOpGenericAdaptor : public detail::NamedComputationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NamedComputationOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  NamedComputationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NamedComputationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : NamedComputationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NamedComputationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NamedComputationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NamedComputationOpGenericAdaptor(RangeT values, const NamedComputationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NamedComputationOp, typename = std::enable_if_t<std::is_same_v<LateInst, NamedComputationOp>>>
  NamedComputationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class NamedComputationOpAdaptor : public NamedComputationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NamedComputationOpGenericAdaptor::NamedComputationOpGenericAdaptor;
  NamedComputationOpAdaptor(NamedComputationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NamedComputationOp : public ::mlir::Op<NamedComputationOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<ReturnOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::RecursivelySpeculatableImplTrait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::InferTypeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::sdy::ShardableDataFlowOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NamedComputationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NamedComputationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<NamedComputationOp>::refineReturnTypes;
  using ::mlir::sdy::ShardableDataFlowOpInterface::Trait<NamedComputationOp>::transformTargetSharding;
  using ::mlir::sdy::ShardableDataFlowOpInterface::Trait<NamedComputationOp>::getNonEdgeOwnerTargets;
  using ::mlir::sdy::ShardableDataFlowOpInterface::Trait<NamedComputationOp>::shouldKeepEdgeOwnerShardingsDivisible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("in_shardings"), ::llvm::StringRef("name"), ::llvm::StringRef("out_shardings")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInShardingsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInShardingsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOutShardingsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getOutShardingsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.named_computation");
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  ::mlir::sdy::TensorShardingPerValueAttr getInShardingsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::sdy::TensorShardingPerValueAttr>(getProperties().in_shardings);
  }

  ::std::optional<::mlir::sdy::TensorShardingPerValueAttr> getInShardings();
  ::mlir::sdy::TensorShardingPerValueAttr getOutShardingsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::sdy::TensorShardingPerValueAttr>(getProperties().out_shardings);
  }

  ::std::optional<::mlir::sdy::TensorShardingPerValueAttr> getOutShardings();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setInShardingsAttr(::mlir::sdy::TensorShardingPerValueAttr attr) {
    getProperties().in_shardings = attr;
  }

  void setOutShardingsAttr(::mlir::sdy::TensorShardingPerValueAttr attr) {
    getProperties().out_shardings = attr;
  }

  ::mlir::Attribute removeInShardingsAttr() {
      auto attr = getProperties().in_shardings;
      getProperties().in_shardings = {};
      return attr;
  }

  ::mlir::Attribute removeOutShardingsAttr() {
      auto attr = getProperties().out_shardings;
      getProperties().out_shardings = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::mlir::StringAttr name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static NamedComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::mlir::StringAttr name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static NamedComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::mlir::StringAttr name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static NamedComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static NamedComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::llvm::StringRef name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static NamedComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::llvm::StringRef name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static NamedComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::llvm::StringRef name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static NamedComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static NamedComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef name, ::mlir::ValueRange operands, /*optional*/::mlir::sdy::TensorShardingPerValueAttr in_shardings, /*optional*/::mlir::sdy::TensorShardingPerValueAttr out_shardings);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NamedComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NamedComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NamedComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NamedComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NamedComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NamedComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NamedComputationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NamedComputationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  mlir::SmallVector<mlir::sdy::TensorShardingAttr> getBlockArgumentEdgeOwnerShardings();
  void setBlockArgumentEdgeOwnerShardings(mlir::ArrayRef<mlir::sdy::TensorShardingAttr> shardings);
  mlir::SmallVector<mlir::sdy::TensorShardingAttr> getOpResultEdgeOwnerShardings();
  void setOpResultEdgeOwnerShardings(mlir::ArrayRef<mlir::sdy::TensorShardingAttr> shardings);
  mlir::ArrayRef<mlir::BlockArgument> getBlockArgumentEdgeOwners();
  mlir::ResultRange getOpResultEdgeOwners();
  mlir::SmallVector<mlir::OpOperand*> getEdgeSources(mlir::Value owner);
  mlir::Value getEdgeOwnerFromTarget(mlir::Value target);
  mlir::Value getEdgeOwnerFromSource(mlir::OpOperand&source);
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::NamedComputationOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::PropagationBarrierOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PropagationBarrierOpGenericAdaptorBase {
public:
  struct Properties {
    using allowed_directionTy = ::mlir::sdy::PropagationDirectionAttr;
    allowed_directionTy allowed_direction;

    auto getAllowedDirection() const {
      auto &propStorage = this->allowed_direction;
      return ::llvm::cast<::mlir::sdy::PropagationDirectionAttr>(propStorage);
    }
    void setAllowedDirection(const ::mlir::sdy::PropagationDirectionAttr &propValue) {
      this->allowed_direction = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.allowed_direction == this->allowed_direction &&
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
  PropagationBarrierOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.propagation_barrier", odsAttrs.getContext());
  }

  PropagationBarrierOpGenericAdaptorBase(PropagationBarrierOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sdy::PropagationDirectionAttr getAllowedDirectionAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::PropagationDirectionAttr>(getProperties().allowed_direction);
    return attr;
  }

  ::mlir::sdy::PropagationDirection getAllowedDirection();
};

} // namespace detail
template <typename RangeT>
class PropagationBarrierOpGenericAdaptor : public detail::PropagationBarrierOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PropagationBarrierOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  PropagationBarrierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PropagationBarrierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PropagationBarrierOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PropagationBarrierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PropagationBarrierOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PropagationBarrierOpGenericAdaptor(RangeT values, const PropagationBarrierOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PropagationBarrierOp, typename = std::enable_if_t<std::is_same_v<LateInst, PropagationBarrierOp>>>
  PropagationBarrierOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PropagationBarrierOpAdaptor : public PropagationBarrierOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PropagationBarrierOpGenericAdaptor::PropagationBarrierOpGenericAdaptor;
  PropagationBarrierOpAdaptor(PropagationBarrierOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PropagationBarrierOp : public ::mlir::Op<PropagationBarrierOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PropagationBarrierOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PropagationBarrierOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<PropagationBarrierOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("allowed_direction")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAllowedDirectionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAllowedDirectionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.propagation_barrier");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
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
  ::mlir::sdy::PropagationDirectionAttr getAllowedDirectionAttr() {
    return ::llvm::cast<::mlir::sdy::PropagationDirectionAttr>(getProperties().allowed_direction);
  }

  ::mlir::sdy::PropagationDirection getAllowedDirection();
  void setAllowedDirectionAttr(::mlir::sdy::PropagationDirectionAttr attr) {
    getProperties().allowed_direction = attr;
  }

  void setAllowedDirection(::mlir::sdy::PropagationDirection attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::PropagationDirectionAttr allowed_direction);
  static PropagationBarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::PropagationDirectionAttr allowed_direction);
  static PropagationBarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::PropagationDirectionAttr allowed_direction);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::sdy::PropagationDirectionAttr allowed_direction);
  static PropagationBarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::sdy::PropagationDirectionAttr allowed_direction);
  static PropagationBarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::sdy::PropagationDirectionAttr allowed_direction);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::PropagationDirectionAttr allowed_direction);
  static PropagationBarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::PropagationDirectionAttr allowed_direction);
  static PropagationBarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::PropagationDirectionAttr allowed_direction);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::PropagationDirection allowed_direction);
  static PropagationBarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::PropagationDirection allowed_direction);
  static PropagationBarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::PropagationDirection allowed_direction);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::sdy::PropagationDirection allowed_direction);
  static PropagationBarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::sdy::PropagationDirection allowed_direction);
  static PropagationBarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::sdy::PropagationDirection allowed_direction);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::PropagationDirection allowed_direction);
  static PropagationBarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::PropagationDirection allowed_direction);
  static PropagationBarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::PropagationDirection allowed_direction);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PropagationBarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PropagationBarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PropagationBarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PropagationBarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PropagationBarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PropagationBarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PropagationBarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PropagationBarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::PropagationBarrierOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::ReduceScatterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReduceScatterOpGenericAdaptorBase {
public:
  struct Properties {
    using out_shardingTy = ::mlir::sdy::TensorShardingAttr;
    out_shardingTy out_sharding;

    auto getOutSharding() const {
      auto &propStorage = this->out_sharding;
      return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setOutSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->out_sharding = propValue;
    }
    using reduce_scatter_axesTy = ::mlir::sdy::ListOfAxisRefListsAttr;
    reduce_scatter_axesTy reduce_scatter_axes;

    auto getReduceScatterAxes() const {
      auto &propStorage = this->reduce_scatter_axes;
      return ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(propStorage);
    }
    void setReduceScatterAxes(const ::mlir::sdy::ListOfAxisRefListsAttr &propValue) {
      this->reduce_scatter_axes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.out_sharding == this->out_sharding &&
        rhs.reduce_scatter_axes == this->reduce_scatter_axes &&
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
      odsOpName.emplace("sdy.reduce_scatter", odsAttrs.getContext());
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

  ::mlir::sdy::ListOfAxisRefListsAttr getReduceScatterAxesAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(getProperties().reduce_scatter_axes);
    return attr;
  }

  ::llvm::ArrayRef<AxisRefListAttr> getReduceScatterAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
    return attr;
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
};

} // namespace detail
template <typename RangeT>
class ReduceScatterOpGenericAdaptor : public detail::ReduceScatterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReduceScatterOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
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

  ValueT getTensor() {
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
class ReduceScatterOp : public ::mlir::Op<ReduceScatterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::sdy::CollectiveOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReduceScatterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReduceScatterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::sdy::CollectiveOpInterface::Trait<ReduceScatterOp>::allowDifferentMeshes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("out_sharding"), ::llvm::StringRef("reduce_scatter_axes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOutShardingAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOutShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getReduceScatterAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getReduceScatterAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.reduce_scatter");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::ListOfAxisRefListsAttr getReduceScatterAxesAttr() {
    return ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(getProperties().reduce_scatter_axes);
  }

  ::llvm::ArrayRef<AxisRefListAttr> getReduceScatterAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
  void setReduceScatterAxesAttr(::mlir::sdy::ListOfAxisRefListsAttr attr) {
    getProperties().reduce_scatter_axes = attr;
  }

  void setReduceScatterAxes(::llvm::ArrayRef<AxisRefListAttr> attrValue);
  void setOutShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().out_sharding = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> reduce_scatter_axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  ::mlir::Type getType();
  bool allowMissingInputSharding();
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ReduceScatterOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::ReplicatedToUnreducedOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReplicatedToUnreducedOpGenericAdaptorBase {
public:
  struct Properties {
    using axesTy = ::mlir::sdy::AxisRefListAttr;
    axesTy axes;

    auto getAxes() const {
      auto &propStorage = this->axes;
      return ::llvm::cast<::mlir::sdy::AxisRefListAttr>(propStorage);
    }
    void setAxes(const ::mlir::sdy::AxisRefListAttr &propValue) {
      this->axes = propValue;
    }
    using out_shardingTy = ::mlir::sdy::TensorShardingAttr;
    out_shardingTy out_sharding;

    auto getOutSharding() const {
      auto &propStorage = this->out_sharding;
      return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setOutSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->out_sharding = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.axes == this->axes &&
        rhs.out_sharding == this->out_sharding &&
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
  ReplicatedToUnreducedOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.replicated_to_unreduced", odsAttrs.getContext());
  }

  ReplicatedToUnreducedOpGenericAdaptorBase(ReplicatedToUnreducedOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sdy::AxisRefListAttr getAxesAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::AxisRefListAttr>(getProperties().axes);
    return attr;
  }

  ::llvm::ArrayRef<AxisRefAttr> getAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
    return attr;
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
};

} // namespace detail
template <typename RangeT>
class ReplicatedToUnreducedOpGenericAdaptor : public detail::ReplicatedToUnreducedOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReplicatedToUnreducedOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  ReplicatedToUnreducedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReplicatedToUnreducedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReplicatedToUnreducedOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReplicatedToUnreducedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReplicatedToUnreducedOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReplicatedToUnreducedOpGenericAdaptor(RangeT values, const ReplicatedToUnreducedOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReplicatedToUnreducedOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReplicatedToUnreducedOp>>>
  ReplicatedToUnreducedOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ReplicatedToUnreducedOpAdaptor : public ReplicatedToUnreducedOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReplicatedToUnreducedOpGenericAdaptor::ReplicatedToUnreducedOpGenericAdaptor;
  ReplicatedToUnreducedOpAdaptor(ReplicatedToUnreducedOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReplicatedToUnreducedOp : public ::mlir::Op<ReplicatedToUnreducedOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait, ::mlir::sdy::CollectiveOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReplicatedToUnreducedOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReplicatedToUnreducedOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("axes"), ::llvm::StringRef("out_sharding")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAxesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOutShardingAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getOutShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.replicated_to_unreduced");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::AxisRefListAttr getAxesAttr() {
    return ::llvm::cast<::mlir::sdy::AxisRefListAttr>(getProperties().axes);
  }

  ::llvm::ArrayRef<AxisRefAttr> getAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
  void setAxesAttr(::mlir::sdy::AxisRefListAttr attr) {
    getProperties().axes = attr;
  }

  void setAxes(::llvm::ArrayRef<AxisRefAttr> attrValue);
  void setOutShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().out_sharding = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::AxisRefListAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ReplicatedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplicatedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplicatedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplicatedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplicatedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplicatedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplicatedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplicatedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplicatedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ReplicatedToUnreducedOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::ReshardOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReshardOpGenericAdaptorBase {
public:
  struct Properties {
    using shardingTy = ::mlir::sdy::TensorShardingAttr;
    shardingTy sharding;

    auto getSharding() const {
      auto &propStorage = this->sharding;
      return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->sharding = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sharding == this->sharding &&
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
  ReshardOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.reshard", odsAttrs.getContext());
  }

  ReshardOpGenericAdaptorBase(ReshardOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sdy::TensorShardingAttr getShardingAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().sharding);
    return attr;
  }

  ::mlir::sdy::TensorShardingAttr getSharding();
};

} // namespace detail
template <typename RangeT>
class ReshardOpGenericAdaptor : public detail::ReshardOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReshardOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ReshardOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReshardOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReshardOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReshardOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReshardOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReshardOpGenericAdaptor(RangeT values, const ReshardOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReshardOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReshardOp>>>
  ReshardOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ReshardOpAdaptor : public ReshardOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReshardOpGenericAdaptor::ReshardOpGenericAdaptor;
  ReshardOpAdaptor(ReshardOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReshardOp : public ::mlir::Op<ReshardOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReshardOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReshardOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sharding")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getShardingAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.reshard");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::TensorShardingAttr getShardingAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().sharding);
  }

  ::mlir::sdy::TensorShardingAttr getSharding();
  void setShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().sharding = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ReshardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ReshardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ReshardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ReshardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ReshardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ReshardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReshardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReshardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReshardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReshardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReshardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReshardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReshardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReshardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ReshardOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::ReturnOp declarations
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
      odsOpName.emplace("sdy.return", odsAttrs.getContext());
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
  static constexpr int odsIndex_results = 0;
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

  RangeT getResults() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
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
class ReturnOp : public ::mlir::Op<ReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_results = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<ReturnOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.return");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange results);
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange results);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange results);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ReturnOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::ShardedToUnreducedOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShardedToUnreducedOpGenericAdaptorBase {
public:
  struct Properties {
    using axesTy = ::mlir::sdy::ListOfAxisRefListsAttr;
    axesTy axes;

    auto getAxes() const {
      auto &propStorage = this->axes;
      return ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(propStorage);
    }
    void setAxes(const ::mlir::sdy::ListOfAxisRefListsAttr &propValue) {
      this->axes = propValue;
    }
    using out_shardingTy = ::mlir::sdy::TensorShardingAttr;
    out_shardingTy out_sharding;

    auto getOutSharding() const {
      auto &propStorage = this->out_sharding;
      return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setOutSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->out_sharding = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.axes == this->axes &&
        rhs.out_sharding == this->out_sharding &&
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
  ShardedToUnreducedOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.sharded_to_unreduced", odsAttrs.getContext());
  }

  ShardedToUnreducedOpGenericAdaptorBase(ShardedToUnreducedOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sdy::ListOfAxisRefListsAttr getAxesAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(getProperties().axes);
    return attr;
  }

  ::llvm::ArrayRef<AxisRefListAttr> getAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
    return attr;
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
};

} // namespace detail
template <typename RangeT>
class ShardedToUnreducedOpGenericAdaptor : public detail::ShardedToUnreducedOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShardedToUnreducedOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  ShardedToUnreducedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShardedToUnreducedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ShardedToUnreducedOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShardedToUnreducedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ShardedToUnreducedOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShardedToUnreducedOpGenericAdaptor(RangeT values, const ShardedToUnreducedOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShardedToUnreducedOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShardedToUnreducedOp>>>
  ShardedToUnreducedOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ShardedToUnreducedOpAdaptor : public ShardedToUnreducedOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShardedToUnreducedOpGenericAdaptor::ShardedToUnreducedOpGenericAdaptor;
  ShardedToUnreducedOpAdaptor(ShardedToUnreducedOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShardedToUnreducedOp : public ::mlir::Op<ShardedToUnreducedOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait, ::mlir::sdy::CollectiveOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShardedToUnreducedOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShardedToUnreducedOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("axes"), ::llvm::StringRef("out_sharding")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAxesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOutShardingAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getOutShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.sharded_to_unreduced");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::ListOfAxisRefListsAttr getAxesAttr() {
    return ::llvm::cast<::mlir::sdy::ListOfAxisRefListsAttr>(getProperties().axes);
  }

  ::llvm::ArrayRef<AxisRefListAttr> getAxes();
  ::mlir::sdy::TensorShardingAttr getOutShardingAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().out_sharding);
  }

  ::mlir::sdy::TensorShardingAttr getOutSharding();
  void setAxesAttr(::mlir::sdy::ListOfAxisRefListsAttr attr) {
    getProperties().axes = attr;
  }

  void setAxes(::llvm::ArrayRef<AxisRefListAttr> attrValue);
  void setOutShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().out_sharding = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sdy::ListOfAxisRefListsAttr axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static ShardedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::llvm::ArrayRef<AxisRefListAttr> axes, ::mlir::sdy::TensorShardingAttr out_sharding);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardedToUnreducedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardedToUnreducedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ShardedToUnreducedOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::ShardingConstraintOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShardingConstraintOpGenericAdaptorBase {
public:
  struct Properties {
    using shardingTy = ::mlir::sdy::TensorShardingAttr;
    shardingTy sharding;

    auto getSharding() const {
      auto &propStorage = this->sharding;
      return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(propStorage);
    }
    void setSharding(const ::mlir::sdy::TensorShardingAttr &propValue) {
      this->sharding = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sharding == this->sharding &&
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
  ShardingConstraintOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.sharding_constraint", odsAttrs.getContext());
  }

  ShardingConstraintOpGenericAdaptorBase(ShardingConstraintOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sdy::TensorShardingAttr getShardingAttr() {
    auto attr = ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().sharding);
    return attr;
  }

  ::mlir::sdy::TensorShardingAttr getSharding();
};

} // namespace detail
template <typename RangeT>
class ShardingConstraintOpGenericAdaptor : public detail::ShardingConstraintOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShardingConstraintOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ShardingConstraintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShardingConstraintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ShardingConstraintOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShardingConstraintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ShardingConstraintOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShardingConstraintOpGenericAdaptor(RangeT values, const ShardingConstraintOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShardingConstraintOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShardingConstraintOp>>>
  ShardingConstraintOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ShardingConstraintOpAdaptor : public ShardingConstraintOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShardingConstraintOpGenericAdaptor::ShardingConstraintOpGenericAdaptor;
  ShardingConstraintOpAdaptor(ShardingConstraintOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShardingConstraintOp : public ::mlir::Op<ShardingConstraintOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShardingConstraintOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShardingConstraintOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sharding")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getShardingAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getShardingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.sharding_constraint");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  ::mlir::sdy::TensorShardingAttr getShardingAttr() {
    return ::llvm::cast<::mlir::sdy::TensorShardingAttr>(getProperties().sharding);
  }

  ::mlir::sdy::TensorShardingAttr getSharding();
  void setShardingAttr(::mlir::sdy::TensorShardingAttr attr) {
    getProperties().sharding = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ShardingConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ShardingConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ShardingConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ShardingConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ShardingConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static ShardingConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::sdy::TensorShardingAttr sharding);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ShardingConstraintOp)

namespace mlir::sdy {


//===----------------------------------------------------------------------===//
// ::mlir::sdy::ShardingGroupOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShardingGroupOpGenericAdaptorBase {
public:
  struct Properties {
    using group_idTy = ::mlir::IntegerAttr;
    group_idTy group_id;

    auto getGroupId() const {
      auto &propStorage = this->group_id;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setGroupId(const ::mlir::IntegerAttr &propValue) {
      this->group_id = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.group_id == this->group_id &&
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
  ShardingGroupOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sdy.sharding_group", odsAttrs.getContext());
  }

  ShardingGroupOpGenericAdaptorBase(ShardingGroupOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getGroupIdAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().group_id);
    return attr;
  }

  uint64_t getGroupId();
};

} // namespace detail
template <typename RangeT>
class ShardingGroupOpGenericAdaptor : public detail::ShardingGroupOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShardingGroupOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ShardingGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShardingGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ShardingGroupOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShardingGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ShardingGroupOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShardingGroupOpGenericAdaptor(RangeT values, const ShardingGroupOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShardingGroupOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShardingGroupOp>>>
  ShardingGroupOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ShardingGroupOpAdaptor : public ShardingGroupOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShardingGroupOpGenericAdaptor::ShardingGroupOpGenericAdaptor;
  ShardingGroupOpAdaptor(ShardingGroupOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShardingGroupOp : public ::mlir::Op<ShardingGroupOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShardingGroupOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShardingGroupOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<ShardingGroupOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("group_id")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGroupIdAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGroupIdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sdy.sharding_group");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getGroupIdAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().group_id);
  }

  uint64_t getGroupId();
  void setGroupIdAttr(::mlir::IntegerAttr attr) {
    getProperties().group_id = attr;
  }

  void setGroupId(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::IntegerAttr group_id);
  static ShardingGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::IntegerAttr group_id);
  static ShardingGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::IntegerAttr group_id);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr group_id);
  static ShardingGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr group_id);
  static ShardingGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr group_id);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, uint64_t group_id);
  static ShardingGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, uint64_t group_id);
  static ShardingGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, uint64_t group_id);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t group_id);
  static ShardingGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t group_id);
  static ShardingGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t group_id);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ShardingGroupOp)


#endif // GET_OP_CLASSES

