/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: mhlo_canonicalize.td                                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_mhlo_canonicalize1(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!(((::llvm::isa<::mlir::DenseIntElementsAttr>(attr))) && ((true)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": integer elements attribute";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_mhlo_canonicalize2(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((hlo::isSequenceStartingWith0(attr)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": ";
    });
  }
  return ::mlir::success();
}
/* Generated from:
    external/xla/xla/mlir_hlo/mhlo/IR/mhlo_canonicalize.td:47
*/
struct DPadToPad : public ::mlir::RewritePattern {
  DPadToPad(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("mhlo.dynamic_pad", 1, context, {"mhlo.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Attribute edge_padding_high;
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::mlir::Operation::operand_range padding_value(op0->getOperands());
    ::mlir::Attribute interior_padding;
    ::mlir::Attribute edge_padding_low;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::mhlo::DynamicPadOp>(op0); (void)castedOp0;
    input = castedOp0.getODSOperands(0);
    padding_value = castedOp0.getODSOperands(1);
    {
      auto *op1 = (*castedOp0.getODSOperands(2).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 2 of castedOp0";
        });
      }
        ::mlir::Attribute arg1_0;
        if (!(!::mlir::failed(::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0)))))){
          return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
            diag << "::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0))) return ::mlir::failure";
          });
        }
        edge_padding_low = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_mhlo_canonicalize1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'integer elements attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }
    {
      auto *op1 = (*castedOp0.getODSOperands(3).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 3 of castedOp0";
        });
      }
        ::mlir::Attribute arg1_0;
        if (!(!::mlir::failed(::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0)))))){
          return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
            diag << "::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0))) return ::mlir::failure";
          });
        }
        edge_padding_high = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_mhlo_canonicalize1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'integer elements attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }
    {
      auto *op1 = (*castedOp0.getODSOperands(4).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 4 of castedOp0";
        });
      }
        ::mlir::Attribute arg1_0;
        if (!(!::mlir::failed(::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0)))))){
          return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
            diag << "::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0))) return ::mlir::failure";
          });
        }
        interior_padding = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_mhlo_canonicalize1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'integer elements attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = cast<DenseIntElementsAttr>(edge_padding_low); (void)nativeVar_0;
    auto nativeVar_1 = nativeVar_0.mapValues(rewriter.getI64Type(), [](llvm::APInt x) { return x.sext(64); }); (void)nativeVar_1;
    auto nativeVar_2 = cast<DenseIntElementsAttr>(edge_padding_high); (void)nativeVar_2;
    auto nativeVar_3 = nativeVar_2.mapValues(rewriter.getI64Type(), [](llvm::APInt x) { return x.sext(64); }); (void)nativeVar_3;
    auto nativeVar_4 = cast<DenseIntElementsAttr>(interior_padding); (void)nativeVar_4;
    auto nativeVar_5 = nativeVar_4.mapValues(rewriter.getI64Type(), [](llvm::APInt x) { return x.sext(64); }); (void)nativeVar_5;
    ::mlir::mhlo::PadOp tblgen_PadOp_6;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::mhlo::PadOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_values.push_back((*padding_value.begin()));
      tblgen_props.edge_padding_low = ::llvm::dyn_cast_if_present<decltype(tblgen_props.edge_padding_low)>(nativeVar_1);
      tblgen_props.edge_padding_high = ::llvm::dyn_cast_if_present<decltype(tblgen_props.edge_padding_high)>(nativeVar_3);
      tblgen_props.interior_padding = ::llvm::dyn_cast_if_present<decltype(tblgen_props.interior_padding)>(nativeVar_5);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_PadOp_6 = ::mlir::mhlo::PadOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_PadOp_6.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/xla/xla/mlir_hlo/mhlo/IR/mhlo_canonicalize.td:60
