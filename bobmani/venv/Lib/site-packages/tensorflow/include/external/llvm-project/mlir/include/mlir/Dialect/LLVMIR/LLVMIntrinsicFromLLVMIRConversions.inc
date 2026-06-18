if (intrinsicID == llvm::Intrinsic::acos) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::ACosOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::asin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::ASinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::atan2) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::ATan2Op::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::atan) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::ATanOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::abs) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {1},
        {StringLiteral("is_int_min_poison")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::AbsOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::annotation) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::Annotation::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::assume) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        true,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::AssumeOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::bitreverse) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::BitReverseOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::bswap) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::ByteSwapOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::experimental_constrained_fpext) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands.take_front( 1), {}, false,
        {}, {}, mlirOperands, mlirAttrs))) {
      return failure();
    }

    FPExceptionBehaviorAttr fpExceptionBehaviorAttr =
        moduleImport.matchFPExceptionBehaviorAttr(llvmOperands[1]);
    mlirAttrs.push_back(
        odsBuilder.getNamedAttr(
            ::mlir::LLVM::ConstrainedFPExtIntr::getFPExceptionBehaviorAttrName(),
            fpExceptionBehaviorAttr)); 
    moduleImport.mapValue(inst) = ::mlir::LLVM::ConstrainedFPExtIntr::create(odsBuilder, moduleImport.translateLoc(inst->getDebugLoc()),
      moduleImport.convertType(inst->getType()), mlirOperands, mlirAttrs);
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::experimental_constrained_fptrunc) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands.take_front( 1), {}, false,
        {}, {}, mlirOperands, mlirAttrs))) {
      return failure();
    }

    FPExceptionBehaviorAttr fpExceptionBehaviorAttr =
        moduleImport.matchFPExceptionBehaviorAttr(llvmOperands[2]);
    mlirAttrs.push_back(
        odsBuilder.getNamedAttr(
            ::mlir::LLVM::ConstrainedFPTruncIntr::getFPExceptionBehaviorAttrName(),
            fpExceptionBehaviorAttr)); 
    RoundingModeAttr roundingModeAttr = moduleImport.matchRoundingModeAttr(llvmOperands[1]);
    mlirAttrs.push_back(
        odsBuilder.getNamedAttr(::mlir::LLVM::ConstrainedFPTruncIntr::getRoundingModeAttrName(),
                               roundingModeAttr));
    
    moduleImport.mapValue(inst) = ::mlir::LLVM::ConstrainedFPTruncIntr::create(odsBuilder, moduleImport.translateLoc(inst->getDebugLoc()),
      moduleImport.convertType(inst->getType()), mlirOperands, mlirAttrs);
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::experimental_constrained_sitofp) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands.take_front( 1), {}, false,
        {}, {}, mlirOperands, mlirAttrs))) {
      return failure();
    }

    FPExceptionBehaviorAttr fpExceptionBehaviorAttr =
        moduleImport.matchFPExceptionBehaviorAttr(llvmOperands[2]);
    mlirAttrs.push_back(
        odsBuilder.getNamedAttr(
            ::mlir::LLVM::ConstrainedSIToFP::getFPExceptionBehaviorAttrName(),
            fpExceptionBehaviorAttr)); 
    RoundingModeAttr roundingModeAttr = moduleImport.matchRoundingModeAttr(llvmOperands[1]);
    mlirAttrs.push_back(
        odsBuilder.getNamedAttr(::mlir::LLVM::ConstrainedSIToFP::getRoundingModeAttrName(),
                               roundingModeAttr));
    
    moduleImport.mapValue(inst) = ::mlir::LLVM::ConstrainedSIToFP::create(odsBuilder, moduleImport.translateLoc(inst->getDebugLoc()),
      moduleImport.convertType(inst->getType()), mlirOperands, mlirAttrs);
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::experimental_constrained_uitofp) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands.take_front( 1), {}, false,
        {}, {}, mlirOperands, mlirAttrs))) {
      return failure();
    }

    FPExceptionBehaviorAttr fpExceptionBehaviorAttr =
        moduleImport.matchFPExceptionBehaviorAttr(llvmOperands[2]);
    mlirAttrs.push_back(
        odsBuilder.getNamedAttr(
            ::mlir::LLVM::ConstrainedUIToFP::getFPExceptionBehaviorAttrName(),
            fpExceptionBehaviorAttr)); 
    RoundingModeAttr roundingModeAttr = moduleImport.matchRoundingModeAttr(llvmOperands[1]);
    mlirAttrs.push_back(
        odsBuilder.getNamedAttr(::mlir::LLVM::ConstrainedUIToFP::getRoundingModeAttrName(),
                               roundingModeAttr));
    
    moduleImport.mapValue(inst) = ::mlir::LLVM::ConstrainedUIToFP::create(odsBuilder, moduleImport.translateLoc(inst->getDebugLoc()),
      moduleImport.convertType(inst->getType()), mlirOperands, mlirAttrs);
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::copysign) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CopySignOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::coro_align) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CoroAlignOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::coro_begin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CoroBeginOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::coro_end) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CoroEndOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::coro_free) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CoroFreeOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::coro_id) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CoroIdOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::coro_promise) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CoroPromiseOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::coro_resume) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::CoroResumeOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::coro_save) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CoroSaveOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::coro_size) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CoroSizeOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::coro_suspend) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CoroSuspendOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::cos) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CosOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::cosh) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CoshOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ctlz) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {1},
        {StringLiteral("is_zero_poison")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CountLeadingZerosOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::cttz) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {1},
        {StringLiteral("is_zero_poison")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CountTrailingZerosOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ctpop) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::CtPopOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::dbg_declare) {


    // Add debug intrindic to the list of intrinsics that need to be converted once the
    // full function was converted.
    moduleImport.addDebugIntrinsic(inst);
    return success();
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::dbg_label) {


    DILabelAttr labelAttr = moduleImport.matchLabelAttr(llvmOperands[0]);
    // Drop the intrinsic if the label translation fails due to cylic metadata.
    if (!labelAttr)
      return success();
    moduleImport.mapNoResultOp(inst) = ::mlir::LLVM::DbgLabelOp::create(odsBuilder, moduleImport.translateLoc(inst->getDebugLoc()), labelAttr);
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::dbg_value) {


    // Add debug intrindic to the list of intrinsics that need to be converted once the
    // full function was converted.
    moduleImport.addDebugIntrinsic(inst);
    return success();
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::debugtrap) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::DebugTrap::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::eh_typeid_for) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::EhTypeidForOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::exp2) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::Exp2Op::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::exp10) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::Exp10Op::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::exp) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::ExpOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::expect) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::ExpectOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::expect_with_probability) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {2},
        {StringLiteral("prob")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::ExpectWithProbabilityOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::fabs) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::FAbsOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ceil) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::FCeilOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::floor) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::FFloorOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::fma) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::FMAOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::fmuladd) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::FMulAddOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::trunc) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::FTruncOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::frexp) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::FractionExpOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::fshl) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::FshlOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::fshr) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::FshrOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::get_active_lane_mask) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::GetActiveLaneMaskOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::invariant_end) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {1},
        {StringLiteral("size")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::InvariantEndOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::invariant_start) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {0},
        {StringLiteral("size")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::InvariantStartOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::is_constant) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::IsConstantOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::is_fpclass) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {1},
        {StringLiteral("bit")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::IsFPClass::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::launder_invariant_group) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::LaunderInvariantGroupOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::lifetime_end) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::LifetimeEndOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::lifetime_start) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::LifetimeStartOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::llrint) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::LlrintOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::llround) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::LlroundOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ldexp) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::LoadExpOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::log2) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::Log2Op::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::log10) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::Log10Op::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::log) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::LogOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::lrint) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::LrintOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::lround) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::LroundOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::masked_load) {
FailureOr<Value> _llvmir_gen_operand_data = moduleImport.convertValue(llvmOperands[0]);
if (failed(_llvmir_gen_operand_data))
  return failure();
FailureOr<Value> _llvmir_gen_operand_mask = moduleImport.convertValue(llvmOperands[1]);
if (failed(_llvmir_gen_operand_mask))
  return failure();
FailureOr<Value> _llvmir_gen_operand_pass_thru = moduleImport.convertValue(llvmOperands[2]);
if (failed(_llvmir_gen_operand_pass_thru))
  return failure();


    auto *intrinInst = dyn_cast<llvm::IntrinsicInst>(inst);
    bool nontemporal = intrinInst->hasMetadata(llvm::LLVMContext::MD_nontemporal);
    llvm::Align alignment = intrinInst->getParamAlign(0).valueOrOne();
    moduleImport.mapValue(inst) = LLVM::MaskedLoadOp::create(odsBuilder, moduleImport.translateLoc(inst->getDebugLoc()),
      moduleImport.convertType(inst->getType()), *_llvmir_gen_operand_data, *_llvmir_gen_operand_mask, *_llvmir_gen_operand_pass_thru,
      odsBuilder.getI32IntegerAttr(alignment.value()),
      nontemporal ? odsBuilder.getUnitAttr() : nullptr);
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::masked_store) {
FailureOr<Value> _llvmir_gen_operand_value = moduleImport.convertValue(llvmOperands[0]);
if (failed(_llvmir_gen_operand_value))
  return failure();
FailureOr<Value> _llvmir_gen_operand_data = moduleImport.convertValue(llvmOperands[1]);
if (failed(_llvmir_gen_operand_data))
  return failure();
FailureOr<Value> _llvmir_gen_operand_mask = moduleImport.convertValue(llvmOperands[2]);
if (failed(_llvmir_gen_operand_mask))
  return failure();


    auto *intrinInst = dyn_cast<llvm::IntrinsicInst>(inst);
    llvm::Align alignment = intrinInst->getParamAlign(1).valueOrOne();
    moduleImport.mapNoResultOp(inst) = LLVM::MaskedStoreOp::create(odsBuilder, moduleImport.translateLoc(inst->getDebugLoc()),
      *_llvmir_gen_operand_value, *_llvmir_gen_operand_data, *_llvmir_gen_operand_mask, odsBuilder.getI32IntegerAttr(alignment.value()));
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::matrix_column_major_load) {
FailureOr<Value> _llvmir_gen_operand_data = moduleImport.convertValue(llvmOperands[0]);
if (failed(_llvmir_gen_operand_data))
  return failure();
FailureOr<Value> _llvmir_gen_operand_stride = moduleImport.convertValue(llvmOperands[1]);
if (failed(_llvmir_gen_operand_stride))
  return failure();


    moduleImport.mapValue(inst) = LLVM::MatrixColumnMajorLoadOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), moduleImport.convertType(inst->getType()), *_llvmir_gen_operand_data, *_llvmir_gen_operand_stride,
      moduleImport.matchIntegerAttr(llvmOperands[2]), moduleImport.matchIntegerAttr(llvmOperands[3]), moduleImport.matchIntegerAttr(llvmOperands[4]));
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::matrix_column_major_store) {
FailureOr<Value> _llvmir_gen_operand_matrix = moduleImport.convertValue(llvmOperands[0]);
if (failed(_llvmir_gen_operand_matrix))
  return failure();
FailureOr<Value> _llvmir_gen_operand_data = moduleImport.convertValue(llvmOperands[1]);
if (failed(_llvmir_gen_operand_data))
  return failure();
FailureOr<Value> _llvmir_gen_operand_stride = moduleImport.convertValue(llvmOperands[2]);
if (failed(_llvmir_gen_operand_stride))
  return failure();


    moduleImport.mapNoResultOp(inst) = LLVM::MatrixColumnMajorStoreOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), *_llvmir_gen_operand_matrix, *_llvmir_gen_operand_data, *_llvmir_gen_operand_stride,
      moduleImport.matchIntegerAttr(llvmOperands[3]), moduleImport.matchIntegerAttr(llvmOperands[4]), moduleImport.matchIntegerAttr(llvmOperands[5]));
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::matrix_multiply) {
FailureOr<Value> _llvmir_gen_operand_lhs = moduleImport.convertValue(llvmOperands[0]);
if (failed(_llvmir_gen_operand_lhs))
  return failure();
FailureOr<Value> _llvmir_gen_operand_rhs = moduleImport.convertValue(llvmOperands[1]);
if (failed(_llvmir_gen_operand_rhs))
  return failure();


    moduleImport.mapValue(inst) = LLVM::MatrixMultiplyOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), moduleImport.convertType(inst->getType()), *_llvmir_gen_operand_lhs, *_llvmir_gen_operand_rhs,
      moduleImport.matchIntegerAttr(llvmOperands[2]), moduleImport.matchIntegerAttr(llvmOperands[3]), moduleImport.matchIntegerAttr(llvmOperands[4]));
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::matrix_transpose) {
FailureOr<Value> _llvmir_gen_operand_matrix = moduleImport.convertValue(llvmOperands[0]);
if (failed(_llvmir_gen_operand_matrix))
  return failure();


    moduleImport.mapValue(inst) = LLVM::MatrixTransposeOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), moduleImport.convertType(inst->getType()), *_llvmir_gen_operand_matrix,
      moduleImport.matchIntegerAttr(llvmOperands[1]), moduleImport.matchIntegerAttr(llvmOperands[2]));
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::maxnum) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::MaxNumOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::maximum) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::MaximumOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::memcpy_inline) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {2, 3},
        {StringLiteral("len"), StringLiteral("isVolatile")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::MemcpyInlineOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    
    moduleImport.convertArgAndResultAttrs(
      inst, op, {2, 3});
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::memcpy) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {3},
        {StringLiteral("isVolatile")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::MemcpyOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    
    moduleImport.convertArgAndResultAttrs(
      inst, op, {3});
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::memmove) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {3},
        {StringLiteral("isVolatile")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::MemmoveOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    
    moduleImport.convertArgAndResultAttrs(
      inst, op, {3});
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::memset_inline) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {2, 3},
        {StringLiteral("len"), StringLiteral("isVolatile")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::MemsetInlineOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    
    moduleImport.convertArgAndResultAttrs(
      inst, op, {2, 3});
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::memset) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {3},
        {StringLiteral("isVolatile")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::MemsetOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    
    moduleImport.convertArgAndResultAttrs(
      inst, op, {3});
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::minnum) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::MinNumOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::minimum) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::MinimumOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::nearbyint) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::NearbyintOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::experimental_noalias_scope_decl) {


    FailureOr<SmallVector<LLVM::AliasScopeAttr>> scopeAttrs =
      moduleImport.matchAliasScopeAttrs(llvmOperands[0]);
    // Drop the intrinsic if the alias scope translation fails since the scope
    // is not used by an aliasing operation, such as a load or store, that is
    // used to convert the alias scope metadata.
    if (failed(scopeAttrs))
      return success();
    if (scopeAttrs->size() != 1)
      return failure();
    moduleImport.mapNoResultOp(inst) = LLVM::NoAliasScopeDeclOp::create(
      odsBuilder, moduleImport.translateLoc(inst->getDebugLoc()), (*scopeAttrs)[0]);
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::powi) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::PowIOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::pow) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::PowOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::prefetch) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {1, 2, 3},
        {StringLiteral("rw"), StringLiteral("hint"), StringLiteral("cache")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::Prefetch::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ptr_annotation) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::PtrAnnotation::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ptrmask) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::PtrMaskOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::rint) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::RintOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::roundeven) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::RoundEvenOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::round) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::RoundOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::sadd_sat) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SAddSat::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::sadd_with_overflow) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SAddWithOverflowOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::scmp) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SCmpOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::smax) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SMaxOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::smin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SMinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::smul_with_overflow) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SMulWithOverflowOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ssa_copy) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SSACopyOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::sshl_sat) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SSHLSat::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ssub_sat) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SSubSat::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ssub_with_overflow) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SSubWithOverflowOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::sin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::sincos) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SincosOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::sinh) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SinhOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::sqrt) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::SqrtOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::stackrestore) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::StackRestoreOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::stacksave) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::StackSaveOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::stepvector) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::StepVectorOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::strip_invariant_group) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::StripInvariantGroupOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::tan) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::TanOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::tanh) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::TanhOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::threadlocal_address) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::ThreadlocalAddressOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::trap) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::Trap::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::uadd_sat) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::UAddSat::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::uadd_with_overflow) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::UAddWithOverflowOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ubsantrap) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {0},
        {StringLiteral("failureKind")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::UBSanTrap::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ucmp) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::UCmpOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::umax) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::UMaxOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::umin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::UMinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::umul_with_overflow) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::UMulWithOverflowOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::ushl_sat) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::USHLSat::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::usub_sat) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::USubSat::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::usub_with_overflow) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::USubWithOverflowOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_ashr) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPAShrOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_add) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPAddOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_and) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPAndOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fadd) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFAddOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fdiv) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFDivOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fmuladd) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFMulAddOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fmul) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFMulOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fneg) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFNegOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fpext) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFPExtOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fptosi) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFPToSIOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fptoui) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFPToUIOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fptrunc) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFPTruncOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_frem) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFRemOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fsub) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFSubOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_fma) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPFmaOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_inttoptr) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPIntToPtrOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_lshr) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPLShrOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_load) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPLoadOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_merge) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPMergeMinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_mul) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPMulOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_or) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPOrOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_ptrtoint) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPPtrToIntOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_add) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceAddOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_and) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceAndOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_fadd) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceFAddOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_fmax) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceFMaxOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_fmin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceFMinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_fmul) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceFMulOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_mul) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceMulOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_or) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceOrOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_smax) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceSMaxOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_smin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceSMinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_umax) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceUMaxOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_umin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceUMinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_reduce_xor) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPReduceXorOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_sdiv) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPSDivOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_sext) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPSExtOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_sitofp) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPSIToFPOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_smax) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPSMaxOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_smin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPSMinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_srem) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPSRemOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_select) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPSelectMinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_shl) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPShlOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_store) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::VPStoreOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::experimental_vp_strided_load) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPStridedLoadOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::experimental_vp_strided_store) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::VPStridedStoreOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_sub) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPSubOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_trunc) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPTruncOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_udiv) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPUDivOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_uitofp) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPUIToFPOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_umax) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPUMaxOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_umin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPUMinOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_urem) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPURemOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_xor) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPXorOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vp_zext) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::VPZExtOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vacopy) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::VaCopyOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vaend) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::VaEndOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vastart) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::VaStartOp::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::var_annotation) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::VarAnnotation::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::masked_compressstore) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {};
    auto op = ::mlir::LLVM::masked_compressstore::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    
    moduleImport.convertArgAndResultAttrs(
      inst, op, {});
    moduleImport.mapNoResultOp(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::masked_expandload) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::masked_expandload::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    
    moduleImport.convertArgAndResultAttrs(
      inst, op, {});
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::masked_gather) {
FailureOr<Value> _llvmir_gen_operand_ptrs = moduleImport.convertValue(llvmOperands[0]);
if (failed(_llvmir_gen_operand_ptrs))
  return failure();
FailureOr<Value> _llvmir_gen_operand_mask = moduleImport.convertValue(llvmOperands[1]);
if (failed(_llvmir_gen_operand_mask))
  return failure();
FailureOr<SmallVector<Value>> _llvmir_gen_operand_pass_thru = moduleImport.convertValues(llvmOperands.drop_front(2));
if (failed(_llvmir_gen_operand_pass_thru))
  return failure();


    auto *intrinInst = dyn_cast<llvm::IntrinsicInst>(inst);
    llvm::Align alignment = intrinInst->getParamAlign(0).valueOrOne();
    moduleImport.mapValue(inst) = LLVM::masked_gather::create(odsBuilder, moduleImport.translateLoc(inst->getDebugLoc()),
      moduleImport.convertType(inst->getType()), *_llvmir_gen_operand_ptrs, *_llvmir_gen_operand_mask, *_llvmir_gen_operand_pass_thru,
      odsBuilder.getI32IntegerAttr(alignment.value()));
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::masked_scatter) {
FailureOr<Value> _llvmir_gen_operand_value = moduleImport.convertValue(llvmOperands[0]);
if (failed(_llvmir_gen_operand_value))
  return failure();
FailureOr<Value> _llvmir_gen_operand_ptrs = moduleImport.convertValue(llvmOperands[1]);
if (failed(_llvmir_gen_operand_ptrs))
  return failure();
FailureOr<Value> _llvmir_gen_operand_mask = moduleImport.convertValue(llvmOperands[2]);
if (failed(_llvmir_gen_operand_mask))
  return failure();


    auto *intrinInst = dyn_cast<llvm::IntrinsicInst>(inst);
    llvm::Align alignment = intrinInst->getParamAlign(1).valueOrOne();
    moduleImport.mapNoResultOp(inst) = LLVM::masked_scatter::create(odsBuilder, moduleImport.translateLoc(inst->getDebugLoc()),
      *_llvmir_gen_operand_value, *_llvmir_gen_operand_ptrs, *_llvmir_gen_operand_mask, odsBuilder.getI32IntegerAttr(alignment.value()));
  
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_deinterleave2) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_deinterleave2::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_extract) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {1},
        {StringLiteral("pos")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_extract::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_insert) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {2},
        {StringLiteral("pos")},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_insert::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_interleave2) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_interleave2::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_add) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_add::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_and) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_and::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_fadd) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_fadd::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_fmax) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_fmax::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_fmaximum) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_fmaximum::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_fmin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_fmin::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_fminimum) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_fminimum::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_fmul) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_fmul::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.setFastmathFlagsAttr(inst, op);moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_mul) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_mul::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_or) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_or::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_smax) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_smax::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_smin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_smin::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_umax) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_umax::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_umin) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_umin::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vector_reduce_xor) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vector_reduce_xor::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
if (intrinsicID == llvm::Intrinsic::vscale) {


    SmallVector<Value> mlirOperands;
    SmallVector<NamedAttribute> mlirAttrs;
    if (failed(moduleImport.convertIntrinsicArguments(
        llvmOperands,
        llvmOpBundles,
        false,
        {},
        {},
        mlirOperands,
        mlirAttrs))) {
      return failure();
    }
    SmallVector<Type> resultTypes =
    {moduleImport.convertType(inst->getType())};
    auto op = ::mlir::LLVM::vscale::create(odsBuilder,
      moduleImport.translateLoc(inst->getDebugLoc()), resultTypes, mlirOperands, mlirAttrs);
    moduleImport.mapValue(inst) = op;
  return success();
}
