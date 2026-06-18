/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: VhloToVersionPatterns.td                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_VhloToVersionPatterns1(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((isNoneType(attr)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": None type";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_VhloToVersionPatterns2(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((isEmptyTensor(attr)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": Empty dims";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_VhloToVersionPatterns3(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((isDefaultResultAccuracy(attr)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": Default result accuracy";
    });
  }
  return ::mlir::success();
}
/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:79
*/
struct AllGatherOpDowngradeV2ToV1 : public ::mlir::RewritePattern {
  AllGatherOpDowngradeV2ToV1(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.all_gather_v2", 1, context, {"vhlo.all_gather_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::AllGatherOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute all_gather_dim;
    ::mlir::Attribute use_global_device_ids;
    ::mlir::Attribute replica_groups;
    ::mlir::Attribute channel_id;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::AllGatherOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getAllGatherDim();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_gather_v2' to have attribute 'all_gather_dim' of type '::mlir::Attribute'";
        });
      }
      all_gather_dim = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getReplicaGroups();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_gather_v2' to have attribute 'replica_groups' of type '::mlir::Attribute'";
        });
      }
      replica_groups = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelId();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_gather_v2' to have attribute 'channel_id' of type '::mlir::Attribute'";
        });
      }
      channel_id = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseGlobalDeviceIds();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_gather_v2' to have attribute 'use_global_device_ids' of type '::mlir::Attribute'";
        });
      }
      use_global_device_ids = tblgen_attr;
    }
    if (!((operand.size() == 1))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'operand' failed to satisfy constraint: 'Single operand'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = operand.front(); (void)nativeVar_0;
    ::mlir::vhlo::AllGatherOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::AllGatherOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back(nativeVar_0);
      tblgen_props.all_gather_dim = ::llvm::dyn_cast_if_present<decltype(tblgen_props.all_gather_dim)>(all_gather_dim);
      tblgen_props.replica_groups = ::llvm::dyn_cast_if_present<decltype(tblgen_props.replica_groups)>(replica_groups);
      tblgen_props.channel_id = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_id)>(channel_id);
      tblgen_props.use_global_device_ids = ::llvm::dyn_cast_if_present<decltype(tblgen_props.use_global_device_ids)>(use_global_device_ids);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::AllGatherOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_1 = src.getODSResults(0).front(); (void)nativeVar_1;
    copyDiscardableAttrs(nativeVar_1, (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:74
*/
struct AllGatherOpUpgradeV1ToV2 : public ::mlir::RewritePattern {
  AllGatherOpUpgradeV1ToV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.all_gather_v1", 1, context, {"vhlo.all_gather_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::AllGatherOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute all_gather_dim;
    ::mlir::Attribute use_global_device_ids;
    ::mlir::Attribute replica_groups;
    ::mlir::Attribute channel_id;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::AllGatherOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getAllGatherDim();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_gather_v1' to have attribute 'all_gather_dim' of type '::mlir::Attribute'";
        });
      }
      all_gather_dim = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getReplicaGroups();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_gather_v1' to have attribute 'replica_groups' of type '::mlir::Attribute'";
        });
      }
      replica_groups = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelId();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_gather_v1' to have attribute 'channel_id' of type '::mlir::Attribute'";
        });
      }
      channel_id = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseGlobalDeviceIds();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_gather_v1' to have attribute 'use_global_device_ids' of type '::mlir::Attribute'";
        });
      }
      use_global_device_ids = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = {(*operand.begin())}; (void)nativeVar_0;
    ::mlir::vhlo::AllGatherOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::AllGatherOpV2::Properties tblgen_props; (void)tblgen_props;
      for (auto v: nativeVar_0) {
        tblgen_values.push_back(v);
      }
      tblgen_props.all_gather_dim = ::llvm::dyn_cast_if_present<decltype(tblgen_props.all_gather_dim)>(all_gather_dim);
      tblgen_props.replica_groups = ::llvm::dyn_cast_if_present<decltype(tblgen_props.replica_groups)>(replica_groups);
      tblgen_props.channel_id = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_id)>(channel_id);
      tblgen_props.use_global_device_ids = ::llvm::dyn_cast_if_present<decltype(tblgen_props.use_global_device_ids)>(use_global_device_ids);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::AllGatherOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_1 = dst.getODSResults(0).front(); (void)nativeVar_1;
    copyDiscardableAttrs((*src.getODSResults(0).begin()), nativeVar_1);

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:89
*/
struct AllToAllOpDowngradeV2ToV1 : public ::mlir::RewritePattern {
  AllToAllOpDowngradeV2ToV1(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.all_to_all_v2", 1, context, {"vhlo.all_to_all_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::AllToAllOpV2 src;
    ::mlir::Attribute concat_dimension;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute replica_groups;
    ::mlir::Attribute split_dimension;
    ::mlir::Attribute split_count;
    ::mlir::Attribute channel_id;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::AllToAllOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSplitDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_to_all_v2' to have attribute 'split_dimension' of type '::mlir::Attribute'";
        });
      }
      split_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getConcatDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_to_all_v2' to have attribute 'concat_dimension' of type '::mlir::Attribute'";
        });
      }
      concat_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSplitCount();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_to_all_v2' to have attribute 'split_count' of type '::mlir::Attribute'";
        });
      }
      split_count = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getReplicaGroups();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_to_all_v2' to have attribute 'replica_groups' of type '::mlir::Attribute'";
        });
      }
      replica_groups = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelId();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_to_all_v2' to have attribute 'channel_id' of type '::mlir::Attribute'";
        });
      }
      channel_id = tblgen_attr;
    }
    if (!((operand.size() == 1))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'operand' failed to satisfy constraint: 'Single operand'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = operand.front(); (void)nativeVar_0;
    ::mlir::vhlo::AllToAllOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::AllToAllOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back(nativeVar_0);
      tblgen_props.split_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.split_dimension)>(split_dimension);
      tblgen_props.concat_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.concat_dimension)>(concat_dimension);
      tblgen_props.split_count = ::llvm::dyn_cast_if_present<decltype(tblgen_props.split_count)>(split_count);
      tblgen_props.replica_groups = ::llvm::dyn_cast_if_present<decltype(tblgen_props.replica_groups)>(replica_groups);
      tblgen_props.channel_id = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_id)>(channel_id);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::AllToAllOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_1 = src.getODSResults(0).front(); (void)nativeVar_1;
    copyDiscardableAttrs(nativeVar_1, (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:84
*/
struct AllToAllOpUpgradeV1ToV2 : public ::mlir::RewritePattern {
  AllToAllOpUpgradeV1ToV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.all_to_all_v1", 1, context, {"vhlo.all_to_all_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::AllToAllOpV1 src;
    ::mlir::Attribute concat_dimension;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute replica_groups;
    ::mlir::Attribute split_dimension;
    ::mlir::Attribute split_count;
    ::mlir::Attribute channel_id;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::AllToAllOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSplitDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_to_all_v1' to have attribute 'split_dimension' of type '::mlir::Attribute'";
        });
      }
      split_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getConcatDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_to_all_v1' to have attribute 'concat_dimension' of type '::mlir::Attribute'";
        });
      }
      concat_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSplitCount();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_to_all_v1' to have attribute 'split_count' of type '::mlir::Attribute'";
        });
      }
      split_count = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getReplicaGroups();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_to_all_v1' to have attribute 'replica_groups' of type '::mlir::Attribute'";
        });
      }
      replica_groups = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelId();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.all_to_all_v1' to have attribute 'channel_id' of type '::mlir::Attribute'";
        });
      }
      channel_id = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = {(*operand.begin())}; (void)nativeVar_0;
    ::mlir::vhlo::AllToAllOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::AllToAllOpV2::Properties tblgen_props; (void)tblgen_props;
      for (auto v: nativeVar_0) {
        tblgen_values.push_back(v);
      }
      tblgen_props.split_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.split_dimension)>(split_dimension);
      tblgen_props.concat_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.concat_dimension)>(concat_dimension);
      tblgen_props.split_count = ::llvm::dyn_cast_if_present<decltype(tblgen_props.split_count)>(split_count);
      tblgen_props.replica_groups = ::llvm::dyn_cast_if_present<decltype(tblgen_props.replica_groups)>(replica_groups);
      tblgen_props.channel_id = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_id)>(channel_id);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::AllToAllOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_1 = dst.getODSResults(0).front(); (void)nativeVar_1;
    copyDiscardableAttrs((*src.getODSResults(0).begin()), nativeVar_1);

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:94
*/
struct DotGeneralOpDowngradeV2ToV1 : public ::mlir::RewritePattern {
  DotGeneralOpDowngradeV2ToV1(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.dot_general_v2", 1, context, {"vhlo.dot_general_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Attribute lhs_contracting_dimensions;
    ::mlir::Attribute lhs_batching_dimensions;
    ::mlir::vhlo::DotGeneralOpV2 src;
    ::mlir::Attribute precision_config;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Attribute rhs_contracting_dimensions;
    ::mlir::Attribute rhs_batching_dimensions;
    ::mlir::Attribute lhs_precision_type;
    ::mlir::Attribute allow_imprecise_accumulation;
    ::mlir::Attribute rhs_precision_type;
    ::mlir::Attribute accumulation_type;
    ::mlir::Attribute lhs_component_count;
    ::mlir::Attribute rhs_component_count;
    ::mlir::Attribute num_primitive_operations;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::DotGeneralOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLhsBatchingDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'lhs_batching_dimensions' of type '::mlir::Attribute'";
        });
      }
      lhs_batching_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getRhsBatchingDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'rhs_batching_dimensions' of type '::mlir::Attribute'";
        });
      }
      rhs_batching_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLhsContractingDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'lhs_contracting_dimensions' of type '::mlir::Attribute'";
        });
      }
      lhs_contracting_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getRhsContractingDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'rhs_contracting_dimensions' of type '::mlir::Attribute'";
        });
      }
      rhs_contracting_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getPrecisionConfig();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'precision_config' of type '::mlir::Attribute'";
        });
      }
      precision_config = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLhsPrecisionType();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'lhs_precision_type' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns1(rewriter, castedOp0, tblgen_attr, "op 'vhlo.dot_general_v2' attribute 'lhs_precision_type' failed to satisfy constraint: 'None type'"))) {
        return ::mlir::failure();
      }
      lhs_precision_type = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getRhsPrecisionType();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'rhs_precision_type' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns1(rewriter, castedOp0, tblgen_attr, "op 'vhlo.dot_general_v2' attribute 'rhs_precision_type' failed to satisfy constraint: 'None type'"))) {
        return ::mlir::failure();
      }
      rhs_precision_type = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getAccumulationType();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'accumulation_type' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns1(rewriter, castedOp0, tblgen_attr, "op 'vhlo.dot_general_v2' attribute 'accumulation_type' failed to satisfy constraint: 'None type'"))) {
        return ::mlir::failure();
      }
      accumulation_type = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLhsComponentCount();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'lhs_component_count' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns1(rewriter, castedOp0, tblgen_attr, "op 'vhlo.dot_general_v2' attribute 'lhs_component_count' failed to satisfy constraint: 'None type'"))) {
        return ::mlir::failure();
      }
      lhs_component_count = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getRhsComponentCount();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'rhs_component_count' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns1(rewriter, castedOp0, tblgen_attr, "op 'vhlo.dot_general_v2' attribute 'rhs_component_count' failed to satisfy constraint: 'None type'"))) {
        return ::mlir::failure();
      }
      rhs_component_count = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getNumPrimitiveOperations();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'num_primitive_operations' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns1(rewriter, castedOp0, tblgen_attr, "op 'vhlo.dot_general_v2' attribute 'num_primitive_operations' failed to satisfy constraint: 'None type'"))) {
        return ::mlir::failure();
      }
      num_primitive_operations = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getAllowImpreciseAccumulation();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v2' to have attribute 'allow_imprecise_accumulation' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns1(rewriter, castedOp0, tblgen_attr, "op 'vhlo.dot_general_v2' attribute 'allow_imprecise_accumulation' failed to satisfy constraint: 'None type'"))) {
        return ::mlir::failure();
      }
      allow_imprecise_accumulation = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::DotGeneralOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::DotGeneralOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*lhs.begin()));
      tblgen_values.push_back((*rhs.begin()));
      tblgen_props.lhs_batching_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.lhs_batching_dimensions)>(lhs_batching_dimensions);
      tblgen_props.rhs_batching_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.rhs_batching_dimensions)>(rhs_batching_dimensions);
      tblgen_props.lhs_contracting_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.lhs_contracting_dimensions)>(lhs_contracting_dimensions);
      tblgen_props.rhs_contracting_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.rhs_contracting_dimensions)>(rhs_contracting_dimensions);
      tblgen_props.precision_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.precision_config)>(precision_config);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::DotGeneralOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:100