*/
struct RealDSliceToSlice : public ::mlir::RewritePattern {
  RealDSliceToSlice(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("mhlo.real_dynamic_slice", 1, context, {"mhlo.slice"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Attribute limit_indices;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute start_indices;
    ::mlir::Attribute strides;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::mhlo::RealDynamicSliceOp>(op0); (void)castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
        ::mlir::Attribute arg1_0;
        if (!(!::mlir::failed(::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0)))))){
          return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
            diag << "::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0))) return ::mlir::failure";
          });
        }
        start_indices = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_mhlo_canonicalize1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'integer elements attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }
    {
      auto *op1 = (*castedOp0.getODSOperands(2).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 2 of castedOp0";
        });
      }
        ::mlir::Attribute arg1_0;
        if (!(!::mlir::failed(::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0)))))){
          return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
            diag << "::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0))) return ::mlir::failure";
          });
        }
        limit_indices = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_mhlo_canonicalize1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'integer elements attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }
    {
      auto *op1 = (*castedOp0.getODSOperands(3).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 3 of castedOp0";
        });
      }
        ::mlir::Attribute arg1_0;
        if (!(!::mlir::failed(::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0)))))){
          return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
            diag << "::mlir::success(::mlir::matchPattern(op1->getResult(0), ::mlir::m_Constant(&arg1_0))) return ::mlir::failure";
          });
        }
        strides = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_mhlo_canonicalize1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'integer elements attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = cast<DenseIntElementsAttr>(start_indices); (void)nativeVar_0;
    auto nativeVar_1 = nativeVar_0.mapValues(rewriter.getI64Type(), [](llvm::APInt x) { return x.sext(64); }); (void)nativeVar_1;
    auto nativeVar_2 = cast<DenseIntElementsAttr>(limit_indices); (void)nativeVar_2;
    auto nativeVar_3 = nativeVar_2.mapValues(rewriter.getI64Type(), [](llvm::APInt x) { return x.sext(64); }); (void)nativeVar_3;
    auto nativeVar_4 = cast<DenseIntElementsAttr>(strides); (void)nativeVar_4;
    auto nativeVar_5 = nativeVar_4.mapValues(rewriter.getI64Type(), [](llvm::APInt x) { return x.sext(64); }); (void)nativeVar_5;
    ::mlir::mhlo::SliceOp tblgen_SliceOp_6;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::mhlo::SliceOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.start_indices = ::llvm::dyn_cast_if_present<decltype(tblgen_props.start_indices)>(nativeVar_1);
      tblgen_props.limit_indices = ::llvm::dyn_cast_if_present<decltype(tblgen_props.limit_indices)>(nativeVar_3);
      tblgen_props.strides = ::llvm::dyn_cast_if_present<decltype(tblgen_props.strides)>(nativeVar_5);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SliceOp_6 = ::mlir::mhlo::SliceOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SliceOp_6.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/xla/xla/mlir_hlo/mhlo/IR/mhlo_canonicalize.td:35
*/
struct RemoveRedundantDynamicBroadcast : public ::mlir::RewritePattern {
  RemoveRedundantDynamicBroadcast(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("mhlo.dynamic_broadcast_in_dim", 2, context, {"mhlo.dynamic_reshape"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range shape(op0->getOperands());
    ::mlir::Operation::operand_range shape0(op0->getOperands());
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::DenseIntElementsAttr known_expanding_dimensions;
    ::mlir::DenseIntElementsAttr known_nonexpanding_dimensions;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::mhlo::DynamicBroadcastInDimOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::mhlo::DynamicReshapeOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::mhlo::DynamicReshapeOp type";
        });
      }
      operand = castedOp1.getODSOperands(0);
      shape = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }
    shape0 = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBroadcastDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'mhlo.dynamic_broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseIntElementsAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_mhlo_canonicalize2(rewriter, castedOp0, tblgen_attr, "op 'mhlo.dynamic_broadcast_in_dim' attribute 'broadcast_dimensions' failed to satisfy constraint: ''"))) {
        return ::mlir::failure();
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKnownExpandingDimensions();
      known_expanding_dimensions = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKnownNonexpandingDimensions();
      known_nonexpanding_dimensions = tblgen_attr;
    }
    if (!(*shape.begin() == *shape0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'shape' and 'shape0' must be equal";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::mhlo::DynamicReshapeOp tblgen_DynamicReshapeOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::mhlo::DynamicReshapeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*shape.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DynamicReshapeOp_0 = ::mlir::mhlo::DynamicReshapeOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DynamicReshapeOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/xla/xla/mlir_hlo/mhlo/IR/mhlo_canonicalize.td:29
*/
struct RemoveRedundantDynamicReshape : public ::mlir::RewritePattern {
  RemoveRedundantDynamicReshape(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("mhlo.dynamic_reshape", 2, context, {"mhlo.dynamic_reshape"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Operation::operand_range shape1(op0->getOperands());
    ::mlir::Operation::operand_range shape2(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::mhlo::DynamicReshapeOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::mhlo::DynamicReshapeOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::mhlo::DynamicReshapeOp type";
        });
      }
      operand = castedOp1.getODSOperands(0);
      shape1 = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }
    shape2 = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::mhlo::DynamicReshapeOp tblgen_DynamicReshapeOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::mhlo::DynamicReshapeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*shape2.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DynamicReshapeOp_0 = ::mlir::mhlo::DynamicReshapeOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DynamicReshapeOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<DPadToPad>(patterns.getContext());
  patterns.add<RealDSliceToSlice>(patterns.getContext());
  patterns.add<RemoveRedundantDynamicBroadcast>(patterns.getContext());
  patterns.add<RemoveRedundantDynamicReshape>(patterns.getContext());
}
