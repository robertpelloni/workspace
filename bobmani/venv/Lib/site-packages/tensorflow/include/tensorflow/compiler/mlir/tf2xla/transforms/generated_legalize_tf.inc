/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: legalize_tf_patterns.td                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_legalize_tf_patterns1(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Type type,
    ::llvm::StringRef failureStr) {
  if (!(((::llvm::isa<::mlir::RankedTensorType>(type))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": ranked tensor of any type values";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_legalize_tf_patterns2(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Type type,
    ::llvm::StringRef failureStr) {
  if (!(((::llvm::isa<::mlir::TensorType>(type))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": tensor of any type values";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_legalize_tf_patterns3(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Type type,
    ::llvm::StringRef failureStr) {
  if (!((((::llvm::isa<::mlir::RankedTensorType>(type))) && ((::llvm::cast<::mlir::ShapedType>(type).hasStaticShape()))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": statically shaped tensor of any type values";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_legalize_tf_patterns4(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Type type,
    ::llvm::StringRef failureStr) {
  if (!(((::llvm::isa<::mlir::RankedTensorType>(type))) && ([](::mlir::Type elementType) { return (((::llvm::isa<::mlir::Float4E2M1FNType>(elementType))) || ((::llvm::isa<::mlir::Float6E2M3FNType>(elementType))) || ((::llvm::isa<::mlir::Float6E3M2FNType>(elementType))) || ((::llvm::isa<::mlir::Float8E3M4Type>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3Type>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3FNType>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3B11FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E5M2Type>(elementType))) || ((::llvm::isa<::mlir::Float8E5M2FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E8M0FNUType>(elementType))) || ((elementType.isF16())) || ((elementType.isF32())) || ((elementType.isF64())) || ((::llvm::isa<::mlir::BFloat16Type>(elementType)))) || ((elementType.isSignlessInteger(1))) || ((((elementType.isSignlessInteger(2))) || ((elementType.isSignlessInteger(4))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64)))) || (((elementType.isUnsignedInteger(2))) || ((elementType.isUnsignedInteger(4))) || ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))))) || (((::llvm::isa<::mlir::ComplexType>(elementType))) && (((::llvm::cast<::mlir::ComplexType>(elementType).getElementType().isF32())) || ((::llvm::cast<::mlir::ComplexType>(elementType).getElementType().isF64())))) || (((((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 2)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 4)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 8)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 16)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 32)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType))))) || ((((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 2)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 4)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 8)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 16)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 32)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))))); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_legalize_tf_patterns5(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Type type,
    ::llvm::StringRef failureStr) {
  if (!((((::llvm::isa<::mlir::TensorType>(type))) && ((mlir::hlo::isValidQuantizedDimension(type)))) && ([](::mlir::Type elementType) { return (((::llvm::isa<::mlir::Float4E2M1FNType>(elementType))) || ((::llvm::isa<::mlir::Float6E2M3FNType>(elementType))) || ((::llvm::isa<::mlir::Float6E3M2FNType>(elementType))) || ((::llvm::isa<::mlir::Float8E3M4Type>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3Type>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3FNType>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3B11FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E5M2Type>(elementType))) || ((::llvm::isa<::mlir::Float8E5M2FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E8M0FNUType>(elementType))) || ((elementType.isF16())) || ((elementType.isF32())) || ((elementType.isF64())) || ((::llvm::isa<::mlir::BFloat16Type>(elementType)))) || ((elementType.isSignlessInteger(1))) || ((((elementType.isSignlessInteger(2))) || ((elementType.isSignlessInteger(4))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64)))) || (((elementType.isUnsignedInteger(2))) || ((elementType.isUnsignedInteger(4))) || ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))))) || (((::llvm::isa<::mlir::ComplexType>(elementType))) && (((::llvm::cast<::mlir::ComplexType>(elementType).getElementType().isF32())) || ((::llvm::cast<::mlir::ComplexType>(elementType).getElementType().isF64())))) || (((((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 2)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 4)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 8)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 16)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 32)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType))))) || ((((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 2)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 4)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 8)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 16)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 32)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))))) || (((((::llvm::isa<::mlir::quant::UniformQuantizedPerAxisType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageTypeIntegralWidth() == 2)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedPerAxisType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageTypeIntegralWidth() == 4)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedPerAxisType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageTypeIntegralWidth() == 8)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedPerAxisType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageTypeIntegralWidth() == 16)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedPerAxisType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageTypeIntegralWidth() == 32)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType))))) || ((((::llvm::isa<::mlir::quant::UniformQuantizedPerAxisType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageTypeIntegralWidth() == 2)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedPerAxisType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageTypeIntegralWidth() == 4)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedPerAxisType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageTypeIntegralWidth() == 8)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedPerAxisType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageTypeIntegralWidth() == 16)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedPerAxisType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).getStorageTypeIntegralWidth() == 32)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedPerAxisType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))))); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_legalize_tf_patterns1(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((::llvm::isa<::mlir::ElementsAttr>(attr)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": constant vector/tensor attribute";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_legalize_tf_patterns2(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((llvm::cast<BoolAttr>(attr).getValue()))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": ";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_legalize_tf_patterns3(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!(((::llvm::isa<::mlir::ElementsAttr>(attr))) && ((llvm::cast<ElementsAttr>(attr).getShapedType().getNumElements() == 1)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": Scalar ElementsAttr";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_legalize_tf_patterns4(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64))))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": 64-bit signless integer attribute";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_legalize_tf_patterns5(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((true))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": any attribute";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_legalize_tf_patterns6(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": flat symbol reference attribute";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_legalize_tf_patterns7(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((attr == rewriter.getBoolAttr(false)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": constant attribute false";
    });
  }
  return ::mlir::success();
}
static ::llvm::LogicalResult static_dag_matcher_0(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Attribute &axis) {
  (void)tblgen_ops;
    ::mlir::Attribute arg1_0;
    if (!(!::mlir::failed(::mlir::success(::mlir::matchPattern(op0->getResult(0), ::mlir::m_Constant(&arg1_0)))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "::mlir::success(::mlir::matchPattern(op0->getResult(0), ::mlir::m_Constant(&arg1_0))) return ::mlir::failure";
      });
    }
    axis = arg1_0;
    if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns1(rewriter, op0, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'constant vector/tensor attribute'"))) {
      return ::mlir::failure();
    }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_1(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &l, ::mlir::Operation::operand_range &r) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::mlir::TF::RightShiftOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::mlir::TF::RightShiftOp type";
    });
  }
  if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp1, (*castedOp1.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.RightShift' failed to satisfy constraint: 'tensor of any type values'"))) {
    return ::mlir::failure();
  }
  l = castedOp1.getODSOperands(0);
  if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp1, (*castedOp1.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.RightShift' failed to satisfy constraint: 'tensor of any type values'"))) {
    return ::mlir::failure();
  }
  r = castedOp1.getODSOperands(1);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_2(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &l, ::mlir::Operation::operand_range &r) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::mlir::TF::FloorDivOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::mlir::TF::FloorDivOp type";
    });
  }
  if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp1, (*castedOp1.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.FloorDiv' failed to satisfy constraint: 'tensor of any type values'"))) {
    return ::mlir::failure();
  }
  l = castedOp1.getODSOperands(0);
  if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp1, (*castedOp1.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.FloorDiv' failed to satisfy constraint: 'tensor of any type values'"))) {
    return ::mlir::failure();
  }
  r = castedOp1.getODSOperands(1);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_3(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &l, ::mlir::Operation::operand_range &r) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::mlir::TF::FloorModOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::mlir::TF::FloorModOp type";
    });
  }
  if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp1, (*castedOp1.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.FloorMod' failed to satisfy constraint: 'tensor of any type values'"))) {
    return ::mlir::failure();
  }
  l = castedOp1.getODSOperands(0);
  if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp1, (*castedOp1.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.FloorMod' failed to satisfy constraint: 'tensor of any type values'"))) {
    return ::mlir::failure();
  }
  r = castedOp1.getODSOperands(1);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_4(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Attribute &group_assignment) {
  (void)tblgen_ops;
    ::mlir::Attribute arg1_0;
    if (!(!::mlir::failed(::mlir::success(::mlir::matchPattern(op0->getResult(0), ::mlir::m_Constant(&arg1_0)))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "::mlir::success(::mlir::matchPattern(op0->getResult(0), ::mlir::m_Constant(&arg1_0))) return ::mlir::failure";
      });
    }
    group_assignment = arg1_0;
    if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns1(rewriter, op0, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'constant vector/tensor attribute'"))) {
      return ::mlir::failure();
    }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_5(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Attribute &slice_sizes) {
  (void)tblgen_ops;
    ::mlir::Attribute arg1_0;
    if (!(!::mlir::failed(::mlir::success(::mlir::matchPattern(op0->getResult(0), ::mlir::m_Constant(&arg1_0)))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "::mlir::success(::mlir::matchPattern(op0->getResult(0), ::mlir::m_Constant(&arg1_0))) return ::mlir::failure";
      });
    }
    slice_sizes = arg1_0;
    if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns5(rewriter, op0, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'any attribute'"))) {
      return ::mlir::failure();
    }
  return ::mlir::success();
}

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:363
*/
struct LegalizeGatherV2 : public ::mlir::RewritePattern {
  LegalizeGatherV2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.GatherV2", 1, context, {"stablehlo.torch_index_select"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr batch_dims;
    ::mlir::Operation::operand_range params(op0->getOperands());
    ::mlir::Operation::operand_range indices(op0->getOperands());
    ::mlir::Attribute axis;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::GatherV2Op>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.GatherV2' failed to satisfy constraint: 'ranked tensor of any type values'"))) {
      return ::mlir::failure();
    }
    params = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.GatherV2' failed to satisfy constraint: 'ranked tensor of any type values'"))) {
      return ::mlir::failure();
    }
    indices = castedOp0.getODSOperands(1);
    {
      auto *op1 = (*castedOp0.getODSOperands(2).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 2 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, axis))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBatchDims();
      if (!tblgen_attr) tblgen_attr = rewriter.getIntegerAttr(rewriter.getIntegerType(64), 0);
      batch_dims = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = GetHLOAxisFromTFAxis(axis, llvm::cast<RankedTensorType>((*params.begin()).getType()).getRank(), &rewriter); (void)nativeVar_0;
    auto nativeVar_1 = GetHLOAxisFromTFAxis(batch_dims, llvm::cast<RankedTensorType>((*indices.begin()).getType()).getRank(), &rewriter); (void)nativeVar_1;
    ::mlir::stablehlo::TorchIndexSelectOp tblgen_TorchIndexSelectOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::TorchIndexSelectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*params.begin()));
      tblgen_values.push_back((*indices.begin()));
      tblgen_props.dim = ::llvm::dyn_cast_if_present<decltype(tblgen_props.dim)>(nativeVar_0);
      tblgen_props.batch_dims = ::llvm::dyn_cast_if_present<decltype(tblgen_props.batch_dims)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_TorchIndexSelectOp_2 = ::mlir::stablehlo::TorchIndexSelectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_TorchIndexSelectOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:100