*/
struct DotGeneralOpUpradeV1ToV2 : public ::mlir::RewritePattern {
  DotGeneralOpUpradeV1ToV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.dot_general_v1", 1, context, {"vhlo.dot_general_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Attribute lhs_contracting_dimensions;
    ::mlir::Attribute lhs_batching_dimensions;
    ::mlir::vhlo::DotGeneralOpV1 src;
    ::mlir::Attribute precision_config;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Attribute rhs_contracting_dimensions;
    ::mlir::Attribute rhs_batching_dimensions;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::DotGeneralOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLhsBatchingDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v1' to have attribute 'lhs_batching_dimensions' of type '::mlir::Attribute'";
        });
      }
      lhs_batching_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getRhsBatchingDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v1' to have attribute 'rhs_batching_dimensions' of type '::mlir::Attribute'";
        });
      }
      rhs_batching_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLhsContractingDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v1' to have attribute 'lhs_contracting_dimensions' of type '::mlir::Attribute'";
        });
      }
      lhs_contracting_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getRhsContractingDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v1' to have attribute 'rhs_contracting_dimensions' of type '::mlir::Attribute'";
        });
      }
      rhs_contracting_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getPrecisionConfig();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dot_general_v1' to have attribute 'precision_config' of type '::mlir::Attribute'";
        });
      }
      precision_config = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getNoneType(rewriter); (void)nativeVar_0;
    auto nativeVar_1 = getNoneType(rewriter); (void)nativeVar_1;
    auto nativeVar_2 = getNoneType(rewriter); (void)nativeVar_2;
    auto nativeVar_3 = getNoneType(rewriter); (void)nativeVar_3;
    auto nativeVar_4 = getNoneType(rewriter); (void)nativeVar_4;
    auto nativeVar_5 = getNoneType(rewriter); (void)nativeVar_5;
    auto nativeVar_6 = getNoneType(rewriter); (void)nativeVar_6;
    ::mlir::vhlo::DotGeneralOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::DotGeneralOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*lhs.begin()));
      tblgen_values.push_back((*rhs.begin()));
      tblgen_props.lhs_batching_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.lhs_batching_dimensions)>(lhs_batching_dimensions);
      tblgen_props.rhs_batching_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.rhs_batching_dimensions)>(rhs_batching_dimensions);
      tblgen_props.lhs_contracting_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.lhs_contracting_dimensions)>(lhs_contracting_dimensions);
      tblgen_props.rhs_contracting_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.rhs_contracting_dimensions)>(rhs_contracting_dimensions);
      tblgen_props.precision_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.precision_config)>(precision_config);
      tblgen_props.lhs_precision_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.lhs_precision_type)>(nativeVar_0);
      tblgen_props.rhs_precision_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.rhs_precision_type)>(nativeVar_1);
      tblgen_props.accumulation_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.accumulation_type)>(nativeVar_2);
      tblgen_props.lhs_component_count = ::llvm::dyn_cast_if_present<decltype(tblgen_props.lhs_component_count)>(nativeVar_3);
      tblgen_props.rhs_component_count = ::llvm::dyn_cast_if_present<decltype(tblgen_props.rhs_component_count)>(nativeVar_4);
      tblgen_props.num_primitive_operations = ::llvm::dyn_cast_if_present<decltype(tblgen_props.num_primitive_operations)>(nativeVar_5);
      tblgen_props.allow_imprecise_accumulation = ::llvm::dyn_cast_if_present<decltype(tblgen_props.allow_imprecise_accumulation)>(nativeVar_6);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::DotGeneralOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:49
