/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: decompose_resource_ops.td                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_decompose_resource_ops1(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((::llvm::isa<::mlir::BoolAttr>(attr)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": bool attribute";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_decompose_resource_ops2(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((attr == rewriter.getBoolAttr(true)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": constant attribute true";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_decompose_resource_ops3(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((attr == rewriter.getBoolAttr(false)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": constant attribute false";
    });
  }
  return ::mlir::success();
}
/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:69
*/
struct DecomposeAssignAddVariableOp : public ::mlir::RewritePattern {
  DecomposeAssignAddVariableOp(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.AssignAddVariableOp", 1, context, {"tf.AddV2", "tf.AssignVariableOp"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range resource(op0->getOperands());
    ::mlir::TF::AssignAddVariableOp src_op;
    ::mlir::Operation::operand_range value(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AssignAddVariableOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    resource = castedOp0.getODSOperands(0);
    value = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*resource.begin()), llvm::cast<TensorType>((*value.begin()).getType()).getElementType()),  (*resource.begin())); (void)nativeVar_0;
    ::mlir::TF::AddV2Op tblgen_AddV2Op_1;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      ::mlir::Value tblgen_value_1 = (*value.begin());
      tblgen_AddV2Op_1 = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_2 = rewriter.getBoolAttr(false); (void)nativeVar_2;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*resource.begin()));
      tblgen_values.push_back((*tblgen_AddV2Op_1.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_3 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:82
*/
struct DecomposeAssignSubVariableOp : public ::mlir::RewritePattern {
  DecomposeAssignSubVariableOp(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.AssignSubVariableOp", 1, context, {"tf.AssignVariableOp", "tf.Sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range resource(op0->getOperands());
    ::mlir::TF::AssignSubVariableOp src_op;
    ::mlir::Operation::operand_range value(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AssignSubVariableOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    resource = castedOp0.getODSOperands(0);
    value = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*resource.begin()), llvm::cast<TensorType>((*value.begin()).getType()).getElementType()),  (*resource.begin())); (void)nativeVar_0;
    ::mlir::TF::SubOp tblgen_SubOp_1;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      ::mlir::Value tblgen_value_1 = (*value.begin());
      tblgen_SubOp_1 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_2 = rewriter.getBoolAttr(false); (void)nativeVar_2;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*resource.begin()));
      tblgen_values.push_back((*tblgen_SubOp_1.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_3 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:625
*/
struct DecomposeCollectiveReduceV2 : public ::mlir::RewritePattern {
  DecomposeCollectiveReduceV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.CollectiveReduceV2", 1, context, {"tf.CollectiveReduceV2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::CollectiveReduceV2Op src_op;
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::mlir::Operation::operand_range group_key(op0->getOperands());
    ::mlir::Operation::operand_range group_size(op0->getOperands());
    ::mlir::Operation::operand_range instance_key(op0->getOperands());
    ::mlir::StringAttr final_op;
    ::mlir::Operation::operand_range ordering_token(op0->getOperands());
    ::mlir::StringAttr merge_op;
    ::mlir::StringAttr communication_hint;
    ::mlir::FloatAttr timeout_seconds;
    ::mlir::BoolAttr is_stateless;
    ::mlir::IntegerAttr max_subdivs_per_device;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::CollectiveReduceV2Op>(op0); (void)castedOp0;
    src_op = castedOp0;
    input = castedOp0.getODSOperands(0);
    group_size = castedOp0.getODSOperands(1);
    group_key = castedOp0.getODSOperands(2);
    instance_key = castedOp0.getODSOperands(3);
    ordering_token = castedOp0.getODSOperands(4);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getMergeOp();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.CollectiveReduceV2' to have attribute 'merge_op' of type '::mlir::StringAttr'";
        });
      }
      merge_op = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getFinalOp();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.CollectiveReduceV2' to have attribute 'final_op' of type '::mlir::StringAttr'";
        });
      }
      final_op = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getCommunicationHint();
      if (!tblgen_attr) tblgen_attr = rewriter.getStringAttr("auto");
      communication_hint = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getTimeoutSeconds();
      if (!tblgen_attr) tblgen_attr = rewriter.getFloatAttr(rewriter.getF32Type(), 0.0f);
      timeout_seconds = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIsStateless();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      is_stateless = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getMaxSubdivsPerDevice();
      if (!tblgen_attr) tblgen_attr = rewriter.getIntegerAttr(rewriter.getIntegerType(64), -1);
      max_subdivs_per_device = tblgen_attr;
    }
    if (!(((ordering_token.size() == 1)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'ordering_token' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = llvm::SmallVector<mlir::Value>{}; (void)nativeVar_0;
    ::mlir::TF::CollectiveReduceV2Op tblgen_CollectiveReduceV2Op_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::CollectiveReduceV2Op::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_values.push_back((*group_size.begin()));
      tblgen_values.push_back((*group_key.begin()));
      tblgen_values.push_back((*instance_key.begin()));
      for (auto v: nativeVar_0) {
        tblgen_values.push_back(v);
      }
      tblgen_props.merge_op = ::llvm::dyn_cast_if_present<decltype(tblgen_props.merge_op)>(merge_op);
      tblgen_props.final_op = ::llvm::dyn_cast_if_present<decltype(tblgen_props.final_op)>(final_op);
      tblgen_props.communication_hint = ::llvm::dyn_cast_if_present<decltype(tblgen_props.communication_hint)>(communication_hint);
      tblgen_props.timeout_seconds = ::llvm::dyn_cast_if_present<decltype(tblgen_props.timeout_seconds)>(timeout_seconds);
      tblgen_props.is_stateless = ::llvm::dyn_cast_if_present<decltype(tblgen_props.is_stateless)>(is_stateless);
      tblgen_props.max_subdivs_per_device = ::llvm::dyn_cast_if_present<decltype(tblgen_props.max_subdivs_per_device)>(max_subdivs_per_device);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_CollectiveReduceV2Op_1 = ::mlir::TF::CollectiveReduceV2Op::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_CollectiveReduceV2Op_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:239
*/
struct DecomposeResourceApplyAdagrad : public ::mlir::RewritePattern {
  DecomposeResourceApplyAdagrad(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyAdagrad", 1, context, {"tf.Const", "tf.ResourceApplyAdagradV2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range accum_resource(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::mlir::BoolAttr update_slots;
    ::mlir::BoolAttr use_locking;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyAdagradOp>(op0); (void)castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    accum_resource = castedOp0.getODSOperands(1);
    lr = castedOp0.getODSOperands(2);
    grad = castedOp0.getODSOperands(3);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      use_locking = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUpdateSlots();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(true);
      update_slots = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = GetScalarOfType(getElementTypeOrSelf((*grad.begin())),0); (void)nativeVar_0;
    ::mlir::TF::ConstOp zero_epsilon;
    {
      zero_epsilon = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    ::mlir::TF::ResourceApplyAdagradV2Op tblgen_ResourceApplyAdagradV2Op_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::ResourceApplyAdagradV2Op::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*accum_resource.begin()));
      tblgen_values.push_back((*lr.begin()));
      tblgen_values.push_back((*zero_epsilon.getODSResults(0).begin()));
      tblgen_values.push_back((*grad.begin()));
      tblgen_props.use_locking = ::llvm::dyn_cast_if_present<decltype(tblgen_props.use_locking)>(use_locking);
      tblgen_props.update_slots = ::llvm::dyn_cast_if_present<decltype(tblgen_props.update_slots)>(update_slots);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_ResourceApplyAdagradV2Op_1 = ::mlir::TF::ResourceApplyAdagradV2Op::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:215
*/
struct DecomposeResourceApplyAdagradV2 : public ::mlir::RewritePattern {
  DecomposeResourceApplyAdagradV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyAdagradV2", 1, context, {"tf.AddV2", "tf.AssignSubVariableOp", "tf.AssignVariableOp", "tf.Div", "tf.Mul", "tf.Sqrt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range epsilon(op0->getOperands());
    ::mlir::Operation::operand_range accum_resource(op0->getOperands());
    ::mlir::TF::ResourceApplyAdagradV2Op src_op;
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::mlir::BoolAttr update_slots;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyAdagradV2Op>(op0); (void)castedOp0;
    src_op = castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    accum_resource = castedOp0.getODSOperands(1);
    lr = castedOp0.getODSOperands(2);
    epsilon = castedOp0.getODSOperands(3);
    grad = castedOp0.getODSOperands(4);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops1(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyAdagradV2' attribute 'use_locking' failed to satisfy constraint: 'bool attribute'"))) {
        return ::mlir::failure();
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUpdateSlots();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(true);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops2(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyAdagradV2' attribute 'update_slots' failed to satisfy constraint: 'constant attribute true'"))) {
        return ::mlir::failure();
      }
      update_slots = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*accum_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*accum_resource.begin())); (void)nativeVar_0;
    ::mlir::TF::MulOp tblgen_MulOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      ::mlir::Value tblgen_value_1 = (*grad.begin());
      tblgen_MulOp_1 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op new_accum;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_1.getODSResults(0).begin());
      new_accum = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*lr.begin());
      ::mlir::Value tblgen_value_1 = (*grad.begin());
      tblgen_MulOp_2 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SqrtOp tblgen_SqrtOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*new_accum.getODSResults(0).begin());
      tblgen_SqrtOp_3 = ::mlir::TF::SqrtOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::AddV2Op tblgen_AddV2Op_4;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SqrtOp_3.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*epsilon.begin());
      tblgen_AddV2Op_4 = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::DivOp tblgen_DivOp_5;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_2.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_AddV2Op_4.getODSResults(0).begin());
      tblgen_DivOp_5 = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AssignSubVariableOp tblgen_AssignSubVariableOp_6;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignSubVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*tblgen_DivOp_5.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignSubVariableOp_6 = ::mlir::TF::AssignSubVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    auto nativeVar_7 = rewriter.getBoolAttr(false); (void)nativeVar_7;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_8;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*accum_resource.begin()));
      tblgen_values.push_back((*new_accum.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_7);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_8 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:304
*/
struct DecomposeResourceApplyAdamNesterov : public ::mlir::RewritePattern {
  DecomposeResourceApplyAdamNesterov(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyAdam", 1, context, {"tf.AddV2", "tf.AssignSubVariableOp", "tf.AssignVariableOp", "tf.Const", "tf.Div", "tf.Mul", "tf.Sqrt", "tf.Square", "tf.Sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr use_nesterov;
    ::mlir::Operation::operand_range m_resource(op0->getOperands());
    ::mlir::TF::ResourceApplyAdamOp src_op;
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range beta1(op0->getOperands());
    ::mlir::Operation::operand_range v_resource(op0->getOperands());
    ::mlir::Operation::operand_range beta1_power(op0->getOperands());
    ::mlir::Operation::operand_range beta2_power(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range beta2(op0->getOperands());
    ::mlir::Operation::operand_range epsilon(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyAdamOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    m_resource = castedOp0.getODSOperands(1);
    v_resource = castedOp0.getODSOperands(2);
    beta1_power = castedOp0.getODSOperands(3);
    beta2_power = castedOp0.getODSOperands(4);
    lr = castedOp0.getODSOperands(5);
    beta1 = castedOp0.getODSOperands(6);
    beta2 = castedOp0.getODSOperands(7);
    epsilon = castedOp0.getODSOperands(8);
    grad = castedOp0.getODSOperands(9);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops1(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyAdam' attribute 'use_locking' failed to satisfy constraint: 'bool attribute'"))) {
        return ::mlir::failure();
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseNesterov();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops2(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyAdam' attribute 'use_nesterov' failed to satisfy constraint: 'constant attribute true'"))) {
        return ::mlir::failure();
      }
      use_nesterov = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = GetScalarOfType(getElementTypeOrSelf((*grad.begin())),1); (void)nativeVar_0;
    ::mlir::TF::ConstOp one;
    {
      one = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*beta2_power.begin());
      tblgen_SubOp_1 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SqrtOp tblgen_SqrtOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubOp_1.getODSResults(0).begin());
      tblgen_SqrtOp_2 = ::mlir::TF::SqrtOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*beta1_power.begin());
      tblgen_SubOp_3 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::DivOp tblgen_DivOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SqrtOp_2.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_SubOp_3.getODSResults(0).begin());
      tblgen_DivOp_4 = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp alpha;
    {
      ::mlir::Value tblgen_value_0 = (*lr.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_DivOp_4.getODSResults(0).begin());
      alpha = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_5 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*m_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*m_resource.begin())); (void)nativeVar_5;
    ::mlir::TF::MulOp tblgen_MulOp_6;
    {
      ::mlir::Value tblgen_value_0 = (*beta1.begin());
      ::mlir::Value tblgen_value_1 = nativeVar_5;
      tblgen_MulOp_6 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_7;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*beta1.begin());
      tblgen_SubOp_7 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_8;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubOp_7.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*grad.begin());
      tblgen_MulOp_8 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op new_m;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_6.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_8.getODSResults(0).begin());
      new_m = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_9 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*v_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*v_resource.begin())); (void)nativeVar_9;
    ::mlir::TF::MulOp tblgen_MulOp_10;
    {
      ::mlir::Value tblgen_value_0 = (*beta2.begin());
      ::mlir::Value tblgen_value_1 = nativeVar_9;
      tblgen_MulOp_10 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_11;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*beta2.begin());
      tblgen_SubOp_11 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SquareOp tblgen_SquareOp_12;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      tblgen_SquareOp_12 = ::mlir::TF::SquareOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_13;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubOp_11.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_SquareOp_12.getODSResults(0).begin());
      tblgen_MulOp_13 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op new_v;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_10.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_13.getODSResults(0).begin());
      new_v = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_14;
    {
      ::mlir::Value tblgen_value_0 = (*new_m.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*beta1.begin());
      tblgen_MulOp_14 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_15;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*beta1.begin());
      tblgen_SubOp_15 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_16;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubOp_15.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*grad.begin());
      tblgen_MulOp_16 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op tblgen_AddV2Op_17;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_14.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_16.getODSResults(0).begin());
      tblgen_AddV2Op_17 = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_18;
    {
      ::mlir::Value tblgen_value_0 = (*alpha.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_AddV2Op_17.getODSResults(0).begin());
      tblgen_MulOp_18 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SqrtOp tblgen_SqrtOp_19;
    {
      ::mlir::Value tblgen_value_0 = (*new_v.getODSResults(0).begin());
      tblgen_SqrtOp_19 = ::mlir::TF::SqrtOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::AddV2Op tblgen_AddV2Op_20;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SqrtOp_19.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*epsilon.begin());
      tblgen_AddV2Op_20 = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::DivOp tblgen_DivOp_21;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_18.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_AddV2Op_20.getODSResults(0).begin());
      tblgen_DivOp_21 = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AssignSubVariableOp tblgen_AssignSubVariableOp_22;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignSubVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*tblgen_DivOp_21.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignSubVariableOp_22 = ::mlir::TF::AssignSubVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    auto nativeVar_23 = rewriter.getBoolAttr(false); (void)nativeVar_23;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_24;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*m_resource.begin()));
      tblgen_values.push_back((*new_m.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_23);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_24 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    auto nativeVar_25 = rewriter.getBoolAttr(false); (void)nativeVar_25;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_26;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*v_resource.begin()));
      tblgen_values.push_back((*new_v.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_25);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_26 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:258
*/
struct DecomposeResourceApplyAdamNonNesterov : public ::mlir::RewritePattern {
  DecomposeResourceApplyAdamNonNesterov(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyAdam", 1, context, {"tf.AddV2", "tf.AssignSubVariableOp", "tf.AssignVariableOp", "tf.Const", "tf.Div", "tf.Mul", "tf.Sqrt", "tf.Square", "tf.Sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr use_nesterov;
    ::mlir::Operation::operand_range m_resource(op0->getOperands());
    ::mlir::TF::ResourceApplyAdamOp src_op;
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range beta1(op0->getOperands());
    ::mlir::Operation::operand_range v_resource(op0->getOperands());
    ::mlir::Operation::operand_range beta1_power(op0->getOperands());
    ::mlir::Operation::operand_range beta2_power(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range beta2(op0->getOperands());
    ::mlir::Operation::operand_range epsilon(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyAdamOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    m_resource = castedOp0.getODSOperands(1);
    v_resource = castedOp0.getODSOperands(2);
    beta1_power = castedOp0.getODSOperands(3);
    beta2_power = castedOp0.getODSOperands(4);
    lr = castedOp0.getODSOperands(5);
    beta1 = castedOp0.getODSOperands(6);
    beta2 = castedOp0.getODSOperands(7);
    epsilon = castedOp0.getODSOperands(8);
    grad = castedOp0.getODSOperands(9);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops1(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyAdam' attribute 'use_locking' failed to satisfy constraint: 'bool attribute'"))) {
        return ::mlir::failure();
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseNesterov();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops3(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyAdam' attribute 'use_nesterov' failed to satisfy constraint: 'constant attribute false'"))) {
        return ::mlir::failure();
      }
      use_nesterov = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = GetScalarOfType(getElementTypeOrSelf((*grad.begin())),1); (void)nativeVar_0;
    ::mlir::TF::ConstOp one;
    {
      one = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*beta2_power.begin());
      tblgen_SubOp_1 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SqrtOp tblgen_SqrtOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubOp_1.getODSResults(0).begin());
      tblgen_SqrtOp_2 = ::mlir::TF::SqrtOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*beta1_power.begin());
      tblgen_SubOp_3 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::DivOp tblgen_DivOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SqrtOp_2.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_SubOp_3.getODSResults(0).begin());
      tblgen_DivOp_4 = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp alpha;
    {
      ::mlir::Value tblgen_value_0 = (*lr.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_DivOp_4.getODSResults(0).begin());
      alpha = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_5 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*m_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*m_resource.begin())); (void)nativeVar_5;
    ::mlir::TF::MulOp tblgen_MulOp_6;
    {
      ::mlir::Value tblgen_value_0 = (*beta1.begin());
      ::mlir::Value tblgen_value_1 = nativeVar_5;
      tblgen_MulOp_6 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_7;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*beta1.begin());
      tblgen_SubOp_7 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_8;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubOp_7.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*grad.begin());
      tblgen_MulOp_8 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op new_m;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_6.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_8.getODSResults(0).begin());
      new_m = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_9 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*v_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*v_resource.begin())); (void)nativeVar_9;
    ::mlir::TF::MulOp tblgen_MulOp_10;
    {
      ::mlir::Value tblgen_value_0 = (*beta2.begin());
      ::mlir::Value tblgen_value_1 = nativeVar_9;
      tblgen_MulOp_10 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_11;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*beta2.begin());
      tblgen_SubOp_11 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SquareOp tblgen_SquareOp_12;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      tblgen_SquareOp_12 = ::mlir::TF::SquareOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_13;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubOp_11.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_SquareOp_12.getODSResults(0).begin());
      tblgen_MulOp_13 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op new_v;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_10.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_13.getODSResults(0).begin());
      new_v = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_14;
    {
      ::mlir::Value tblgen_value_0 = (*alpha.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*new_m.getODSResults(0).begin());
      tblgen_MulOp_14 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SqrtOp tblgen_SqrtOp_15;
    {
      ::mlir::Value tblgen_value_0 = (*new_v.getODSResults(0).begin());
      tblgen_SqrtOp_15 = ::mlir::TF::SqrtOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::AddV2Op tblgen_AddV2Op_16;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SqrtOp_15.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*epsilon.begin());
      tblgen_AddV2Op_16 = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::DivOp tblgen_DivOp_17;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_14.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_AddV2Op_16.getODSResults(0).begin());
      tblgen_DivOp_17 = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AssignSubVariableOp tblgen_AssignSubVariableOp_18;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignSubVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*tblgen_DivOp_17.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignSubVariableOp_18 = ::mlir::TF::AssignSubVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    auto nativeVar_19 = rewriter.getBoolAttr(false); (void)nativeVar_19;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_20;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*m_resource.begin()));
      tblgen_values.push_back((*new_m.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_19);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_20 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    auto nativeVar_21 = rewriter.getBoolAttr(false); (void)nativeVar_21;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_22;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*v_resource.begin()));
      tblgen_values.push_back((*new_v.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_21);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_22 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:401
*/
struct DecomposeResourceApplyCenteredRMSProp : public ::mlir::RewritePattern {
  DecomposeResourceApplyCenteredRMSProp(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyCenteredRMSProp", 1, context, {"tf.AddV2", "tf.AssignSubVariableOp", "tf.AssignVariableOp", "tf.Const", "tf.Div", "tf.Mul", "tf.Sqrt", "tf.Square", "tf.Sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range mom_resource(op0->getOperands());
    ::mlir::TF::ResourceApplyCenteredRMSPropOp src_op;
    ::mlir::Operation::operand_range momentum(op0->getOperands());
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range mg_resource(op0->getOperands());
    ::mlir::Operation::operand_range ms_resource(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range rho(op0->getOperands());
    ::mlir::Operation::operand_range epsilon(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::mlir::BoolAttr use_locking;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyCenteredRMSPropOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    mg_resource = castedOp0.getODSOperands(1);
    ms_resource = castedOp0.getODSOperands(2);
    mom_resource = castedOp0.getODSOperands(3);
    lr = castedOp0.getODSOperands(4);
    rho = castedOp0.getODSOperands(5);
    momentum = castedOp0.getODSOperands(6);
    epsilon = castedOp0.getODSOperands(7);
    grad = castedOp0.getODSOperands(8);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      use_locking = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = GetScalarOfType(getElementTypeOrSelf((*grad.begin())),1); (void)nativeVar_0;
    ::mlir::TF::ConstOp one;
    {
      one = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    auto nativeVar_1 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*ms_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*ms_resource.begin())); (void)nativeVar_1;
    ::mlir::TF::MulOp tblgen_MulOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      ::mlir::Value tblgen_value_1 = (*grad.begin());
      tblgen_MulOp_2 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*rho.begin());
      tblgen_SubOp_3 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_2.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_SubOp_3.getODSResults(0).begin());
      tblgen_MulOp_4 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_5 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*ms_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*ms_resource.begin())); (void)nativeVar_5;
    ::mlir::TF::MulOp tblgen_MulOp_6;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_5;
      ::mlir::Value tblgen_value_1 = (*rho.begin());
      tblgen_MulOp_6 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op ms_new;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_4.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_6.getODSResults(0).begin());
      ms_new = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_7 = rewriter.getBoolAttr(false); (void)nativeVar_7;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_8;
    {
      ::mlir::Value tblgen_value_0 = (*ms_resource.begin());
      ::mlir::Value tblgen_value_1 = (*ms_new.getODSResults(0).begin());
      tblgen_AssignVariableOp_8 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc,
        /*resource=*/tblgen_value_0,
        /*value=*/tblgen_value_1,
        /*validate_shape=*/nativeVar_7
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_9;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*rho.begin());
      tblgen_SubOp_9 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_10;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_SubOp_9.getODSResults(0).begin());
      tblgen_MulOp_10 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_11 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*mg_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*mg_resource.begin())); (void)nativeVar_11;
    ::mlir::TF::MulOp tblgen_MulOp_12;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_11;
      ::mlir::Value tblgen_value_1 = (*rho.begin());
      tblgen_MulOp_12 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op mg_new;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_10.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_12.getODSResults(0).begin());
      mg_new = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_13 = rewriter.getBoolAttr(false); (void)nativeVar_13;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_14;
    {
      ::mlir::Value tblgen_value_0 = (*mg_resource.begin());
      ::mlir::Value tblgen_value_1 = (*mg_new.getODSResults(0).begin());
      tblgen_AssignVariableOp_14 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc,
        /*resource=*/tblgen_value_0,
        /*value=*/tblgen_value_1,
        /*validate_shape=*/nativeVar_13
      );
    }
    auto nativeVar_15 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*mom_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*mom_resource.begin())); (void)nativeVar_15;
    ::mlir::TF::MulOp tblgen_MulOp_16;
    {
      ::mlir::Value tblgen_value_0 = (*momentum.begin());
      ::mlir::Value tblgen_value_1 = nativeVar_15;
      tblgen_MulOp_16 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_17;
    {
      ::mlir::Value tblgen_value_0 = (*lr.begin());
      ::mlir::Value tblgen_value_1 = (*grad.begin());
      tblgen_MulOp_17 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SquareOp tblgen_SquareOp_18;
    {
      ::mlir::Value tblgen_value_0 = (*mg_new.getODSResults(0).begin());
      tblgen_SquareOp_18 = ::mlir::TF::SquareOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_19;
    {
      ::mlir::Value tblgen_value_0 = (*ms_new.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_SquareOp_18.getODSResults(0).begin());
      tblgen_SubOp_19 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op tblgen_AddV2Op_20;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubOp_19.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*epsilon.begin());
      tblgen_AddV2Op_20 = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SqrtOp tblgen_SqrtOp_21;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_AddV2Op_20.getODSResults(0).begin());
      tblgen_SqrtOp_21 = ::mlir::TF::SqrtOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::DivOp tblgen_DivOp_22;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_17.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_SqrtOp_21.getODSResults(0).begin());
      tblgen_DivOp_22 = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op mom_new;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_16.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_DivOp_22.getODSResults(0).begin());
      mom_new = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_23 = rewriter.getBoolAttr(false); (void)nativeVar_23;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_24;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*mom_resource.begin()));
      tblgen_values.push_back((*mom_new.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_23);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_24 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    ::mlir::TF::AssignSubVariableOp tblgen_AssignSubVariableOp_25;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignSubVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*mom_new.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignSubVariableOp_25 = ::mlir::TF::AssignSubVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:454
*/
struct DecomposeResourceApplyFtrl : public ::mlir::RewritePattern {
  DecomposeResourceApplyFtrl(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyFtrl", 1, context, {"tf.Const", "tf.ResourceApplyFtrlV2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l1(op0->getOperands());
    ::mlir::Operation::operand_range var(op0->getOperands());
    ::mlir::Operation::operand_range linear(op0->getOperands());
    ::mlir::Operation::operand_range accum(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range l2(op0->getOperands());
    ::mlir::Operation::operand_range lr_power(op0->getOperands());
    ::mlir::BoolAttr use_locking;
    ::mlir::BoolAttr multiply_linear_by_lr;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyFtrlOp>(op0); (void)castedOp0;
    var = castedOp0.getODSOperands(0);
    accum = castedOp0.getODSOperands(1);
    linear = castedOp0.getODSOperands(2);
    grad = castedOp0.getODSOperands(3);
    lr = castedOp0.getODSOperands(4);
    l1 = castedOp0.getODSOperands(5);
    l2 = castedOp0.getODSOperands(6);
    lr_power = castedOp0.getODSOperands(7);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      use_locking = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getMultiplyLinearByLr();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      multiply_linear_by_lr = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = GetScalarOfType(getElementTypeOrSelf((*lr_power.begin())),0); (void)nativeVar_0;
    ::mlir::TF::ConstOp tblgen_ConstOp_1;
    {
      tblgen_ConstOp_1 = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    ::mlir::TF::ResourceApplyFtrlV2Op tblgen_ResourceApplyFtrlV2Op_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::ResourceApplyFtrlV2Op::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var.begin()));
      tblgen_values.push_back((*accum.begin()));
      tblgen_values.push_back((*linear.begin()));
      tblgen_values.push_back((*grad.begin()));
      tblgen_values.push_back((*lr.begin()));
      tblgen_values.push_back((*l1.begin()));
      tblgen_values.push_back((*l2.begin()));
      tblgen_values.push_back((*tblgen_ConstOp_1.getODSResults(0).begin()));
      tblgen_values.push_back((*lr_power.begin()));
      tblgen_props.use_locking = ::llvm::dyn_cast_if_present<decltype(tblgen_props.use_locking)>(use_locking);
      tblgen_props.multiply_linear_by_lr = ::llvm::dyn_cast_if_present<decltype(tblgen_props.multiply_linear_by_lr)>(multiply_linear_by_lr);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_ResourceApplyFtrlV2Op_2 = ::mlir::TF::ResourceApplyFtrlV2Op::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:461
*/
struct DecomposeResourceApplyFtrlV2 : public ::mlir::RewritePattern {
  DecomposeResourceApplyFtrlV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyFtrlV2", 1, context, {"tf.AddV2", "tf.AssignAddVariableOp", "tf.AssignVariableOp", "tf.Const", "tf.Div", "tf.Mul", "tf.Neg", "tf.Pow", "tf.Square", "tf.Sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::ResourceApplyFtrlV2Op src_op;
    ::mlir::Operation::operand_range l1(op0->getOperands());
    ::mlir::Operation::operand_range var(op0->getOperands());
    ::mlir::Operation::operand_range linear(op0->getOperands());
    ::mlir::Operation::operand_range accum(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range l2(op0->getOperands());
    ::mlir::Operation::operand_range l2_shrinkage(op0->getOperands());
    ::mlir::Operation::operand_range lr_power(op0->getOperands());
    ::mlir::BoolAttr use_locking;
    ::mlir::BoolAttr multiply_linear_by_lr;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyFtrlV2Op>(op0); (void)castedOp0;
    src_op = castedOp0;
    var = castedOp0.getODSOperands(0);
    accum = castedOp0.getODSOperands(1);
    linear = castedOp0.getODSOperands(2);
    grad = castedOp0.getODSOperands(3);
    lr = castedOp0.getODSOperands(4);
    l1 = castedOp0.getODSOperands(5);
    l2 = castedOp0.getODSOperands(6);
    l2_shrinkage = castedOp0.getODSOperands(7);
    lr_power = castedOp0.getODSOperands(8);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      use_locking = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getMultiplyLinearByLr();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      multiply_linear_by_lr = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = GetScalarOfType(getElementTypeOrSelf((*lr.begin())),0); (void)nativeVar_0;
    ::mlir::TF::ConstOp zero;
    {
      zero = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    auto nativeVar_1 = GetScalarOfType(getElementTypeOrSelf((*lr.begin())),1); (void)nativeVar_1;
    ::mlir::TF::ConstOp one;
    {
      one = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_1
      );
    }
    auto nativeVar_2 = GetScalarOfType(getElementTypeOrSelf((*lr.begin())),2); (void)nativeVar_2;
    ::mlir::TF::ConstOp two;
    {
      two = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_2
      );
    }
    auto nativeVar_3 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*var.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*var.begin())); (void)nativeVar_3;
    ::mlir::TF::MulOp tblgen_MulOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*l2_shrinkage.begin());
      ::mlir::Value tblgen_value_1 = nativeVar_3;
      tblgen_MulOp_4 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_5;
    {
      ::mlir::Value tblgen_value_0 = (*two.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_4.getODSResults(0).begin());
      tblgen_MulOp_5 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op grad_with_shrinkage;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_5.getODSResults(0).begin());
      grad_with_shrinkage = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_6 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*accum.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*accum.begin())); (void)nativeVar_6;
    ::mlir::TF::SquareOp tblgen_SquareOp_7;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      tblgen_SquareOp_7 = ::mlir::TF::SquareOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::AddV2Op accum_new;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_6;
      ::mlir::Value tblgen_value_1 = (*tblgen_SquareOp_7.getODSResults(0).begin());
      accum_new = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_8;
    {
      ::mlir::Value tblgen_value_0 = (*grad_with_shrinkage.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*lr.begin());
      tblgen_MulOp_8 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::NegOp tblgen_NegOp_9;
    {
      ::mlir::Value tblgen_value_0 = (*lr_power.begin());
      tblgen_NegOp_9 = ::mlir::TF::NegOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::PowOp tblgen_PowOp_10;
    {
      ::mlir::Value tblgen_value_0 = (*accum_new.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_NegOp_9.getODSResults(0).begin());
      tblgen_PowOp_10 = ::mlir::TF::PowOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_11 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*accum.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*accum.begin())); (void)nativeVar_11;
    ::mlir::TF::NegOp tblgen_NegOp_12;
    {
      ::mlir::Value tblgen_value_0 = (*lr_power.begin());
      tblgen_NegOp_12 = ::mlir::TF::NegOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::PowOp tblgen_PowOp_13;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_11;
      ::mlir::Value tblgen_value_1 = (*tblgen_NegOp_12.getODSResults(0).begin());
      tblgen_PowOp_13 = ::mlir::TF::PowOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp sub;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_PowOp_10.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_PowOp_13.getODSResults(0).begin());
      sub = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_14 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*var.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*var.begin())); (void)nativeVar_14;
    ::mlir::TF::MulOp tblgen_MulOp_15;
    {
      ::mlir::Value tblgen_value_0 = (*sub.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = nativeVar_14;
      tblgen_MulOp_15 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_16;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_8.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_15.getODSResults(0).begin());
      tblgen_SubOp_16 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::DivOp tblgen_DivOp_17;
    {
      ::mlir::Value tblgen_value_0 = (*sub.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*lr.begin());
      tblgen_DivOp_17 = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_18 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*var.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*var.begin())); (void)nativeVar_18;
    ::mlir::TF::MulOp tblgen_MulOp_19;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_DivOp_17.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = nativeVar_18;
      tblgen_MulOp_19 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_20;
    {
      ::mlir::Value tblgen_value_0 = (*grad_with_shrinkage.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_19.getODSResults(0).begin());
      tblgen_SubOp_20 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_21 = (multiply_linear_by_lr).getValue() ? (tblgen_SubOp_16) : (tblgen_SubOp_20); (void)nativeVar_21;
    ::mlir::TF::AssignAddVariableOp tblgen_AssignAddVariableOp_22;
    {
      ::mlir::Value tblgen_value_0 = (*linear.begin());
      ::mlir::Value tblgen_value_1 = nativeVar_21;
      tblgen_AssignAddVariableOp_22 = ::mlir::TF::AssignAddVariableOp::create(rewriter, odsLoc,
        /*resource=*/tblgen_value_0,
        /*value=*/tblgen_value_1
      );
    }
    ::mlir::TF::NegOp tblgen_NegOp_23;
    {
      ::mlir::Value tblgen_value_0 = (*lr_power.begin());
      tblgen_NegOp_23 = ::mlir::TF::NegOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::PowOp tblgen_PowOp_24;
    {
      ::mlir::Value tblgen_value_0 = (*accum_new.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_NegOp_23.getODSResults(0).begin());
      tblgen_PowOp_24 = ::mlir::TF::PowOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_25 = (multiply_linear_by_lr).getValue() ? ((*one.getODSResults(0).begin())) : ((*lr.begin())); (void)nativeVar_25;
    ::mlir::TF::DivOp tblgen_DivOp_26;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_PowOp_24.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = nativeVar_25;
      tblgen_DivOp_26 = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_27;
    {
      ::mlir::Value tblgen_value_0 = (*two.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*l2.begin());
      tblgen_MulOp_27 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_28 = (multiply_linear_by_lr).getValue() ? ((*lr.begin())) : ((*one.getODSResults(0).begin())); (void)nativeVar_28;
    ::mlir::TF::MulOp tblgen_MulOp_29;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_27.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = nativeVar_28;
      tblgen_MulOp_29 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op quadratic;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_DivOp_26.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_29.getODSResults(0).begin());
      quadratic = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_30;
    {
      ::mlir::Value tblgen_value_0 = (*l1.begin());
      ::mlir::Value tblgen_value_1 = (*lr.begin());
      tblgen_MulOp_30 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::NegOp tblgen_NegOp_31;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_30.getODSResults(0).begin());
      tblgen_NegOp_31 = ::mlir::TF::NegOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    auto nativeVar_32 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*linear.begin()), llvm::cast<TensorType>((*l1.begin()).getType()).getElementType()),  (*linear.begin())); (void)nativeVar_32;
    ::mlir::TF::MulOp tblgen_MulOp_33;
    {
      ::mlir::Value tblgen_value_0 = (*l1.begin());
      ::mlir::Value tblgen_value_1 = (*lr.begin());
      tblgen_MulOp_33 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_34 = TF::ClipByValueOp::create(rewriter,   src_op.getLoc(),  nativeVar_32.getType(), nativeVar_32, tblgen_NegOp_31, tblgen_MulOp_33); (void)nativeVar_34;
    ::mlir::TF::NegOp tblgen_NegOp_35;
    {
      ::mlir::Value tblgen_value_0 = (*l1.begin());
      tblgen_NegOp_35 = ::mlir::TF::NegOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    auto nativeVar_36 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*linear.begin()), llvm::cast<TensorType>((*l1.begin()).getType()).getElementType()),  (*linear.begin())); (void)nativeVar_36;
    auto nativeVar_37 = TF::ClipByValueOp::create(rewriter,   src_op.getLoc(),  nativeVar_36.getType(), nativeVar_36, tblgen_NegOp_35, (*l1.begin())); (void)nativeVar_37;
    auto nativeVar_38 = (multiply_linear_by_lr).getValue() ? (nativeVar_34) : (nativeVar_37); (void)nativeVar_38;
    auto nativeVar_39 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*linear.begin()), llvm::cast<TensorType>((*l1.begin()).getType()).getElementType()),  (*linear.begin())); (void)nativeVar_39;
    ::mlir::TF::SubOp linear_clipped_minus_linear;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_38;
      ::mlir::Value tblgen_value_1 = nativeVar_39;
      linear_clipped_minus_linear = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::DivOp tblgen_DivOp_40;
    {
      ::mlir::Value tblgen_value_0 = (*linear_clipped_minus_linear.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*quadratic.getODSResults(0).begin());
      tblgen_DivOp_40 = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_41 = rewriter.getBoolAttr(false); (void)nativeVar_41;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_42;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var.begin()));
      tblgen_values.push_back((*tblgen_DivOp_40.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_41);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_42 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    auto nativeVar_43 = rewriter.getBoolAttr(false); (void)nativeVar_43;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_44;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*accum.begin()));
      tblgen_values.push_back((*accum_new.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_43);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_44 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:97
*/
struct DecomposeResourceApplyGradientDescentOp : public ::mlir::RewritePattern {
  DecomposeResourceApplyGradientDescentOp(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyGradientDescent", 1, context, {"tf.AssignVariableOp", "tf.Mul", "tf.Sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range resource(op0->getOperands());
    ::mlir::TF::ResourceApplyGradientDescentOp src_op;
    ::mlir::Operation::operand_range alpha(op0->getOperands());
    ::mlir::Operation::operand_range delta(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyGradientDescentOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    resource = castedOp0.getODSOperands(0);
    alpha = castedOp0.getODSOperands(1);
    delta = castedOp0.getODSOperands(2);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops1(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyGradientDescent' attribute 'use_locking' failed to satisfy constraint: 'bool attribute'"))) {
        return ::mlir::failure();
      }
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*resource.begin()), llvm::cast<TensorType>((*alpha.begin()).getType()).getElementType()),  (*resource.begin())); (void)nativeVar_0;
    ::mlir::TF::MulOp tblgen_MulOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*alpha.begin());
      ::mlir::Value tblgen_value_1 = (*delta.begin());
      tblgen_MulOp_1 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_2;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_1.getODSResults(0).begin());
      tblgen_SubOp_2 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_3 = rewriter.getBoolAttr(false); (void)nativeVar_3;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_4;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*resource.begin()));
      tblgen_values.push_back((*tblgen_SubOp_2.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_3);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_4 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:186
*/
struct DecomposeResourceApplyKerasMomentumOpNesterov : public ::mlir::RewritePattern {
  DecomposeResourceApplyKerasMomentumOpNesterov(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyKerasMomentum", 1, context, {"tf.AssignAddVariableOp", "tf.AssignVariableOp", "tf.Mul", "tf.Sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr use_nesterov;
    ::mlir::Operation::operand_range accum_resource(op0->getOperands());
    ::mlir::TF::ResourceApplyKerasMomentumOp src_op;
    ::mlir::Operation::operand_range momentum(op0->getOperands());
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyKerasMomentumOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    accum_resource = castedOp0.getODSOperands(1);
    lr = castedOp0.getODSOperands(2);
    grad = castedOp0.getODSOperands(3);
    momentum = castedOp0.getODSOperands(4);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops1(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyKerasMomentum' attribute 'use_locking' failed to satisfy constraint: 'bool attribute'"))) {
        return ::mlir::failure();
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseNesterov();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops2(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyKerasMomentum' attribute 'use_nesterov' failed to satisfy constraint: 'constant attribute true'"))) {
        return ::mlir::failure();
      }
      use_nesterov = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*accum_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*accum_resource.begin())); (void)nativeVar_0;
    ::mlir::TF::MulOp tblgen_MulOp_1;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      ::mlir::Value tblgen_value_1 = (*momentum.begin());
      tblgen_MulOp_1 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp grad_lr;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      ::mlir::Value tblgen_value_1 = (*lr.begin());
      grad_lr = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp accum_new;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*grad_lr.getODSResults(0).begin());
      accum_new = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_2 = rewriter.getBoolAttr(false); (void)nativeVar_2;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*accum_resource.begin()));
      tblgen_values.push_back((*accum_new.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_3 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    ::mlir::TF::MulOp tblgen_MulOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*accum_new.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*momentum.begin());
      tblgen_MulOp_4 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_5;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_4.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*grad_lr.getODSResults(0).begin());
      tblgen_SubOp_5 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AssignAddVariableOp tblgen_AssignAddVariableOp_6;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignAddVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*tblgen_SubOp_5.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignAddVariableOp_6 = ::mlir::TF::AssignAddVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:164
