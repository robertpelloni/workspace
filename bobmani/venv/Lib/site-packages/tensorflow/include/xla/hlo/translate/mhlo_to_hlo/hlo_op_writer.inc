/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* MLIR XLA Builders                                                          *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

mlir::LogicalResult ExportXlaOp(::mlir::mhlo::ErfOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Erf(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::AbsOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Abs(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::AddOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Add(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::AfterAllOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  std::vector<xla::XlaOp> xla_arg_0;
  for (auto operand : op.getODSOperands(0)) {
    xla::XlaOp result;
    if (failed(GetXlaOp(operand, value_map, &result, op)))
      return mlir::failure();
    xla_arg_0.push_back(result);
  }
  auto xla_result = xla::AfterAll(ctx.builder, Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::AndOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::And(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::Atan2Op op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Atan2(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::BatchNormInferenceOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_2;
  if (failed(GetXlaOp(*op.getODSOperands(2).begin(), value_map, &xla_arg_2, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_3;
  if (failed(GetXlaOp(*op.getODSOperands(3).begin(), value_map, &xla_arg_3, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_4;
  if (failed(GetXlaOp(*op.getODSOperands(4).begin(), value_map, &xla_arg_4, op)))
    return mlir::failure();
  auto xla_arg_5 = ConvertAPFloat(op.getEpsilon());
  auto xla_arg_6 = Convertuint64_t(op.getFeatureIndex());
  auto xla_result = xla::BatchNormInference(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2), Unwrap(xla_arg_3), Unwrap(xla_arg_4), Unwrap(xla_arg_5), Unwrap(xla_arg_6));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::BroadcastOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_broadcast_sizes(op.getBroadcastSizes());
  auto xla_result = xla::Broadcast(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::CbrtOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_result_accuracy(op.getResultAccuracy());
  auto xla_result = xla::Cbrt(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::CeilOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Ceil(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::CholeskyOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convertbool(op.getLower());
  auto xla_result = xla::Cholesky(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ClampOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_2;
  if (failed(GetXlaOp(*op.getODSOperands(2).begin(), value_map, &xla_arg_2, op)))
    return mlir::failure();
  auto xla_result = xla::Clamp(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ClzOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Clz(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::CollectivePermuteOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_source_target_pairs(op.getSourceTargetPairs());
  auto xla_arg_2 = Convert_channel_handle(op.getChannelHandle());
  auto xla_result = xla::CollectivePermute(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ComplexOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Complex(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ConcatenateOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  std::vector<xla::XlaOp> xla_arg_0;
  for (auto operand : op.getODSOperands(0)) {
    xla::XlaOp result;
    if (failed(GetXlaOp(operand, value_map, &result, op)))
      return mlir::failure();
    xla_arg_0.push_back(result);
  }
  auto xla_arg_1 = Convertuint64_t(op.getDimension());
  auto xla_result = xla::ConcatInDim(ctx.builder, Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::CreateTokenOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  auto xla_result = xla::CreateToken(ctx.builder);
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::CrossReplicaSumOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_replica_groups(op.getReplicaGroups());
  auto xla_result = xla::CrossReplicaSum(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::DivOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Div(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::DynamicSliceOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  std::vector<xla::XlaOp> xla_arg_1;
  for (auto operand : op.getODSOperands(1)) {
    xla::XlaOp result;
    if (failed(GetXlaOp(operand, value_map, &result, op)))
      return mlir::failure();
    xla_arg_1.push_back(result);
  }
  auto xla_arg_2 = Convert_slice_sizes(op.getSliceSizes());
  auto xla_result = xla::DynamicSlice(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::DynamicUpdateSliceOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  std::vector<xla::XlaOp> xla_arg_2;
  for (auto operand : op.getODSOperands(2)) {
    xla::XlaOp result;
    if (failed(GetXlaOp(operand, value_map, &result, op)))
      return mlir::failure();
    xla_arg_2.push_back(result);
  }
  auto xla_result = xla::DynamicUpdateSlice(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::EinsumOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_arg_2 = ConvertStringRef(op.getEinsumConfig());
  auto xla_result = xla::Einsum(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ExpOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_result_accuracy(op.getResultAccuracy());
  auto xla_result = xla::Exp(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::Expm1Op op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_result_accuracy(op.getResultAccuracy());
  auto xla_result = xla::Expm1(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::FftOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_fft_type(op.getFftType());
  auto xla_arg_2 = Convert_fft_length(op.getFftLength());
  auto xla_result = xla::Fft(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::FloorOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Floor(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::GatherOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_arg_2 = Convert_dimension_numbers(op.getDimensionNumbers());
  auto xla_arg_3 = Convert_slice_sizes(op.getSliceSizes());
  auto xla_arg_4 = Convertbool(op.getIndicesAreSorted());
  auto xla_result = xla::Gather(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2), Unwrap(xla_arg_3), Unwrap(xla_arg_4));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::GetDimensionSizeOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convertuint64_t(op.getDimension());
  auto xla_result = xla::GetDimensionSize(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::GetTupleElementOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convertuint32_t(op.getIndex());
  auto xla_result = xla::GetTupleElement(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ImagOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Imag(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::IsFiniteOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::IsFinite(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::Log1pOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_result_accuracy(op.getResultAccuracy());
  auto xla_result = xla::Log1p(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::LogOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_result_accuracy(op.getResultAccuracy());
  auto xla_result = xla::Log(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::LogisticOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_result_accuracy(op.getResultAccuracy());
  auto xla_result = xla::Logistic(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::MaxOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Max(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::MinOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Min(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::MulOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Mul(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::NegOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Neg(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::NotOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Not(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::OrOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Or(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::PopulationCountOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::PopulationCount(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::PowOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Pow(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::RealOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Real(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ReducePrecisionOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convertuint32_t(op.getExponentBits());
  auto xla_arg_2 = Convertuint32_t(op.getMantissaBits());
  auto xla_result = xla::ReducePrecision(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::RemOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Rem(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ReplicaIdOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  auto xla_result = xla::ReplicaId(ctx.builder);
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ReverseOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_dimensions(op.getDimensions());
  auto xla_result = xla::Rev(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::RoundNearestEvenOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::RoundNearestEven(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::RoundOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Round(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::RsqrtOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_result_accuracy(op.getResultAccuracy());
  auto xla_result = xla::Rsqrt(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::SelectOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_2;
  if (failed(GetXlaOp(*op.getODSOperands(2).begin(), value_map, &xla_arg_2, op)))
    return mlir::failure();
  auto xla_result = xla::Select(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ShiftLeftOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::ShiftLeft(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ShiftRightArithmeticOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::ShiftRightArithmetic(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::ShiftRightLogicalOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::ShiftRightLogical(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::SignOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_result = xla::Sign(Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::SliceOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_start_indices(op.getStartIndices());
  auto xla_arg_2 = Convert_limit_indices(op.getLimitIndices());
  auto xla_arg_3 = Convert_strides(op.getStrides());
  auto xla_result = xla::Slice(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2), Unwrap(xla_arg_3));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::SqrtOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_result_accuracy(op.getResultAccuracy());
  auto xla_result = xla::Sqrt(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::TanhOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_result_accuracy(op.getResultAccuracy());
  auto xla_result = xla::Tanh(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::TorchIndexSelectOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_arg_2 = Convertuint64_t(op.getDim());
  auto xla_arg_3 = Convertuint64_t(op.getBatchDims());
  auto xla_result = xla::TorchIndexSelect(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2), Unwrap(xla_arg_3));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::TransposeOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  auto xla_arg_1 = Convert_permutation(op.getPermutation());
  auto xla_result = xla::Transpose(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::TriangularSolveOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_arg_2 = Convertbool(op.getLeftSide());
  auto xla_arg_3 = Convertbool(op.getLower());
  auto xla_arg_4 = Convertbool(op.getUnitDiagonal());
  auto xla_arg_5 = Convert_transpose_a(op.getTransposeA());
  auto xla_result = xla::TriangularSolve(Unwrap(xla_arg_0), Unwrap(xla_arg_1), Unwrap(xla_arg_2), Unwrap(xla_arg_3), Unwrap(xla_arg_4), Unwrap(xla_arg_5));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::TupleOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  std::vector<xla::XlaOp> xla_arg_0;
  for (auto operand : op.getODSOperands(0)) {
    xla::XlaOp result;
    if (failed(GetXlaOp(operand, value_map, &result, op)))
      return mlir::failure();
    xla_arg_0.push_back(result);
  }
  auto xla_result = xla::Tuple(ctx.builder, Unwrap(xla_arg_0));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOp(::mlir::stablehlo::XorOp op, OpLoweringContext ctx) {
  auto& value_map = *ctx.values;
  auto result = op.getResult();
  xla::XlaOp xla_arg_0;
  if (failed(GetXlaOp(*op.getODSOperands(0).begin(), value_map, &xla_arg_0, op)))
    return mlir::failure();
  xla::XlaOp xla_arg_1;
  if (failed(GetXlaOp(*op.getODSOperands(1).begin(), value_map, &xla_arg_1, op)))
    return mlir::failure();
  auto xla_result = xla::Xor(Unwrap(xla_arg_0), Unwrap(xla_arg_1));
  value_map[result] = xla_result;
  return mlir::success();
}
mlir::LogicalResult ExportXlaOperator(
mlir::Operation* op, OpLoweringContext lowering_context) {

  xla::XlaScopedShardingAssignment sharding(lowering_context.builder, CreateOpShardingFromAttribute(op));

  xla::XlaScopedFrontendAttributesAssignment frontend_attributes(lowering_context.builder, CreateXlaFrontendAttributesFromOp(op));

  xla::XlaScopedOpMetadataAssignment op_metadata(lowering_context.builder, mlir::mhlo::CreateOpMetadataFromLocation(op, lowering_context.frame_index_builder));

  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::AcosOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::AcoshOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::AddDependencyOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::AllToAllOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::AsinOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::AsinhOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::AsyncDoneOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::AsyncStartOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::AsyncUpdateOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::AtanhOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::BitcastOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::CopyOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::CoshOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::CustomCallOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::DomainOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::ErfOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::FusionOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::MinimumBroadcastShapesOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::RaggedDotOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::ScanOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::SinhOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::StochasticConvertOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::TopKOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::TraceOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::mhlo::XlaRngGetAndUpdateStateOp>(op)) {
    return ::mlir::mhlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::AbsOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::AddOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::AfterAllOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::AllGatherOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::AllReduceOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::AllToAllOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::AndOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::Atan2Op>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::BatchNormGradOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::BatchNormInferenceOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::BatchNormTrainingOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::BitcastConvertOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::BroadcastInDimOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::BroadcastOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CaseOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CbrtOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CeilOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CholeskyOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ClampOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ClzOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CollectiveBroadcastOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CollectivePermuteOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CompareOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ComplexOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CompositeOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ConcatenateOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ConstantOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ConvertOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ConvolutionOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CosineOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CreateTokenOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CrossReplicaSumOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::CustomCallOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DivOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DotGeneralOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DotOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DynamicBroadcastInDimOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DynamicConvOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DynamicGatherOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DynamicIotaOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DynamicPadOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DynamicReshapeOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DynamicSliceOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::DynamicUpdateSliceOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::EinsumOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ExpOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::Expm1Op>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::FftOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::FloorOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::GatherOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::GetDimensionSizeOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::GetTupleElementOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::IfOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ImagOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::InfeedOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::IotaOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::IsFiniteOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::Log1pOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::LogOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::LogisticOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::MapOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::MaxOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::MinOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::MulOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::NegOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::NotOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::OptimizationBarrierOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::OrOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::OutfeedOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::PadOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::PartitionIdOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::PopulationCountOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::PowOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::RealDynamicSliceOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::RealOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::RecvOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ReduceOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ReducePrecisionOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ReduceScatterOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ReduceWindowOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::RemOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ReplicaIdOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ReshapeOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ReturnOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ReverseOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::RngBitGeneratorOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::RngOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::RoundNearestEvenOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::RoundOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::RsqrtOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ScatterOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::SelectAndScatterOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::SelectOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::SendOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::SetDimensionSizeOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ShiftLeftOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ShiftRightArithmeticOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::ShiftRightLogicalOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::SignOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::SineOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::SliceOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::SortOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::SqrtOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::SubtractOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::TanOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::TanhOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::TorchIndexSelectOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::TransposeOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::TriangularSolveOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::TupleOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::UnaryEinsumOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::UniformDequantizeOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::UniformQuantizeOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::WhileOp>(op)) {
    return ::mlir::stablehlo::ExportXlaOp(xla_op, lowering_context);
  }
  if (auto xla_op = llvm::dyn_cast<::mlir::stablehlo::XorOp>(op)) {
    return ExportXlaOp(xla_op, lowering_context);
  }
  return mlir::failure();
}