*/
struct DynamicConvDowngradeV2ToV1 : public ::mlir::RewritePattern {
  DynamicConvDowngradeV2ToV1(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.dynamic_conv_v2", 1, context, {"vhlo.dynamic_conv_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range d_padding(op0->getOperands());
    ::mlir::vhlo::DynamicConvOpV2 src;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::Attribute input_spatial_dimensions;
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Attribute window_reversal;
    ::mlir::Attribute window_strides;
    ::mlir::Attribute lhs_dilation;
    ::mlir::Attribute rhs_dilation;
    ::mlir::Attribute input_batch_dimension;
    ::mlir::Attribute feature_group_count;
    ::mlir::Attribute kernel_input_feature_dimension;
    ::mlir::Attribute input_feature_dimension;
    ::mlir::Attribute output_feature_dimension;
    ::mlir::Attribute kernel_output_feature_dimension;
    ::mlir::Attribute kernel_spatial_dimensions;
    ::mlir::Attribute output_batch_dimension;
    ::mlir::Attribute output_spatial_dimensions;
    ::mlir::Attribute batch_group_count;
    ::mlir::Attribute precision_config;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::DynamicConvOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    d_padding = castedOp0.getODSOperands(2);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getWindowStrides();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'window_strides' of type '::mlir::Attribute'";
        });
      }
      window_strides = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLhsDilation();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'lhs_dilation' of type '::mlir::Attribute'";
        });
      }
      lhs_dilation = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getRhsDilation();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'rhs_dilation' of type '::mlir::Attribute'";
        });
      }
      rhs_dilation = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getWindowReversal();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'window_reversal' of type '::mlir::Attribute'";
        });
      }
      window_reversal = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getInputBatchDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'input_batch_dimension' of type '::mlir::Attribute'";
        });
      }
      input_batch_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getInputFeatureDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'input_feature_dimension' of type '::mlir::Attribute'";
        });
      }
      input_feature_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getInputSpatialDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'input_spatial_dimensions' of type '::mlir::Attribute'";
        });
      }
      input_spatial_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKernelInputFeatureDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'kernel_input_feature_dimension' of type '::mlir::Attribute'";
        });
      }
      kernel_input_feature_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKernelOutputFeatureDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'kernel_output_feature_dimension' of type '::mlir::Attribute'";
        });
      }
      kernel_output_feature_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKernelSpatialDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'kernel_spatial_dimensions' of type '::mlir::Attribute'";
        });
      }
      kernel_spatial_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOutputBatchDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'output_batch_dimension' of type '::mlir::Attribute'";
        });
      }
      output_batch_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOutputFeatureDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'output_feature_dimension' of type '::mlir::Attribute'";
        });
      }
      output_feature_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOutputSpatialDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'output_spatial_dimensions' of type '::mlir::Attribute'";
        });
      }
      output_spatial_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getFeatureGroupCount();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'feature_group_count' of type '::mlir::Attribute'";
        });
      }
      feature_group_count = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBatchGroupCount();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'batch_group_count' of type '::mlir::Attribute'";
        });
      }
      batch_group_count = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getPrecisionConfig();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v2' to have attribute 'precision_config' of type '::mlir::Attribute'";
        });
      }
      precision_config = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultConvPadding(rewriter, (*lhs.begin())); (void)nativeVar_0;
    ::mlir::vhlo::DynamicConvOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::DynamicConvOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*lhs.begin()));
      tblgen_values.push_back((*rhs.begin()));
      tblgen_values.push_back((*d_padding.begin()));
      tblgen_props.window_strides = ::llvm::dyn_cast_if_present<decltype(tblgen_props.window_strides)>(window_strides);
      tblgen_props.padding = ::llvm::dyn_cast_if_present<decltype(tblgen_props.padding)>(nativeVar_0);
      tblgen_props.lhs_dilation = ::llvm::dyn_cast_if_present<decltype(tblgen_props.lhs_dilation)>(lhs_dilation);
      tblgen_props.rhs_dilation = ::llvm::dyn_cast_if_present<decltype(tblgen_props.rhs_dilation)>(rhs_dilation);
      tblgen_props.window_reversal = ::llvm::dyn_cast_if_present<decltype(tblgen_props.window_reversal)>(window_reversal);
      tblgen_props.input_batch_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.input_batch_dimension)>(input_batch_dimension);
      tblgen_props.input_feature_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.input_feature_dimension)>(input_feature_dimension);
      tblgen_props.input_spatial_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.input_spatial_dimensions)>(input_spatial_dimensions);
      tblgen_props.kernel_input_feature_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.kernel_input_feature_dimension)>(kernel_input_feature_dimension);
      tblgen_props.kernel_output_feature_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.kernel_output_feature_dimension)>(kernel_output_feature_dimension);
      tblgen_props.kernel_spatial_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.kernel_spatial_dimensions)>(kernel_spatial_dimensions);
      tblgen_props.output_batch_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.output_batch_dimension)>(output_batch_dimension);
      tblgen_props.output_feature_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.output_feature_dimension)>(output_feature_dimension);
      tblgen_props.output_spatial_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.output_spatial_dimensions)>(output_spatial_dimensions);
      tblgen_props.feature_group_count = ::llvm::dyn_cast_if_present<decltype(tblgen_props.feature_group_count)>(feature_group_count);
      tblgen_props.batch_group_count = ::llvm::dyn_cast_if_present<decltype(tblgen_props.batch_group_count)>(batch_group_count);
      tblgen_props.precision_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.precision_config)>(precision_config);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::DynamicConvOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:44
