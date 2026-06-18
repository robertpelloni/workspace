/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: tf_data_optimization.td                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

/* Generated from:
    tensorflow/compiler/mlir/tensorflow/transforms/tf_data_optimization.td:24
*/
struct FuseMapAndBatch : public ::mlir::RewritePattern {
  FuseMapAndBatch(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.BatchDatasetV2", 2, context, {"tf.Const", "tf.MapAndBatchDataset"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range drop_remainder(op0->getOperands());
    ::mlir::Operation::operand_range input_dataset(op0->getOperands());
    ::mlir::ArrayAttr output_types;
    ::mlir::Operation::operand_range other_arguments(op0->getOperands());
    ::mlir::SymbolRefAttr f;
    ::mlir::ArrayAttr output_shapes;
    ::mlir::BoolAttr use_inter_op_parallelism;
    ::mlir::BoolAttr force_synchronous;
    ::mlir::BoolAttr preserve_cardinality;
    ::mlir::StringAttr map_dataset_metadata;
    ::mlir::Operation::operand_range batch_size(op0->getOperands());
    ::mlir::BoolAttr parallel_copy;
    ::mlir::ArrayAttr batch_output_types;
    ::mlir::ArrayAttr batch_output_shapes;
    ::mlir::StringAttr unused_batch_dataset_metadata;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::BatchDatasetV2Op>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::TF::MapDatasetOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::TF::MapDatasetOp type";
        });
      }
      input_dataset = castedOp1.getODSOperands(0);
      other_arguments = castedOp1.getODSOperands(1);
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getF();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'tf.MapDataset' to have attribute 'f' of type '::mlir::SymbolRefAttr'";
          });
        }
        f = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getOutputTypes();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'tf.MapDataset' to have attribute 'output_types' of type '::mlir::ArrayAttr'";
          });
        }
        output_types = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getOutputShapes();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'tf.MapDataset' to have attribute 'output_shapes' of type '::mlir::ArrayAttr'";
          });
        }
        output_shapes = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getUseInterOpParallelism();
        if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(true);
        use_inter_op_parallelism = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getPreserveCardinality();
        if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
        preserve_cardinality = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getForceSynchronous();
        if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
        force_synchronous = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getMetadata();
        if (!tblgen_attr) tblgen_attr = rewriter.getStringAttr("");
        map_dataset_metadata = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    batch_size = castedOp0.getODSOperands(1);
    drop_remainder = castedOp0.getODSOperands(2);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getParallelCopy();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      parallel_copy = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOutputTypes();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.BatchDatasetV2' to have attribute 'output_types' of type '::mlir::ArrayAttr'";
        });
      }
      batch_output_types = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getOutputShapes();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.BatchDatasetV2' to have attribute 'output_shapes' of type '::mlir::ArrayAttr'";
        });
      }
      batch_output_shapes = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getMetadata();
      if (!tblgen_attr) tblgen_attr = rewriter.getStringAttr("");
      unused_batch_dataset_metadata = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = DenseElementsAttr::get<int64_t>(RankedTensorType::get({}, rewriter.getIntegerType(64)), 1); (void)nativeVar_0;
    ::mlir::TF::ConstOp tblgen_ConstOp_1;
    {
      tblgen_ConstOp_1 = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    ::mlir::TF::MapAndBatchDatasetOp tblgen_MapAndBatchDatasetOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::MapAndBatchDatasetOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input_dataset.begin()));
      for (auto v: other_arguments) {
        tblgen_values.push_back(v);
      }
      tblgen_values.push_back((*batch_size.begin()));
      tblgen_values.push_back((*tblgen_ConstOp_1.getODSResults(0).begin()));
      tblgen_values.push_back((*drop_remainder.begin()));
      tblgen_props.f = ::llvm::dyn_cast_if_present<decltype(tblgen_props.f)>(f);
      tblgen_props.output_types = ::llvm::dyn_cast_if_present<decltype(tblgen_props.output_types)>(batch_output_types);
      tblgen_props.output_shapes = ::llvm::dyn_cast_if_present<decltype(tblgen_props.output_shapes)>(batch_output_shapes);
      tblgen_props.preserve_cardinality = ::llvm::dyn_cast_if_present<decltype(tblgen_props.preserve_cardinality)>(preserve_cardinality);
      tblgen_props.metadata = ::llvm::dyn_cast_if_present<decltype(tblgen_props.metadata)>(map_dataset_metadata);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_MapAndBatchDatasetOp_2 = ::mlir::TF::MapAndBatchDatasetOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_MapAndBatchDatasetOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<FuseMapAndBatch>(patterns.getContext());
}