*/
struct DecomposeResourceApplyKerasMomentumOpNonNesterov : public ::mlir::RewritePattern {
  DecomposeResourceApplyKerasMomentumOpNonNesterov(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyKerasMomentum", 1, context, {"tf.AssignAddVariableOp", "tf.AssignVariableOp", "tf.Mul", "tf.Sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr use_nesterov;
    ::mlir::Operation::operand_range accum_resource(op0->getOperands());
    ::mlir::TF::ResourceApplyKerasMomentumOp src_op;
    ::mlir::Operation::operand_range momentum(op0->getOperands());
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyKerasMomentumOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    accum_resource = castedOp0.getODSOperands(1);
    lr = castedOp0.getODSOperands(2);
    grad = castedOp0.getODSOperands(3);
    momentum = castedOp0.getODSOperands(4);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops1(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyKerasMomentum' attribute 'use_locking' failed to satisfy constraint: 'bool attribute'"))) {
        return ::mlir::failure();
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseNesterov();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops3(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyKerasMomentum' attribute 'use_nesterov' failed to satisfy constraint: 'constant attribute false'"))) {
        return ::mlir::failure();
      }
      use_nesterov = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*accum_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*accum_resource.begin())); (void)nativeVar_0;
    ::mlir::TF::MulOp tblgen_MulOp_1;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      ::mlir::Value tblgen_value_1 = (*momentum.begin());
      tblgen_MulOp_1 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      ::mlir::Value tblgen_value_1 = (*lr.begin());
      tblgen_MulOp_2 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp accum_new;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_2.getODSResults(0).begin());
      accum_new = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_3 = rewriter.getBoolAttr(false); (void)nativeVar_3;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_4;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*accum_resource.begin()));
      tblgen_values.push_back((*accum_new.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_3);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_4 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    ::mlir::TF::AssignAddVariableOp tblgen_AssignAddVariableOp_5;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignAddVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*accum_new.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignAddVariableOp_5 = ::mlir::TF::AssignAddVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:136
*/
struct DecomposeResourceApplyMomentumOpNesterov : public ::mlir::RewritePattern {
  DecomposeResourceApplyMomentumOpNesterov(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyMomentum", 1, context, {"tf.AddV2", "tf.AssignSubVariableOp", "tf.AssignVariableOp", "tf.Mul"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr use_nesterov;
    ::mlir::Operation::operand_range accum_resource(op0->getOperands());
    ::mlir::TF::ResourceApplyMomentumOp src_op;
    ::mlir::Operation::operand_range momentum(op0->getOperands());
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyMomentumOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    accum_resource = castedOp0.getODSOperands(1);
    lr = castedOp0.getODSOperands(2);
    grad = castedOp0.getODSOperands(3);
    momentum = castedOp0.getODSOperands(4);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops1(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyMomentum' attribute 'use_locking' failed to satisfy constraint: 'bool attribute'"))) {
        return ::mlir::failure();
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseNesterov();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops2(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyMomentum' attribute 'use_nesterov' failed to satisfy constraint: 'constant attribute true'"))) {
        return ::mlir::failure();
      }
      use_nesterov = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*accum_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*accum_resource.begin())); (void)nativeVar_0;
    ::mlir::TF::MulOp tblgen_MulOp_1;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      ::mlir::Value tblgen_value_1 = (*momentum.begin());
      tblgen_MulOp_1 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op accum_new;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*grad.begin());
      accum_new = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_2 = rewriter.getBoolAttr(false); (void)nativeVar_2;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*accum_resource.begin()));
      tblgen_values.push_back((*accum_new.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_3 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    ::mlir::TF::MulOp tblgen_MulOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      ::mlir::Value tblgen_value_1 = (*lr.begin());
      tblgen_MulOp_4 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_5;
    {
      ::mlir::Value tblgen_value_0 = (*momentum.begin());
      ::mlir::Value tblgen_value_1 = (*lr.begin());
      tblgen_MulOp_5 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_6;
    {
      ::mlir::Value tblgen_value_0 = (*accum_new.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_5.getODSResults(0).begin());
      tblgen_MulOp_6 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op tblgen_AddV2Op_7;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_4.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_6.getODSResults(0).begin());
      tblgen_AddV2Op_7 = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AssignSubVariableOp tblgen_AssignSubVariableOp_8;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignSubVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*tblgen_AddV2Op_7.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignSubVariableOp_8 = ::mlir::TF::AssignSubVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:114
*/
struct DecomposeResourceApplyMomentumOpNonNesterov : public ::mlir::RewritePattern {
  DecomposeResourceApplyMomentumOpNonNesterov(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyMomentum", 1, context, {"tf.AddV2", "tf.AssignSubVariableOp", "tf.AssignVariableOp", "tf.Mul"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr use_nesterov;
    ::mlir::Operation::operand_range accum_resource(op0->getOperands());
    ::mlir::TF::ResourceApplyMomentumOp src_op;
    ::mlir::Operation::operand_range momentum(op0->getOperands());
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyMomentumOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    accum_resource = castedOp0.getODSOperands(1);
    lr = castedOp0.getODSOperands(2);
    grad = castedOp0.getODSOperands(3);
    momentum = castedOp0.getODSOperands(4);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops1(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyMomentum' attribute 'use_locking' failed to satisfy constraint: 'bool attribute'"))) {
        return ::mlir::failure();
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseNesterov();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_decompose_resource_ops3(rewriter, castedOp0, tblgen_attr, "op 'tf.ResourceApplyMomentum' attribute 'use_nesterov' failed to satisfy constraint: 'constant attribute false'"))) {
        return ::mlir::failure();
      }
      use_nesterov = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*accum_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*accum_resource.begin())); (void)nativeVar_0;
    ::mlir::TF::MulOp tblgen_MulOp_1;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      ::mlir::Value tblgen_value_1 = (*momentum.begin());
      tblgen_MulOp_1 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op accum_new;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*grad.begin());
      accum_new = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_2 = rewriter.getBoolAttr(false); (void)nativeVar_2;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*accum_resource.begin()));
      tblgen_values.push_back((*accum_new.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_3 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    ::mlir::TF::MulOp tblgen_MulOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*accum_new.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*lr.begin());
      tblgen_MulOp_4 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AssignSubVariableOp tblgen_AssignSubVariableOp_5;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignSubVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*tblgen_MulOp_4.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignSubVariableOp_5 = ::mlir::TF::AssignSubVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:598
*/
struct DecomposeResourceApplyProximalAdagrad : public ::mlir::RewritePattern {
  DecomposeResourceApplyProximalAdagrad(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyProximalAdagrad", 1, context, {"tf.Abs", "tf.Add", "tf.AddV2", "tf.AssignVariableOp", "tf.Const", "tf.Div", "tf.Greater", "tf.Maximum", "tf.Mul", "tf.Rsqrt", "tf.SelectV2", "tf.Sign", "tf.Square", "tf.Sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range accum_resource(op0->getOperands());
    ::mlir::TF::ResourceApplyProximalAdagradOp src_op;
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range l2(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range l1(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::mlir::BoolAttr use_locking;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyProximalAdagradOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    accum_resource = castedOp0.getODSOperands(1);
    lr = castedOp0.getODSOperands(2);
    l1 = castedOp0.getODSOperands(3);
    l2 = castedOp0.getODSOperands(4);
    grad = castedOp0.getODSOperands(5);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      use_locking = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = GetScalarOfType(getElementTypeOrSelf((*grad.begin())),1); (void)nativeVar_0;
    ::mlir::TF::ConstOp one;
    {
      one = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    auto nativeVar_1 = GetScalarOfType(getElementTypeOrSelf((*grad.begin())),0); (void)nativeVar_1;
    ::mlir::TF::ConstOp zero;
    {
      zero = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_1
      );
    }
    auto nativeVar_2 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*accum_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*accum_resource.begin())); (void)nativeVar_2;
    ::mlir::TF::SquareOp tblgen_SquareOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      tblgen_SquareOp_3 = ::mlir::TF::SquareOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::AddV2Op accum_new;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_2;
      ::mlir::Value tblgen_value_1 = (*tblgen_SquareOp_3.getODSResults(0).begin());
      accum_new = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::RsqrtOp tblgen_RsqrtOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*accum_new.getODSResults(0).begin());
      tblgen_RsqrtOp_4 = ::mlir::TF::RsqrtOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::MulOp adagrad_lr;
    {
      ::mlir::Value tblgen_value_0 = (*lr.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_RsqrtOp_4.getODSResults(0).begin());
      adagrad_lr = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_5 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*var_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*var_resource.begin())); (void)nativeVar_5;
    ::mlir::TF::MulOp tblgen_MulOp_6;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      ::mlir::Value tblgen_value_1 = (*adagrad_lr.getODSResults(0).begin());
      tblgen_MulOp_6 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp prox_var;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_5;
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_6.getODSResults(0).begin());
      prox_var = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SignOp tblgen_SignOp_7;
    {
      ::mlir::Value tblgen_value_0 = (*prox_var.getODSResults(0).begin());
      tblgen_SignOp_7 = ::mlir::TF::SignOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::AbsOp tblgen_AbsOp_8;
    {
      ::mlir::Value tblgen_value_0 = (*prox_var.getODSResults(0).begin());
      tblgen_AbsOp_8 = ::mlir::TF::AbsOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_9;
    {
      ::mlir::Value tblgen_value_0 = (*adagrad_lr.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*l1.begin());
      tblgen_MulOp_9 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_10;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_AbsOp_8.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_9.getODSResults(0).begin());
      tblgen_SubOp_10 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MaximumOp tblgen_MaximumOp_11;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubOp_10.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*zero.getODSResults(0).begin());
      tblgen_MaximumOp_11 = ::mlir::TF::MaximumOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp l1_gt_zero;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SignOp_7.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MaximumOp_11.getODSResults(0).begin());
      l1_gt_zero = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::GreaterOp tblgen_GreaterOp_12;
    {
      ::mlir::Value tblgen_value_0 = (*l1.begin());
      ::mlir::Value tblgen_value_1 = (*zero.getODSResults(0).begin());
      tblgen_GreaterOp_12 = ::mlir::TF::GreaterOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SelectV2Op var_numerator;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_GreaterOp_12.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*l1_gt_zero.getODSResults(0).begin());
      ::mlir::Value tblgen_value_2 = (*prox_var.getODSResults(0).begin());
      var_numerator = ::mlir::TF::SelectV2Op::create(rewriter, odsLoc,
        /*condition=*/tblgen_value_0,
        /*then_value=*/tblgen_value_1,
        /*else_value=*/tblgen_value_2
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_13;
    {
      ::mlir::Value tblgen_value_0 = (*adagrad_lr.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*l2.begin());
      tblgen_MulOp_13 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddOp tblgen_AddOp_14;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_13.getODSResults(0).begin());
      tblgen_AddOp_14 = ::mlir::TF::AddOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::DivOp var_new;
    {
      ::mlir::Value tblgen_value_0 = (*var_numerator.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_AddOp_14.getODSResults(0).begin());
      var_new = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_15 = rewriter.getBoolAttr(false); (void)nativeVar_15;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_16;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*var_new.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_15);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_16 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    auto nativeVar_17 = rewriter.getBoolAttr(false); (void)nativeVar_17;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_18;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*accum_resource.begin()));
      tblgen_values.push_back((*accum_new.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_17);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_18 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:561
*/
struct DecomposeResourceApplyRMSProp : public ::mlir::RewritePattern {
  DecomposeResourceApplyRMSProp(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceApplyRMSProp", 1, context, {"tf.AddV2", "tf.AssignSubVariableOp", "tf.AssignVariableOp", "tf.Const", "tf.Div", "tf.Mul", "tf.Sqrt", "tf.Square", "tf.Sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range epsilon(op0->getOperands());
    ::mlir::Operation::operand_range mom_resource(op0->getOperands());
    ::mlir::TF::ResourceApplyRMSPropOp src_op;
    ::mlir::Operation::operand_range momentum(op0->getOperands());
    ::mlir::Operation::operand_range var_resource(op0->getOperands());
    ::mlir::Operation::operand_range ms_resource(op0->getOperands());
    ::mlir::Operation::operand_range lr(op0->getOperands());
    ::mlir::Operation::operand_range rho(op0->getOperands());
    ::mlir::Operation::operand_range grad(op0->getOperands());
    ::mlir::BoolAttr use_locking;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceApplyRMSPropOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    var_resource = castedOp0.getODSOperands(0);
    ms_resource = castedOp0.getODSOperands(1);
    mom_resource = castedOp0.getODSOperands(2);
    lr = castedOp0.getODSOperands(3);
    rho = castedOp0.getODSOperands(4);
    momentum = castedOp0.getODSOperands(5);
    epsilon = castedOp0.getODSOperands(6);
    grad = castedOp0.getODSOperands(7);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getUseLocking();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      use_locking = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = GetScalarOfType(getElementTypeOrSelf((*grad.begin())),1); (void)nativeVar_0;
    ::mlir::TF::ConstOp one;
    {
      one = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    auto nativeVar_1 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*ms_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*ms_resource.begin())); (void)nativeVar_1;
    auto nativeVar_2 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*ms_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*ms_resource.begin())); (void)nativeVar_2;
    ::mlir::TF::MulOp tblgen_MulOp_3;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_2;
      ::mlir::Value tblgen_value_1 = (*rho.begin());
      tblgen_MulOp_3 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SquareOp tblgen_SquareOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*grad.begin());
      tblgen_SquareOp_4 = ::mlir::TF::SquareOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::SubOp tblgen_SubOp_5;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*rho.begin());
      tblgen_SubOp_5 = ::mlir::TF::SubOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_6;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SquareOp_4.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_SubOp_5.getODSResults(0).begin());
      tblgen_MulOp_6 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op ms_new;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_3.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_MulOp_6.getODSResults(0).begin());
      ms_new = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_7 = rewriter.getBoolAttr(false); (void)nativeVar_7;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_8;
    {
      ::mlir::Value tblgen_value_0 = (*ms_resource.begin());
      ::mlir::Value tblgen_value_1 = (*ms_new.getODSResults(0).begin());
      tblgen_AssignVariableOp_8 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc,
        /*resource=*/tblgen_value_0,
        /*value=*/tblgen_value_1,
        /*validate_shape=*/nativeVar_7
      );
    }
    auto nativeVar_9 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*mom_resource.begin()), llvm::cast<TensorType>((*grad.begin()).getType()).getElementType()),  (*mom_resource.begin())); (void)nativeVar_9;
    ::mlir::TF::MulOp tblgen_MulOp_10;
    {
      ::mlir::Value tblgen_value_0 = (*momentum.begin());
      ::mlir::Value tblgen_value_1 = nativeVar_9;
      tblgen_MulOp_10 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::MulOp tblgen_MulOp_11;
    {
      ::mlir::Value tblgen_value_0 = (*lr.begin());
      ::mlir::Value tblgen_value_1 = (*grad.begin());
      tblgen_MulOp_11 = ::mlir::TF::MulOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op tblgen_AddV2Op_12;
    {
      ::mlir::Value tblgen_value_0 = (*ms_new.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*epsilon.begin());
      tblgen_AddV2Op_12 = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::SqrtOp tblgen_SqrtOp_13;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_AddV2Op_12.getODSResults(0).begin());
      tblgen_SqrtOp_13 = ::mlir::TF::SqrtOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0
      );
    }
    ::mlir::TF::DivOp tblgen_DivOp_14;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_11.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_SqrtOp_13.getODSResults(0).begin());
      tblgen_DivOp_14 = ::mlir::TF::DivOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    ::mlir::TF::AddV2Op mom_new;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_MulOp_10.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_DivOp_14.getODSResults(0).begin());
      mom_new = ::mlir::TF::AddV2Op::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*y=*/tblgen_value_1
      );
    }
    auto nativeVar_15 = rewriter.getBoolAttr(false); (void)nativeVar_15;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_16;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*mom_resource.begin()));
      tblgen_values.push_back((*mom_new.getODSResults(0).begin()));
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_15);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_16 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    ::mlir::TF::AssignSubVariableOp tblgen_AssignSubVariableOp_17;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignSubVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*var_resource.begin()));
      tblgen_values.push_back((*mom_new.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignSubVariableOp_17 = ::mlir::TF::AssignSubVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:349
*/
struct DecomposeResourceGather : public ::mlir::RewritePattern {
  DecomposeResourceGather(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceGather", 1, context, {"tf.Const", "tf.GatherV2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range indices(op0->getOperands());
    ::mlir::TF::ResourceGatherOp old_result;
    ::mlir::Operation::operand_range resource(op0->getOperands());
    ::mlir::IntegerAttr batch_dims;
    ::mlir::BoolAttr validate_indices;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceGatherOp>(op0); (void)castedOp0;
    old_result = castedOp0;
    resource = castedOp0.getODSOperands(0);
    indices = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBatchDims();
      if (!tblgen_attr) tblgen_attr = rewriter.getIntegerAttr(rewriter.getIntegerType(64), 0);
      batch_dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getValidateIndices();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(true);
      validate_indices = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   (*old_result.getODSResults(0).begin()).getLoc(),  GetResourceSubtypeOrDefault(    (*resource.begin()), llvm::cast<TensorType>((*old_result.getODSResults(0).begin()).getType()).getElementType()),  (*resource.begin())); (void)nativeVar_0;
    ::mlir::TF::ConstOp tblgen_ConstOp_1;
    {
      tblgen_ConstOp_1 = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/batch_dims
      );
    }
    ::mlir::TF::GatherV2Op dest;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::GatherV2Op::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back(nativeVar_0);
      tblgen_values.push_back((*indices.begin()));
      tblgen_values.push_back((*tblgen_ConstOp_1.getODSResults(0).begin()));
      tblgen_props.batch_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.batch_dims)>(batch_dims);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      dest = ::mlir::TF::GatherV2Op::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ dest.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    CopyXlaOutsideCompilationAttributesAdaptor((*old_result.getODSResults(0).begin()), (*dest.getODSResults(0).begin()));

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:361
*/
struct DecomposeResourceScatterAdd : public ::mlir::RewritePattern {
  DecomposeResourceScatterAdd(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceScatterAdd", 1, context, {"tf.AssignVariableOp", "tf.Const", "tf.ExpandDims"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range updates(op0->getOperands());
    ::mlir::Operation::operand_range resource(op0->getOperands());
    ::mlir::TF::ResourceScatterAddOp src_op;
    ::mlir::Operation::operand_range indices(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceScatterAddOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    resource = castedOp0.getODSOperands(0);
    indices = castedOp0.getODSOperands(1);
    updates = castedOp0.getODSOperands(2);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*resource.begin()), llvm::cast<TensorType>((*updates.begin()).getType()).getElementType()),  (*resource.begin())); (void)nativeVar_0;
    auto nativeVar_1 = GetScalarOfType(getElementTypeOrSelf((*indices.begin())),-1); (void)nativeVar_1;
    ::mlir::TF::ConstOp tblgen_ConstOp_2;
    {
      tblgen_ConstOp_2 = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_1
      );
    }
    ::mlir::TF::ExpandDimsOp tblgen_ExpandDimsOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*indices.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_ConstOp_2.getODSResults(0).begin());
      tblgen_ExpandDimsOp_3 = ::mlir::TF::ExpandDimsOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*dim=*/tblgen_value_1
      );
    }
    auto nativeVar_4 = TF::TensorScatterAddOp::create(rewriter, nativeVar_0.getLoc(), nativeVar_0.getType(), nativeVar_0, tblgen_ExpandDimsOp_3, (*updates.begin()), rewriter.getStringAttr("")); (void)nativeVar_4;
    auto nativeVar_5 = rewriter.getBoolAttr(false); (void)nativeVar_5;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_6;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*resource.begin()));
      tblgen_values.push_back(nativeVar_4);
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_5);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_6 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:376
*/
struct DecomposeResourceScatterUpdate : public ::mlir::RewritePattern {
  DecomposeResourceScatterUpdate(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ResourceScatterUpdate", 1, context, {"tf.AssignVariableOp", "tf.Const", "tf.ExpandDims"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range updates(op0->getOperands());
    ::mlir::Operation::operand_range resource(op0->getOperands());
    ::mlir::TF::ResourceScatterUpdateOp src_op;
    ::mlir::Operation::operand_range indices(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ResourceScatterUpdateOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    resource = castedOp0.getODSOperands(0);
    indices = castedOp0.getODSOperands(1);
    updates = castedOp0.getODSOperands(2);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter,   src_op.getLoc(),  GetResourceSubtypeOrDefault(    (*resource.begin()), llvm::cast<TensorType>((*updates.begin()).getType()).getElementType()),  (*resource.begin())); (void)nativeVar_0;
    auto nativeVar_1 = GetScalarOfType(getElementTypeOrSelf((*indices.begin())),-1); (void)nativeVar_1;
    ::mlir::TF::ConstOp tblgen_ConstOp_2;
    {
      tblgen_ConstOp_2 = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_1
      );
    }
    ::mlir::TF::ExpandDimsOp tblgen_ExpandDimsOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*indices.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_ConstOp_2.getODSResults(0).begin());
      tblgen_ExpandDimsOp_3 = ::mlir::TF::ExpandDimsOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*dim=*/tblgen_value_1
      );
    }
    auto nativeVar_4 = TF::TensorScatterUpdateOp::create(rewriter, nativeVar_0.getLoc(), nativeVar_0.getType(), nativeVar_0, tblgen_ExpandDimsOp_3, (*updates.begin()), rewriter.getStringAttr("")); (void)nativeVar_4;
    auto nativeVar_5 = rewriter.getBoolAttr(false); (void)nativeVar_5;
    ::mlir::TF::AssignVariableOp tblgen_AssignVariableOp_6;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::AssignVariableOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*resource.begin()));
      tblgen_values.push_back(nativeVar_4);
      tblgen_props.validate_shape = ::llvm::dyn_cast_if_present<decltype(tblgen_props.validate_shape)>(nativeVar_5);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_AssignVariableOp_6 = ::mlir::TF::AssignVariableOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/decompose_resource_ops.td:390