*/
struct DynamicConvUpgradeV1ToV2 : public ::mlir::RewritePattern {
  DynamicConvUpgradeV1ToV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.dynamic_conv_v1", 1, context, {"vhlo.dynamic_conv_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range d_padding(op0->getOperands());
    ::mlir::vhlo::DynamicConvOpV1 src;
    ::mlir::Attribute precision_config;
    ::mlir::Attribute padding;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::Attribute input_spatial_dimensions;
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Attribute window_strides;
    ::mlir::Attribute lhs_dilation;
    ::mlir::Attribute rhs_dilation;
    ::mlir::Attribute window_reversal;
    ::mlir::Attribute input_batch_dimension;
    ::mlir::Attribute feature_group_count;
    ::mlir::Attribute kernel_input_feature_dimension;
    ::mlir::Attribute input_feature_dimension;
    ::mlir::Attribute output_feature_dimension;
    ::mlir::Attribute kernel_output_feature_dimension;
    ::mlir::Attribute kernel_spatial_dimensions;
    ::mlir::Attribute output_batch_dimension;
    ::mlir::Attribute output_spatial_dimensions;
    ::mlir::Attribute batch_group_count;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::DynamicConvOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    d_padding = castedOp0.getODSOperands(2);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getWindowStrides();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'window_strides' of type '::mlir::Attribute'";
        });
      }
      window_strides = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getPadding();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'padding' of type '::mlir::Attribute'";
        });
      }
      padding = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLhsDilation();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'lhs_dilation' of type '::mlir::Attribute'";
        });
      }
      lhs_dilation = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getRhsDilation();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'rhs_dilation' of type '::mlir::Attribute'";
        });
      }
      rhs_dilation = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getWindowReversal();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'window_reversal' of type '::mlir::Attribute'";
        });
      }
      window_reversal = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getInputBatchDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'input_batch_dimension' of type '::mlir::Attribute'";
        });
      }
      input_batch_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getInputFeatureDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'input_feature_dimension' of type '::mlir::Attribute'";
        });
      }
      input_feature_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getInputSpatialDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'input_spatial_dimensions' of type '::mlir::Attribute'";
        });
      }
      input_spatial_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKernelInputFeatureDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'kernel_input_feature_dimension' of type '::mlir::Attribute'";
        });
      }
      kernel_input_feature_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKernelOutputFeatureDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'kernel_output_feature_dimension' of type '::mlir::Attribute'";
        });
      }
      kernel_output_feature_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKernelSpatialDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'kernel_spatial_dimensions' of type '::mlir::Attribute'";
        });
      }
      kernel_spatial_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOutputBatchDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'output_batch_dimension' of type '::mlir::Attribute'";
        });
      }
      output_batch_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOutputFeatureDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'output_feature_dimension' of type '::mlir::Attribute'";
        });
      }
      output_feature_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOutputSpatialDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'output_spatial_dimensions' of type '::mlir::Attribute'";
        });
      }
      output_spatial_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getFeatureGroupCount();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'feature_group_count' of type '::mlir::Attribute'";
        });
      }
      feature_group_count = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBatchGroupCount();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'batch_group_count' of type '::mlir::Attribute'";
        });
      }
      batch_group_count = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getPrecisionConfig();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_conv_v1' to have attribute 'precision_config' of type '::mlir::Attribute'";
        });
      }
      precision_config = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::DynamicConvOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::DynamicConvOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*lhs.begin()));
      tblgen_values.push_back((*rhs.begin()));
      tblgen_values.push_back((*d_padding.begin()));
      tblgen_props.window_strides = ::llvm::dyn_cast_if_present<decltype(tblgen_props.window_strides)>(window_strides);
      tblgen_props.lhs_dilation = ::llvm::dyn_cast_if_present<decltype(tblgen_props.lhs_dilation)>(lhs_dilation);
      tblgen_props.rhs_dilation = ::llvm::dyn_cast_if_present<decltype(tblgen_props.rhs_dilation)>(rhs_dilation);
      tblgen_props.window_reversal = ::llvm::dyn_cast_if_present<decltype(tblgen_props.window_reversal)>(window_reversal);
      tblgen_props.input_batch_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.input_batch_dimension)>(input_batch_dimension);
      tblgen_props.input_feature_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.input_feature_dimension)>(input_feature_dimension);
      tblgen_props.input_spatial_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.input_spatial_dimensions)>(input_spatial_dimensions);
      tblgen_props.kernel_input_feature_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.kernel_input_feature_dimension)>(kernel_input_feature_dimension);
      tblgen_props.kernel_output_feature_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.kernel_output_feature_dimension)>(kernel_output_feature_dimension);
      tblgen_props.kernel_spatial_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.kernel_spatial_dimensions)>(kernel_spatial_dimensions);
      tblgen_props.output_batch_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.output_batch_dimension)>(output_batch_dimension);
      tblgen_props.output_feature_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.output_feature_dimension)>(output_feature_dimension);
      tblgen_props.output_spatial_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.output_spatial_dimensions)>(output_spatial_dimensions);
      tblgen_props.feature_group_count = ::llvm::dyn_cast_if_present<decltype(tblgen_props.feature_group_count)>(feature_group_count);
      tblgen_props.batch_group_count = ::llvm::dyn_cast_if_present<decltype(tblgen_props.batch_group_count)>(batch_group_count);
      tblgen_props.precision_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.precision_config)>(precision_config);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::DynamicConvOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:69