*/
struct LowerAssert : public ::mlir::RewritePattern {
  LowerAssert(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Assert", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range condition(op0->getOperands());
    ::mlir::Operation::operand_range data(op0->getOperands());
    ::mlir::IntegerAttr summarize;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AssertOp>(op0); (void)castedOp0;
    condition = castedOp0.getODSOperands(0);
    data = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSummarize();
      if (!tblgen_attr) tblgen_attr = rewriter.getIntegerAttr(rewriter.getIntegerType(64), 3);
      summarize = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:131
*/
struct LowerRightShiftSigned : public ::mlir::RewritePattern {
  LowerRightShiftSigned(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.RightShift", 1, context, {"chlo.broadcast_shift_right_arithmetic"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_1(rewriter, op0, tblgen_ops, l, r))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::mlir::TF::RightShiftOp>(op0); (void)castedOp0;
    if (!(((::llvm::isa<::mlir::TensorType>(((*r.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isSignlessInteger(1))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*r.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'r' failed to satisfy constraint: 'tensor of 1-bit signless integer or 8-bit signless integer or 16-bit signless integer or 32-bit signless integer or 64-bit signless integer values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastShiftRightArithmeticOp tblgen_BroadcastShiftRightArithmeticOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastShiftRightArithmeticOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastShiftRightArithmeticOp_1 = ::mlir::chlo::BroadcastShiftRightArithmeticOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastShiftRightArithmeticOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:137
*/
struct LowerRightShiftUnsigned : public ::mlir::RewritePattern {
  LowerRightShiftUnsigned(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.RightShift", 1, context, {"chlo.broadcast_shift_right_logical"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_1(rewriter, op0, tblgen_ops, l, r))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::mlir::TF::RightShiftOp>(op0); (void)castedOp0;
    if (!(((::llvm::isa<::mlir::TensorType>(((*r.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*r.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'r' failed to satisfy constraint: 'tensor of 8-bit unsigned integer or 16-bit unsigned integer or 32-bit unsigned integer or 64-bit unsigned integer values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastShiftRightLogicalOp tblgen_BroadcastShiftRightLogicalOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastShiftRightLogicalOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastShiftRightLogicalOp_1 = ::mlir::chlo::BroadcastShiftRightLogicalOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastShiftRightLogicalOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:87
*/
struct GeneratedConvert0 : public ::mlir::RewritePattern {
  GeneratedConvert0(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ApproximateEqual", 1, context, {"chlo.broadcast_compare", "stablehlo.abs", "stablehlo.constant", "stablehlo.subtract"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::TF::ApproximateEqualOp result;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::FloatAttr tolerance;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ApproximateEqualOp>(op0); (void)castedOp0;
    result = castedOp0;
    x = castedOp0.getODSOperands(0);
    y = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getTolerance();
      if (!tblgen_attr) tblgen_attr = rewriter.getFloatAttr(rewriter.getF32Type(), 1e-05f);
      tolerance = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::SubtractOp tblgen_SubtractOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_SubtractOp_0 = ::mlir::stablehlo::SubtractOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    ::mlir::stablehlo::AbsOp abs;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubtractOp_0.getODSResults(0).begin());
      abs = ::mlir::stablehlo::AbsOp::create(rewriter, odsLoc,
        /*operand=*/tblgen_value_0
      );
    }
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_1;
    {
      tblgen_ConstantOp_1 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/tolerance
      );
    }
    auto nativeVar_2 = stablehlo::ConvertOp::create(rewriter, (*result.getODSResults(0).begin()).getLoc(), tblgen_ConstantOp_1, getElementTypeOrSelf((*abs.getODSResults(0).begin()).getType())); (void)nativeVar_2;
    auto nativeVar_3 = DenseI64ArrayAttr(); (void)nativeVar_3;
    auto nativeVar_4 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_4;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_5;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastCompareOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*abs.getODSResults(0).begin()));
      tblgen_values.push_back(nativeVar_2);
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_3);
      tblgen_props.comparison_direction = ::llvm::dyn_cast_if_present<decltype(tblgen_props.comparison_direction)>(::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::LT));
      tblgen_props.compare_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.compare_type)>(nativeVar_4);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastCompareOp_5 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastCompareOp_5.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert1 : public ::mlir::RewritePattern {
  GeneratedConvert1(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.AddV2", 1, context, {"chlo.broadcast_add"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AddV2Op>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.AddV2' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.AddV2' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastAddOp tblgen_BroadcastAddOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastAddOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastAddOp_1 = ::mlir::chlo::BroadcastAddOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastAddOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert2 : public ::mlir::RewritePattern {
  GeneratedConvert2(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Atan2", 1, context, {"chlo.broadcast_atan2"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::Atan2Op>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Atan2' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Atan2' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastAtan2Op tblgen_BroadcastAtan2Op_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastAtan2Op::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastAtan2Op_1 = ::mlir::chlo::BroadcastAtan2Op::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastAtan2Op_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert3 : public ::mlir::RewritePattern {
  GeneratedConvert3(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Complex", 1, context, {"chlo.broadcast_complex"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ComplexOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Complex' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Complex' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastComplexOp tblgen_BroadcastComplexOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastComplexOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastComplexOp_1 = ::mlir::chlo::BroadcastComplexOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastComplexOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert4 : public ::mlir::RewritePattern {
  GeneratedConvert4(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Div", 1, context, {"chlo.broadcast_divide"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::DivOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Div' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Div' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastDivOp tblgen_BroadcastDivOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastDivOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastDivOp_1 = ::mlir::chlo::BroadcastDivOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastDivOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert5 : public ::mlir::RewritePattern {
  GeneratedConvert5(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.LeftShift", 1, context, {"chlo.broadcast_shift_left"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::LeftShiftOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.LeftShift' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.LeftShift' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastShiftLeftOp tblgen_BroadcastShiftLeftOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastShiftLeftOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastShiftLeftOp_1 = ::mlir::chlo::BroadcastShiftLeftOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastShiftLeftOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert6 : public ::mlir::RewritePattern {
  GeneratedConvert6(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Maximum", 1, context, {"chlo.broadcast_maximum"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::MaximumOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Maximum' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Maximum' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastMaxOp tblgen_BroadcastMaxOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastMaxOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastMaxOp_1 = ::mlir::chlo::BroadcastMaxOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastMaxOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert7 : public ::mlir::RewritePattern {
  GeneratedConvert7(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Minimum", 1, context, {"chlo.broadcast_minimum"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::MinimumOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Minimum' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Minimum' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastMinOp tblgen_BroadcastMinOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastMinOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastMinOp_1 = ::mlir::chlo::BroadcastMinOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastMinOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert8 : public ::mlir::RewritePattern {
  GeneratedConvert8(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Mod", 1, context, {"chlo.broadcast_remainder"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ModOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Mod' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Mod' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastRemOp tblgen_BroadcastRemOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastRemOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastRemOp_1 = ::mlir::chlo::BroadcastRemOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastRemOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert9 : public ::mlir::RewritePattern {
  GeneratedConvert9(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Mul", 1, context, {"chlo.broadcast_multiply"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::MulOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Mul' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Mul' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastMulOp tblgen_BroadcastMulOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastMulOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastMulOp_1 = ::mlir::chlo::BroadcastMulOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastMulOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert10 : public ::mlir::RewritePattern {
  GeneratedConvert10(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.NextAfter", 1, context, {"chlo.broadcast_next_after"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::NextAfterOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.NextAfter' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.NextAfter' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastNextAfterOp tblgen_BroadcastNextAfterOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastNextAfterOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastNextAfterOp_1 = ::mlir::chlo::BroadcastNextAfterOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastNextAfterOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert11 : public ::mlir::RewritePattern {
  GeneratedConvert11(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Polygamma", 1, context, {"chlo.broadcast_polygamma"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::PolygammaOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Polygamma' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Polygamma' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastPolygammaOp tblgen_BroadcastPolygammaOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastPolygammaOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastPolygammaOp_1 = ::mlir::chlo::BroadcastPolygammaOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastPolygammaOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert12 : public ::mlir::RewritePattern {
  GeneratedConvert12(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Pow", 1, context, {"chlo.broadcast_power"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::PowOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Pow' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Pow' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastPowOp tblgen_BroadcastPowOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastPowOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastPowOp_1 = ::mlir::chlo::BroadcastPowOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastPowOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert13 : public ::mlir::RewritePattern {
  GeneratedConvert13(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.RealDiv", 1, context, {"chlo.broadcast_divide"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::RealDivOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.RealDiv' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.RealDiv' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastDivOp tblgen_BroadcastDivOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastDivOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastDivOp_1 = ::mlir::chlo::BroadcastDivOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastDivOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert14 : public ::mlir::RewritePattern {
  GeneratedConvert14(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Sub", 1, context, {"chlo.broadcast_subtract"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SubOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Sub' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Sub' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastSubOp tblgen_BroadcastSubOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastSubOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastSubOp_1 = ::mlir::chlo::BroadcastSubOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastSubOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:129
*/
struct GeneratedConvert15 : public ::mlir::RewritePattern {
  GeneratedConvert15(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Zeta", 1, context, {"chlo.broadcast_zeta"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ZetaOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Zeta' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Zeta' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastZetaOp tblgen_BroadcastZetaOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastZetaOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastZetaOp_1 = ::mlir::chlo::BroadcastZetaOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastZetaOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:146
*/
struct GeneratedConvert16 : public ::mlir::RewritePattern {
  GeneratedConvert16(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.FloorDiv", 1, context, {"chlo.broadcast_divide", "stablehlo.floor"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_2(rewriter, op0, tblgen_ops, l, r))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::mlir::TF::FloorDivOp>(op0); (void)castedOp0;
    if (!(((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isF16())) || ((elementType.isF32())) || ((elementType.isF64())); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'tensor of 16-bit float or 32-bit float or 64-bit float values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastDivOp tblgen_BroadcastDivOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*l.begin());
      ::mlir::Value tblgen_value_1 = (*r.begin());
      tblgen_BroadcastDivOp_1 = ::mlir::chlo::BroadcastDivOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_0
      );
    }
    ::mlir::stablehlo::FloorOp tblgen_FloorOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::FloorOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_BroadcastDivOp_1.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_FloorOp_2 = ::mlir::stablehlo::FloorOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_FloorOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:161
*/
struct GeneratedConvert17 : public ::mlir::RewritePattern {
  GeneratedConvert17(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.FloorDiv", 1, context, {"chlo.broadcast_and", "chlo.broadcast_compare", "chlo.broadcast_divide", "chlo.broadcast_multiply", "chlo.broadcast_subtract", "stablehlo.constant", "stablehlo.select"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_2(rewriter, op0, tblgen_ops, l, r))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::mlir::TF::FloorDivOp>(op0); (void)castedOp0;
    if (!(((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isSignlessInteger(1))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'tensor of 1-bit signless integer or 8-bit signless integer or 16-bit signless integer or 32-bit signless integer or 64-bit signless integer values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastDivOp div;
    {
      ::mlir::Value tblgen_value_0 = (*l.begin());
      ::mlir::Value tblgen_value_1 = (*r.begin());
      div = ::mlir::chlo::BroadcastDivOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_0
      );
    }
    auto nativeVar_1 = hlo::getBroadcastDimensionsAttr(&rewriter, (*div.getODSResults(0).begin()), (*r.begin())); (void)nativeVar_1;
    ::mlir::chlo::BroadcastMulOp mul;
    {
      ::mlir::Value tblgen_value_0 = (*div.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*r.begin());
      mul = ::mlir::chlo::BroadcastMulOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_1
      );
    }
    auto nativeVar_2 = hlo::getBroadcastDimensionsAttr(&rewriter, (*mul.getODSResults(0).begin()), (*l.begin())); (void)nativeVar_2;
    auto nativeVar_3 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_3;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*mul.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*l.begin());
      tblgen_BroadcastCompareOp_4 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_2,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::NE),
        /*compare_type=*/nativeVar_3
      );
    }
    auto nativeVar_5 = hlo::getScalarOfType(getElementTypeOrSelf((*l.begin())),0); (void)nativeVar_5;
    ::mlir::stablehlo::ConstantOp l_zeros;
    {
      l_zeros = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_5
      );
    }
    auto nativeVar_6 = DenseI64ArrayAttr(); (void)nativeVar_6;
    auto nativeVar_7 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_7;
    ::mlir::chlo::BroadcastCompareOp l_cmp;
    {
      ::mlir::Value tblgen_value_0 = (*l.begin());
      ::mlir::Value tblgen_value_1 = (*l_zeros.getODSResults(0).begin());
      l_cmp = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_6,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::LT),
        /*compare_type=*/nativeVar_7
      );
    }
    auto nativeVar_8 = hlo::getScalarOfType(getElementTypeOrSelf((*r.begin())),0); (void)nativeVar_8;
    ::mlir::stablehlo::ConstantOp r_zeros;
    {
      r_zeros = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_8
      );
    }
    auto nativeVar_9 = DenseI64ArrayAttr(); (void)nativeVar_9;
    auto nativeVar_10 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_10;
    ::mlir::chlo::BroadcastCompareOp r_cmp;
    {
      ::mlir::Value tblgen_value_0 = (*r.begin());
      ::mlir::Value tblgen_value_1 = (*r_zeros.getODSResults(0).begin());
      r_cmp = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_9,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::LT),
        /*compare_type=*/nativeVar_10
      );
    }
    auto nativeVar_11 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l_cmp.getODSResults(0).begin()), (*r_cmp.getODSResults(0).begin())); (void)nativeVar_11;
    auto nativeVar_12 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_12;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_13;
    {
      ::mlir::Value tblgen_value_0 = (*l_cmp.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*r_cmp.getODSResults(0).begin());
      tblgen_BroadcastCompareOp_13 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_11,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::NE),
        /*compare_type=*/nativeVar_12
      );
    }
    auto nativeVar_14 = DenseI64ArrayAttr(); (void)nativeVar_14;
    ::mlir::chlo::BroadcastAndOp tblgen_BroadcastAndOp_15;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_BroadcastCompareOp_4.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_BroadcastCompareOp_13.getODSResults(0).begin());
      tblgen_BroadcastAndOp_15 = ::mlir::chlo::BroadcastAndOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_14
      );
    }
    auto nativeVar_16 = hlo::getScalarOfType(getElementTypeOrSelf((*div.getODSResults(0).begin())),1); (void)nativeVar_16;
    ::mlir::stablehlo::ConstantOp ones;
    {
      ones = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_16
      );
    }
    auto nativeVar_17 = DenseI64ArrayAttr(); (void)nativeVar_17;
    ::mlir::chlo::BroadcastSubOp tblgen_BroadcastSubOp_18;
    {
      ::mlir::Value tblgen_value_0 = (*div.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*ones.getODSResults(0).begin());
      tblgen_BroadcastSubOp_18 = ::mlir::chlo::BroadcastSubOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_17
      );
    }
    ::mlir::stablehlo::SelectOp tblgen_SelectOp_19;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SelectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_BroadcastAndOp_15.getODSResults(0).begin()));
      tblgen_values.push_back((*tblgen_BroadcastSubOp_18.getODSResults(0).begin()));
      tblgen_values.push_back((*div.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SelectOp_19 = ::mlir::stablehlo::SelectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SelectOp_19.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:189
*/
struct GeneratedConvert18 : public ::mlir::RewritePattern {
  GeneratedConvert18(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.FloorDiv", 1, context, {"chlo.broadcast_divide"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_2(rewriter, op0, tblgen_ops, l, r))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::mlir::TF::FloorDivOp>(op0); (void)castedOp0;
    if (!(((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'tensor of 8-bit unsigned integer or 16-bit unsigned integer or 32-bit unsigned integer or 64-bit unsigned integer values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastDivOp tblgen_BroadcastDivOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastDivOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastDivOp_1 = ::mlir::chlo::BroadcastDivOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastDivOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:199
*/
struct GeneratedConvert19 : public ::mlir::RewritePattern {
  GeneratedConvert19(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.FloorMod", 1, context, {"chlo.broadcast_add", "chlo.broadcast_and", "chlo.broadcast_compare", "chlo.broadcast_remainder", "stablehlo.constant", "stablehlo.select"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_3(rewriter, op0, tblgen_ops, l, r))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::mlir::TF::FloorModOp>(op0); (void)castedOp0;
    if (!(((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64))) || ((elementType.isF16())) || ((elementType.isF32())) || ((elementType.isF64())); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'tensor of 8-bit signless integer or 16-bit signless integer or 32-bit signless integer or 64-bit signless integer or 16-bit float or 32-bit float or 64-bit float values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastRemOp rem;
    {
      ::mlir::Value tblgen_value_0 = (*l.begin());
      ::mlir::Value tblgen_value_1 = (*r.begin());
      rem = ::mlir::chlo::BroadcastRemOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_0
      );
    }
    auto nativeVar_1 = hlo::getScalarOfType(getElementTypeOrSelf((*l.begin())),0); (void)nativeVar_1;
    ::mlir::stablehlo::ConstantOp l_zeros;
    {
      l_zeros = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_1
      );
    }
    auto nativeVar_2 = DenseI64ArrayAttr(); (void)nativeVar_2;
    auto nativeVar_3 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_3;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*rem.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*l_zeros.getODSResults(0).begin());
      tblgen_BroadcastCompareOp_4 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_2,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::NE),
        /*compare_type=*/nativeVar_3
      );
    }
    auto nativeVar_5 = hlo::getScalarOfType(getElementTypeOrSelf((*r.begin())),0); (void)nativeVar_5;
    ::mlir::stablehlo::ConstantOp r_zeros;
    {
      r_zeros = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_5
      );
    }
    auto nativeVar_6 = DenseI64ArrayAttr(); (void)nativeVar_6;
    auto nativeVar_7 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_7;
    ::mlir::chlo::BroadcastCompareOp r_cmp;
    {
      ::mlir::Value tblgen_value_0 = (*r.begin());
      ::mlir::Value tblgen_value_1 = (*r_zeros.getODSResults(0).begin());
      r_cmp = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_6,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::LT),
        /*compare_type=*/nativeVar_7
      );
    }
    auto nativeVar_8 = hlo::getBroadcastDimensionsAttr(&rewriter, (*rem.getODSResults(0).begin()), (*r_zeros.getODSResults(0).begin())); (void)nativeVar_8;
    auto nativeVar_9 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_9;
    ::mlir::chlo::BroadcastCompareOp rem_cmp;
    {
      ::mlir::Value tblgen_value_0 = (*rem.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*r_zeros.getODSResults(0).begin());
      rem_cmp = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_8,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::LT),
        /*compare_type=*/nativeVar_9
      );
    }
    auto nativeVar_10 = hlo::getBroadcastDimensionsAttr(&rewriter, (*r_cmp.getODSResults(0).begin()), (*rem_cmp.getODSResults(0).begin())); (void)nativeVar_10;
    auto nativeVar_11 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_11;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_12;
    {
      ::mlir::Value tblgen_value_0 = (*r_cmp.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*rem_cmp.getODSResults(0).begin());
      tblgen_BroadcastCompareOp_12 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_10,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::NE),
        /*compare_type=*/nativeVar_11
      );
    }
    auto nativeVar_13 = DenseI64ArrayAttr(); (void)nativeVar_13;
    ::mlir::chlo::BroadcastAndOp tblgen_BroadcastAndOp_14;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_BroadcastCompareOp_4.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_BroadcastCompareOp_12.getODSResults(0).begin());
      tblgen_BroadcastAndOp_14 = ::mlir::chlo::BroadcastAndOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_13
      );
    }
    auto nativeVar_15 = hlo::getBroadcastDimensionsAttr(&rewriter, (*r.begin()), (*rem.getODSResults(0).begin())); (void)nativeVar_15;
    ::mlir::chlo::BroadcastAddOp tblgen_BroadcastAddOp_16;
    {
      ::mlir::Value tblgen_value_0 = (*r.begin());
      ::mlir::Value tblgen_value_1 = (*rem.getODSResults(0).begin());
      tblgen_BroadcastAddOp_16 = ::mlir::chlo::BroadcastAddOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_15
      );
    }
    ::mlir::stablehlo::SelectOp tblgen_SelectOp_17;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SelectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_BroadcastAndOp_14.getODSResults(0).begin()));
      tblgen_values.push_back((*tblgen_BroadcastAddOp_16.getODSResults(0).begin()));
      tblgen_values.push_back((*rem.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SelectOp_17 = ::mlir::stablehlo::SelectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SelectOp_17.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:223
*/
struct GeneratedConvert20 : public ::mlir::RewritePattern {
  GeneratedConvert20(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.FloorMod", 1, context, {"chlo.broadcast_remainder"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_3(rewriter, op0, tblgen_ops, l, r))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::mlir::TF::FloorModOp>(op0); (void)castedOp0;
    if (!(((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'tensor of 8-bit unsigned integer or 16-bit unsigned integer or 32-bit unsigned integer or 64-bit unsigned integer values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastRemOp tblgen_BroadcastRemOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastRemOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastRemOp_1 = ::mlir::chlo::BroadcastRemOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastRemOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:230
*/
struct GeneratedConvert21 : public ::mlir::RewritePattern {
  GeneratedConvert21(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.RiscAdd", 1, context, {"stablehlo.add"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::RiscAddOp>(op0); (void)castedOp0;
    l = castedOp0.getODSOperands(0);
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::AddOp tblgen_AddOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::AddOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AddOp_0 = ::mlir::stablehlo::AddOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AddOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:232
*/
struct GeneratedConvert22 : public ::mlir::RewritePattern {
  GeneratedConvert22(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.RiscDot", 1, context, {"stablehlo.dot", "tf.Const", "tf.Transpose"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr transpose_a;
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::BoolAttr transpose_b;
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::RiscDotOp>(op0); (void)castedOp0;
    a = castedOp0.getODSOperands(0);
    b = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getTransposeA();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      transpose_a = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getTransposeB();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      transpose_b = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = Get2DTransposePerm(transpose_a, &rewriter); (void)nativeVar_0;
    ::mlir::TF::ConstOp tblgen_ConstOp_1;
    {
      tblgen_ConstOp_1 = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    ::mlir::TF::TransposeOp tblgen_TransposeOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*a.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_ConstOp_1.getODSResults(0).begin());
      tblgen_TransposeOp_2 = ::mlir::TF::TransposeOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*perm=*/tblgen_value_1
      );
    }
    auto nativeVar_3 = Get2DTransposePerm(transpose_b, &rewriter); (void)nativeVar_3;
    ::mlir::TF::ConstOp tblgen_ConstOp_4;
    {
      tblgen_ConstOp_4 = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_3
      );
    }
    ::mlir::TF::TransposeOp tblgen_TransposeOp_5;
    {
      ::mlir::Value tblgen_value_0 = (*b.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_ConstOp_4.getODSResults(0).begin());
      tblgen_TransposeOp_5 = ::mlir::TF::TransposeOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*perm=*/tblgen_value_1
      );
    }
    auto nativeVar_6 = ArrayAttr(); (void)nativeVar_6;
    ::mlir::stablehlo::DotOp tblgen_DotOp_7;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DotOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_TransposeOp_2.getODSResults(0).begin()));
      tblgen_values.push_back((*tblgen_TransposeOp_5.getODSResults(0).begin()));
      tblgen_props.precision_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.precision_config)>(nativeVar_6);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DotOp_7 = ::mlir::stablehlo::DotOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DotOp_7.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:252
*/
struct GeneratedConvert23 : public ::mlir::RewritePattern {
  GeneratedConvert23(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.LogicalAnd", 1, context, {"chlo.broadcast_and"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::LogicalAndOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.LogicalAnd' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.LogicalAnd' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);
    if (!((((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isSignlessInteger(1))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType()))) || (((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'tensor of 1-bit signless integer or 8-bit signless integer or 16-bit signless integer or 32-bit signless integer or 64-bit signless integer values or tensor of 8-bit unsigned integer or 16-bit unsigned integer or 32-bit unsigned integer or 64-bit unsigned integer values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastAndOp tblgen_BroadcastAndOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastAndOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastAndOp_1 = ::mlir::chlo::BroadcastAndOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastAndOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:252
*/
struct GeneratedConvert24 : public ::mlir::RewritePattern {
  GeneratedConvert24(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.LogicalOr", 1, context, {"chlo.broadcast_or"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::LogicalOrOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.LogicalOr' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.LogicalOr' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);
    if (!((((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isSignlessInteger(1))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType()))) || (((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'tensor of 1-bit signless integer or 8-bit signless integer or 16-bit signless integer or 32-bit signless integer or 64-bit signless integer values or tensor of 8-bit unsigned integer or 16-bit unsigned integer or 32-bit unsigned integer or 64-bit unsigned integer values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastOrOp tblgen_BroadcastOrOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastOrOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastOrOp_1 = ::mlir::chlo::BroadcastOrOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastOrOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:252
*/
struct GeneratedConvert25 : public ::mlir::RewritePattern {
  GeneratedConvert25(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.BitwiseAnd", 1, context, {"chlo.broadcast_and"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::BitwiseAndOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.BitwiseAnd' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.BitwiseAnd' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);
    if (!((((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isSignlessInteger(1))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType()))) || (((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'tensor of 1-bit signless integer or 8-bit signless integer or 16-bit signless integer or 32-bit signless integer or 64-bit signless integer values or tensor of 8-bit unsigned integer or 16-bit unsigned integer or 32-bit unsigned integer or 64-bit unsigned integer values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastAndOp tblgen_BroadcastAndOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastAndOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastAndOp_1 = ::mlir::chlo::BroadcastAndOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastAndOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:252
*/
struct GeneratedConvert26 : public ::mlir::RewritePattern {
  GeneratedConvert26(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.BitwiseOr", 1, context, {"chlo.broadcast_or"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::BitwiseOrOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.BitwiseOr' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.BitwiseOr' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);
    if (!((((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isSignlessInteger(1))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType()))) || (((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'tensor of 1-bit signless integer or 8-bit signless integer or 16-bit signless integer or 32-bit signless integer or 64-bit signless integer values or tensor of 8-bit unsigned integer or 16-bit unsigned integer or 32-bit unsigned integer or 64-bit unsigned integer values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastOrOp tblgen_BroadcastOrOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastOrOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastOrOp_1 = ::mlir::chlo::BroadcastOrOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastOrOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:252
*/
struct GeneratedConvert27 : public ::mlir::RewritePattern {
  GeneratedConvert27(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.BitwiseXor", 1, context, {"chlo.broadcast_xor"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::BitwiseXorOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.BitwiseXor' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.BitwiseXor' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);
    if (!((((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isSignlessInteger(1))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType()))) || (((::llvm::isa<::mlir::TensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'tensor of 1-bit signless integer or 8-bit signless integer or 16-bit signless integer or 32-bit signless integer or 64-bit signless integer values or tensor of 8-bit unsigned integer or 16-bit unsigned integer or 32-bit unsigned integer or 64-bit unsigned integer values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    ::mlir::chlo::BroadcastXorOp tblgen_BroadcastXorOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastXorOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastXorOp_1 = ::mlir::chlo::BroadcastXorOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastXorOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:264
*/
struct GeneratedConvert28 : public ::mlir::RewritePattern {
  GeneratedConvert28(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Greater", 1, context, {"chlo.broadcast_compare"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::GreaterOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Greater' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Greater' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    auto nativeVar_1 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_1;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastCompareOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      tblgen_props.comparison_direction = ::llvm::dyn_cast_if_present<decltype(tblgen_props.comparison_direction)>(::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::GT));
      tblgen_props.compare_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.compare_type)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastCompareOp_2 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastCompareOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:265
*/
struct GeneratedConvert29 : public ::mlir::RewritePattern {
  GeneratedConvert29(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.GreaterEqual", 1, context, {"chlo.broadcast_compare"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::GreaterEqualOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.GreaterEqual' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.GreaterEqual' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    auto nativeVar_1 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_1;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastCompareOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      tblgen_props.comparison_direction = ::llvm::dyn_cast_if_present<decltype(tblgen_props.comparison_direction)>(::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::GE));
      tblgen_props.compare_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.compare_type)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastCompareOp_2 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastCompareOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:266
*/
struct GeneratedConvert30 : public ::mlir::RewritePattern {
  GeneratedConvert30(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Less", 1, context, {"chlo.broadcast_compare"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::LessOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Less' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Less' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    auto nativeVar_1 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_1;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastCompareOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      tblgen_props.comparison_direction = ::llvm::dyn_cast_if_present<decltype(tblgen_props.comparison_direction)>(::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::LT));
      tblgen_props.compare_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.compare_type)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastCompareOp_2 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastCompareOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:267
*/
struct GeneratedConvert31 : public ::mlir::RewritePattern {
  GeneratedConvert31(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.LessEqual", 1, context, {"chlo.broadcast_compare"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::LessEqualOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.LessEqual' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.LessEqual' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    auto nativeVar_1 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_1;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastCompareOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      tblgen_props.comparison_direction = ::llvm::dyn_cast_if_present<decltype(tblgen_props.comparison_direction)>(::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::LE));
      tblgen_props.compare_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.compare_type)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastCompareOp_2 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastCompareOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:277
*/
struct GeneratedConvert32 : public ::mlir::RewritePattern {
  GeneratedConvert32(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Equal", 1, context, {"chlo.broadcast_compare"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr incompatible_shape_error;
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::EqualOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Equal' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Equal' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIncompatibleShapeError();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(true);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns2(rewriter, castedOp0, tblgen_attr, "op 'tf.Equal' attribute 'incompatible_shape_error' failed to satisfy constraint: ''"))) {
        return ::mlir::failure();
      }
      incompatible_shape_error = tblgen_attr;
    }
    if (!(((::llvm::isa<::mlir::RankedTensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return (((::llvm::isa<::mlir::Float4E2M1FNType>(elementType))) || ((::llvm::isa<::mlir::Float6E2M3FNType>(elementType))) || ((::llvm::isa<::mlir::Float6E3M2FNType>(elementType))) || ((::llvm::isa<::mlir::Float8E3M4Type>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3Type>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3FNType>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3B11FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E5M2Type>(elementType))) || ((::llvm::isa<::mlir::Float8E5M2FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E8M0FNUType>(elementType))) || ((elementType.isF16())) || ((elementType.isF32())) || ((elementType.isF64())) || ((::llvm::isa<::mlir::BFloat16Type>(elementType)))) || ((elementType.isSignlessInteger(1))) || ((((elementType.isSignlessInteger(2))) || ((elementType.isSignlessInteger(4))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64)))) || (((elementType.isUnsignedInteger(2))) || ((elementType.isUnsignedInteger(4))) || ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))))) || (((::llvm::isa<::mlir::ComplexType>(elementType))) && (((::llvm::cast<::mlir::ComplexType>(elementType).getElementType().isF32())) || ((::llvm::cast<::mlir::ComplexType>(elementType).getElementType().isF64())))) || (((((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 2)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 4)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 8)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 16)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 32)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType))))) || ((((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 2)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 4)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 8)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 16)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 32)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    auto nativeVar_1 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_1;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastCompareOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      tblgen_props.comparison_direction = ::llvm::dyn_cast_if_present<decltype(tblgen_props.comparison_direction)>(::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::EQ));
      tblgen_props.compare_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.compare_type)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastCompareOp_2 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastCompareOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:278
*/
struct GeneratedConvert33 : public ::mlir::RewritePattern {
  GeneratedConvert33(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.NotEqual", 1, context, {"chlo.broadcast_compare"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr incompatible_shape_error;
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::NotEqualOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.NotEqual' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.NotEqual' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIncompatibleShapeError();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(true);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns2(rewriter, castedOp0, tblgen_attr, "op 'tf.NotEqual' attribute 'incompatible_shape_error' failed to satisfy constraint: ''"))) {
        return ::mlir::failure();
      }
      incompatible_shape_error = tblgen_attr;
    }
    if (!(((::llvm::isa<::mlir::RankedTensorType>(((*l.begin()).getType())))) && ([](::mlir::Type elementType) { return (((::llvm::isa<::mlir::Float4E2M1FNType>(elementType))) || ((::llvm::isa<::mlir::Float6E2M3FNType>(elementType))) || ((::llvm::isa<::mlir::Float6E3M2FNType>(elementType))) || ((::llvm::isa<::mlir::Float8E3M4Type>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3Type>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3FNType>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E4M3B11FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E5M2Type>(elementType))) || ((::llvm::isa<::mlir::Float8E5M2FNUZType>(elementType))) || ((::llvm::isa<::mlir::Float8E8M0FNUType>(elementType))) || ((elementType.isF16())) || ((elementType.isF32())) || ((elementType.isF64())) || ((::llvm::isa<::mlir::BFloat16Type>(elementType)))) || ((elementType.isSignlessInteger(1))) || ((((elementType.isSignlessInteger(2))) || ((elementType.isSignlessInteger(4))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64)))) || (((elementType.isUnsignedInteger(2))) || ((elementType.isUnsignedInteger(4))) || ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64))))) || (((::llvm::isa<::mlir::ComplexType>(elementType))) && (((::llvm::cast<::mlir::ComplexType>(elementType).getElementType().isF32())) || ((::llvm::cast<::mlir::ComplexType>(elementType).getElementType().isF64())))) || (((((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 2)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 4)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 8)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 16)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 32)) && ((::llvm::cast<::mlir::IntegerType>(::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageType()).isSignless())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType))))) || ((((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 2)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 4)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 8)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 16)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))) || (((::llvm::isa<::mlir::quant::UniformQuantizedType>(elementType))) && ((::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).getStorageTypeIntegralWidth() == 32)) && ((!::llvm::cast<::mlir::quant::UniformQuantizedType>(elementType).isSigned())) && ((mlir::hlo::isValidStablehloQuantizedElementType(elementType)))))); }(::llvm::cast<::mlir::ShapedType>(((*l.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'l' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getBroadcastDimensionsAttr(&rewriter, (*l.begin()), (*r.begin())); (void)nativeVar_0;
    auto nativeVar_1 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_1;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastCompareOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*l.begin()));
      tblgen_values.push_back((*r.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      tblgen_props.comparison_direction = ::llvm::dyn_cast_if_present<decltype(tblgen_props.comparison_direction)>(::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::NE));
      tblgen_props.compare_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.compare_type)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastCompareOp_2 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastCompareOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:305
*/
struct GeneratedConvert34 : public ::mlir::RewritePattern {
  GeneratedConvert34(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ConcatV2", 1, context, {"stablehlo.concatenate"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range inputs(op0->getOperands());
    ::mlir::Attribute axis;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ConcatV2Op>(op0); (void)castedOp0;
    inputs = castedOp0.getODSOperands(0);
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
        axis = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns3(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'Scalar ElementsAttr'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }
    if (!((llvm::isa<RankedTensorType>((*inputs.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'inputs' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = GetHLOAxisFromTFAxis(axis, llvm::cast<RankedTensorType>((*inputs.begin()).getType()).getRank(), &rewriter); (void)nativeVar_0;
    ::mlir::stablehlo::ConcatenateOp tblgen_ConcatenateOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::ConcatenateOp::Properties tblgen_props; (void)tblgen_props;
      for (auto v: inputs) {
        tblgen_values.push_back(v);
      }
      tblgen_props.dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.dimension)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ConcatenateOp_1 = ::mlir::stablehlo::ConcatenateOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ConcatenateOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:314
*/
struct GeneratedConvert35 : public ::mlir::RewritePattern {
  GeneratedConvert35(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.CollectivePermute", 1, context, {"stablehlo.collective_permute"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::mlir::Attribute source_target_pairs;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::CollectivePermuteOp>(op0); (void)castedOp0;
    input = castedOp0.getODSOperands(0);
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
        source_target_pairs = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'constant vector/tensor attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = 
      llvm::cast<mlir::DenseIntElementsAttr>(hlo::convertElementsAttr(
        llvm::cast<ElementsAttr>(source_target_pairs), rewriter.getIntegerType(64)))
      ; (void)nativeVar_0;
    auto nativeVar_1 = stablehlo::ChannelHandleAttr(); (void)nativeVar_1;
    ::mlir::stablehlo::CollectivePermuteOp tblgen_CollectivePermuteOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::CollectivePermuteOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.source_target_pairs = ::llvm::dyn_cast_if_present<decltype(tblgen_props.source_target_pairs)>(nativeVar_0);
      tblgen_props.channel_handle = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_handle)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_CollectivePermuteOp_2 = ::mlir::stablehlo::CollectivePermuteOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_CollectivePermuteOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:323
*/
struct GeneratedConvert36 : public ::mlir::RewritePattern {
  GeneratedConvert36(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.CrossReplicaSum", 1, context, {"stablehlo.cross-replica-sum"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::mlir::Attribute group_assignment;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::CrossReplicaSumOp>(op0); (void)castedOp0;
    input = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_4(rewriter, op1, tblgen_ops, group_assignment))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = 
      llvm::cast<mlir::DenseIntElementsAttr>(hlo::convertElementsAttr(
        llvm::cast<ElementsAttr>(group_assignment), rewriter.getIntegerType(64)))
      ; (void)nativeVar_0;
    ::mlir::stablehlo::CrossReplicaSumOp tblgen_CrossReplicaSumOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::CrossReplicaSumOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.replica_groups = ::llvm::dyn_cast_if_present<decltype(tblgen_props.replica_groups)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_CrossReplicaSumOp_1 = ::mlir::stablehlo::CrossReplicaSumOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_CrossReplicaSumOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:332
*/
struct GeneratedConvert37 : public ::mlir::RewritePattern {
  GeneratedConvert37(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.AllToAll", 1, context, {"stablehlo.all_to_all"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr split_count;
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::mlir::Attribute group_assignment;
    ::mlir::IntegerAttr concat_dimension;
    ::mlir::IntegerAttr split_dimension;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AllToAllOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.AllToAll' failed to satisfy constraint: 'ranked tensor of any type values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_4(rewriter, op1, tblgen_ops, group_assignment))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getConcatDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.AllToAll' to have attribute 'concat_dimension' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns4(rewriter, castedOp0, tblgen_attr, "op 'tf.AllToAll' attribute 'concat_dimension' failed to satisfy constraint: '64-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      concat_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSplitDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.AllToAll' to have attribute 'split_dimension' of type '::mlir::IntegerAttr'";
        });
      }
      split_dimension = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSplitCount();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.AllToAll' to have attribute 'split_count' of type '::mlir::IntegerAttr'";
        });
      }
      split_count = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = SmallVector<Value, 1>{(*input.begin())}; (void)nativeVar_0;
    auto nativeVar_1 = 
      llvm::cast<mlir::DenseIntElementsAttr>(hlo::convertElementsAttr(
        llvm::cast<ElementsAttr>(group_assignment), rewriter.getIntegerType(64)))
      ; (void)nativeVar_1;
    auto nativeVar_2 = stablehlo::ChannelHandleAttr(); (void)nativeVar_2;
    ::mlir::stablehlo::AllToAllOp tblgen_AllToAllOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::AllToAllOp::Properties tblgen_props; (void)tblgen_props;
      for (auto v: nativeVar_0) {
        tblgen_values.push_back(v);
      }
      tblgen_props.split_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.split_dimension)>(split_dimension);
      tblgen_props.concat_dimension = ::llvm::dyn_cast_if_present<decltype(tblgen_props.concat_dimension)>(concat_dimension);
      tblgen_props.split_count = ::llvm::dyn_cast_if_present<decltype(tblgen_props.split_count)>(split_count);
      tblgen_props.replica_groups = ::llvm::dyn_cast_if_present<decltype(tblgen_props.replica_groups)>(nativeVar_1);
      tblgen_props.channel_handle = ::llvm::dyn_cast_if_present<decltype(tblgen_props.channel_handle)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AllToAllOp_3 = ::mlir::stablehlo::AllToAllOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AllToAllOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:348
*/
struct GeneratedConvert38 : public ::mlir::RewritePattern {
  GeneratedConvert38(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.FFT", 1, context, {"stablehlo.fft"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::FFTOp res;
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::FFTOp>(op0); (void)castedOp0;
    res = castedOp0;
    input = castedOp0.getODSOperands(0);
    if (!((CheckInnerDimStatic(llvm::cast<ShapedType>((*input.begin()).getType()), &rewriter)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'input' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = GetInnerDimFromValue(llvm::cast<ShapedType>((*res.getODSResults(0).begin()).getType()), &rewriter); (void)nativeVar_0;
    ::mlir::stablehlo::FftOp tblgen_FftOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::FftOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.fft_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.fft_type)>(::mlir::stablehlo::FftTypeAttr::get(rewriter.getContext(), ::mlir::stablehlo::FftType::FFT));
      tblgen_props.fft_length = ::llvm::dyn_cast_if_present<decltype(tblgen_props.fft_length)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_FftOp_1 = ::mlir::stablehlo::FftOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_FftOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:352
*/
struct GeneratedConvert39 : public ::mlir::RewritePattern {
  GeneratedConvert39(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.IFFT", 1, context, {"stablehlo.fft"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::IFFTOp res;
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::IFFTOp>(op0); (void)castedOp0;
    res = castedOp0;
    input = castedOp0.getODSOperands(0);
    if (!((CheckInnerDimStatic(llvm::cast<ShapedType>((*input.begin()).getType()), &rewriter)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'input' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = GetInnerDimFromValue(llvm::cast<ShapedType>((*res.getODSResults(0).begin()).getType()), &rewriter); (void)nativeVar_0;
    ::mlir::stablehlo::FftOp tblgen_FftOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::FftOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.fft_type = ::llvm::dyn_cast_if_present<decltype(tblgen_props.fft_type)>(::mlir::stablehlo::FftTypeAttr::get(rewriter.getContext(), ::mlir::stablehlo::FftType::IFFT));
      tblgen_props.fft_length = ::llvm::dyn_cast_if_present<decltype(tblgen_props.fft_length)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_FftOp_1 = ::mlir::stablehlo::FftOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_FftOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:384
*/
struct GeneratedConvert40 : public ::mlir::RewritePattern {
  GeneratedConvert40(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.PadV2", 1, context, {"stablehlo.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::mlir::Attribute padding;
    ::mlir::Operation::operand_range c(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::PadV2Op>(op0); (void)castedOp0;
    input = castedOp0.getODSOperands(0);
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
        padding = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'constant vector/tensor attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }
    c = castedOp0.getODSOperands(2);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = SliceDenseIntElementsAttrColumn2D(llvm::cast<ElementsAttr>(padding), 0 ); (void)nativeVar_0;
    auto nativeVar_1 = SliceDenseIntElementsAttrColumn2D(llvm::cast<ElementsAttr>(padding), 1 ); (void)nativeVar_1;
    auto nativeVar_2 = GetInteriorPadding(llvm::cast<ElementsAttr>(padding)); (void)nativeVar_2;
    ::mlir::stablehlo::PadOp tblgen_PadOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::PadOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_values.push_back((*c.begin()));
      tblgen_props.edge_padding_low = ::llvm::dyn_cast_if_present<decltype(tblgen_props.edge_padding_low)>(nativeVar_0);
      tblgen_props.edge_padding_high = ::llvm::dyn_cast_if_present<decltype(tblgen_props.edge_padding_high)>(nativeVar_1);
      tblgen_props.interior_padding = ::llvm::dyn_cast_if_present<decltype(tblgen_props.interior_padding)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_PadOp_3 = ::mlir::stablehlo::PadOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_PadOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:395
*/
struct GeneratedConvert41 : public ::mlir::RewritePattern {
  GeneratedConvert41(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Identity", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range op(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::IdentityOp>(op0); (void)castedOp0;
    op = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ op }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:395
*/
struct GeneratedConvert42 : public ::mlir::RewritePattern {
  GeneratedConvert42(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.StopGradient", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range op(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::StopGradientOp>(op0); (void)castedOp0;
    op = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ op }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:395
*/
struct GeneratedConvert43 : public ::mlir::RewritePattern {
  GeneratedConvert43(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf._EagerConst", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range op(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::_EagerConstOp>(op0); (void)castedOp0;
    op = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ op }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:399
*/
struct GeneratedConvert44 : public ::mlir::RewritePattern {
  GeneratedConvert44(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.PreventGradient", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::StringAttr msg;
    ::mlir::Operation::operand_range op(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::PreventGradientOp>(op0); (void)castedOp0;
    op = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getMessage();
      if (!tblgen_attr) tblgen_attr = rewriter.getStringAttr("");
      msg = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ op }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:399
*/
struct GeneratedConvert45 : public ::mlir::RewritePattern {
  GeneratedConvert45(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.CheckNumerics", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::StringAttr msg;
    ::mlir::Operation::operand_range op(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::CheckNumericsOp>(op0); (void)castedOp0;
    op = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getMessage();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.CheckNumerics' to have attribute 'message' of type '::mlir::StringAttr'";
        });
      }
      msg = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ op }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:408
*/
struct GeneratedConvert46 : public ::mlir::RewritePattern {
  GeneratedConvert46(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.MatMul", 1, context, {"stablehlo.dot", "tf.Const", "tf.Transpose"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr transpose_a;
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::BoolAttr transpose_b;
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::mlir::BoolAttr grad_a;
    ::mlir::BoolAttr grad_b;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::MatMulOp>(op0); (void)castedOp0;
    a = castedOp0.getODSOperands(0);
    b = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getTransposeA();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      transpose_a = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getTransposeB();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      transpose_b = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getGradA();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      grad_a = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getGradB();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      grad_b = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = Get2DTransposePerm(transpose_a, &rewriter); (void)nativeVar_0;
    ::mlir::TF::ConstOp tblgen_ConstOp_1;
    {
      tblgen_ConstOp_1 = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    ::mlir::TF::TransposeOp tblgen_TransposeOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*a.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_ConstOp_1.getODSResults(0).begin());
      tblgen_TransposeOp_2 = ::mlir::TF::TransposeOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*perm=*/tblgen_value_1
      );
    }
    auto nativeVar_3 = Get2DTransposePerm(transpose_b, &rewriter); (void)nativeVar_3;
    ::mlir::TF::ConstOp tblgen_ConstOp_4;
    {
      tblgen_ConstOp_4 = ::mlir::TF::ConstOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_3
      );
    }
    ::mlir::TF::TransposeOp tblgen_TransposeOp_5;
    {
      ::mlir::Value tblgen_value_0 = (*b.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_ConstOp_4.getODSResults(0).begin());
      tblgen_TransposeOp_5 = ::mlir::TF::TransposeOp::create(rewriter, odsLoc,
        /*x=*/tblgen_value_0,
        /*perm=*/tblgen_value_1
      );
    }
    auto nativeVar_6 = GetPrecisionConfig(&rewriter); (void)nativeVar_6;
    ::mlir::stablehlo::DotOp tblgen_DotOp_7;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DotOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_TransposeOp_2.getODSResults(0).begin()));
      tblgen_values.push_back((*tblgen_TransposeOp_5.getODSResults(0).begin()));
      tblgen_props.precision_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.precision_config)>(nativeVar_6);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DotOp_7 = ::mlir::stablehlo::DotOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DotOp_7.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:418
*/
struct GeneratedConvert47 : public ::mlir::RewritePattern {
  GeneratedConvert47(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ZerosLike", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range arg(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ZerosLikeOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.ZerosLike' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    arg = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ::mlir::stablehlo::getConstantLike(rewriter, odsLoc, 0, (*arg.begin())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:425
*/
struct GeneratedConvert48 : public ::mlir::RewritePattern {
  GeneratedConvert48(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.OnesLike", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range arg(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::OnesLikeOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.OnesLike' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    arg = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ::mlir::stablehlo::getConstantLike(rewriter, odsLoc, 1, (*arg.begin())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:432
*/
struct GeneratedConvert49 : public ::mlir::RewritePattern {
  GeneratedConvert49(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Elu", 1, context, {"stablehlo.compare", "stablehlo.exponential_minus_one", "stablehlo.select"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range features(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::EluOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Elu' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    features = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto zero = ::mlir::stablehlo::getConstantLike(rewriter, odsLoc, 0, (*features.begin())); (void)zero;
    auto nativeVar_0 = ::mlir::stablehlo::ComparisonTypeAttr(); (void)nativeVar_0;
    ::mlir::stablehlo::CompareOp tblgen_CompareOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*features.begin());
      ::mlir::Value tblgen_value_1 = zero;
      tblgen_CompareOp_1 = ::mlir::stablehlo::CompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        ::mlir::stablehlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::stablehlo::ComparisonDirection::GT),
        /*compare_type=*/nativeVar_0
      );
    }
    ::mlir::stablehlo::Expm1Op tblgen_Expm1Op_2;
    {
      ::mlir::Value tblgen_value_0 = (*features.begin());
      tblgen_Expm1Op_2 = ::mlir::stablehlo::Expm1Op::create(rewriter, odsLoc,
        /*operand=*/tblgen_value_0,
        ::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT))
      );
    }
    ::mlir::stablehlo::SelectOp tblgen_SelectOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SelectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_CompareOp_1.getODSResults(0).begin()));
      tblgen_values.push_back((*features.begin()));
      tblgen_values.push_back((*tblgen_Expm1Op_2.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SelectOp_3 = ::mlir::stablehlo::SelectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SelectOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:441
*/
struct GeneratedConvert50 : public ::mlir::RewritePattern {
  GeneratedConvert50(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.EluGrad", 1, context, {"chlo.broadcast_add", "chlo.broadcast_compare", "stablehlo.constant", "stablehlo.multiply", "stablehlo.select"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range features(op0->getOperands());
    ::mlir::Operation::operand_range gradients(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::EluGradOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns3(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.EluGrad' failed to satisfy constraint: 'statically shaped tensor of any type values'"))) {
      return ::mlir::failure();
    }
    gradients = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.EluGrad' failed to satisfy constraint: 'ranked tensor of any type values'"))) {
      return ::mlir::failure();
    }
    features = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getScalarOfType(getElementTypeOrSelf((*features.begin())),0); (void)nativeVar_0;
    ::mlir::stablehlo::ConstantOp zero;
    {
      zero = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    auto nativeVar_1 = hlo::getBroadcastDimensionsAttr(&rewriter, (*zero.getODSResults(0).begin()), (*features.begin())); (void)nativeVar_1;
    auto nativeVar_2 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_2;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*features.begin());
      ::mlir::Value tblgen_value_1 = (*zero.getODSResults(0).begin());
      tblgen_BroadcastCompareOp_3 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_1,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::GT),
        /*compare_type=*/nativeVar_2
      );
    }
    auto nativeVar_4 = hlo::getScalarOfType(getElementTypeOrSelf((*features.begin())),1); (void)nativeVar_4;
    ::mlir::stablehlo::ConstantOp one;
    {
      one = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_4
      );
    }
    auto nativeVar_5 = hlo::getBroadcastDimensionsAttr(&rewriter, (*one.getODSResults(0).begin()), (*features.begin())); (void)nativeVar_5;
    ::mlir::chlo::BroadcastAddOp tblgen_BroadcastAddOp_6;
    {
      ::mlir::Value tblgen_value_0 = (*features.begin());
      ::mlir::Value tblgen_value_1 = (*one.getODSResults(0).begin());
      tblgen_BroadcastAddOp_6 = ::mlir::chlo::BroadcastAddOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_5
      );
    }
    ::mlir::stablehlo::MulOp tblgen_MulOp_7;
    {
      ::mlir::Value tblgen_value_0 = (*gradients.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_BroadcastAddOp_6.getODSResults(0).begin());
      tblgen_MulOp_7 = ::mlir::stablehlo::MulOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    ::mlir::stablehlo::SelectOp tblgen_SelectOp_8;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SelectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_BroadcastCompareOp_3.getODSResults(0).begin()));
      tblgen_values.push_back((*gradients.begin()));
      tblgen_values.push_back((*tblgen_MulOp_7.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SelectOp_8 = ::mlir::stablehlo::SelectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SelectOp_8.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:464
*/
struct GeneratedConvert51 : public ::mlir::RewritePattern {
  GeneratedConvert51(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Relu", 1, context, {"chlo.broadcast_maximum", "stablehlo.constant"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ReluOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Relu' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);
    if (!(((::llvm::isa<::mlir::TensorType>(((*input.begin()).getType())))) && ([](::mlir::Type elementType) { return (((((elementType.isSignlessInteger(4))) || ((llvm::isa<mlir::TF::Int4RefType>(elementType)))) || (((elementType.isSignlessInteger(8))) || ((llvm::isa<mlir::TF::Int8RefType>(elementType)))) || (((elementType.isSignlessInteger(16))) || ((llvm::isa<mlir::TF::Int16RefType>(elementType)))) || (((elementType.isSignlessInteger(32))) || ((llvm::isa<mlir::TF::Int32RefType>(elementType)))) || (((elementType.isSignlessInteger(64))) || ((llvm::isa<mlir::TF::Int64RefType>(elementType))))) || ((((elementType.isUnsignedInteger(4))) || ((llvm::isa<mlir::TF::Uint4RefType>(elementType)))) || (((elementType.isUnsignedInteger(8))) || ((llvm::isa<mlir::TF::Uint8RefType>(elementType)))) || (((elementType.isUnsignedInteger(16))) || ((llvm::isa<mlir::TF::Uint16RefType>(elementType)))) || (((elementType.isUnsignedInteger(32))) || ((llvm::isa<mlir::TF::Uint32RefType>(elementType)))) || (((elementType.isUnsignedInteger(64))) || ((llvm::isa<mlir::TF::Uint64RefType>(elementType)))))) || ((((elementType.isF16())) || ((llvm::isa<mlir::TF::HalfRefType>(elementType)))) || (((elementType.isF32())) || ((llvm::isa<mlir::TF::FloatRefType>(elementType)))) || (((elementType.isF64())) || ((llvm::isa<mlir::TF::DoubleRefType>(elementType)))) || (((::llvm::isa<::mlir::BFloat16Type>(elementType))) || ((llvm::isa<mlir::TF::Bfloat16RefType>(elementType)))) || (((::llvm::isa<::mlir::Float8E4M3FNType>(elementType))) || ((llvm::isa<mlir::TF::Float8E4M3FNRefType>(elementType)))) || (((::llvm::isa<::mlir::Float8E5M2Type>(elementType))) || ((llvm::isa<mlir::TF::Float8E5M2RefType>(elementType))))); }(::llvm::cast<::mlir::ShapedType>(((*input.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'input' failed to satisfy constraint: 'tensor of integer or floating-point values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getScalarOfType(getElementTypeOrSelf((*input.begin())),0); (void)nativeVar_0;
    ::mlir::stablehlo::ConstantOp zero;
    {
      zero = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    auto nativeVar_1 = hlo::getBroadcastDimensionsAttr(&rewriter, (*zero.getODSResults(0).begin()), (*input.begin())); (void)nativeVar_1;
    ::mlir::chlo::BroadcastMaxOp tblgen_BroadcastMaxOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastMaxOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*zero.getODSResults(0).begin()));
      tblgen_values.push_back((*input.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastMaxOp_2 = ::mlir::chlo::BroadcastMaxOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastMaxOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:471
*/
struct GeneratedConvert52 : public ::mlir::RewritePattern {
  GeneratedConvert52(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Relu6", 1, context, {"stablehlo.clamp", "stablehlo.constant"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::Relu6Op>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Relu6' failed to satisfy constraint: 'ranked tensor of any type values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);
    if (!(((::llvm::isa<::mlir::TensorType>(((*input.begin()).getType())))) && ([](::mlir::Type elementType) { return (((((elementType.isSignlessInteger(4))) || ((llvm::isa<mlir::TF::Int4RefType>(elementType)))) || (((elementType.isSignlessInteger(8))) || ((llvm::isa<mlir::TF::Int8RefType>(elementType)))) || (((elementType.isSignlessInteger(16))) || ((llvm::isa<mlir::TF::Int16RefType>(elementType)))) || (((elementType.isSignlessInteger(32))) || ((llvm::isa<mlir::TF::Int32RefType>(elementType)))) || (((elementType.isSignlessInteger(64))) || ((llvm::isa<mlir::TF::Int64RefType>(elementType))))) || ((((elementType.isUnsignedInteger(4))) || ((llvm::isa<mlir::TF::Uint4RefType>(elementType)))) || (((elementType.isUnsignedInteger(8))) || ((llvm::isa<mlir::TF::Uint8RefType>(elementType)))) || (((elementType.isUnsignedInteger(16))) || ((llvm::isa<mlir::TF::Uint16RefType>(elementType)))) || (((elementType.isUnsignedInteger(32))) || ((llvm::isa<mlir::TF::Uint32RefType>(elementType)))) || (((elementType.isUnsignedInteger(64))) || ((llvm::isa<mlir::TF::Uint64RefType>(elementType)))))) || ((((elementType.isF16())) || ((llvm::isa<mlir::TF::HalfRefType>(elementType)))) || (((elementType.isF32())) || ((llvm::isa<mlir::TF::FloatRefType>(elementType)))) || (((elementType.isF64())) || ((llvm::isa<mlir::TF::DoubleRefType>(elementType)))) || (((::llvm::isa<::mlir::BFloat16Type>(elementType))) || ((llvm::isa<mlir::TF::Bfloat16RefType>(elementType)))) || (((::llvm::isa<::mlir::Float8E4M3FNType>(elementType))) || ((llvm::isa<mlir::TF::Float8E4M3FNRefType>(elementType)))) || (((::llvm::isa<::mlir::Float8E5M2Type>(elementType))) || ((llvm::isa<mlir::TF::Float8E5M2RefType>(elementType))))); }(::llvm::cast<::mlir::ShapedType>(((*input.begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'input' failed to satisfy constraint: 'tensor of integer or floating-point values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = hlo::getScalarOfType(getElementTypeOrSelf((*input.begin())),0); (void)nativeVar_0;
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_1;
    {
      tblgen_ConstantOp_1 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    auto nativeVar_2 = hlo::getScalarOfType(getElementTypeOrSelf((*input.begin())),6); (void)nativeVar_2;
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_3;
    {
      tblgen_ConstantOp_3 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_2
      );
    }
    ::mlir::stablehlo::ClampOp tblgen_ClampOp_4;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::ClampOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_ConstantOp_1.getODSResults(0).begin()));
      tblgen_values.push_back((*input.begin()));
      tblgen_values.push_back((*tblgen_ConstantOp_3.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ClampOp_4 = ::mlir::stablehlo::ClampOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ClampOp_4.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:480
*/
struct GeneratedConvert53 : public ::mlir::RewritePattern {
  GeneratedConvert53(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ReluGrad", 1, context, {"stablehlo.compare", "stablehlo.select"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range features(op0->getOperands());
    ::mlir::Operation::operand_range gradients(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ReluGradOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.ReluGrad' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    gradients = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.ReluGrad' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    features = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto zero = ::mlir::stablehlo::getConstantLike(rewriter, odsLoc, 0, (*features.begin())); (void)zero;
    auto nativeVar_0 = ::mlir::stablehlo::ComparisonTypeAttr(); (void)nativeVar_0;
    ::mlir::stablehlo::CompareOp tblgen_CompareOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*features.begin());
      ::mlir::Value tblgen_value_1 = zero;
      tblgen_CompareOp_1 = ::mlir::stablehlo::CompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        ::mlir::stablehlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::stablehlo::ComparisonDirection::GT),
        /*compare_type=*/nativeVar_0
      );
    }
    ::mlir::stablehlo::SelectOp tblgen_SelectOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SelectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_CompareOp_1.getODSResults(0).begin()));
      tblgen_values.push_back((*gradients.begin()));
      tblgen_values.push_back(zero);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SelectOp_2 = ::mlir::stablehlo::SelectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SelectOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:492
*/
struct GeneratedConvert54 : public ::mlir::RewritePattern {
  GeneratedConvert54(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Softsign", 1, context, {"stablehlo.abs", "stablehlo.add", "stablehlo.divide"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SoftsignOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Softsign' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ::mlir::stablehlo::getConstantLike(rewriter, odsLoc, 1, (*input.begin())); (void)nativeVar_0;
    ::mlir::stablehlo::AbsOp tblgen_AbsOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*input.begin());
      tblgen_AbsOp_1 = ::mlir::stablehlo::AbsOp::create(rewriter, odsLoc,
        /*operand=*/tblgen_value_0
      );
    }
    ::mlir::stablehlo::AddOp tblgen_AddOp_2;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      ::mlir::Value tblgen_value_1 = (*tblgen_AbsOp_1.getODSResults(0).begin());
      tblgen_AddOp_2 = ::mlir::stablehlo::AddOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    ::mlir::stablehlo::DivOp tblgen_DivOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DivOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_values.push_back((*tblgen_AddOp_2.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DivOp_3 = ::mlir::stablehlo::DivOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DivOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:501
*/
struct GeneratedConvert55 : public ::mlir::RewritePattern {
  GeneratedConvert55(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.SoftsignGrad", 1, context, {"chlo.broadcast_add", "chlo.broadcast_divide", "stablehlo.abs", "stablehlo.constant", "stablehlo.multiply"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range features(op0->getOperands());
    ::mlir::Operation::operand_range gradients(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SoftsignGradOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.SoftsignGrad' failed to satisfy constraint: 'ranked tensor of any type values'"))) {
      return ::mlir::failure();
    }
    gradients = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.SoftsignGrad' failed to satisfy constraint: 'ranked tensor of any type values'"))) {
      return ::mlir::failure();
    }
    features = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = hlo::getScalarOfType(getElementTypeOrSelf((*features.begin())),1); (void)nativeVar_0;
    ::mlir::stablehlo::ConstantOp one;
    {
      one = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    ::mlir::stablehlo::AbsOp tblgen_AbsOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*features.begin());
      tblgen_AbsOp_1 = ::mlir::stablehlo::AbsOp::create(rewriter, odsLoc,
        /*operand=*/tblgen_value_0
      );
    }
    auto nativeVar_2 = hlo::getBroadcastDimensionsAttr(&rewriter, (*one.getODSResults(0).begin()), (*features.begin())); (void)nativeVar_2;
    ::mlir::chlo::BroadcastAddOp add;
    {
      ::mlir::Value tblgen_value_0 = (*one.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_AbsOp_1.getODSResults(0).begin());
      add = ::mlir::chlo::BroadcastAddOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_2
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::MulOp tblgen_MulOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*add.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*add.getODSResults(0).begin());
      tblgen_MulOp_3 = ::mlir::stablehlo::MulOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_4 = hlo::getBroadcastDimensionsAttr(&rewriter, (*gradients.begin()), (*add.getODSResults(0).begin())); (void)nativeVar_4;
    ::mlir::chlo::BroadcastDivOp tblgen_BroadcastDivOp_5;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastDivOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*gradients.begin()));
      tblgen_values.push_back((*tblgen_MulOp_3.getODSResults(0).begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_4);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastDivOp_5 = ::mlir::chlo::BroadcastDivOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastDivOp_5.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:528
*/
struct GeneratedConvert56 : public ::mlir::RewritePattern {
  GeneratedConvert56(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Slice", 1, context, {"stablehlo.dynamic_slice"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::SliceOp op;
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::mlir::Operation::operand_range starting_indices(op0->getOperands());
    ::mlir::Attribute slice_sizes;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SliceOp>(op0); (void)castedOp0;
    op = castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Slice' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.Slice' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    starting_indices = castedOp0.getODSOperands(1);
    {
      auto *op1 = (*castedOp0.getODSOperands(2).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 2 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_5(rewriter, op1, tblgen_ops, slice_sizes))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((CanBeTranslatedToDynamicSlice((*input.begin()), (*starting_indices.begin()), llvm::cast<DenseIntElementsAttr>(slice_sizes))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'input, starting_indices, slice_sizes' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = UnpackTensorAlongZeroDim((*op.getODSResults(0).begin()).getLoc(), (*starting_indices.begin()), &rewriter).getOutput(); (void)nativeVar_0;
    auto nativeVar_1 = TFSliceSizes2HLOSliceSizes((*input.begin()), (*starting_indices.begin()), llvm::cast<DenseIntElementsAttr>(slice_sizes),&rewriter); (void)nativeVar_1;
    ::mlir::stablehlo::DynamicSliceOp tblgen_DynamicSliceOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DynamicSliceOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      for (auto v: nativeVar_0) {
        tblgen_values.push_back(v);
      }
      tblgen_props.slice_sizes = ::llvm::dyn_cast_if_present<decltype(tblgen_props.slice_sizes)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DynamicSliceOp_2 = ::mlir::stablehlo::DynamicSliceOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DynamicSliceOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:540
*/
struct GeneratedConvert57 : public ::mlir::RewritePattern {
  GeneratedConvert57(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.SelectV2", 1, context, {"chlo.broadcast_select"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range pred(op0->getOperands());
    ::mlir::Operation::operand_range on_true(op0->getOperands());
    ::mlir::Operation::operand_range on_false(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SelectV2Op>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.SelectV2' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    pred = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.SelectV2' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    on_true = castedOp0.getODSOperands(1);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(2).begin()).getType(), "operand 2 of op 'tf.SelectV2' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    on_false = castedOp0.getODSOperands(2);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::BroadcastSelectOp tblgen_BroadcastSelectOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::BroadcastSelectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*pred.begin()));
      tblgen_values.push_back((*on_true.begin()));
      tblgen_values.push_back((*on_false.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BroadcastSelectOp_0 = ::mlir::chlo::BroadcastSelectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BroadcastSelectOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:554
*/
struct GeneratedConvert58 : public ::mlir::RewritePattern {
  GeneratedConvert58(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.PartitionedCall", 1, context, {"func.call"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::PartitionedCallOp op;
    ::mlir::Operation::operand_range args(op0->getOperands());
    ::mlir::StringAttr config;
    ::mlir::ArrayAttr args_attrs;
    ::mlir::StringAttr config_proto;
    ::mlir::ArrayAttr res_attrs;
    ::mlir::StringAttr executor_type;
    ::mlir::SymbolRefAttr f;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::PartitionedCallOp>(op0); (void)castedOp0;
    op = castedOp0;
    args = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getArgAttrs();
      args_attrs = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResAttrs();
      res_attrs = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getF();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.PartitionedCall' to have attribute 'f' of type '::mlir::SymbolRefAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns6(rewriter, castedOp0, tblgen_attr, "op 'tf.PartitionedCall' attribute 'f' failed to satisfy constraint: 'flat symbol reference attribute'"))) {
        return ::mlir::failure();
      }
      f = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getConfig();
      if (!tblgen_attr) tblgen_attr = rewriter.getStringAttr("");
      config = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getConfigProto();
      if (!tblgen_attr) tblgen_attr = rewriter.getStringAttr("");
      config_proto = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getExecutorType();
      if (!tblgen_attr) tblgen_attr = rewriter.getStringAttr("");
      executor_type = tblgen_attr;
    }
    if (!((ArgTypesMatchCallee(&*rewriter.getInsertionPoint(), args, f)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op, args, f' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::func::CallOp tblgen_CallOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::func::CallOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_props.callee = ::llvm::dyn_cast_if_present<decltype(tblgen_props.callee)>(f);
      for (auto v: args) {
        tblgen_values.push_back(v);
      }
      tblgen_props.arg_attrs = ::llvm::dyn_cast_if_present<decltype(tblgen_props.arg_attrs)>(args_attrs);
      tblgen_props.res_attrs = ::llvm::dyn_cast_if_present<decltype(tblgen_props.res_attrs)>(res_attrs);
      tblgen_props.no_inline = ::llvm::dyn_cast_if_present<decltype(tblgen_props.no_inline)>(((false) ? rewriter.getUnitAttr() : nullptr));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_CallOp_0 = ::mlir::func::CallOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_CallOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:554
*/
struct GeneratedConvert59 : public ::mlir::RewritePattern {
  GeneratedConvert59(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.StatefulPartitionedCall", 1, context, {"func.call"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::StatefulPartitionedCallOp op;
    ::mlir::Operation::operand_range args(op0->getOperands());
    ::mlir::StringAttr config;
    ::mlir::ArrayAttr args_attrs;
    ::mlir::StringAttr config_proto;
    ::mlir::ArrayAttr res_attrs;
    ::mlir::StringAttr executor_type;
    ::mlir::FlatSymbolRefAttr f;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::StatefulPartitionedCallOp>(op0); (void)castedOp0;
    op = castedOp0;
    args = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getArgAttrs();
      args_attrs = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResAttrs();
      res_attrs = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getF();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.StatefulPartitionedCall' to have attribute 'f' of type '::mlir::FlatSymbolRefAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns6(rewriter, castedOp0, tblgen_attr, "op 'tf.StatefulPartitionedCall' attribute 'f' failed to satisfy constraint: 'flat symbol reference attribute'"))) {
        return ::mlir::failure();
      }
      f = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getConfig();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.StatefulPartitionedCall' to have attribute 'config' of type '::mlir::StringAttr'";
        });
      }
      config = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getConfigProto();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.StatefulPartitionedCall' to have attribute 'config_proto' of type '::mlir::StringAttr'";
        });
      }
      config_proto = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getExecutorType();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.StatefulPartitionedCall' to have attribute 'executor_type' of type '::mlir::StringAttr'";
        });
      }
      executor_type = tblgen_attr;
    }
    if (!((ArgTypesMatchCallee(&*rewriter.getInsertionPoint(), args, f)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op, args, f' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::func::CallOp tblgen_CallOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::func::CallOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_props.callee = ::llvm::dyn_cast_if_present<decltype(tblgen_props.callee)>(f);
      for (auto v: args) {
        tblgen_values.push_back(v);
      }
      tblgen_props.arg_attrs = ::llvm::dyn_cast_if_present<decltype(tblgen_props.arg_attrs)>(args_attrs);
      tblgen_props.res_attrs = ::llvm::dyn_cast_if_present<decltype(tblgen_props.res_attrs)>(res_attrs);
      tblgen_props.no_inline = ::llvm::dyn_cast_if_present<decltype(tblgen_props.no_inline)>(((false) ? rewriter.getUnitAttr() : nullptr));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_CallOp_0 = ::mlir::func::CallOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_CallOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:563
*/
struct GeneratedConvert60 : public ::mlir::RewritePattern {
  GeneratedConvert60(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.LegacyCall", 1, context, {"func.call"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::BoolAttr attr;
    ::mlir::TF::LegacyCallOp op;
    ::mlir::Operation::operand_range args(op0->getOperands());
    ::mlir::ArrayAttr args_attrs;
    ::mlir::ArrayAttr res_attrs;
    ::mlir::FlatSymbolRefAttr f;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::LegacyCallOp>(op0); (void)castedOp0;
    op = castedOp0;
    args = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getArgAttrs();
      args_attrs = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getResAttrs();
      res_attrs = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getF();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.LegacyCall' to have attribute 'f' of type '::mlir::FlatSymbolRefAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns6(rewriter, castedOp0, tblgen_attr, "op 'tf.LegacyCall' attribute 'f' failed to satisfy constraint: 'flat symbol reference attribute'"))) {
        return ::mlir::failure();
      }
      f = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().get_disableCallShapeInference();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      attr = tblgen_attr;
    }
    if (!((ArgTypesMatchCallee(&*rewriter.getInsertionPoint(), args, f)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op, args, f' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::func::CallOp tblgen_CallOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::func::CallOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_props.callee = ::llvm::dyn_cast_if_present<decltype(tblgen_props.callee)>(f);
      for (auto v: args) {
        tblgen_values.push_back(v);
      }
      tblgen_props.arg_attrs = ::llvm::dyn_cast_if_present<decltype(tblgen_props.arg_attrs)>(args_attrs);
      tblgen_props.res_attrs = ::llvm::dyn_cast_if_present<decltype(tblgen_props.res_attrs)>(res_attrs);
      tblgen_props.no_inline = ::llvm::dyn_cast_if_present<decltype(tblgen_props.no_inline)>(((false) ? rewriter.getUnitAttr() : nullptr));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_CallOp_0 = ::mlir::func::CallOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_CallOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:576
*/
struct GeneratedConvert61 : public ::mlir::RewritePattern {
  GeneratedConvert61(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ReverseV2", 1, context, {"stablehlo.reverse"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range values(op0->getOperands());
    ::mlir::Attribute axis;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ReverseV2Op>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.ReverseV2' failed to satisfy constraint: 'ranked tensor of any type values'"))) {
      return ::mlir::failure();
    }
    values = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, axis))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ConvertAxisAttr((*values.begin()), llvm::cast<ElementsAttr>(axis), &rewriter); (void)nativeVar_0;
    ::mlir::stablehlo::ReverseOp tblgen_ReverseOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::ReverseOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*values.begin()));
      tblgen_props.dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.dimensions)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ReverseOp_1 = ::mlir::stablehlo::ReverseOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ReverseOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert62 : public ::mlir::RewritePattern {
  GeneratedConvert62(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Abs", 1, context, {"stablehlo.abs"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AbsOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Abs' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::AbsOp tblgen_AbsOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::AbsOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AbsOp_0 = ::mlir::stablehlo::AbsOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AbsOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert63 : public ::mlir::RewritePattern {
  GeneratedConvert63(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Ceil", 1, context, {"stablehlo.ceil"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::CeilOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Ceil' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::CeilOp tblgen_CeilOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::CeilOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_CeilOp_0 = ::mlir::stablehlo::CeilOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_CeilOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert64 : public ::mlir::RewritePattern {
  GeneratedConvert64(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ComplexAbs", 1, context, {"stablehlo.abs"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ComplexAbsOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.ComplexAbs' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::AbsOp tblgen_AbsOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::AbsOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AbsOp_0 = ::mlir::stablehlo::AbsOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AbsOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert65 : public ::mlir::RewritePattern {
  GeneratedConvert65(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Erf", 1, context, {"chlo.erf"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ErfOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Erf' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::ErfOp tblgen_ErfOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::ErfOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ErfOp_0 = ::mlir::chlo::ErfOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ErfOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert66 : public ::mlir::RewritePattern {
  GeneratedConvert66(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Floor", 1, context, {"stablehlo.floor"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::FloorOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Floor' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::FloorOp tblgen_FloorOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::FloorOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_FloorOp_0 = ::mlir::stablehlo::FloorOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_FloorOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert67 : public ::mlir::RewritePattern {
  GeneratedConvert67(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Imag", 1, context, {"stablehlo.imag"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ImagOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Imag' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::ImagOp tblgen_ImagOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::ImagOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ImagOp_0 = ::mlir::stablehlo::ImagOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ImagOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert68 : public ::mlir::RewritePattern {
  GeneratedConvert68(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Invert", 1, context, {"stablehlo.not"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::InvertOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Invert' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::NotOp tblgen_NotOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::NotOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_NotOp_0 = ::mlir::stablehlo::NotOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_NotOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert69 : public ::mlir::RewritePattern {
  GeneratedConvert69(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.IsFinite", 1, context, {"stablehlo.is_finite"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::IsFiniteOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.IsFinite' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::IsFiniteOp tblgen_IsFiniteOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::IsFiniteOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_IsFiniteOp_0 = ::mlir::stablehlo::IsFiniteOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_IsFiniteOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert70 : public ::mlir::RewritePattern {
  GeneratedConvert70(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.LogicalNot", 1, context, {"stablehlo.not"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::LogicalNotOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.LogicalNot' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::NotOp tblgen_NotOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::NotOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_NotOp_0 = ::mlir::stablehlo::NotOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_NotOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert71 : public ::mlir::RewritePattern {
  GeneratedConvert71(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Neg", 1, context, {"stablehlo.negate"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::NegOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Neg' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::NegOp tblgen_NegOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::NegOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_NegOp_0 = ::mlir::stablehlo::NegOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_NegOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:596
*/
struct GeneratedConvert72 : public ::mlir::RewritePattern {
  GeneratedConvert72(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Real", 1, context, {"stablehlo.real"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::RealOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Real' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::RealOp tblgen_RealOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::RealOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_RealOp_0 = ::mlir::stablehlo::RealOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_RealOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert73 : public ::mlir::RewritePattern {
  GeneratedConvert73(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Cos", 1, context, {"stablehlo.cosine"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::CosOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Cos' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::CosineOp tblgen_CosineOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::CosineOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_CosineOp_0 = ::mlir::stablehlo::CosineOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_CosineOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert74 : public ::mlir::RewritePattern {
  GeneratedConvert74(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Exp", 1, context, {"stablehlo.exponential"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ExpOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Exp' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::ExpOp tblgen_ExpOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::ExpOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ExpOp_0 = ::mlir::stablehlo::ExpOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ExpOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert75 : public ::mlir::RewritePattern {
  GeneratedConvert75(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Expm1", 1, context, {"stablehlo.exponential_minus_one"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::Expm1Op>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Expm1' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::Expm1Op tblgen_Expm1Op_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::Expm1Op::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_Expm1Op_0 = ::mlir::stablehlo::Expm1Op::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_Expm1Op_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert76 : public ::mlir::RewritePattern {
  GeneratedConvert76(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Log", 1, context, {"stablehlo.log"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::LogOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Log' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::LogOp tblgen_LogOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::LogOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_LogOp_0 = ::mlir::stablehlo::LogOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_LogOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert77 : public ::mlir::RewritePattern {
  GeneratedConvert77(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Log1p", 1, context, {"stablehlo.log_plus_one"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::Log1pOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Log1p' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::Log1pOp tblgen_Log1pOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::Log1pOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_Log1pOp_0 = ::mlir::stablehlo::Log1pOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_Log1pOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert78 : public ::mlir::RewritePattern {
  GeneratedConvert78(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Rsqrt", 1, context, {"stablehlo.rsqrt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::RsqrtOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Rsqrt' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::RsqrtOp tblgen_RsqrtOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::RsqrtOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_RsqrtOp_0 = ::mlir::stablehlo::RsqrtOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_RsqrtOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert79 : public ::mlir::RewritePattern {
  GeneratedConvert79(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Sigmoid", 1, context, {"stablehlo.logistic"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SigmoidOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Sigmoid' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::LogisticOp tblgen_LogisticOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::LogisticOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_LogisticOp_0 = ::mlir::stablehlo::LogisticOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_LogisticOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert80 : public ::mlir::RewritePattern {
  GeneratedConvert80(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Sin", 1, context, {"stablehlo.sine"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SinOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Sin' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::SineOp tblgen_SineOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SineOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SineOp_0 = ::mlir::stablehlo::SineOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SineOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert81 : public ::mlir::RewritePattern {
  GeneratedConvert81(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Sqrt", 1, context, {"stablehlo.sqrt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SqrtOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Sqrt' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::SqrtOp tblgen_SqrtOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SqrtOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SqrtOp_0 = ::mlir::stablehlo::SqrtOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SqrtOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert82 : public ::mlir::RewritePattern {
  GeneratedConvert82(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Tanh", 1, context, {"stablehlo.tanh"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::TanhOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Tanh' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::TanhOp tblgen_TanhOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::TanhOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_TanhOp_0 = ::mlir::stablehlo::TanhOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_TanhOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:614
*/
struct GeneratedConvert83 : public ::mlir::RewritePattern {
  GeneratedConvert83(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Tan", 1, context, {"stablehlo.tan"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::TanOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Tan' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::TanOp tblgen_TanOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::TanOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.result_accuracy = ::llvm::dyn_cast_if_present<decltype(tblgen_props.result_accuracy)>(::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT)));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_TanOp_0 = ::mlir::stablehlo::TanOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_TanOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert84 : public ::mlir::RewritePattern {
  GeneratedConvert84(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Acos", 1, context, {"chlo.acos"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AcosOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Acos' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::AcosOp tblgen_AcosOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::AcosOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AcosOp_0 = ::mlir::chlo::AcosOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AcosOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert85 : public ::mlir::RewritePattern {
  GeneratedConvert85(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Acosh", 1, context, {"chlo.acosh"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AcoshOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Acosh' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::AcoshOp tblgen_AcoshOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::AcoshOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AcoshOp_0 = ::mlir::chlo::AcoshOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AcoshOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert86 : public ::mlir::RewritePattern {
  GeneratedConvert86(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Asin", 1, context, {"chlo.asin"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AsinOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Asin' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::AsinOp tblgen_AsinOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::AsinOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AsinOp_0 = ::mlir::chlo::AsinOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AsinOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert87 : public ::mlir::RewritePattern {
  GeneratedConvert87(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Asinh", 1, context, {"chlo.asinh"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AsinhOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Asinh' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::AsinhOp tblgen_AsinhOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::AsinhOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AsinhOp_0 = ::mlir::chlo::AsinhOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AsinhOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert88 : public ::mlir::RewritePattern {
  GeneratedConvert88(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Atan", 1, context, {"chlo.atan"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AtanOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Atan' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::AtanOp tblgen_AtanOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::AtanOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AtanOp_0 = ::mlir::chlo::AtanOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AtanOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert89 : public ::mlir::RewritePattern {
  GeneratedConvert89(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Atanh", 1, context, {"chlo.atanh"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AtanhOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Atanh' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::AtanhOp tblgen_AtanhOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::AtanhOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AtanhOp_0 = ::mlir::chlo::AtanhOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AtanhOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert90 : public ::mlir::RewritePattern {
  GeneratedConvert90(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Cosh", 1, context, {"chlo.cosh"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::CoshOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Cosh' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::CoshOp tblgen_CoshOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::CoshOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_CoshOp_0 = ::mlir::chlo::CoshOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_CoshOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert91 : public ::mlir::RewritePattern {
  GeneratedConvert91(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Conj", 1, context, {"chlo.conj"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ConjOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Conj' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::ConjOp tblgen_ConjOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::ConjOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ConjOp_0 = ::mlir::chlo::ConjOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ConjOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert92 : public ::mlir::RewritePattern {
  GeneratedConvert92(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Digamma", 1, context, {"chlo.digamma"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::DigammaOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Digamma' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::DigammaOp tblgen_DigammaOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::DigammaOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DigammaOp_0 = ::mlir::chlo::DigammaOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DigammaOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert93 : public ::mlir::RewritePattern {
  GeneratedConvert93(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Erfc", 1, context, {"chlo.erfc"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ErfcOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Erfc' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::ErfcOp tblgen_ErfcOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::ErfcOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ErfcOp_0 = ::mlir::chlo::ErfcOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ErfcOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert94 : public ::mlir::RewritePattern {
  GeneratedConvert94(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.IsInf", 1, context, {"chlo.is_inf"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::IsInfOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.IsInf' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::IsInfOp tblgen_IsInfOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::IsInfOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_IsInfOp_0 = ::mlir::chlo::IsInfOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_IsInfOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert95 : public ::mlir::RewritePattern {
  GeneratedConvert95(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Lgamma", 1, context, {"chlo.lgamma"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::LgammaOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Lgamma' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::LgammaOp tblgen_LgammaOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::LgammaOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_LgammaOp_0 = ::mlir::chlo::LgammaOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_LgammaOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:633
*/
struct GeneratedConvert96 : public ::mlir::RewritePattern {
  GeneratedConvert96(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Sinh", 1, context, {"chlo.sinh"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SinhOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns5(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Sinh' failed to satisfy constraint: 'tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized or per-axis integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::chlo::SinhOp tblgen_SinhOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::chlo::SinhOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SinhOp_0 = ::mlir::chlo::SinhOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SinhOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:637
*/
struct GeneratedConvert97 : public ::mlir::RewritePattern {
  GeneratedConvert97(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Angle", 1, context, {"stablehlo.atan2", "stablehlo.imag", "stablehlo.real"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::AngleOp>(op0); (void)castedOp0;
    x = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::ImagOp tblgen_ImagOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_ImagOp_0 = ::mlir::stablehlo::ImagOp::create(rewriter, odsLoc,
        /*operand=*/tblgen_value_0
      );
    }
    ::mlir::stablehlo::RealOp tblgen_RealOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_RealOp_1 = ::mlir::stablehlo::RealOp::create(rewriter, odsLoc,
        /*operand=*/tblgen_value_0
      );
    }
    ::mlir::stablehlo::Atan2Op tblgen_Atan2Op_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::Atan2Op::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_ImagOp_0.getODSResults(0).begin()));
      tblgen_values.push_back((*tblgen_RealOp_1.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_Atan2Op_2 = ::mlir::stablehlo::Atan2Op::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_Atan2Op_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:640
*/
struct GeneratedConvert98 : public ::mlir::RewritePattern {
  GeneratedConvert98(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Cast", 1, context, {"stablehlo.convert"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range arg(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::CastOp>(op0); (void)castedOp0;
    arg = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getTruncate();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      if (!tblgen_attr) return ::mlir::failure();
      if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns7(rewriter, castedOp0, tblgen_attr, "op 'tf.Cast' attribute 'Truncate' failed to satisfy constraint: 'constant attribute false'"))) {
        return ::mlir::failure();
      }
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::ConvertOp tblgen_ConvertOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::ConvertOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*arg.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ConvertOp_0 = ::mlir::stablehlo::ConvertOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ConvertOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:642
*/
struct GeneratedConvert99 : public ::mlir::RewritePattern {
  GeneratedConvert99(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Transpose", 1, context, {"stablehlo.transpose"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::TransposeOp res;
    ::mlir::Operation::operand_range arg(op0->getOperands());
    ::mlir::Attribute permutation;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::TransposeOp>(op0); (void)castedOp0;
    res = castedOp0;
    arg = castedOp0.getODSOperands(0);
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
        permutation = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'constant vector/tensor attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = 
      ToDenseI64ArrayAttr(
        llvm::cast<mlir::DenseIntElementsAttr>(hlo::convertElementsAttr(
          llvm::cast<ElementsAttr>(permutation), rewriter.getIntegerType(64))), &rewriter)
      ; (void)nativeVar_0;
    ::mlir::stablehlo::TransposeOp tblgen_TransposeOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::TransposeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*arg.begin()));
      tblgen_props.permutation = ::llvm::dyn_cast_if_present<decltype(tblgen_props.permutation)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_TransposeOp_1 = ::mlir::stablehlo::TransposeOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_TransposeOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:648
*/
struct GeneratedConvert100 : public ::mlir::RewritePattern {
  GeneratedConvert100(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.ExpandDims", 3, context, {"stablehlo.reshape"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::ExpandDimsOp res;
    ::mlir::Operation::operand_range arg(op0->getOperands());
    ::mlir::Operation::operand_range ignored(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ExpandDimsOp>(op0); (void)castedOp0;
    res = castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.ExpandDims' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    arg = castedOp0.getODSOperands(0);
    ignored = castedOp0.getODSOperands(1);
    if (!((((::llvm::isa<::mlir::RankedTensorType>(((*res.getODSResults(0).begin()).getType())))) && ((::llvm::cast<::mlir::ShapedType>(((*res.getODSResults(0).begin()).getType())).hasStaticShape()))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(((*res.getODSResults(0).begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'res' failed to satisfy constraint: 'statically shaped tensor of any type values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::ReshapeOp tblgen_ReshapeOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::ReshapeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*arg.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ReshapeOp_0 = ::mlir::stablehlo::ReshapeOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ReshapeOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:648
*/
struct GeneratedConvert101 : public ::mlir::RewritePattern {
  GeneratedConvert101(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Reshape", 3, context, {"stablehlo.reshape"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::ReshapeOp res;
    ::mlir::Operation::operand_range arg(op0->getOperands());
    ::mlir::Operation::operand_range ignored(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::ReshapeOp>(op0); (void)castedOp0;
    res = castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Reshape' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    arg = castedOp0.getODSOperands(0);
    ignored = castedOp0.getODSOperands(1);
    if (!((((::llvm::isa<::mlir::RankedTensorType>(((*res.getODSResults(0).begin()).getType())))) && ((::llvm::cast<::mlir::ShapedType>(((*res.getODSResults(0).begin()).getType())).hasStaticShape()))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(((*res.getODSResults(0).begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'res' failed to satisfy constraint: 'statically shaped tensor of any type values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::ReshapeOp tblgen_ReshapeOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::ReshapeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*arg.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ReshapeOp_0 = ::mlir::stablehlo::ReshapeOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ReshapeOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:648
*/
struct GeneratedConvert102 : public ::mlir::RewritePattern {
  GeneratedConvert102(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Squeeze", 3, context, {"stablehlo.reshape"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::SqueezeOp res;
    ::mlir::Operation::operand_range arg(op0->getOperands());
    ::mlir::ArrayAttr ignored;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SqueezeOp>(op0); (void)castedOp0;
    res = castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Squeeze' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    arg = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSqueezeDims();
      if (!tblgen_attr) tblgen_attr = rewriter.getI64ArrayAttr({});
      ignored = tblgen_attr;
    }
    if (!((((::llvm::isa<::mlir::RankedTensorType>(((*res.getODSResults(0).begin()).getType())))) && ((::llvm::cast<::mlir::ShapedType>(((*res.getODSResults(0).begin()).getType())).hasStaticShape()))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(((*res.getODSResults(0).begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'res' failed to satisfy constraint: 'statically shaped tensor of any type values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::ReshapeOp tblgen_ReshapeOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::ReshapeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*arg.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ReshapeOp_0 = ::mlir::stablehlo::ReshapeOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ReshapeOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:654
*/
struct GeneratedConvert103 : public ::mlir::RewritePattern {
  GeneratedConvert103(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Sign", 1, context, {"stablehlo.sign"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SignOp>(op0); (void)castedOp0;
    x = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::SignOp tblgen_SignOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SignOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*x.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SignOp_0 = ::mlir::stablehlo::SignOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SignOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:664
*/
struct GeneratedConvert104 : public ::mlir::RewritePattern {
  GeneratedConvert104(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Bitcast", 1, context, {"stablehlo.bitcast_convert"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::BitcastOp res;
    ::mlir::Operation::operand_range arg(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::BitcastOp>(op0); (void)castedOp0;
    res = castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Bitcast' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    arg = castedOp0.getODSOperands(0);
    if (!((getElementTypeOrSelf((*res.getODSResults(0).begin()).getType()).isIntOrFloat() && getElementTypeOrSelf((*arg.begin()).getType()).isIntOrFloat()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'res, arg' failed to satisfy constraint: 'element types must be integers or floats'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::BitcastConvertOp tblgen_BitcastConvertOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::BitcastConvertOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*arg.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_BitcastConvertOp_0 = ::mlir::stablehlo::BitcastConvertOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_BitcastConvertOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:679
*/
struct GeneratedConvert105 : public ::mlir::RewritePattern {
  GeneratedConvert105(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.RandomUniform", 1, context, {"stablehlo.constant", "stablehlo.rng"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range shape(op0->getOperands());
    ::mlir::TF::RandomUniformOp old;
    ::mlir::IntegerAttr seed;
    ::mlir::IntegerAttr seed2;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::RandomUniformOp>(op0); (void)castedOp0;
    old = castedOp0;
    shape = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSeed();
      if (!tblgen_attr) tblgen_attr = rewriter.getIntegerAttr(rewriter.getIntegerType(64), 0);
      seed = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSeed2();
      if (!tblgen_attr) tblgen_attr = rewriter.getIntegerAttr(rewriter.getIntegerType(64), 0);
      seed2 = tblgen_attr;
    }
    if (!((llvm::isa<RankedTensorType>((*shape.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'shape' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getFloatAttr(old.getDtype(), 0.0); (void)nativeVar_0;
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_1;
    {
      tblgen_ConstantOp_1 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    auto nativeVar_2 = rewriter.getFloatAttr(old.getDtype(), 1.0); (void)nativeVar_2;
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_3;
    {
      tblgen_ConstantOp_3 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_2
      );
    }
    auto nativeVar_4 = CastValueToI64((*old.getODSResults(0).begin()).getLoc(), (*shape.begin()), &rewriter); (void)nativeVar_4;
    ::mlir::stablehlo::RngOp tblgen_RngOp_5;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::RngOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_ConstantOp_1.getODSResults(0).begin()));
      tblgen_values.push_back((*tblgen_ConstantOp_3.getODSResults(0).begin()));
      tblgen_values.push_back(nativeVar_4);
      tblgen_props.rng_distribution = ::llvm::dyn_cast_if_present<decltype(tblgen_props.rng_distribution)>(::mlir::stablehlo::RngDistributionAttr::get(rewriter.getContext(), ::mlir::stablehlo::RngDistribution::UNIFORM));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_RngOp_5 = ::mlir::stablehlo::RngOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_RngOp_5.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:689
*/
struct GeneratedConvert106 : public ::mlir::RewritePattern {
  GeneratedConvert106(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.RandomStandardNormal", 1, context, {"stablehlo.constant", "stablehlo.rng"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range shape(op0->getOperands());
    ::mlir::TF::RandomStandardNormalOp old;
    ::mlir::IntegerAttr seed;
    ::mlir::IntegerAttr seed2;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::RandomStandardNormalOp>(op0); (void)castedOp0;
    old = castedOp0;
    shape = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSeed();
      if (!tblgen_attr) tblgen_attr = rewriter.getIntegerAttr(rewriter.getIntegerType(64), 0);
      seed = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getSeed2();
      if (!tblgen_attr) tblgen_attr = rewriter.getIntegerAttr(rewriter.getIntegerType(64), 0);
      seed2 = tblgen_attr;
    }
    if (!((llvm::isa<RankedTensorType>((*shape.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'shape' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getFloatAttr(old.getDtype(), 0.0); (void)nativeVar_0;
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_1;
    {
      tblgen_ConstantOp_1 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    auto nativeVar_2 = rewriter.getFloatAttr(old.getDtype(), 1.0); (void)nativeVar_2;
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_3;
    {
      tblgen_ConstantOp_3 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_2
      );
    }
    auto nativeVar_4 = CastValueToI64((*old.getODSResults(0).begin()).getLoc(), (*shape.begin()), &rewriter); (void)nativeVar_4;
    ::mlir::stablehlo::RngOp tblgen_RngOp_5;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::RngOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_ConstantOp_1.getODSResults(0).begin()));
      tblgen_values.push_back((*tblgen_ConstantOp_3.getODSResults(0).begin()));
      tblgen_values.push_back(nativeVar_4);
      tblgen_props.rng_distribution = ::llvm::dyn_cast_if_present<decltype(tblgen_props.rng_distribution)>(::mlir::stablehlo::RngDistributionAttr::get(rewriter.getContext(), ::mlir::stablehlo::RngDistribution::NORMAL));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_RngOp_5 = ::mlir::stablehlo::RngOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_RngOp_5.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:708
*/
struct GeneratedConvert107 : public ::mlir::RewritePattern {
  GeneratedConvert107(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.SigmoidGrad", 1, context, {"stablehlo.constant", "stablehlo.multiply", "stablehlo.subtract"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range l(op0->getOperands());
    ::mlir::Operation::operand_range r(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SigmoidGradOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.SigmoidGrad' failed to satisfy constraint: 'ranked tensor of any type values'"))) {
      return ::mlir::failure();
    }
    l = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.SigmoidGrad' failed to satisfy constraint: 'ranked tensor of any type values'"))) {
      return ::mlir::failure();
    }
    r = castedOp0.getODSOperands(1);
    if (!((::llvm::dyn_cast<ShapedType>((*l.begin()).getType()).hasStaticShape()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'l' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::MulOp tblgen_MulOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*r.begin());
      ::mlir::Value tblgen_value_1 = (*l.begin());
      tblgen_MulOp_0 = ::mlir::stablehlo::MulOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = hlo::getSplat(&rewriter, (*l.begin()), 1); (void)nativeVar_1;
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_2;
    {
      tblgen_ConstantOp_2 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_1
      );
    }
    ::mlir::stablehlo::SubtractOp tblgen_SubtractOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_ConstantOp_2.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*l.begin());
      tblgen_SubtractOp_3 = ::mlir::stablehlo::SubtractOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    ::mlir::stablehlo::MulOp tblgen_MulOp_4;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::MulOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_MulOp_0.getODSResults(0).begin()));
      tblgen_values.push_back((*tblgen_SubtractOp_3.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_MulOp_4 = ::mlir::stablehlo::MulOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_MulOp_4.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:720
*/
struct GeneratedConvert108 : public ::mlir::RewritePattern {
  GeneratedConvert108(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.Softplus", 1, context, {"chlo.broadcast_add", "chlo.broadcast_compare", "stablehlo.constant", "stablehlo.exponential", "stablehlo.log", "stablehlo.log_plus_one", "stablehlo.negate", "stablehlo.select"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range features(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::SoftplusOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.Softplus' failed to satisfy constraint: 'tensor of any type values'"))) {
      return ::mlir::failure();
    }
    features = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::mlir::stablehlo::ExpOp features_exp;
    {
      ::mlir::Value tblgen_value_0 = (*features.begin());
      features_exp = ::mlir::stablehlo::ExpOp::create(rewriter, odsLoc,
        /*operand=*/tblgen_value_0,
        ::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT))
      );
    }
    auto nativeVar_0 = GetEpsilonValue((*features.begin()).getType()); (void)nativeVar_0;
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_1;
    {
      tblgen_ConstantOp_1 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_0
      );
    }
    ::mlir::stablehlo::LogOp tblgen_LogOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_ConstantOp_1.getODSResults(0).begin());
      tblgen_LogOp_2 = ::mlir::stablehlo::LogOp::create(rewriter, odsLoc,
        /*operand=*/tblgen_value_0,
        ::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT))
      );
    }
    auto nativeVar_3 = hlo::getScalarOfType(getElementTypeOrSelf((*features.begin())),2); (void)nativeVar_3;
    ::mlir::stablehlo::ConstantOp tblgen_ConstantOp_4;
    {
      tblgen_ConstantOp_4 = ::mlir::stablehlo::ConstantOp::create(rewriter, odsLoc,
        /*value=*/nativeVar_3
      );
    }
    auto nativeVar_5 = DenseI64ArrayAttr(); (void)nativeVar_5;
    ::mlir::chlo::BroadcastAddOp threshold;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_LogOp_2.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_ConstantOp_4.getODSResults(0).begin());
      threshold = ::mlir::chlo::BroadcastAddOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_5
      );
    }
    ::mlir::stablehlo::NegOp tblgen_NegOp_6;
    {
      ::mlir::Value tblgen_value_0 = (*threshold.getODSResults(0).begin());
      tblgen_NegOp_6 = ::mlir::stablehlo::NegOp::create(rewriter, odsLoc,
        /*operand=*/tblgen_value_0
      );
    }
    auto nativeVar_7 = DenseI64ArrayAttr(); (void)nativeVar_7;
    auto nativeVar_8 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_8;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_9;
    {
      ::mlir::Value tblgen_value_0 = (*features.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_NegOp_6.getODSResults(0).begin());
      tblgen_BroadcastCompareOp_9 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_7,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::GT),
        /*compare_type=*/nativeVar_8
      );
    }
    auto nativeVar_10 = DenseI64ArrayAttr(); (void)nativeVar_10;
    auto nativeVar_11 = ::mlir::chlo::ComparisonTypeAttr(); (void)nativeVar_11;
    ::mlir::chlo::BroadcastCompareOp tblgen_BroadcastCompareOp_12;
    {
      ::mlir::Value tblgen_value_0 = (*features.begin());
      ::mlir::Value tblgen_value_1 = (*threshold.getODSResults(0).begin());
      tblgen_BroadcastCompareOp_12 = ::mlir::chlo::BroadcastCompareOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1,
        /*broadcast_dimensions=*/nativeVar_10,
        ::mlir::chlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::chlo::ComparisonDirection::LT),
        /*compare_type=*/nativeVar_11
      );
    }
    ::mlir::stablehlo::Log1pOp tblgen_Log1pOp_13;
    {
      ::mlir::Value tblgen_value_0 = (*features_exp.getODSResults(0).begin());
      tblgen_Log1pOp_13 = ::mlir::stablehlo::Log1pOp::create(rewriter, odsLoc,
        /*operand=*/tblgen_value_0,
        ::mlir::stablehlo::ResultAccuracyAttr::get(rewriter.getContext(), APFloat(0.0), APFloat(0.0), 0, ::mlir::stablehlo::ResultAccuracyModeAttr::get(rewriter.getContext(), ::mlir::stablehlo::ResultAccuracyMode::DEFAULT))
      );
    }
    ::mlir::stablehlo::SelectOp tblgen_SelectOp_14;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_BroadcastCompareOp_12.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*features_exp.getODSResults(0).begin());
      ::mlir::Value tblgen_value_2 = (*tblgen_Log1pOp_13.getODSResults(0).begin());
      tblgen_SelectOp_14 = ::mlir::stablehlo::SelectOp::create(rewriter, odsLoc,
        /*pred=*/tblgen_value_0,
        /*on_true=*/tblgen_value_1,
        /*on_false=*/tblgen_value_2
      );
    }
    ::mlir::stablehlo::SelectOp output;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_BroadcastCompareOp_9.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*features.begin());
      ::mlir::Value tblgen_value_2 = (*tblgen_SelectOp_14.getODSResults(0).begin());
      output = ::mlir::stablehlo::SelectOp::create(rewriter, odsLoc,
        /*pred=*/tblgen_value_0,
        /*on_true=*/tblgen_value_1,
        /*on_false=*/tblgen_value_2
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ output.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:756
*/
struct GeneratedConvert109 : public ::mlir::RewritePattern {
  GeneratedConvert109(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.XlaReplicaId", 1, context, {"stablehlo.replica_id", "tf.Cast"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::XlaReplicaIdOp>(op0); (void)castedOp0;

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::ReplicaIdOp tblgen_ReplicaIdOp_0;
    {
      tblgen_ReplicaIdOp_0 = ::mlir::stablehlo::ReplicaIdOp::create(rewriter, odsLoc
      );
    }
    ::mlir::TF::CastOp tblgen_CastOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::TF::CastOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_ReplicaIdOp_0.getODSResults(0).begin()));
      tblgen_props.Truncate = ::llvm::dyn_cast_if_present<decltype(tblgen_props.Truncate)>(rewriter.getBoolAttr(false));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_CastOp_1 = ::mlir::TF::CastOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_CastOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:767
*/
struct GeneratedConvert110 : public ::mlir::RewritePattern {
  GeneratedConvert110(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.XlaGather", 1, context, {"stablehlo.gather"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::BoolAttr indices_are_sorted;
    ::mlir::Operation::operand_range start_indices(op0->getOperands());
    ::mlir::Attribute slice_sizes;
    ::mlir::StringAttr dimension_numbers;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::XlaGatherOp>(op0); (void)castedOp0;
    operand = castedOp0.getODSOperands(0);
    start_indices = castedOp0.getODSOperands(1);
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
        slice_sizes = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_legalize_tf_patterns1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'constant vector/tensor attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getDimensionNumbers();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.XlaGather' to have attribute 'dimension_numbers' of type '::mlir::StringAttr'";
        });
      }
      dimension_numbers = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndicesAreSorted();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.XlaGather' to have attribute 'indices_are_sorted' of type '::mlir::BoolAttr'";
        });
      }
      indices_are_sorted = tblgen_attr;
    }
    if (!((HasValidGatherDims(dimension_numbers)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'dimension_numbers' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = GetGatherDimNumsAttr(dimension_numbers, &rewriter); (void)nativeVar_0;
    auto nativeVar_1 = 
      ToDenseI64ArrayAttr(
        llvm::cast<mlir::DenseIntElementsAttr>(hlo::convertElementsAttr(
          llvm::cast<ElementsAttr>(slice_sizes), rewriter.getIntegerType(64))), &rewriter)
      ; (void)nativeVar_1;
    ::mlir::stablehlo::GatherOp tblgen_GatherOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::GatherOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*start_indices.begin()));
      tblgen_props.dimension_numbers = ::llvm::dyn_cast_if_present<decltype(tblgen_props.dimension_numbers)>(nativeVar_0);
      tblgen_props.slice_sizes = ::llvm::dyn_cast_if_present<decltype(tblgen_props.slice_sizes)>(nativeVar_1);
      tblgen_props.indices_are_sorted = ::llvm::dyn_cast_if_present<decltype(tblgen_props.indices_are_sorted)>(indices_are_sorted);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_GatherOp_2 = ::mlir::stablehlo::GatherOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_GatherOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:787
*/
struct GeneratedConvert111 : public ::mlir::RewritePattern {
  GeneratedConvert111(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.XlaDot", 1, context, {"stablehlo.dot_general"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::StringAttr precision_config;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::StringAttr dimension_numbers;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::XlaDotOp>(op0); (void)castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getDimensionNumbers();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.XlaDot' to have attribute 'dimension_numbers' of type '::mlir::StringAttr'";
        });
      }
      dimension_numbers = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getPrecisionConfig();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.XlaDot' to have attribute 'precision_config' of type '::mlir::StringAttr'";
        });
      }
      precision_config = tblgen_attr;
    }
    if (!((HasValidDotDims(dimension_numbers)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'dimension_numbers' failed to satisfy constraint: ''";
      });
    }
    if (!((HasValidPrecisionConfig(precision_config)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'precision_config' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = GetDotDimNumsAttr(dimension_numbers, &rewriter); (void)nativeVar_0;
    auto nativeVar_1 = GetPrecisionConfigAttr(precision_config, &rewriter); (void)nativeVar_1;
    auto nativeVar_2 = mlir::stablehlo::DotAlgorithmAttr{}; (void)nativeVar_2;
    ::mlir::stablehlo::DotGeneralOp tblgen_DotGeneralOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DotGeneralOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*lhs.begin()));
      tblgen_values.push_back((*rhs.begin()));
      tblgen_props.dot_dimension_numbers = ::llvm::dyn_cast_if_present<decltype(tblgen_props.dot_dimension_numbers)>(nativeVar_0);
      tblgen_props.precision_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.precision_config)>(nativeVar_1);
      tblgen_props.algorithm = ::llvm::dyn_cast_if_present<decltype(tblgen_props.algorithm)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DotGeneralOp_3 = ::mlir::stablehlo::DotGeneralOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DotGeneralOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:798
*/
struct GeneratedConvert112 : public ::mlir::RewritePattern {
  GeneratedConvert112(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.XlaDotV2", 1, context, {"stablehlo.dot_general"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::StringAttr precision_config;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::StringAttr dimension_numbers;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::XlaDotV2Op>(op0); (void)castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getDimensionNumbers();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.XlaDotV2' to have attribute 'dimension_numbers' of type '::mlir::StringAttr'";
        });
      }
      dimension_numbers = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getPrecisionConfig();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.XlaDotV2' to have attribute 'precision_config' of type '::mlir::StringAttr'";
        });
      }
      precision_config = tblgen_attr;
    }
    if (!((HasValidDotDims(dimension_numbers)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'dimension_numbers' failed to satisfy constraint: ''";
      });
    }
    if (!((HasValidPrecisionConfig(precision_config)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'precision_config' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = GetDotDimNumsAttr(dimension_numbers, &rewriter); (void)nativeVar_0;
    auto nativeVar_1 = GetPrecisionConfigAttr(precision_config, &rewriter); (void)nativeVar_1;
    auto nativeVar_2 = mlir::stablehlo::DotAlgorithmAttr{}; (void)nativeVar_2;
    ::mlir::stablehlo::DotGeneralOp tblgen_DotGeneralOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DotGeneralOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*lhs.begin()));
      tblgen_values.push_back((*rhs.begin()));
      tblgen_props.dot_dimension_numbers = ::llvm::dyn_cast_if_present<decltype(tblgen_props.dot_dimension_numbers)>(nativeVar_0);
      tblgen_props.precision_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.precision_config)>(nativeVar_1);
      tblgen_props.algorithm = ::llvm::dyn_cast_if_present<decltype(tblgen_props.algorithm)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DotGeneralOp_3 = ::mlir::stablehlo::DotGeneralOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DotGeneralOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:809
*/
struct GeneratedConvert113 : public ::mlir::RewritePattern {
  GeneratedConvert113(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.XlaDynamicSlice", 1, context, {"stablehlo.dynamic_slice"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::TF::XlaDynamicSliceOp op;
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::mlir::Operation::operand_range starting_indices(op0->getOperands());
    ::mlir::Attribute slice_sizes;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::XlaDynamicSliceOp>(op0); (void)castedOp0;
    op = castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'tf.XlaDynamicSlice' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    input = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_legalize_tf_patterns4(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'tf.XlaDynamicSlice' failed to satisfy constraint: 'ranked tensor of 4/6/8/16/32/64-bit float or bool or 2/4/8/16/32/64-bit integer or complex type with 32/64-bit float elements or per-tensor integer quantized values'"))) {
      return ::mlir::failure();
    }
    starting_indices = castedOp0.getODSOperands(1);
    {
      auto *op1 = (*castedOp0.getODSOperands(2).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 2 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_5(rewriter, op1, tblgen_ops, slice_sizes))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = UnpackTensorAlongZeroDim((*op.getODSResults(0).begin()).getLoc(), (*starting_indices.begin()), &rewriter).getOutput(); (void)nativeVar_0;
    auto nativeVar_1 = TFSliceSizes2HLOSliceSizes((*input.begin()), (*starting_indices.begin()), llvm::cast<DenseIntElementsAttr>(slice_sizes),&rewriter); (void)nativeVar_1;
    ::mlir::stablehlo::DynamicSliceOp tblgen_DynamicSliceOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DynamicSliceOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      for (auto v: nativeVar_0) {
        tblgen_values.push_back(v);
      }
      tblgen_props.slice_sizes = ::llvm::dyn_cast_if_present<decltype(tblgen_props.slice_sizes)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DynamicSliceOp_2 = ::mlir::stablehlo::DynamicSliceOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DynamicSliceOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:819
*/
struct GeneratedConvert114 : public ::mlir::RewritePattern {
  GeneratedConvert114(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.XlaEinsum", 1, context, {"stablehlo.einsum"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::StringAttr equation;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::XlaEinsumOp>(op0); (void)castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getEquation();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'tf.XlaEinsum' to have attribute 'equation' of type '::mlir::StringAttr'";
        });
      }
      equation = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::EinsumOp tblgen_EinsumOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::EinsumOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*lhs.begin()));
      tblgen_values.push_back((*rhs.begin()));
      tblgen_props.einsum_config = ::llvm::dyn_cast_if_present<decltype(tblgen_props.einsum_config)>(equation);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_EinsumOp_0 = ::mlir::stablehlo::EinsumOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_EinsumOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    tensorflow/compiler/mlir/tf2xla/transforms/legalize_tf_patterns.td:826
*/
struct GeneratedConvert115 : public ::mlir::RewritePattern {
  GeneratedConvert115(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("tf.XlaOptimizationBarrier", 1, context, {"stablehlo.optimization_barrier"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range args(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::TF::XlaOptimizationBarrierOp>(op0); (void)castedOp0;
    args = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::OptimizationBarrierOp tblgen_OptimizationBarrierOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::OptimizationBarrierOp::Properties tblgen_props; (void)tblgen_props;
      for (auto v: args) {
        tblgen_values.push_back(v);
      }
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_OptimizationBarrierOp_0 = ::mlir::stablehlo::OptimizationBarrierOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_OptimizationBarrierOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<LegalizeGatherV2>(patterns.getContext());
  patterns.add<LowerAssert>(patterns.getContext());
  patterns.add<LowerRightShiftSigned>(patterns.getContext());
  patterns.add<LowerRightShiftUnsigned>(patterns.getContext());
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
  patterns.add<GeneratedConvert24>(patterns.getContext());
  patterns.add<GeneratedConvert25>(patterns.getContext());
  patterns.add<GeneratedConvert26>(patterns.getContext());
  patterns.add<GeneratedConvert27>(patterns.getContext());
  patterns.add<GeneratedConvert28>(patterns.getContext());
  patterns.add<GeneratedConvert29>(patterns.getContext());
  patterns.add<GeneratedConvert30>(patterns.getContext());
  patterns.add<GeneratedConvert31>(patterns.getContext());
  patterns.add<GeneratedConvert32>(patterns.getContext());
  patterns.add<GeneratedConvert33>(patterns.getContext());
  patterns.add<GeneratedConvert34>(patterns.getContext());
  patterns.add<GeneratedConvert35>(patterns.getContext());
  patterns.add<GeneratedConvert36>(patterns.getContext());
  patterns.add<GeneratedConvert37>(patterns.getContext());
  patterns.add<GeneratedConvert38>(patterns.getContext());
  patterns.add<GeneratedConvert39>(patterns.getContext());
  patterns.add<GeneratedConvert40>(patterns.getContext());
  patterns.add<GeneratedConvert41>(patterns.getContext());
  patterns.add<GeneratedConvert42>(patterns.getContext());
  patterns.add<GeneratedConvert43>(patterns.getContext());
  patterns.add<GeneratedConvert44>(patterns.getContext());
  patterns.add<GeneratedConvert45>(patterns.getContext());
  patterns.add<GeneratedConvert46>(patterns.getContext());
  patterns.add<GeneratedConvert47>(patterns.getContext());
  patterns.add<GeneratedConvert48>(patterns.getContext());
  patterns.add<GeneratedConvert49>(patterns.getContext());
  patterns.add<GeneratedConvert50>(patterns.getContext());
  patterns.add<GeneratedConvert51>(patterns.getContext());
  patterns.add<GeneratedConvert52>(patterns.getContext());
  patterns.add<GeneratedConvert53>(patterns.getContext());
  patterns.add<GeneratedConvert54>(patterns.getContext());
  patterns.add<GeneratedConvert55>(patterns.getContext());
  patterns.add<GeneratedConvert56>(patterns.getContext());
  patterns.add<GeneratedConvert57>(patterns.getContext());
  patterns.add<GeneratedConvert58>(patterns.getContext());
  patterns.add<GeneratedConvert59>(patterns.getContext());
  patterns.add<GeneratedConvert60>(patterns.getContext());
  patterns.add<GeneratedConvert61>(patterns.getContext());
  patterns.add<GeneratedConvert62>(patterns.getContext());
  patterns.add<GeneratedConvert63>(patterns.getContext());
  patterns.add<GeneratedConvert64>(patterns.getContext());
  patterns.add<GeneratedConvert65>(patterns.getContext());
  patterns.add<GeneratedConvert66>(patterns.getContext());
  patterns.add<GeneratedConvert67>(patterns.getContext());
  patterns.add<GeneratedConvert68>(patterns.getContext());
  patterns.add<GeneratedConvert69>(patterns.getContext());
  patterns.add<GeneratedConvert70>(patterns.getContext());
  patterns.add<GeneratedConvert71>(patterns.getContext());
  patterns.add<GeneratedConvert72>(patterns.getContext());
  patterns.add<GeneratedConvert73>(patterns.getContext());
  patterns.add<GeneratedConvert74>(patterns.getContext());
  patterns.add<GeneratedConvert75>(patterns.getContext());
  patterns.add<GeneratedConvert76>(patterns.getContext());
  patterns.add<GeneratedConvert77>(patterns.getContext());
  patterns.add<GeneratedConvert78>(patterns.getContext());
  patterns.add<GeneratedConvert79>(patterns.getContext());
  patterns.add<GeneratedConvert80>(patterns.getContext());
  patterns.add<GeneratedConvert81>(patterns.getContext());
  patterns.add<GeneratedConvert82>(patterns.getContext());
  patterns.add<GeneratedConvert83>(patterns.getContext());
  patterns.add<GeneratedConvert84>(patterns.getContext());
  patterns.add<GeneratedConvert85>(patterns.getContext());
  patterns.add<GeneratedConvert86>(patterns.getContext());
  patterns.add<GeneratedConvert87>(patterns.getContext());
  patterns.add<GeneratedConvert88>(patterns.getContext());
  patterns.add<GeneratedConvert89>(patterns.getContext());
  patterns.add<GeneratedConvert90>(patterns.getContext());
  patterns.add<GeneratedConvert91>(patterns.getContext());
  patterns.add<GeneratedConvert92>(patterns.getContext());
  patterns.add<GeneratedConvert93>(patterns.getContext());
  patterns.add<GeneratedConvert94>(patterns.getContext());
  patterns.add<GeneratedConvert95>(patterns.getContext());
  patterns.add<GeneratedConvert96>(patterns.getContext());
  patterns.add<GeneratedConvert97>(patterns.getContext());
  patterns.add<GeneratedConvert98>(patterns.getContext());
  patterns.add<GeneratedConvert99>(patterns.getContext());
  patterns.add<GeneratedConvert100>(patterns.getContext());
  patterns.add<GeneratedConvert101>(patterns.getContext());
  patterns.add<GeneratedConvert102>(patterns.getContext());
  patterns.add<GeneratedConvert103>(patterns.getContext());
  patterns.add<GeneratedConvert104>(patterns.getContext());
  patterns.add<GeneratedConvert105>(patterns.getContext());
  patterns.add<GeneratedConvert106>(patterns.getContext());
  patterns.add<GeneratedConvert107>(patterns.getContext());
  patterns.add<GeneratedConvert108>(patterns.getContext());
  patterns.add<GeneratedConvert109>(patterns.getContext());
  patterns.add<GeneratedConvert110>(patterns.getContext());
  patterns.add<GeneratedConvert111>(patterns.getContext());
  patterns.add<GeneratedConvert112>(patterns.getContext());
  patterns.add<GeneratedConvert113>(patterns.getContext());
  patterns.add<GeneratedConvert114>(patterns.getContext());
  patterns.add<GeneratedConvert115>(patterns.getContext());
}