*/
struct DecomposeVariableShape : public ::mlir::RewritePattern {
  DecomposeVariableShape(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.VariableShape", 1, context, {"tf.Shape"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range resource(op0->getOperands());
    ::mlir::TF::VariableShapeOp src_op;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::VariableShapeOp>(op0); (void)castedOp0;
    src_op = castedOp0;
    resource = castedOp0.getODSOperands(0);
    if (!((HasResourceSubtype((*resource.begin()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'resource' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = TF::ReadVariableOp::create(rewriter, (*src_op.getODSResults(0).begin()).getLoc(), GetResourceSubtype((*resource.begin())), (*resource.begin())); (void)nativeVar_0;
    ::mlir::TF::ShapeOp tblgen_ShapeOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::ShapeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ShapeOp_1 = ::mlir::TF::ShapeOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ShapeOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<DecomposeAssignAddVariableOp>(patterns.getContext());
  patterns.add<DecomposeAssignSubVariableOp>(patterns.getContext());
  patterns.add<DecomposeCollectiveReduceV2>(patterns.getContext());
  patterns.add<DecomposeResourceApplyAdagrad>(patterns.getContext());
  patterns.add<DecomposeResourceApplyAdagradV2>(patterns.getContext());
  patterns.add<DecomposeResourceApplyAdamNesterov>(patterns.getContext());
  patterns.add<DecomposeResourceApplyAdamNonNesterov>(patterns.getContext());
  patterns.add<DecomposeResourceApplyCenteredRMSProp>(patterns.getContext());
  patterns.add<DecomposeResourceApplyFtrl>(patterns.getContext());
  patterns.add<DecomposeResourceApplyFtrlV2>(patterns.getContext());
  patterns.add<DecomposeResourceApplyGradientDescentOp>(patterns.getContext());
  patterns.add<DecomposeResourceApplyKerasMomentumOpNesterov>(patterns.getContext());
  patterns.add<DecomposeResourceApplyKerasMomentumOpNonNesterov>(patterns.getContext());
  patterns.add<DecomposeResourceApplyMomentumOpNesterov>(patterns.getContext());
  patterns.add<DecomposeResourceApplyMomentumOpNonNesterov>(patterns.getContext());
  patterns.add<DecomposeResourceApplyProximalAdagrad>(patterns.getContext());
  patterns.add<DecomposeResourceApplyRMSProp>(patterns.getContext());
  patterns.add<DecomposeResourceGather>(patterns.getContext());
  patterns.add<DecomposeResourceScatterAdd>(patterns.getContext());
  patterns.add<DecomposeResourceScatterUpdate>(patterns.getContext());
  patterns.add<DecomposeVariableShape>(patterns.getContext());
}
