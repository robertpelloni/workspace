if (auto op = dyn_cast<::mlir::NVVM::AggrSmemSize>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_aggr_smem_size,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Barrier0Op>(opInst)) {

      createIntrinsicCall(
          builder, llvm::Intrinsic::nvvm_barrier_cta_sync_aligned_all,
          {builder.getInt32(0)});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BarrierOp>(opInst)) {

    auto [id, args] = NVVM::BarrierOp::getIntrinsicIDAndArgs(
                        *op, moduleTranslation, builder);
    if (op.getReductionOp())
      moduleTranslation.mapValue(op.getRes()) = builder.CreateZExt(createIntrinsicCall(builder, id, args),
                                builder.getInt32Ty());
    else 
      createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BlockDimXOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_ntid_x,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BlockDimYOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_ntid_y,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BlockDimZOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_ntid_z,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BlockIdXOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_ctaid_x,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BlockIdYOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_ctaid_y,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BlockIdZOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_ctaid_z,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BlockInClusterIdXOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_cluster_ctaid_x,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BlockInClusterIdYOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_cluster_ctaid_y,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BlockInClusterIdZOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_cluster_ctaid_z,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Breakpoint>(opInst)) {

    createIntrinsicCall(builder, llvm::Intrinsic::debugtrap);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::BulkStoreOp>(opInst)) {

    auto intId = getStBulkIntrinsicId(
          llvm::cast<LLVM::LLVMPointerType>(op.getAddr().getType()));
    createIntrinsicCall(builder, intId,
                      {moduleTranslation.lookupValue(op.getAddr()), moduleTranslation.lookupValue(op.getSize()), builder.getInt64(op.getInitVal())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Clock64Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_clock64,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClockOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_clock,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterArriveOp>(opInst)) {

      if (op.getAligned())
        createIntrinsicCall(builder, llvm::Intrinsic::nvvm_barrier_cluster_arrive_aligned);
      else
        createIntrinsicCall(builder, llvm::Intrinsic::nvvm_barrier_cluster_arrive);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterArriveRelaxedOp>(opInst)) {

      if (op.getAligned())
        createIntrinsicCall(builder, llvm::Intrinsic::nvvm_barrier_cluster_arrive_relaxed_aligned);
      else
        createIntrinsicCall(builder, llvm::Intrinsic::nvvm_barrier_cluster_arrive_relaxed);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterDim>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_cluster_nctarank,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterDimBlocksXOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_cluster_nctaid_x,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterDimBlocksYOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_cluster_nctaid_y,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterDimBlocksZOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_cluster_nctaid_z,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterDimXOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_nclusterid_x,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterDimYOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_nclusterid_y,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterDimZOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_nclusterid_z,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterId>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_cluster_ctarank,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterIdXOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_clusterid_x,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterIdYOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_clusterid_y,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterIdZOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_clusterid_z,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterLaunchControlQueryCancelOp>(opInst)) {

    auto [id, args] = 
    NVVM::ClusterLaunchControlQueryCancelOp::getIntrinsicIDAndArgs(
                        *op, moduleTranslation, builder);
    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterLaunchControlTryCancelOp>(opInst)) {

    auto [id, args] = 
    NVVM::ClusterLaunchControlTryCancelOp::getIntrinsicIDAndArgs(
                        *op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ClusterWaitOp>(opInst)) {

      if (op.getAligned())
        createIntrinsicCall(builder, llvm::Intrinsic::nvvm_barrier_cluster_wait_aligned);
      else
        createIntrinsicCall(builder, llvm::Intrinsic::nvvm_barrier_cluster_wait);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertBF16x2ToF8x2Op>(opInst)) {

    auto intId = NVVM::ConvertBF16x2ToF8x2Op::getIntrinsicID(op.getRnd(), op.getSat());
    llvm::Value *packedI16 = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getA())});
    if(op.getDst().getType().isInteger(16))
      moduleTranslation.mapValue(op.getDst()) = packedI16;
    else
      moduleTranslation.mapValue(op.getDst()) = builder.CreateBitCast(packedI16,
                      llvm::FixedVectorType::get(llvm::Type::getInt8Ty(builder.getContext()), 2));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF4x2ToF16x2Op>(opInst)) {

    auto [id, args] = NVVM::ConvertF4x2ToF16x2Op::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getDst()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getDst().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF6x2ToF16x2Op>(opInst)) {

    auto [id, args] = NVVM::ConvertF6x2ToF16x2Op::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getDst()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getDst().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF8x2ToBF16x2Op>(opInst)) {

    auto [id, args] = NVVM::ConvertF8x2ToBF16x2Op::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getDst()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getDst().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF8x2ToF16x2Op>(opInst)) {

    auto [id, args] = NVVM::ConvertF8x2ToF16x2Op::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getDst()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getDst().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF16x2ToF8x2Op>(opInst)) {

    auto intId = NVVM::ConvertF16x2ToF8x2Op::getIntrinsicID(op.getDstTy(), op.getRelu());
    llvm::Value *packedI16 = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getA())});
    if(op.getDst().getType().isInteger(16))
      moduleTranslation.mapValue(op.getDst()) = packedI16;
    else
      moduleTranslation.mapValue(op.getDst()) = builder.CreateBitCast(packedI16,
                      llvm::FixedVectorType::get(llvm::Type::getInt8Ty(builder.getContext()), 2));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF32x2ToBF16x2Op>(opInst)) {

    auto [intId, args] = mlir::NVVM::ConvertF32x2ToBF16x2Op::getIntrinsicIDAndArgs(op, moduleTranslation, builder);
    moduleTranslation.mapValue(op.getDst()) = createIntrinsicCall(builder, intId, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF32x2ToF4x2Op>(opInst)) {

    auto [intId, args] = NVVM::ConvertF32x2ToF4x2Op::getIntrinsicIDAndArgs(op, moduleTranslation, builder);
    llvm::Value *packedI16 = createIntrinsicCall(builder, intId, args);
    moduleTranslation.mapValue(op.getDst()) = builder.CreateTruncOrBitCast(packedI16, llvm::Type::getInt8Ty(builder.getContext()));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF32x2ToF6x2Op>(opInst)) {

    auto intId = NVVM::ConvertF32x2ToF6x2Op::getIntrinsicID(op.getDstTy(), op.getRelu());
    llvm::Value *packedI16 = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getA()), moduleTranslation.lookupValue(op.getB())});
    if(op.getDst().getType().isInteger(16))
      moduleTranslation.mapValue(op.getDst()) = packedI16;
    else
      moduleTranslation.mapValue(op.getDst()) = builder.CreateBitCast(packedI16,
                      llvm::FixedVectorType::get(llvm::Type::getInt8Ty(builder.getContext()), 2));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF32x2ToF8x2Op>(opInst)) {

    auto intId = NVVM::ConvertF32x2ToF8x2Op::getIntrinsicID(op.getDstTy(), op.getRnd(), op.getSat(), op.getRelu());
    llvm::Value *packedI16 = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getA()), moduleTranslation.lookupValue(op.getB())});
    if(op.getDst().getType().isInteger(16))
      moduleTranslation.mapValue(op.getDst()) = packedI16;
    else
      moduleTranslation.mapValue(op.getDst()) = builder.CreateBitCast(packedI16,
                      llvm::FixedVectorType::get(llvm::Type::getInt8Ty(builder.getContext()), 2));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF32x2ToF16x2Op>(opInst)) {

    auto [intId, args] = mlir::NVVM::ConvertF32x2ToF16x2Op::getIntrinsicIDAndArgs(op, moduleTranslation, builder);
    moduleTranslation.mapValue(op.getDst()) = createIntrinsicCall(builder, intId, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF32x4ToF4x4Op>(opInst)) {

    auto intId = op.getIntrinsicID();
    moduleTranslation.mapValue(op.getDst()) = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getSrc()), moduleTranslation.lookupValue(op.getRbits())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF32x4ToF6x4Op>(opInst)) {

    auto intId = op.getIntrinsicID();
    moduleTranslation.mapValue(op.getDst()) = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getSrc()), moduleTranslation.lookupValue(op.getRbits())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertF32x4ToF8x4Op>(opInst)) {

    auto intId = op.getIntrinsicID();
    moduleTranslation.mapValue(op.getDst()) = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getSrc()), moduleTranslation.lookupValue(op.getRbits())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ConvertFloatToTF32Op>(opInst)) {

    auto intId = NVVM::ConvertFloatToTF32Op::getIntrinsicID(op.getRnd(), op.getSat(), op.getRelu());
    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getSrc())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncBulkCommitGroupOp>(opInst)) {

    createIntrinsicCall(builder, llvm::Intrinsic::nvvm_cp_async_bulk_commit_group);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncBulkGlobalToSharedClusterOp>(opInst)) {

    auto [id, args] = NVVM::CpAsyncBulkGlobalToSharedClusterOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncBulkPrefetchOp>(opInst)) {

    auto [id, args] = NVVM::CpAsyncBulkPrefetchOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncBulkSharedCTAToGlobalOp>(opInst)) {

    auto [id, args] = NVVM::CpAsyncBulkSharedCTAToGlobalOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncBulkSharedCTAToSharedClusterOp>(opInst)) {

    createIntrinsicCall(builder,
      llvm::Intrinsic::nvvm_cp_async_bulk_shared_cta_to_cluster,
      {moduleTranslation.lookupValue(op.getDstMem()), moduleTranslation.lookupValue(op.getMbar()), moduleTranslation.lookupValue(op.getSrcMem()), moduleTranslation.lookupValue(op.getSize())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncBulkTensorGlobalToSharedClusterOp>(opInst)) {

    auto [id, args] = NVVM::CpAsyncBulkTensorGlobalToSharedClusterOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncBulkTensorPrefetchOp>(opInst)) {

    auto [id, args] = NVVM::CpAsyncBulkTensorPrefetchOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncBulkTensorReduceOp>(opInst)) {

    auto [id, args] = NVVM::CpAsyncBulkTensorReduceOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncBulkTensorSharedCTAToGlobalOp>(opInst)) {

    auto [id, args] = NVVM::CpAsyncBulkTensorSharedCTAToGlobalOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncBulkWaitGroupOp>(opInst)) {

    auto intId = op.getRead() ?
      llvm::Intrinsic::nvvm_cp_async_bulk_wait_group_read :
      llvm::Intrinsic::nvvm_cp_async_bulk_wait_group;
    createIntrinsicCall(builder, intId, builder.getInt32(op.getGroup()));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncCommitGroupOp>(opInst)) {

      createIntrinsicCall(builder, llvm::Intrinsic::nvvm_cp_async_commit_group);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncMBarrierArriveOp>(opInst)) {

    auto [id, args] = NVVM::CpAsyncMBarrierArriveOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncOp>(opInst)) {

    llvm::SmallVector<llvm::Value *> translatedOperands;
    auto id = NVVM::CpAsyncOp::getIntrinsicIDAndArgs(
      *op, moduleTranslation, translatedOperands);
    createIntrinsicCall(builder, id, translatedOperands);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::CpAsyncWaitGroupOp>(opInst)) {

      createIntrinsicCall(
        builder,
        llvm::Intrinsic::nvvm_cp_async_wait_group,
        llvm::ConstantInt::get(
          llvm::Type::getInt32Ty(moduleTranslation.getLLVMContext()),
          op.getN()));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::DotAccumulate2WayOp>(opInst)) {

    auto [id, args] = NVVM::DotAccumulate2WayOp::getIntrinsicIDAndArgs(
                        *op, moduleTranslation, builder);
    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::DotAccumulate4WayOp>(opInst)) {

    auto [id, args] = NVVM::DotAccumulate4WayOp::getIntrinsicIDAndArgs(
                        *op, moduleTranslation, builder);
    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::DynamicSmemSize>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_dynamic_smem_size,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ElectSyncOp>(opInst)) {

    auto *resultTuple = createIntrinsicCall(builder,
        llvm::Intrinsic::nvvm_elect_sync,
        {moduleTranslation.lookupValue(op.getMembermask()) ? moduleTranslation.lookupValue(op.getMembermask()) : builder.getInt32(0xFFFFFFFF)});
    // Extract the second value into moduleTranslation.mapValue(op.getPred())
    moduleTranslation.mapValue(op.getPred()) = builder.CreateExtractValue(resultTuple, 1);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg0Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg0,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg1Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg1,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg2Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg2,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg3Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg3,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg4Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg4,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg5Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg5,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg6Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg6,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg7Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg7,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg8Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg8,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg9Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg9,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg10Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg10,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg11Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg11,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg12Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg12,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg13Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg13,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg14Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg14,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg15Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg15,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg16Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg16,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg17Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg17,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg18Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg18,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg19Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg19,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg20Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg20,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg21Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg21,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg22Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg22,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg23Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg23,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg24Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg24,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg25Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg25,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg26Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg26,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg27Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg27,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg28Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg28,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg29Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg29,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg30Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg30,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::EnvReg31Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_envreg31,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Exit>(opInst)) {

    createIntrinsicCall(builder, llvm::Intrinsic::nvvm_exit);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::FenceMbarrierInitOp>(opInst)) {

    createIntrinsicCall(builder, llvm::Intrinsic::nvvm_fence_mbarrier_init_release_cluster);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::FenceProxyAcquireOp>(opInst)) {

    createIntrinsicCall(
        builder,
        getUnidirectionalFenceProxyID(op.getFromProxy(), op.getToProxy(), op.getScope(), false),
        {moduleTranslation.lookupValue(op.getAddr()), moduleTranslation.lookupValue(op.getSize())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::FenceProxyOp>(opInst)) {

    createIntrinsicCall(builder, getFenceProxyID(op.getKind(), op.getSpace()));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::FenceProxyReleaseOp>(opInst)) {

    createIntrinsicCall(builder, getUnidirectionalFenceProxyID(
                                     op.getFromProxy(), op.getToProxy(), op.getScope(), true));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::FenceProxySyncRestrictOp>(opInst)) {

    createIntrinsicCall(builder, getFenceProxySyncRestrictID(op.getOrder()));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::FenceScClusterOp>(opInst)) {

      createIntrinsicCall(builder, llvm::Intrinsic::nvvm_fence_sc_cluster);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::FenceSyncRestrictOp>(opInst)) {

    createIntrinsicCall(builder, getFenceSyncRestrictID(op.getOrder()));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::GlobalTimerLoOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_globaltimer_lo,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::GlobalTimerOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_globaltimer,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::GridDimXOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_nctaid_x,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::GridDimYOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_nctaid_y,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::GridDimZOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_nctaid_z,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::GridIdOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_gridid,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::GriddepcontrolOp>(opInst)) {

    llvm::Intrinsic::ID id;
      switch (op.getKind()) {
        case NVVM::GridDepActionKind::wait:
          id = llvm::Intrinsic::nvvm_griddepcontrol_wait;
          break;
        case NVVM::GridDepActionKind::launch_dependents:
          id = llvm::Intrinsic::nvvm_griddepcontrol_launch_dependents;
          break;
      }
      createIntrinsicCall(builder, id);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::LaneIdOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_laneid,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::LaneMaskEqOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_lanemask_eq,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::LaneMaskGeOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_lanemask_ge,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::LaneMaskGtOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_lanemask_gt,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::LaneMaskLeOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_lanemask_le,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::LaneMaskLtOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_lanemask_lt,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::LdMatrixOp>(opInst)) {

      auto operands = moduleTranslation.lookupValues(opInst.getOperands());
      auto intId = getLdMatrixIntrinsicId(op.getLayout(), op.getNum(), op.getShape(), op.getEltType());
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, intId, operands, {operands[0]->getType()});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierArriveDropExpectTxOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierArriveDropExpectTxOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getRes().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierArriveDropNocompleteOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierArriveDropNocompleteOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getRes().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierArriveDropOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierArriveDropOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getRes().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierArriveExpectTxOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierArriveExpectTxOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);

    if (op.getNumResults() > 0)
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, args);
    else
      createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierArriveNocompleteOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierArriveNocompleteOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getRes().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierArriveOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierArriveOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getRes().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierCompleteTxOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierCompleteTxOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierExpectTxOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierExpectTxOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierInitOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierInitOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierInvalOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierInvalOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierTestWaitOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierTestWaitOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getRes().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MBarrierTryWaitOp>(opInst)) {

    auto [id, args] = NVVM::MBarrierTryWaitOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getRes().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MapaOp>(opInst)) {

    int addrSpace = llvm::cast<LLVMPointerType>(op.getA().getType()).getAddressSpace();
    
    bool isSharedMemory = addrSpace == static_cast<int> (NVVM::NVVMMemorySpace::Shared);

    auto intId = isSharedMemory? llvm::Intrinsic::nvvm_mapa_shared_cluster : llvm::Intrinsic::nvvm_mapa;
    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getA()), moduleTranslation.lookupValue(op.getB())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MatchSyncOp>(opInst)) {

    auto intId = getMatchSyncIntrinsicId(
        op.getVal().getType(), op.getKind());
    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder,
        intId, {moduleTranslation.lookupValue(op.getThreadMask()), moduleTranslation.lookupValue(op.getVal())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MembarOp>(opInst)) {

    createIntrinsicCall(builder, getMembarIntrinsicID(op.getScope()));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MmaBlockScaleOp>(opInst)) {

    auto [id, args] = NVVM::MmaBlockScaleOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MmaOp>(opInst)) {

    auto operands = moduleTranslation.lookupValues(opInst.getOperands());
    auto intId = mlir::NVVM::MmaOp::getIntrinsicID(
        op.getShape().getM(), op.getShape().getN(), op.getShape().getK(),
        op.getB1Op(), op.getIntOverflowBehavior(),
        op.getLayoutA(), op.getLayoutB(),
        *op.getMultiplicandAPtxType(),
        *op.getMultiplicandBPtxType(),
        op.accumPtxType(),
        op.resultPtxType());

    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(
      builder, intId, operands);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MmaSpBlockScaleOp>(opInst)) {

    auto [id, args] = NVVM::MmaSpBlockScaleOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::MmaSpOp>(opInst)) {

    auto [id, args] = NVVM::MmaSpOp::getIntrinsicIDAndArgs(
                      *op, moduleTranslation, builder);
    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::NanosleepOp>(opInst)) {

      createIntrinsicCall(builder, 
                          llvm::Intrinsic::nvvm_nanosleep, {moduleTranslation.lookupValue(op.getDuration())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::PMEventOp>(opInst)) {

    auto [id, args] = NVVM::PMEventOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::PermuteOp>(opInst)) {

    auto [id, args] = NVVM::PermuteOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    if (op->getNumResults() > 0)
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, id, moduleTranslation.convertType(op.getRes().getType()), args);
    else
      createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::PrefetchOp>(opInst)) {

    auto [id, args] = NVVM::PrefetchOp::getIntrinsicIDAndArgs(op,
                                          moduleTranslation, builder);
    createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::RcpApproxFtzF32Op>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_rcp_approx_ftz_f,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ReduxOp>(opInst)) {

      auto intId = getReduxIntrinsicId(moduleTranslation.convertType(op.getResult().getType()), op.getKind(), op.getAbs(), op.getNan());
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getVal()), moduleTranslation.lookupValue(op.getMaskAndClamp())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::SetMaxRegisterOp>(opInst)) {

    auto intId = (op.getAction() == NVVM::SetMaxRegisterAction::increase) ?
      llvm::Intrinsic::nvvm_setmaxnreg_inc_sync_aligned_u32 :
      llvm::Intrinsic::nvvm_setmaxnreg_dec_sync_aligned_u32;

    createIntrinsicCall(builder, intId, builder.getInt32(op.getRegCount()));
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ShflOp>(opInst)) {

      auto intId = getShflIntrinsicId(
          moduleTranslation.convertType(op.getResult().getType()), op.getKind(), static_cast<bool>(op.getReturnValueAndIsValid()));
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder,
          intId, {moduleTranslation.lookupValue(op.getThreadMask()), moduleTranslation.lookupValue(op.getVal()), moduleTranslation.lookupValue(op.getOffset()), moduleTranslation.lookupValue(op.getMaskAndClamp())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::SmDimOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_nsmid,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::SmIdOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_smid,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::StMatrixOp>(opInst)) {

      auto operands = moduleTranslation.lookupValues(opInst.getOperands());
      auto intId = getStMatrixIntrinsicId(op.getLayout(), moduleTranslation.lookupValues(op.getSources()).size(), op.getShape(), op.getEltType());
      createIntrinsicCall(builder, intId, operands, operands[0]->getType());
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::SyncWarpOp>(opInst)) {

      createIntrinsicCall(builder, llvm::Intrinsic::nvvm_bar_warp_sync, {moduleTranslation.lookupValue(op.getMask())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05AllocOp>(opInst)) {

    llvm::SmallVector<llvm::Value *> args;
    auto id = NVVM::Tcgen05AllocOp::getIntrinsicIDAndArgs(
      *op, moduleTranslation, args);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05CommitOp>(opInst)) {

    llvm::SmallVector<llvm::Value *> args;
    auto id = NVVM::Tcgen05CommitOp::getIntrinsicIDAndArgs(
      *op, moduleTranslation, args);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05CpOp>(opInst)) {

    auto id = NVVM::Tcgen05CpOp::getIntrinsicID(*op);
    createIntrinsicCall(builder, id, {moduleTranslation.lookupValue(op.getTaddr()), moduleTranslation.lookupValue(op.getSmemDesc())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05DeallocOp>(opInst)) {

    llvm::SmallVector<llvm::Value *> args;
    auto id = NVVM::Tcgen05DeallocOp::getIntrinsicIDAndArgs(
      *op, moduleTranslation, args);
    createIntrinsicCall(builder, id, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05FenceOp>(opInst)) {

    auto id = (op.getKind() == NVVM::Tcgen05FenceKind::BEFORE_THREAD_SYNC)
      ? llvm::Intrinsic::nvvm_tcgen05_fence_before_thread_sync
      : llvm::Intrinsic::nvvm_tcgen05_fence_after_thread_sync;
    createIntrinsicCall(builder, id);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05LdOp>(opInst)) {

    llvm::LLVMContext &Context = moduleTranslation.getLLVMContext();
    auto Pack = llvm::ConstantInt::get(Context, llvm::APInt(1, op.getPack()));

    unsigned num = moduleTranslation.convertType(op.getResult().getType())->isVectorTy()
                       ? llvm::cast<llvm::VectorType>(moduleTranslation.convertType(op.getResult().getType()))
                             ->getElementCount()
                             .getFixedValue()
                       : 1;

    auto ID = getTcgen05LdIntrinsicID(op.getShape(), num);
    if (ID == llvm::Intrinsic::not_intrinsic)
      llvm::report_fatal_error("unknow intrinsic signature for tcgen05.ld");

    if (moduleTranslation.lookupValue(op.getOffset()))
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, ID, {moduleTranslation.lookupValue(op.getTmemAddr()), moduleTranslation.lookupValue(op.getOffset()), Pack});
    else
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, ID, {moduleTranslation.lookupValue(op.getTmemAddr()), Pack});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05MMABlockScaleOp>(opInst)) {

    auto [ID, args] = NVVM::Tcgen05MMABlockScaleOp::getIntrinsicIDAndArgs(
        *op, moduleTranslation, builder);
    createIntrinsicCall(builder, ID, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05MMAOp>(opInst)) {

    auto [ID, args] = NVVM::Tcgen05MMAOp::getIntrinsicIDAndArgs(
        *op, moduleTranslation, builder);
    createIntrinsicCall(builder, ID, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05MMASparseBlockScaleOp>(opInst)) {

    auto [ID, args] = NVVM::Tcgen05MMASparseBlockScaleOp::getIntrinsicIDAndArgs(
        *op, moduleTranslation, builder);
    createIntrinsicCall(builder, ID, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05MMASparseOp>(opInst)) {

    auto [ID, args] = NVVM::Tcgen05MMASparseOp::getIntrinsicIDAndArgs(
        *op, moduleTranslation, builder);
    createIntrinsicCall(builder, ID, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05MMAWsOp>(opInst)) {

    auto [ID, args] =
        NVVM::Tcgen05MMAWsOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    createIntrinsicCall(builder, ID, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05MMAWsSparseOp>(opInst)) {

      auto [ID, args] = NVVM::Tcgen05MMAWsSparseOp::getIntrinsicIDAndArgs(
          *op, moduleTranslation, builder);
      createIntrinsicCall(builder, ID, args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05MmaSmemDescOp>(opInst)) {

    NVVM::Tcgen05MmaSmemDescOp::createSmemDescriptor(*op, moduleTranslation, builder);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05RelinquishAllocPermitOp>(opInst)) {

    auto id = (op.getGroup() == NVVM::CTAGroupKind::CTA_1) ?
      llvm::Intrinsic::nvvm_tcgen05_relinq_alloc_permit_cg1 :
      llvm::Intrinsic::nvvm_tcgen05_relinq_alloc_permit_cg2;
    createIntrinsicCall(builder, id);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05ShiftOp>(opInst)) {

    auto id = (op.getGroup() == NVVM::CTAGroupKind::CTA_1) ?
      llvm::Intrinsic::nvvm_tcgen05_shift_down_cg1 :
      llvm::Intrinsic::nvvm_tcgen05_shift_down_cg2;
    createIntrinsicCall(builder, id, {moduleTranslation.lookupValue(op.getTaddr())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05StOp>(opInst)) {

    llvm::LLVMContext &Context = moduleTranslation.getLLVMContext();
    auto Unpack = llvm::ConstantInt::get(Context, llvm::APInt(1, op.getUnpack()));

    auto valTy = moduleTranslation.lookupValue(op.getVal())->getType();
    uint32_t num = valTy->isVectorTy() ? llvm::cast<llvm::VectorType>(valTy)
                                             ->getElementCount()
                                             .getFixedValue()
                                       : 1;

    auto ID = getTcgen05StIntrinsicID(op.getShape(), num);
    if (ID == llvm::Intrinsic::not_intrinsic)
      llvm::report_fatal_error("unknow intrinsic signature for tcgen05.st");

    if (moduleTranslation.lookupValue(op.getOffset()))
      createIntrinsicCall(builder, ID, {moduleTranslation.lookupValue(op.getTmemAddr()), moduleTranslation.lookupValue(op.getOffset()), moduleTranslation.lookupValue(op.getVal()), Unpack});
    else
      createIntrinsicCall(builder, ID, {moduleTranslation.lookupValue(op.getTmemAddr()), moduleTranslation.lookupValue(op.getVal()), Unpack});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::Tcgen05WaitOp>(opInst)) {

    auto id = (op.getKind() == NVVM::Tcgen05WaitKind::LOAD)
      ? llvm::Intrinsic::nvvm_tcgen05_wait_ld
      : llvm::Intrinsic::nvvm_tcgen05_wait_st;
    createIntrinsicCall(builder, id);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::TensormapReplaceOp>(opInst)) {

    auto [id, args] = NVVM::TensormapReplaceOp::getIntrinsicIDAndArgs(*op, moduleTranslation, builder);
    createIntrinsicCall(builder, id, builder.getVoidTy(), args);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ThreadIdXOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_tid_x,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ThreadIdYOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_tid_y,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::ThreadIdZOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_tid_z,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::TotalSmemSize>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_total_smem_size,1,{},{},{},{});
    (void) inst;
    moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::VoteSyncOp>(opInst)) {

    auto intId = getVoteSyncIntrinsicId(op.getKind());
    moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, intId, {moduleTranslation.lookupValue(op.getMask()), moduleTranslation.lookupValue(op.getPred())});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::WMMALoadOp>(opInst)) {

      auto operands = moduleTranslation.lookupValues(opInst.getOperands());
      auto intId = mlir::NVVM::WMMALoadOp::getIntrinsicID(
        op.getM(), op.getN(), op.getK(), op.getLayout(), op.getEltype(), op.getFrag());
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, intId, operands, {operands[0]->getType()});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::WMMAMmaOp>(opInst)) {

      auto operands = moduleTranslation.lookupValues(opInst.getOperands());
      auto intId = mlir::NVVM::WMMAMmaOp::getIntrinsicID(
        op.getM(), op.getN(), op.getK(), op.getLayoutA(), op.getLayoutB(), op.getEltypeA(), op.getEltypeB());
      moduleTranslation.mapValue(op.getRes()) = createIntrinsicCall(builder, intId, operands);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::WMMAStoreOp>(opInst)) {

      auto operands = moduleTranslation.lookupValues(opInst.getOperands());
      auto intId =
        mlir::NVVM::WMMAStoreOp::getIntrinsicID(op.getM(), op.getN(), op.getK(), op.getLayout(), op.getEltype());
      createIntrinsicCall(builder, intId, operands, {operands[0]->getType()});
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::WarpDimOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_nwarpid,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::WarpIdOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_warpid,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::WarpSizeOp>(opInst)) {

    auto *inst = LLVM::detail::createIntrinsicCall(
      builder, moduleTranslation, &opInst, llvm::Intrinsic::nvvm_read_ptx_sreg_warpsize,1,{},{},{},{});
    (void) inst;
    
    if (op.getRange()) {
      inst->addRangeRetAttr(::llvm::ConstantRange(
        op.getRange()->getLower(), op.getRange()->getUpper()));
    }
  moduleTranslation.mapValue(op.getRes()) = inst;
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::WgmmaFenceAlignedOp>(opInst)) {

    createIntrinsicCall(builder, llvm::Intrinsic::nvvm_wgmma_fence_sync_aligned);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::WgmmaGroupSyncAlignedOp>(opInst)) {

    createIntrinsicCall(builder, llvm::Intrinsic::nvvm_wgmma_commit_group_sync_aligned);
  
  return success();
}
if (auto op = dyn_cast<::mlir::NVVM::WgmmaWaitGroupSyncOp>(opInst)) {

    createIntrinsicCall(builder, llvm::Intrinsic::nvvm_wgmma_wait_group_sync_aligned, builder.getInt64(op.getGroup()));
  
  return success();
}