*/
struct DynamicGatherOpDowngradeV2ToV1 : public ::mlir::RewritePattern {
  DynamicGatherOpDowngradeV2ToV1(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.dynamic_gather_v2", 1, context, {"vhlo.dynamic_gather_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::DynamicGatherOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Operation::operand_range start_indices(op0->getOperands());
    ::mlir::Attribute start_indices_batching_dims;
    ::mlir::Operation::operand_range slice_sizes(op0->getOperands());
    ::mlir::Attribute offset_dims;
    ::mlir::Attribute operand_batching_dims;
    ::mlir::Attribute collapsed_slice_dims;
    ::mlir::Attribute start_index_map;
    ::mlir::Attribute index_vector_dim;
    ::mlir::Attribute indices_are_sorted;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::DynamicGatherOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    start_indices = castedOp0.getODSOperands(1);
    slice_sizes = castedOp0.getODSOperands(2);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOffsetDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v2' to have attribute 'offset_dims' of type '::mlir::Attribute'";
        });
      }
      offset_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getCollapsedSliceDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v2' to have attribute 'collapsed_slice_dims' of type '::mlir::Attribute'";
        });
      }
      collapsed_slice_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOperandBatchingDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v2' to have attribute 'operand_batching_dims' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns2(rewriter, castedOp0, tblgen_attr, "op 'vhlo.dynamic_gather_v2' attribute 'operand_batching_dims' failed to satisfy constraint: 'Empty dims'"))) {
        return ::mlir::failure();
      }
      operand_batching_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getStartIndicesBatchingDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v2' to have attribute 'start_indices_batching_dims' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns2(rewriter, castedOp0, tblgen_attr, "op 'vhlo.dynamic_gather_v2' attribute 'start_indices_batching_dims' failed to satisfy constraint: 'Empty dims'"))) {
        return ::mlir::failure();
      }
      start_indices_batching_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getStartIndexMap();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v2' to have attribute 'start_index_map' of type '::mlir::Attribute'";
        });
      }
      start_index_map = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndexVectorDim();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v2' to have attribute 'index_vector_dim' of type '::mlir::Attribute'";
        });
      }
      index_vector_dim = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndicesAreSorted();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v2' to have attribute 'indices_are_sorted' of type '::mlir::Attribute'";
        });
      }
      indices_are_sorted = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::DynamicGatherOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::DynamicGatherOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*start_indices.begin()));
      tblgen_values.push_back((*slice_sizes.begin()));
      tblgen_props.offset_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.offset_dims)>(offset_dims);
      tblgen_props.collapsed_slice_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.collapsed_slice_dims)>(collapsed_slice_dims);
      tblgen_props.start_index_map = ::llvm::dyn_cast_if_present<decltype(tblgen_props.start_index_map)>(start_index_map);
      tblgen_props.index_vector_dim = ::llvm::dyn_cast_if_present<decltype(tblgen_props.index_vector_dim)>(index_vector_dim);
      tblgen_props.indices_are_sorted = ::llvm::dyn_cast_if_present<decltype(tblgen_props.indices_are_sorted)>(indices_are_sorted);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::DynamicGatherOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:64
*/
struct DynamicGatherOpUpgradeV1ToV2 : public ::mlir::RewritePattern {
  DynamicGatherOpUpgradeV1ToV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.dynamic_gather_v1", 1, context, {"vhlo.dynamic_gather_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::DynamicGatherOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute start_index_map;
    ::mlir::Operation::operand_range start_indices(op0->getOperands());
    ::mlir::Operation::operand_range slice_sizes(op0->getOperands());
    ::mlir::Attribute offset_dims;
    ::mlir::Attribute collapsed_slice_dims;
    ::mlir::Attribute index_vector_dim;
    ::mlir::Attribute indices_are_sorted;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::DynamicGatherOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    start_indices = castedOp0.getODSOperands(1);
    slice_sizes = castedOp0.getODSOperands(2);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOffsetDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v1' to have attribute 'offset_dims' of type '::mlir::Attribute'";
        });
      }
      offset_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getCollapsedSliceDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v1' to have attribute 'collapsed_slice_dims' of type '::mlir::Attribute'";
        });
      }
      collapsed_slice_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getStartIndexMap();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v1' to have attribute 'start_index_map' of type '::mlir::Attribute'";
        });
      }
      start_index_map = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndexVectorDim();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v1' to have attribute 'index_vector_dim' of type '::mlir::Attribute'";
        });
      }
      index_vector_dim = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndicesAreSorted();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.dynamic_gather_v1' to have attribute 'indices_are_sorted' of type '::mlir::Attribute'";
        });
      }
      indices_are_sorted = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getEmptyI64Tensor(rewriter); (void)nativeVar_0;
    auto nativeVar_1 = getEmptyI64Tensor(rewriter); (void)nativeVar_1;
    ::mlir::vhlo::DynamicGatherOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::DynamicGatherOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*start_indices.begin()));
      tblgen_values.push_back((*slice_sizes.begin()));
      tblgen_props.offset_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.offset_dims)>(offset_dims);
      tblgen_props.collapsed_slice_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.collapsed_slice_dims)>(collapsed_slice_dims);
      tblgen_props.operand_batching_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.operand_batching_dims)>(nativeVar_0);
      tblgen_props.start_indices_batching_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.start_indices_batching_dims)>(nativeVar_1);
      tblgen_props.start_index_map = ::llvm::dyn_cast_if_present<decltype(tblgen_props.start_index_map)>(start_index_map);
      tblgen_props.index_vector_dim = ::llvm::dyn_cast_if_present<decltype(tblgen_props.index_vector_dim)>(index_vector_dim);
      tblgen_props.indices_are_sorted = ::llvm::dyn_cast_if_present<decltype(tblgen_props.indices_are_sorted)>(indices_are_sorted);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::DynamicGatherOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:59
