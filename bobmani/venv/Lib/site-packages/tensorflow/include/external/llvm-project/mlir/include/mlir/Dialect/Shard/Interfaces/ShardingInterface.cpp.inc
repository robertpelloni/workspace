/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns a list of iterator types that describe the number of loops.
/// The iterator types determine how the operation traverses its input and
/// output tensors.
/// 
/// Example 1: A gemm op has 3 loops, M, N and K. Their loop iterator
/// types are parallel, parallel, reduction. This indicates that M and
/// N are traversed in parallel, while the K dimension is used for
/// reduction.
SmallVector<mlir::utils::IteratorType> mlir::shard::ShardingInterface::getLoopIteratorTypes() {
      return getImpl()->getLoopIteratorTypes(getImpl(), getOperation());
  }

/// Return the kind of all reduction loop iterators.
/// The order is the same as the same as the result from
/// `getLoopIteratorTypes`.
/// 
/// Example 1:
/// iterator types =  (parallel, reduction, parallel, reduction)
///                                    ||                   ||
/// reduction kinds = (                sum,                 max)
/// 
/// Example 2:
/// A softmax op's loop iterator types are parallel and
/// reduction.
/// The reduction iterator will be of kind `generic`, since it is non of
/// the available presets.
SmallVector<ReductionKind> mlir::shard::ShardingInterface::getReductionLoopIteratorKinds() {
      return getImpl()->getReductionLoopIteratorKinds(getImpl(), getOperation());
  }

/// Return the indexing maps attribute within the current operation.
/// Indexing maps determine how indices in the iteration space map to
/// tensor indices. They are specified using `affine_map` in MLIR, which
/// provides an affine transformation of indices.
SmallVector<AffineMap> mlir::shard::ShardingInterface::getIndexingMaps() {
      return getImpl()->getIndexingMaps(getImpl(), getOperation());
  }

/// Given that certain operands or results of the operation may have
/// sharding annotations, this method leverages this information to
/// deduce how the operation should be sharded.
/// The passed sharding may be incomplete, this gives freedom for the
/// op to select the most appropriate shardings for all the operands
/// and results and the op itself.
FailureOr<ShardingOption> mlir::shard::ShardingInterface::getShardingOption(ArrayRef<Sharding> operandShardings, ArrayRef<Sharding> resultShardings) {
      return getImpl()->getShardingOption(getImpl(), getOperation(), operandShardings, resultShardings);
  }

/// Based on a given ShardingOption, get the operand and result
/// operations for the operands and results sharding annotations.
/// This is what shardings the operands and results need to have in order
/// to shard the op according to shardingOption.
FailureOr<std::vector<Sharding>> mlir::shard::ShardingInterface::getShardingAnnotations(const ShardingOption & shardingOption) {
      return getImpl()->getShardingAnnotations(getImpl(), getOperation(), shardingOption);
  }

/// Based on a given ShardingOption, this method adds `shard.shard`
/// operations for the operands and results that previously lacked
/// sharding annotations.
LogicalResult mlir::shard::ShardingInterface::addShardingAnnotations(OpBuilder & b, const ShardingOption & shardingOption) {
      return getImpl()->addShardingAnnotations(getImpl(), getOperation(), b, shardingOption);
  }

/// Convert self to SPMD form.
/// This method is used during the partition pass of a program fully
/// annotated with shardings.
/// 
/// The partition algorithm would read the surrounding sharding
/// annotations from the IR for each argument/result and prepare
/// `operandShardings` and `resultShardings`.
/// Values that are not ranked tensors do not have sharding annotations.
/// In this case their corresponding Sharding is null.
/// 
/// For convenience it will also prepare `partitionedOperands`, although
/// they can be retrieved from the `partitionMap`.
/// 
/// The `partitionMap` contains a mapping from unsharded to
/// sharded/partitioned values that are constructed during the partition
/// pass. The interface implementation must populate `partitionMap`
/// with the mapping for this op's results.
/// 
/// `builder` is set to insert new operations in the appropriate point.
/// The implementation should not return the builder to the original
/// insertion point.
/// It should leave it as is after all insertions are done.
/// 
/// The default implementation does full replication.
/// This assumes that all sharding annotations are for full replication.
LogicalResult mlir::shard::ShardingInterface::partition(ArrayRef<Value> partitionedOperands, ArrayRef<Sharding> operandShardings, ArrayRef<Sharding> resultShardings, IRMapping& partitionMap, SymbolTableCollection & symbolTableCollection, OpBuilder & builder) {
      return getImpl()->partition(getImpl(), getOperation(), partitionedOperands, operandShardings, resultShardings, partitionMap, symbolTableCollection, builder);
  }
