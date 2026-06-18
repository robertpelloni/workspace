/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: StablehloLegalizeDeprecatedOpsPatterns.td                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

/* Generated from:
    external/stablehlo/stablehlo/transforms/StablehloLegalizeDeprecatedOpsPatterns.td:38
*/
struct BroadcastToBroadcastInDim : public ::mlir::RewritePattern {
  BroadcastToBroadcastInDim(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.broadcast", 1, context, {"stablehlo.broadcast_in_dim"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::BroadcastOp result;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::DenseI64ArrayAttr broadcast_sizes;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::BroadcastOp>(op0); (void)castedOp0;
    result = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBroadcastSizes();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.broadcast' to have attribute 'broadcast_sizes' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      broadcast_sizes = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getBroadcastDimensionsFromBroadcastSizes(cast<RankedTensorType>((*result.getODSResults(0).begin()).getType()), cast<DenseI64ArrayAttr>(broadcast_sizes)); (void)nativeVar_0;
    ::mlir::stablehlo::BroadcastInDimOp tblgen_BroadcastInDimOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::BroadcastInDimOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastInDimOp_1 = ::mlir::stablehlo::BroadcastInDimOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastInDimOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/StablehloLegalizeDeprecatedOpsPatterns.td:42
*/
struct CreateTokenToAfterAll : public ::mlir::RewritePattern {
  CreateTokenToAfterAll(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.create_token", 1, context, {"stablehlo.after_all"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::CreateTokenOp>(op0); (void)castedOp0;

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ValueRange{}; (void)nativeVar_0;
    ::mlir::stablehlo::AfterAllOp tblgen_AfterAllOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::AfterAllOp::Properties tblgen_props; (void)tblgen_props;
      for (auto v: nativeVar_0) {
        tblgen_values.push_back(v);
      }
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AfterAllOp_1 = ::mlir::stablehlo::AfterAllOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AfterAllOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/StablehloLegalizeDeprecatedOpsPatterns.td:48
*/
struct DotToDotGeneral : public ::mlir::RewritePattern {
  DotToDotGeneral(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.dot", 1, context, {"stablehlo.dot_general"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ArrayAttr precision_config;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::DotOp>(op0); (void)castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getPrecisionConfig();
      precision_config = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getDefaultDotDimensionNumbers((*lhs.begin())); (void)nativeVar_0;
    auto nativeVar_1 = Attribute{}; (void)nativeVar_1;
    ::mlir::stablehlo::DotGeneralOp tblgen_DotGeneralOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DotGeneralOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*lhs.begin()));
      tblgen_values.push_back((*rhs.begin()));
      tblgen_props.dot_dimension_numbers = ::llvm::dyn_cast_if_present<decltype(tblgen_props.dot_dimension_numbers)>(nativeVar_0);
      tblgen_props.precision_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.precision_config)>(precision_config);
      tblgen_props.algorithm = ::llvm::dyn_cast_if_present<decltype(tblgen_props.algorithm)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DotGeneralOp_2 = ::mlir::stablehlo::DotGeneralOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DotGeneralOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/StablehloLegalizeDeprecatedOpsPatterns.td:52
*/
struct UnaryEinsumToEinsum : public ::mlir::RewritePattern {
  UnaryEinsumToEinsum(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.unary_einsum", 1, context, {"stablehlo.constant", "stablehlo.einsum"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::StringAttr equation;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::UnaryEinsumOp>(op0); (void)castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getEinsumConfig();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.unary_einsum' to have attribute 'einsum_config' of type '::mlir::StringAttr'";
        });
      }
      equation = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getScalarOfType(getElementTypeOrSelf((*operand.begin())),1); (void)nativeVar_0;
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_1;
    {
      tblgen_ConstantOp_1 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    auto nativeVar_2 = rewriter.getStringAttr("," + equation.getValue().str()); (void)nativeVar_2;
    ::mlir::stablehlo::EinsumOp tblgen_EinsumOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::EinsumOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_ConstantOp_1.getODSResults(0).begin()));
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.einsum_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.einsum_config)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_EinsumOp_3 = ::mlir::stablehlo::EinsumOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_EinsumOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<BroadcastToBroadcastInDim>(patterns.getContext());
  patterns.add<CreateTokenToAfterAll>(patterns.getContext());
  patterns.add<DotToDotGeneral>(patterns.getContext());
  patterns.add<UnaryEinsumToEinsum>(patterns.getContext());
}