*/
struct GatherOpDowngradeV2ToV1 : public ::mlir::RewritePattern {
  GatherOpDowngradeV2ToV1(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.gather_v2", 1, context, {"vhlo.gather_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::GatherOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute start_index_map;
    ::mlir::Operation::operand_range start_indices(op0->getOperands());
    ::mlir::Attribute offset_dims;
    ::mlir::Attribute operand_batching_dims;
    ::mlir::Attribute collapsed_slice_dims;
    ::mlir::Attribute start_indices_batching_dims;
    ::mlir::Attribute index_vector_dim;
    ::mlir::Attribute slice_sizes;
    ::mlir::Attribute indices_are_sorted;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::GatherOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    start_indices = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOffsetDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v2' to have attribute 'offset_dims' of type '::mlir::Attribute'";
        });
      }
      offset_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getCollapsedSliceDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v2' to have attribute 'collapsed_slice_dims' of type '::mlir::Attribute'";
        });
      }
      collapsed_slice_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOperandBatchingDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v2' to have attribute 'operand_batching_dims' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns2(rewriter, castedOp0, tblgen_attr, "op 'vhlo.gather_v2' attribute 'operand_batching_dims' failed to satisfy constraint: 'Empty dims'"))) {
        return ::mlir::failure();
      }
      operand_batching_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getStartIndicesBatchingDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v2' to have attribute 'start_indices_batching_dims' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns2(rewriter, castedOp0, tblgen_attr, "op 'vhlo.gather_v2' attribute 'start_indices_batching_dims' failed to satisfy constraint: 'Empty dims'"))) {
        return ::mlir::failure();
      }
      start_indices_batching_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getStartIndexMap();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v2' to have attribute 'start_index_map' of type '::mlir::Attribute'";
        });
      }
      start_index_map = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndexVectorDim();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v2' to have attribute 'index_vector_dim' of type '::mlir::Attribute'";
        });
      }
      index_vector_dim = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSliceSizes();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v2' to have attribute 'slice_sizes' of type '::mlir::Attribute'";
        });
      }
      slice_sizes = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndicesAreSorted();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v2' to have attribute 'indices_are_sorted' of type '::mlir::Attribute'";
        });
      }
      indices_are_sorted = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::GatherOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::GatherOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*start_indices.begin()));
      tblgen_props.offset_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.offset_dims)>(offset_dims);
      tblgen_props.collapsed_slice_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.collapsed_slice_dims)>(collapsed_slice_dims);
      tblgen_props.start_index_map = ::llvm::dyn_cast_if_present<decltype(tblgen_props.start_index_map)>(start_index_map);
      tblgen_props.index_vector_dim = ::llvm::dyn_cast_if_present<decltype(tblgen_props.index_vector_dim)>(index_vector_dim);
      tblgen_props.slice_sizes = ::llvm::dyn_cast_if_present<decltype(tblgen_props.slice_sizes)>(slice_sizes);
      tblgen_props.indices_are_sorted = ::llvm::dyn_cast_if_present<decltype(tblgen_props.indices_are_sorted)>(indices_are_sorted);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::GatherOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:54
*/
struct GatherOpUpgradeV1ToV2 : public ::mlir::RewritePattern {
  GatherOpUpgradeV1ToV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.gather_v1", 1, context, {"vhlo.gather_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::GatherOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute start_index_map;
    ::mlir::Operation::operand_range start_indices(op0->getOperands());
    ::mlir::Attribute offset_dims;
    ::mlir::Attribute collapsed_slice_dims;
    ::mlir::Attribute index_vector_dim;
    ::mlir::Attribute slice_sizes;
    ::mlir::Attribute indices_are_sorted;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::GatherOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    start_indices = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOffsetDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v1' to have attribute 'offset_dims' of type '::mlir::Attribute'";
        });
      }
      offset_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getCollapsedSliceDims();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v1' to have attribute 'collapsed_slice_dims' of type '::mlir::Attribute'";
        });
      }
      collapsed_slice_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getStartIndexMap();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v1' to have attribute 'start_index_map' of type '::mlir::Attribute'";
        });
      }
      start_index_map = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndexVectorDim();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v1' to have attribute 'index_vector_dim' of type '::mlir::Attribute'";
        });
      }
      index_vector_dim = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSliceSizes();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v1' to have attribute 'slice_sizes' of type '::mlir::Attribute'";
        });
      }
      slice_sizes = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndicesAreSorted();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.gather_v1' to have attribute 'indices_are_sorted' of type '::mlir::Attribute'";
        });
      }
      indices_are_sorted = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getEmptyI64Tensor(rewriter); (void)nativeVar_0;
    auto nativeVar_1 = getEmptyI64Tensor(rewriter); (void)nativeVar_1;
    ::mlir::vhlo::GatherOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::GatherOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*start_indices.begin()));
      tblgen_props.offset_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.offset_dims)>(offset_dims);
      tblgen_props.collapsed_slice_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.collapsed_slice_dims)>(collapsed_slice_dims);
      tblgen_props.operand_batching_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.operand_batching_dims)>(nativeVar_0);
      tblgen_props.start_indices_batching_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.start_indices_batching_dims)>(nativeVar_1);
      tblgen_props.start_index_map = ::llvm::dyn_cast_if_present<decltype(tblgen_props.start_index_map)>(start_index_map);
      tblgen_props.index_vector_dim = ::llvm::dyn_cast_if_present<decltype(tblgen_props.index_vector_dim)>(index_vector_dim);
      tblgen_props.slice_sizes = ::llvm::dyn_cast_if_present<decltype(tblgen_props.slice_sizes)>(slice_sizes);
      tblgen_props.indices_are_sorted = ::llvm::dyn_cast_if_present<decltype(tblgen_props.indices_are_sorted)>(indices_are_sorted);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::GatherOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:116
*/
struct RecvOpDowngradeV2ToV1 : public ::mlir::RewritePattern {
  RecvOpDowngradeV2ToV1(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.recv_v2", 1, context, {"vhlo.recv_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Attribute channel_type;
    ::mlir::vhlo::RecvOpV2 src;
    ::mlir::Operation::operand_range token(op0->getOperands());
    ::mlir::Attribute channel_id;
    ::mlir::Attribute source_target_pairs;
    ::mlir::Attribute is_host_transfer;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::RecvOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    token = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelId();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.recv_v2' to have attribute 'channel_id' of type '::mlir::Attribute'";
        });
      }
      channel_id = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelType();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.recv_v2' to have attribute 'channel_type' of type '::mlir::Attribute'";
        });
      }
      channel_type = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIsHostTransfer();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.recv_v2' to have attribute 'is_host_transfer' of type '::mlir::Attribute'";
        });
      }
      is_host_transfer = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSourceTargetPairs();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.recv_v2' to have attribute 'source_target_pairs' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns2(rewriter, castedOp0, tblgen_attr, "op 'vhlo.recv_v2' attribute 'source_target_pairs' failed to satisfy constraint: 'Empty dims'"))) {
        return ::mlir::failure();
      }
      source_target_pairs = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::RecvOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::RecvOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*token.begin()));
      tblgen_props.channel_id = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_id)>(channel_id);
      tblgen_props.channel_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_type)>(channel_type);
      tblgen_props.is_host_transfer = ::llvm::dyn_cast_if_present<decltype(tblgen_props.is_host_transfer)>(is_host_transfer);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::RecvOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = src.getODSResults(0).front(); (void)nativeVar_0;
    auto nativeVar_1 = dst.getODSResults(0).front(); (void)nativeVar_1;
    copyDiscardableAttrs(nativeVar_0, nativeVar_1);

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:121
*/
struct RecvOpUpgradeV1ToV2 : public ::mlir::RewritePattern {
  RecvOpUpgradeV1ToV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.recv_v1", 1, context, {"vhlo.recv_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Attribute channel_type;
    ::mlir::vhlo::RecvOpV1 src;
    ::mlir::Operation::operand_range token(op0->getOperands());
    ::mlir::Attribute channel_id;
    ::mlir::Attribute is_host_transfer;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::RecvOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    token = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelId();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.recv_v1' to have attribute 'channel_id' of type '::mlir::Attribute'";
        });
      }
      channel_id = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelType();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.recv_v1' to have attribute 'channel_type' of type '::mlir::Attribute'";
        });
      }
      channel_type = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIsHostTransfer();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.recv_v1' to have attribute 'is_host_transfer' of type '::mlir::Attribute'";
        });
      }
      is_host_transfer = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getEmptyI64Tensor(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::RecvOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::RecvOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*token.begin()));
      tblgen_props.channel_id = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_id)>(channel_id);
      tblgen_props.channel_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_type)>(channel_type);
      tblgen_props.is_host_transfer = ::llvm::dyn_cast_if_present<decltype(tblgen_props.is_host_transfer)>(is_host_transfer);
      tblgen_props.source_target_pairs = ::llvm::dyn_cast_if_present<decltype(tblgen_props.source_target_pairs)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::RecvOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_1 = src.getODSResults(0).front(); (void)nativeVar_1;
    auto nativeVar_2 = dst.getODSResults(0).front(); (void)nativeVar_2;
    copyDiscardableAttrs(nativeVar_1, nativeVar_2);

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:106
*/
struct SendOpDowngradeV2ToV1 : public ::mlir::RewritePattern {
  SendOpDowngradeV2ToV1(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.send_v2", 1, context, {"vhlo.send_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Attribute channel_type;
    ::mlir::vhlo::SendOpV2 src;
    ::mlir::Attribute source_target_pairs;
    ::mlir::Attribute is_host_transfer;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Operation::operand_range token(op0->getOperands());
    ::mlir::Attribute channel_id;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::SendOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    token = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelId();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.send_v2' to have attribute 'channel_id' of type '::mlir::Attribute'";
        });
      }
      channel_id = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelType();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.send_v2' to have attribute 'channel_type' of type '::mlir::Attribute'";
        });
      }
      channel_type = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIsHostTransfer();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.send_v2' to have attribute 'is_host_transfer' of type '::mlir::Attribute'";
        });
      }
      is_host_transfer = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSourceTargetPairs();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.send_v2' to have attribute 'source_target_pairs' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns2(rewriter, castedOp0, tblgen_attr, "op 'vhlo.send_v2' attribute 'source_target_pairs' failed to satisfy constraint: 'Empty dims'"))) {
        return ::mlir::failure();
      }
      source_target_pairs = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::SendOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::SendOpV1::Properties tblgen_props; (void)tblgen_props;
      for (auto v: operand) {
        tblgen_values.push_back(v);
      }
      tblgen_values.push_back((*token.begin()));
      tblgen_props.channel_id = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_id)>(channel_id);
      tblgen_props.channel_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_type)>(channel_type);
      tblgen_props.is_host_transfer = ::llvm::dyn_cast_if_present<decltype(tblgen_props.is_host_transfer)>(is_host_transfer);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::SendOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:111
*/
struct SendOpUpgradeV1ToV2 : public ::mlir::RewritePattern {
  SendOpUpgradeV1ToV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.send_v1", 1, context, {"vhlo.send_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Attribute channel_type;
    ::mlir::vhlo::SendOpV1 src;
    ::mlir::Attribute is_host_transfer;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Operation::operand_range token(op0->getOperands());
    ::mlir::Attribute channel_id;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::SendOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    token = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelId();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.send_v1' to have attribute 'channel_id' of type '::mlir::Attribute'";
        });
      }
      channel_id = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getChannelType();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.send_v1' to have attribute 'channel_type' of type '::mlir::Attribute'";
        });
      }
      channel_type = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIsHostTransfer();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.send_v1' to have attribute 'is_host_transfer' of type '::mlir::Attribute'";
        });
      }
      is_host_transfer = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getEmptyI64Tensor(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::SendOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::SendOpV2::Properties tblgen_props; (void)tblgen_props;
      for (auto v: operand) {
        tblgen_values.push_back(v);
      }
      tblgen_values.push_back((*token.begin()));
      tblgen_props.channel_id = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_id)>(channel_id);
      tblgen_props.channel_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_type)>(channel_type);
      tblgen_props.is_host_transfer = ::llvm::dyn_cast_if_present<decltype(tblgen_props.is_host_transfer)>(is_host_transfer);
      tblgen_props.source_target_pairs = ::llvm::dyn_cast_if_present<decltype(tblgen_props.source_target_pairs)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::SendOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert0 : public ::mlir::RewritePattern {
  GeneratedConvert0(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.cbrt_v1", 1, context, {"vhlo.cbrt_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::CbrtOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::CbrtOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::CbrtOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::CbrtOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::CbrtOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert1 : public ::mlir::RewritePattern {
  GeneratedConvert1(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.cbrt_v2", 1, context, {"vhlo.cbrt_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::CbrtOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::CbrtOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.cbrt_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.cbrt_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::CbrtOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::CbrtOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::CbrtOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert2 : public ::mlir::RewritePattern {
  GeneratedConvert2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.cosine_v1", 1, context, {"vhlo.cosine_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::CosineOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::CosineOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::CosineOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::CosineOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::CosineOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert3 : public ::mlir::RewritePattern {
  GeneratedConvert3(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.cosine_v2", 1, context, {"vhlo.cosine_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::CosineOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::CosineOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.cosine_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.cosine_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::CosineOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::CosineOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::CosineOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert4 : public ::mlir::RewritePattern {
  GeneratedConvert4(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.exponential_v1", 1, context, {"vhlo.exponential_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::ExpOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::ExpOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::ExpOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::ExpOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::ExpOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert5 : public ::mlir::RewritePattern {
  GeneratedConvert5(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.exponential_v2", 1, context, {"vhlo.exponential_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::ExpOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::ExpOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.exponential_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.exponential_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::ExpOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::ExpOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::ExpOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert6 : public ::mlir::RewritePattern {
  GeneratedConvert6(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.exponential_minus_one_v1", 1, context, {"vhlo.exponential_minus_one_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::Expm1OpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::Expm1OpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::Expm1OpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::Expm1OpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::Expm1OpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert7 : public ::mlir::RewritePattern {
  GeneratedConvert7(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.exponential_minus_one_v2", 1, context, {"vhlo.exponential_minus_one_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::Expm1OpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::Expm1OpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.exponential_minus_one_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.exponential_minus_one_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::Expm1OpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::Expm1OpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::Expm1OpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert8 : public ::mlir::RewritePattern {
  GeneratedConvert8(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.log_v1", 1, context, {"vhlo.log_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::LogOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::LogOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::LogOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::LogOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::LogOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert9 : public ::mlir::RewritePattern {
  GeneratedConvert9(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.log_v2", 1, context, {"vhlo.log_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::LogOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::LogOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.log_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.log_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::LogOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::LogOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::LogOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert10 : public ::mlir::RewritePattern {
  GeneratedConvert10(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.log_plus_one_v1", 1, context, {"vhlo.log_plus_one_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::Log1pOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::Log1pOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::Log1pOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::Log1pOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::Log1pOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert11 : public ::mlir::RewritePattern {
  GeneratedConvert11(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.log_plus_one_v2", 1, context, {"vhlo.log_plus_one_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::Log1pOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::Log1pOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.log_plus_one_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.log_plus_one_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::Log1pOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::Log1pOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::Log1pOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert12 : public ::mlir::RewritePattern {
  GeneratedConvert12(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.logistic_v1", 1, context, {"vhlo.logistic_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::LogisticOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::LogisticOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::LogisticOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::LogisticOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::LogisticOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert13 : public ::mlir::RewritePattern {
  GeneratedConvert13(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.logistic_v2", 1, context, {"vhlo.logistic_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::LogisticOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::LogisticOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.logistic_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.logistic_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::LogisticOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::LogisticOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::LogisticOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert14 : public ::mlir::RewritePattern {
  GeneratedConvert14(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.rsqrt_v1", 1, context, {"vhlo.rsqrt_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::RsqrtOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::RsqrtOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::RsqrtOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::RsqrtOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::RsqrtOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert15 : public ::mlir::RewritePattern {
  GeneratedConvert15(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.rsqrt_v2", 1, context, {"vhlo.rsqrt_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::RsqrtOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::RsqrtOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.rsqrt_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.rsqrt_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::RsqrtOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::RsqrtOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::RsqrtOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert16 : public ::mlir::RewritePattern {
  GeneratedConvert16(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.sine_v1", 1, context, {"vhlo.sine_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::SineOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::SineOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::SineOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::SineOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::SineOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert17 : public ::mlir::RewritePattern {
  GeneratedConvert17(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.sine_v2", 1, context, {"vhlo.sine_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::SineOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::SineOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.sine_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.sine_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::SineOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::SineOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::SineOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert18 : public ::mlir::RewritePattern {
  GeneratedConvert18(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.sqrt_v1", 1, context, {"vhlo.sqrt_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::SqrtOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::SqrtOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::SqrtOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::SqrtOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::SqrtOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert19 : public ::mlir::RewritePattern {
  GeneratedConvert19(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.sqrt_v2", 1, context, {"vhlo.sqrt_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::SqrtOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::SqrtOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.sqrt_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.sqrt_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::SqrtOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::SqrtOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::SqrtOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert20 : public ::mlir::RewritePattern {
  GeneratedConvert20(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.tan_v1", 1, context, {"vhlo.tan_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::TanOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::TanOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::TanOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::TanOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::TanOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert21 : public ::mlir::RewritePattern {
  GeneratedConvert21(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.tan_v2", 1, context, {"vhlo.tan_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::TanOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::TanOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.tan_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.tan_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::TanOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::TanOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::TanOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:139
*/
struct GeneratedConvert22 : public ::mlir::RewritePattern {
  GeneratedConvert22(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.tanh_v1", 1, context, {"vhlo.tanh_v2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::TanhOpV1 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::TanhOpV1>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultResultAccuracy(rewriter); (void)nativeVar_0;
    ::mlir::vhlo::TanhOpV2 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::TanhOpV2::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::TanhOpV2::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/VhloToVersionPatterns.td:142
*/
struct GeneratedConvert23 : public ::mlir::RewritePattern {
  GeneratedConvert23(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("vhlo.tanh_v2", 1, context, {"vhlo.tanh_v1"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::vhlo::TanhOpV2 src;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute result_accuracy;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::vhlo::TanhOpV2>(op0); (void)castedOp0;
    src = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResultAccuracy();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'vhlo.tanh_v2' to have attribute 'result_accuracy' of type '::mlir::Attribute'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_VhloToVersionPatterns3(rewriter, castedOp0, tblgen_attr, "op 'vhlo.tanh_v2' attribute 'result_accuracy' failed to satisfy constraint: 'Default result accuracy'"))) {
        return ::mlir::failure();
      }
      result_accuracy = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::vhlo::TanhOpV1 dst;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::vhlo::TanhOpV1::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dst = ::mlir::vhlo::TanhOpV1::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dst.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    copyDiscardableAttrs((*src.getODSResults(0).begin()), (*dst.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<AllGatherOpDowngradeV2ToV1>(patterns.getContext());
  patterns.add<AllGatherOpUpgradeV1ToV2>(patterns.getContext());
  patterns.add<AllToAllOpDowngradeV2ToV1>(patterns.getContext());
  patterns.add<AllToAllOpUpgradeV1ToV2>(patterns.getContext());
  patterns.add<DotGeneralOpDowngradeV2ToV1>(patterns.getContext());
  patterns.add<DotGeneralOpUpradeV1ToV2>(patterns.getContext());
  patterns.add<DynamicConvDowngradeV2ToV1>(patterns.getContext());
  patterns.add<DynamicConvUpgradeV1ToV2>(patterns.getContext());
  patterns.add<DynamicGatherOpDowngradeV2ToV1>(patterns.getContext());
  patterns.add<DynamicGatherOpUpgradeV1ToV2>(patterns.getContext());
  patterns.add<GatherOpDowngradeV2ToV1>(patterns.getContext());
  patterns.add<GatherOpUpgradeV1ToV2>(patterns.getContext());
  patterns.add<RecvOpDowngradeV2ToV1>(patterns.getContext());
  patterns.add<RecvOpUpgradeV1ToV2>(patterns.getContext());
  patterns.add<SendOpDowngradeV2ToV1>(patterns.getContext());
  patterns.add<SendOpUpgradeV1ToV2>(patterns.getContext());
  patterns.add<GeneratedConvert0>(patterns.getContext());
  patterns.add<GeneratedConvert1>(patterns.getContext());
  patterns.add<GeneratedConvert2>(patterns.getContext());
  patterns.add<GeneratedConvert3>(patterns.getContext());
  patterns.add<GeneratedConvert4>(patterns.getContext());
  patterns.add<GeneratedConvert5>(patterns.getContext());
  patterns.add<GeneratedConvert6>(patterns.getContext());
  patterns.add<GeneratedConvert7>(patterns.getContext());
  patterns.add<GeneratedConvert8>(patterns.getContext());
  patterns.add<GeneratedConvert9>(patterns.getContext());
  patterns.add<GeneratedConvert10>(patterns.getContext());
  patterns.add<GeneratedConvert11>(patterns.getContext());
  patterns.add<GeneratedConvert12>(patterns.getContext());
  patterns.add<GeneratedConvert13>(patterns.getContext());
  patterns.add<GeneratedConvert14>(patterns.getContext());
  patterns.add<GeneratedConvert15>(patterns.getContext());
  patterns.add<GeneratedConvert16>(patterns.getContext());
  patterns.add<GeneratedConvert17>(patterns.getContext());
  patterns.add<GeneratedConvert18>(patterns.getContext());
  patterns.add<GeneratedConvert19>(patterns.getContext());
  patterns.add<GeneratedConvert20>(patterns.getContext());
  patterns.add<GeneratedConvert21>(patterns.getContext());
  patterns.add<GeneratedConvert22>(patterns.getContext());
  patterns.add<GeneratedConvert23>(patterns.getContext());
}
