/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: StablehloAggressiveSimplificationPatterns.td                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_StablehloAggressiveSimplificationPatterns1(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Type type,
    ::llvm::StringRef failureStr) {
  if (!((((::llvm::isa<::mlir::RankedTensorType>(type))) && ((::llvm::cast<::mlir::ShapedType>(type).hasStaticShape()))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": statically shaped tensor of any type values";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_StablehloAggressiveSimplificationPatterns2(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Type type,
    ::llvm::StringRef failureStr) {
  if (!((((::llvm::isa<::mlir::RankedTensorType>(type))) && ((::llvm::cast<::mlir::ShapedType>(type).hasStaticShape()))) && ([](::mlir::Type elementType) { return (((elementType.isSignlessInteger(2))) || ((elementType.isSignlessInteger(4))) || ((elementType.isSignlessInteger(8))) || ((elementType.isSignlessInteger(16))) || ((elementType.isSignlessInteger(32))) || ((elementType.isSignlessInteger(64)))) || (((elementType.isUnsignedInteger(2))) || ((elementType.isUnsignedInteger(4))) || ((elementType.isUnsignedInteger(8))) || ((elementType.isUnsignedInteger(16))) || ((elementType.isUnsignedInteger(32))) || ((elementType.isUnsignedInteger(64)))); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": statically shaped tensor of 2/4/8/16/32/64-bit integer values";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns1(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((::mlir::matchPattern(attr, m_AnyAttrOf(m_Zero(), m_AnyZeroFloat()))))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is int or float zero";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns2(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((::mlir::matchPattern(attr, m_Zero())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is integer zero";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns3(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((
    ::mlir::matchPattern(attr,
        ::mlir::detail::constant_int_predicate_matcher{
            [](const llvm::APInt &val) {
                return val.isAllOnes();
        }})
    ))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is integer with all bits set to 1";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns4(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((isIotaRange(cast<DenseI64ArrayAttr>(attr).asArrayRef())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is iota dimensions";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns5(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((llvm::is_sorted(cast<DenseI64ArrayAttr>(attr).asArrayRef())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is sorted dimensions";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns6(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((::mlir::matchPattern(attr, m_One())))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is integer one";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns7(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((attr == ::mlir::stablehlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::stablehlo::ComparisonDirection::EQ)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": constant attribute ::mlir::stablehlo::ComparisonDirection::EQ";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns8(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((attr == ::mlir::stablehlo::ComparisonDirectionAttr::get(rewriter.getContext(), ::mlir::stablehlo::ComparisonDirection::NE)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": constant attribute ::mlir::stablehlo::ComparisonDirection::NE";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns9(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((llvm::isa<DenseIntElementsAttr>(attr)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is dense int elements attr";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns10(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!(((::llvm::isa<::mlir::DenseIntElementsAttr>(attr))) && ((true)))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": integer elements attribute";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns11(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((cast<DenseElementsAttr>(attr).getNumElements() == 0))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is zero extent";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns12(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((::mlir::matchPattern(attr, m_AnyAttrOf(m_One(), m_OneFloat()))))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is integer one";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns13(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((::llvm::all_of(::llvm::cast<DenseI64ArrayAttr>(attr).asArrayRef(), [](int64_t val) { return val == 0; })))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is an array of zeros";
    });
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns14(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!((cast<DenseI64ArrayAttr>(attr).empty()))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": is empty i64 array";
    });
  }
  return ::mlir::success();
}
static ::llvm::LogicalResult static_dag_matcher_0(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::stablehlo::ConstantOp &lhs, ::mlir::ElementsAttr &value) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ConstantOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::mlir::stablehlo::ConstantOp type";
    });
  }
  lhs = castedOp1;
  {
    [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
    if (!(tblgen_attr)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "expected op 'stablehlo.constant' to have attribute 'value' of type '::mlir::ElementsAttr'";
      });
    }
    value = tblgen_attr;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_1(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::stablehlo::ConstantOp &zero, ::mlir::ElementsAttr &value) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ConstantOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::mlir::stablehlo::ConstantOp type";
    });
  }
  zero = castedOp1;
  {
    [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
    if (!(tblgen_attr)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "expected op 'stablehlo.constant' to have attribute 'value' of type '::mlir::ElementsAttr'";
      });
    }
    if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns2(rewriter, castedOp1, tblgen_attr, "op 'stablehlo.constant' attribute 'value' failed to satisfy constraint: 'is integer zero'"))) {
      return ::mlir::failure();
    }
    value = tblgen_attr;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_2(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::stablehlo::ConstantOp &one, ::mlir::ElementsAttr &value) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ConstantOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::mlir::stablehlo::ConstantOp type";
    });
  }
  one = castedOp1;
  {
    [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
    if (!(tblgen_attr)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "expected op 'stablehlo.constant' to have attribute 'value' of type '::mlir::ElementsAttr'";
      });
    }
    if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns3(rewriter, castedOp1, tblgen_attr, "op 'stablehlo.constant' attribute 'value' failed to satisfy constraint: 'is integer with all bits set to 1'"))) {
      return ::mlir::failure();
    }
    value = tblgen_attr;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_3(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &lhs, ::mlir::Operation::operand_range &rhs) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ComplexOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::mlir::stablehlo::ComplexOp type";
    });
  }
  lhs = castedOp1.getODSOperands(0);
  rhs = castedOp1.getODSOperands(1);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_4(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &pred) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::NotOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::mlir::stablehlo::NotOp type";
    });
  }
  pred = castedOp1.getODSOperands(0);
  return ::mlir::success();
}

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:165
*/
struct AddOp_CanonicalizeConstantToRhs : public ::mlir::RewritePattern {
  AddOp_CanonicalizeConstantToRhs(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.add", 2, context, {"stablehlo.add"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::AddOp op;
    ::mlir::stablehlo::ConstantOp lhs;
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::AddOp>(op0); (void)castedOp0;
    op = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, lhs, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    rhs = castedOp0.getODSOperands(1);
    if (!((llvm::isa<BlockArgument>((*rhs.begin())) || !llvm::isa<stablehlo::ConstantOp>((*rhs.begin()).getDefiningOp())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: 'is not a constant.'";
      });
    }
    if (!(((*op.getODSResults(0).begin()).getDefiningOp()->hasTrait<hlo::OpTrait::IsCommutative>()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op' failed to satisfy constraint: 'op is commutative'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::AddOp new_op;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::AddOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*rhs.begin()));
      tblgen_values.push_back((*lhs.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      new_op = ::mlir::stablehlo::AddOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ new_op.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*new_op.getODSResults(0).begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:169
*/
struct AddOp_RemoveNoop : public ::mlir::RewritePattern {
  AddOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.add", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Attribute value;
    ::mlir::stablehlo::AddOp op;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::AddOp>(op0); (void)castedOp0;
    op = castedOp0;
    lhs = castedOp0.getODSOperands(0);
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
        value = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns1(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'is int or float zero'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ lhs }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*lhs.begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:178
*/
struct AndOp_CanonicalizeConstantToRhs : public ::mlir::RewritePattern {
  AndOp_CanonicalizeConstantToRhs(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.and", 2, context, {"stablehlo.and"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::AndOp op;
    ::mlir::stablehlo::ConstantOp lhs;
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::AndOp>(op0); (void)castedOp0;
    op = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, lhs, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    rhs = castedOp0.getODSOperands(1);
    if (!((llvm::isa<BlockArgument>((*rhs.begin())) || !llvm::isa<stablehlo::ConstantOp>((*rhs.begin()).getDefiningOp())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: 'is not a constant.'";
      });
    }
    if (!(((*op.getODSResults(0).begin()).getDefiningOp()->hasTrait<hlo::OpTrait::IsCommutative>()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op' failed to satisfy constraint: 'op is commutative'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::AndOp new_op;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::AndOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*rhs.begin()));
      tblgen_values.push_back((*lhs.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      new_op = ::mlir::stablehlo::AndOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ new_op.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*new_op.getODSResults(0).begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:182
*/
struct AndOp_FoldToZero : public ::mlir::RewritePattern {
  AndOp_FoldToZero(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.and", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::AndOp op;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::stablehlo::ConstantOp zero;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::AndOp>(op0); (void)castedOp0;
    op = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_1(rewriter, op1, tblgen_ops, zero, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ zero.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*zero.getODSResults(0).begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:188
*/
struct AndOp_RemoveNoop : public ::mlir::RewritePattern {
  AndOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.and", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::AndOp op;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::stablehlo::ConstantOp one;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::AndOp>(op0); (void)castedOp0;
    op = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_2(rewriter, op1, tblgen_ops, one, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ lhs }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*lhs.begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:206
*/
struct BroadcastInDimOp_MergeComposition : public ::mlir::RewritePattern {
  BroadcastInDimOp_MergeComposition(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.broadcast_in_dim", 2, context, {"stablehlo.broadcast_in_dim"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::stablehlo::BroadcastInDimOp outer_op;
    ::mlir::DenseI64ArrayAttr inner_dims;
    ::mlir::stablehlo::BroadcastInDimOp inner_op;
    ::mlir::DenseI64ArrayAttr outer_dims;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::BroadcastInDimOp>(op0); (void)castedOp0;
    outer_op = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::BroadcastInDimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::BroadcastInDimOp type";
        });
      }
      inner_op = castedOp1;
      operand = castedOp1.getODSOperands(0);
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getBroadcastDimensions();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'stablehlo.broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
          });
        }
        inner_dims = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBroadcastDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      outer_dims = tblgen_attr;
    }
    if (!((!llvm::cast<ShapedType>((*inner_op.getODSResults(0).begin()).getType()).hasStaticShape() || (llvm::isa<stablehlo::BroadcastInDimOp>((*inner_op.getODSResults(0).begin()).getDefiningOp()) && !(llvm::is_sorted((*inner_op.getODSResults(0).begin()).getDefiningOp<stablehlo::BroadcastInDimOp>().getBroadcastDimensions()) && llvm::cast<ShapedType>((*inner_op.getODSResults(0).begin()).getType()).getNumElements() == llvm::cast<ShapedType>((*operand.begin()).getType()).getNumElements()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'inner_op, operand' failed to satisfy constraint: 'is a broadcast_in_dim op that cannot be simplified to a reshape op'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getMergedBroadcastDimensions(rewriter, outer_dims, inner_dims); (void)nativeVar_0;
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
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:197
*/
struct BroadcastInDimOp_RemoveNoop : public ::mlir::RewritePattern {
  BroadcastInDimOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.broadcast_in_dim", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::BroadcastInDimOp op;
    ::mlir::DenseI64ArrayAttr dims;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::BroadcastInDimOp>(op0); (void)castedOp0;
    op = castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBroadcastDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns4(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.broadcast_in_dim' attribute 'broadcast_dimensions' failed to satisfy constraint: 'is iota dimensions'"))) {
        return ::mlir::failure();
      }
      dims = tblgen_attr;
    }
    if (!(((*op.getODSResults(0).begin()).getType() == (*operand.begin()).getType()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op, operand' failed to satisfy constraint: 'operands are equal'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ operand }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*operand.begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:218
*/
struct BroadcastInDimOp_ReplaceWithReshape : public ::mlir::RewritePattern {
  BroadcastInDimOp_ReplaceWithReshape(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.broadcast_in_dim", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::BroadcastInDimOp op;
    ::mlir::DenseI64ArrayAttr dims;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::BroadcastInDimOp>(op0); (void)castedOp0;
    op = castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_StablehloAggressiveSimplificationPatterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'stablehlo.broadcast_in_dim' failed to satisfy constraint: 'statically shaped tensor of any type values'"))) {
      return ::mlir::failure();
    }
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBroadcastDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns5(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.broadcast_in_dim' attribute 'broadcast_dimensions' failed to satisfy constraint: 'is sorted dimensions'"))) {
        return ::mlir::failure();
      }
      dims = tblgen_attr;
    }
    if (!((llvm::cast<ShapedType>((*op.getODSResults(0).begin()).getType()).getNumElements() == llvm::cast<ShapedType>((*operand.begin()).getType()).getNumElements()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op, operand' failed to satisfy constraint: 'same number of elements'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = stablehlo::ReshapeOp::create(rewriter, odsLoc, (*op.getODSResults(0).begin()).getType(), (*operand.begin())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:227
*/
struct BroadcastInDimOp_ReplaceWithTranspose : public ::mlir::RewritePattern {
  BroadcastInDimOp_ReplaceWithTranspose(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.broadcast_in_dim", 1, context, {"stablehlo.transpose"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::BroadcastInDimOp op;
    ::mlir::DenseI64ArrayAttr dims;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::BroadcastInDimOp>(op0); (void)castedOp0;
    op = castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_StablehloAggressiveSimplificationPatterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'stablehlo.broadcast_in_dim' failed to satisfy constraint: 'statically shaped tensor of any type values'"))) {
      return ::mlir::failure();
    }
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBroadcastDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      dims = tblgen_attr;
    }
    if (!((llvm::cast<ShapedType>((*op.getODSResults(0).begin()).getType()).getNumElements() == llvm::cast<ShapedType>((*operand.begin()).getType()).getNumElements()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op, operand' failed to satisfy constraint: 'same number of elements'";
      });
    }
    if (!((llvm::cast<ShapedType>((*op.getODSResults(0).begin()).getType()).getRank() == llvm::cast<ShapedType>((*operand.begin()).getType()).getRank()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op, operand' failed to satisfy constraint: 'same rank'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getInvertedBroadcastDimensions(rewriter, dims); (void)nativeVar_0;
    ::mlir::stablehlo::TransposeOp tblgen_TransposeOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::TransposeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
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
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:250
*/
struct CompareOp_EqBooleanTrue : public ::mlir::RewritePattern {
  CompareOp_EqBooleanTrue(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.compare", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::stablehlo::ComparisonTypeAttr type;
    ::mlir::stablehlo::ConstantOp cst;
    ::mlir::ElementsAttr value;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::CompareOp>(op0); (void)castedOp0;
    lhs = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ConstantOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::ConstantOp type";
        });
      }
      cst = castedOp1;
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'stablehlo.constant' to have attribute 'value' of type '::mlir::ElementsAttr'";
          });
        }
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns6(rewriter, castedOp1, tblgen_attr, "op 'stablehlo.constant' attribute 'value' failed to satisfy constraint: 'is integer one'"))) {
          return ::mlir::failure();
        }
        value = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getComparisonDirection();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.compare' to have attribute 'comparison_direction' of type '::mlir::stablehlo::ComparisonDirectionAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns7(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.compare' attribute 'comparison_direction' failed to satisfy constraint: 'constant attribute ::mlir::stablehlo::ComparisonDirection::EQ'"))) {
        return ::mlir::failure();
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getCompareType();
      type = tblgen_attr;
    }
    if (!(((::llvm::isa<::mlir::RankedTensorType>(((*cst.getODSResults(0).begin()).getType())))) && ([](::mlir::Type elementType) { return (elementType.isSignlessInteger(1)); }(::llvm::cast<::mlir::ShapedType>(((*cst.getODSResults(0).begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'cst' failed to satisfy constraint: 'ranked tensor of bool values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ lhs }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:240
*/
struct CompareOp_NeBooleanFalse : public ::mlir::RewritePattern {
  CompareOp_NeBooleanFalse(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.compare", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::stablehlo::ComparisonTypeAttr type;
    ::mlir::stablehlo::ConstantOp cst;
    ::mlir::ElementsAttr value;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::CompareOp>(op0); (void)castedOp0;
    lhs = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ConstantOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::ConstantOp type";
        });
      }
      cst = castedOp1;
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'stablehlo.constant' to have attribute 'value' of type '::mlir::ElementsAttr'";
          });
        }
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns2(rewriter, castedOp1, tblgen_attr, "op 'stablehlo.constant' attribute 'value' failed to satisfy constraint: 'is integer zero'"))) {
          return ::mlir::failure();
        }
        value = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getComparisonDirection();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.compare' to have attribute 'comparison_direction' of type '::mlir::stablehlo::ComparisonDirectionAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns8(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.compare' attribute 'comparison_direction' failed to satisfy constraint: 'constant attribute ::mlir::stablehlo::ComparisonDirection::NE'"))) {
        return ::mlir::failure();
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getCompareType();
      type = tblgen_attr;
    }
    if (!(((::llvm::isa<::mlir::RankedTensorType>(((*cst.getODSResults(0).begin()).getType())))) && ([](::mlir::Type elementType) { return (elementType.isSignlessInteger(1)); }(::llvm::cast<::mlir::ShapedType>(((*cst.getODSResults(0).begin()).getType())).getElementType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'cst' failed to satisfy constraint: 'ranked tensor of bool values'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ lhs }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:407
*/
struct ComplexOp_CancelOutComposedOps : public ::mlir::RewritePattern {
  ComplexOp_CancelOutComposedOps(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.complex", 3, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Operation::operand_range operand0(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::ComplexOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::RealOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::RealOp type";
        });
      }
      operand = castedOp1.getODSOperands(0);
      tblgen_ops.push_back(op1);
    }
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ImagOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::ImagOp type";
        });
      }
      operand0 = castedOp1.getODSOperands(0);
      tblgen_ops.push_back(op1);
    }
    if (!(*operand.begin() == *operand0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'operand' and 'operand0' must be equal";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ operand }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:266
*/
struct ConvertOp_RemoveNoop : public ::mlir::RewritePattern {
  ConvertOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.convert", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::ConvertOp convert;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::ConvertOp>(op0); (void)castedOp0;
    convert = castedOp0;
    operand = castedOp0.getODSOperands(0);
    if (!(((*convert.getODSResults(0).begin()).getType() == (*operand.begin()).getType()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'convert, operand' failed to satisfy constraint: 'operands are equal'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ operand }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*convert.getODSResults(0).begin()), (*operand.begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:312
*/
struct DynamicBroadcastInDimOp_FoldToDynamicReshape : public ::mlir::RewritePattern {
  DynamicBroadcastInDimOp_FoldToDynamicReshape(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.dynamic_broadcast_in_dim", 2, context, {"stablehlo.dynamic_reshape"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::DenseI64ArrayAttr dims;
    ::mlir::Operation::operand_range shape(op0->getOperands());
    ::mlir::Operation::operand_range shape0(op0->getOperands());
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::DenseI64ArrayAttr expanding;
    ::mlir::DenseI64ArrayAttr nonexpanding;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicBroadcastInDimOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicReshapeOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::DynamicReshapeOp type";
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
          diag << "expected op 'stablehlo.dynamic_broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns4(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.dynamic_broadcast_in_dim' attribute 'broadcast_dimensions' failed to satisfy constraint: 'is iota dimensions'"))) {
        return ::mlir::failure();
      }
      dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKnownExpandingDimensions();
      expanding = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKnownNonexpandingDimensions();
      nonexpanding = tblgen_attr;
    }
    if (!(*shape.begin() == *shape0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'shape' and 'shape0' must be equal";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::DynamicReshapeOp tblgen_DynamicReshapeOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DynamicReshapeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*shape.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DynamicReshapeOp_0 = ::mlir::stablehlo::DynamicReshapeOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DynamicReshapeOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:281
*/
struct DynamicBroadcastInDimOp_MergeComposition : public ::mlir::RewritePattern {
  DynamicBroadcastInDimOp_MergeComposition(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.dynamic_broadcast_in_dim", 2, context, {"stablehlo.dynamic_broadcast_in_dim"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::DenseI64ArrayAttr dims;
    ::mlir::Operation::operand_range shape(op0->getOperands());
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::DenseI64ArrayAttr dims_p;
    ::mlir::Operation::operand_range shape_p(op0->getOperands());
    ::mlir::DenseI64ArrayAttr expanding_p;
    ::mlir::DenseI64ArrayAttr nonexpanding_p;
    ::mlir::DenseI64ArrayAttr expanding;
    ::mlir::DenseI64ArrayAttr nonexpanding;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicBroadcastInDimOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicBroadcastInDimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::DynamicBroadcastInDimOp type";
        });
      }
      operand = castedOp1.getODSOperands(0);
      shape_p = castedOp1.getODSOperands(1);
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getBroadcastDimensions();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'stablehlo.dynamic_broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
          });
        }
        dims_p = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getKnownExpandingDimensions();
        expanding_p = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getKnownNonexpandingDimensions();
        nonexpanding_p = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    shape = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBroadcastDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.dynamic_broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKnownExpandingDimensions();
      expanding = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKnownNonexpandingDimensions();
      nonexpanding = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getMergedBroadcastDimensions(rewriter, dims, dims_p); (void)nativeVar_0;
    auto nativeVar_1 = rewriter.getDenseI64ArrayAttr({}); (void)nativeVar_1;
    auto nativeVar_2 = rewriter.getDenseI64ArrayAttr({}); (void)nativeVar_2;
    ::mlir::stablehlo::DynamicBroadcastInDimOp tblgen_DynamicBroadcastInDimOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DynamicBroadcastInDimOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*shape.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(nativeVar_0);
      tblgen_props.known_expanding_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.known_expanding_dimensions)>(nativeVar_1);
      tblgen_props.known_nonexpanding_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.known_nonexpanding_dimensions)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DynamicBroadcastInDimOp_3 = ::mlir::stablehlo::DynamicBroadcastInDimOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DynamicBroadcastInDimOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:322
*/
struct DynamicBroadcastInDimOp_RemoveNoop : public ::mlir::RewritePattern {
  DynamicBroadcastInDimOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.dynamic_broadcast_in_dim", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::DenseI64ArrayAttr dims;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Operation::operand_range operand0(op0->getOperands());
    ::mlir::DenseI64ArrayAttr expanding;
    ::mlir::DenseI64ArrayAttr nonexpanding;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicBroadcastInDimOp>(op0); (void)castedOp0;
    operand = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::shape::ShapeOfOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::shape::ShapeOfOp type";
        });
      }
      operand0 = castedOp1.getODSOperands(0);
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBroadcastDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.dynamic_broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns4(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.dynamic_broadcast_in_dim' attribute 'broadcast_dimensions' failed to satisfy constraint: 'is iota dimensions'"))) {
        return ::mlir::failure();
      }
      dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKnownExpandingDimensions();
      expanding = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKnownNonexpandingDimensions();
      nonexpanding = tblgen_attr;
    }
    if (!(*operand.begin() == *operand0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'operand' and 'operand0' must be equal";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ operand }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:302
*/
struct DynamicBroadcastInDimOp_ReplaceNoopWithConvert : public ::mlir::RewritePattern {
  DynamicBroadcastInDimOp_ReplaceNoopWithConvert(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.dynamic_broadcast_in_dim", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::DynamicBroadcastInDimOp op;
    ::mlir::DenseI64ArrayAttr dims;
    ::mlir::Operation::operand_range shape(op0->getOperands());
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::DenseI64ArrayAttr expanding;
    ::mlir::DenseI64ArrayAttr nonexpanding;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicBroadcastInDimOp>(op0); (void)castedOp0;
    op = castedOp0;
    operand = castedOp0.getODSOperands(0);
    shape = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getBroadcastDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.dynamic_broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns4(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.dynamic_broadcast_in_dim' attribute 'broadcast_dimensions' failed to satisfy constraint: 'is iota dimensions'"))) {
        return ::mlir::failure();
      }
      dims = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKnownExpandingDimensions();
      expanding = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getKnownNonexpandingDimensions();
      nonexpanding = tblgen_attr;
    }
    if (!((nonexpanding && cast<DenseI64ArrayAttr>(nonexpanding).size() == llvm::cast<ShapedType>((*op.getODSResults(0).begin()).getType()).getRank()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'nonexpanding, op' failed to satisfy constraint: 'all dims are non-expanding'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = stablehlo::ConvertOp::create(rewriter, odsLoc, (*op.getODSResults(0).begin()).getType(), (*operand.begin())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:335
*/
struct DynamicGatherOp_ReplaceWithGather : public ::mlir::RewritePattern {
  DynamicGatherOp_ReplaceWithGather(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.dynamic_gather", 2, context, {"stablehlo.gather"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::BoolAttr indices_are_sorted;
    ::mlir::Operation::operand_range start_indices(op0->getOperands());
    ::mlir::ElementsAttr slice_sizes;
    ::mlir::stablehlo::GatherDimensionNumbersAttr dimension_numbers;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicGatherOp>(op0); (void)castedOp0;
    operand = castedOp0.getODSOperands(0);
    start_indices = castedOp0.getODSOperands(1);
    {
      auto *op1 = (*castedOp0.getODSOperands(2).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 2 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ConstantOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::ConstantOp type";
        });
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'stablehlo.constant' to have attribute 'value' of type '::mlir::ElementsAttr'";
          });
        }
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns9(rewriter, castedOp1, tblgen_attr, "op 'stablehlo.constant' attribute 'value' failed to satisfy constraint: 'is dense int elements attr'"))) {
          return ::mlir::failure();
        }
        slice_sizes = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getDimensionNumbers();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.dynamic_gather' to have attribute 'dimension_numbers' of type '::mlir::stablehlo::GatherDimensionNumbersAttr'";
        });
      }
      dimension_numbers = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndicesAreSorted();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
      indices_are_sorted = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = convertToI64Array(rewriter, slice_sizes); (void)nativeVar_0;
    ::mlir::stablehlo::GatherOp tblgen_GatherOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::GatherOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*start_indices.begin()));
      tblgen_props.dimension_numbers = ::llvm::dyn_cast_if_present<decltype(tblgen_props.dimension_numbers)>(dimension_numbers);
      tblgen_props.slice_sizes = ::llvm::dyn_cast_if_present<decltype(tblgen_props.slice_sizes)>(nativeVar_0);
      tblgen_props.indices_are_sorted = ::llvm::dyn_cast_if_present<decltype(tblgen_props.indices_are_sorted)>(indices_are_sorted);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_GatherOp_1 = ::mlir::stablehlo::GatherOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_GatherOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:354
*/
struct DynamicPadOp_ReplaceWithPad : public ::mlir::RewritePattern {
  DynamicPadOp_ReplaceWithPad(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.dynamic_pad", 1, context, {"stablehlo.pad"}) {}
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
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicPadOp>(op0); (void)castedOp0;
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
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns10(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'integer elements attribute'"))) {
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
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns10(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'integer elements attribute'"))) {
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
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns10(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'integer elements attribute'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = convertToI64Array(rewriter, edge_padding_low); (void)nativeVar_0;
    auto nativeVar_1 = convertToI64Array(rewriter, edge_padding_high); (void)nativeVar_1;
    auto nativeVar_2 = convertToI64Array(rewriter, interior_padding); (void)nativeVar_2;
    ::mlir::stablehlo::PadOp tblgen_PadOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::PadOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_values.push_back((*padding_value.begin()));
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
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:379
*/
struct DynamicReshapeOp_FoldComposedOpsToShapeOperand : public ::mlir::RewritePattern {
  DynamicReshapeOp_FoldComposedOpsToShapeOperand(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("shape.shape_of", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::shape::ShapeOfOp op;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range shape(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::shape::ShapeOfOp>(op0); (void)castedOp0;
    op = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicReshapeOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::DynamicReshapeOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      shape = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }
    if (!(((*shape.begin()).getType() == (*op.getODSResults(0).begin()).getType()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'shape, op' failed to satisfy constraint: 'operands are equal'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ shape }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:373
*/
struct DynamicReshapeOp_MergeComposition : public ::mlir::RewritePattern {
  DynamicReshapeOp_MergeComposition(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.dynamic_reshape", 2, context, {"stablehlo.dynamic_reshape"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range shape(op0->getOperands());
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Operation::operand_range shape_p(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicReshapeOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicReshapeOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::DynamicReshapeOp type";
        });
      }
      operand = castedOp1.getODSOperands(0);
      shape_p = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }
    shape = castedOp0.getODSOperands(1);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::DynamicReshapeOp tblgen_DynamicReshapeOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::DynamicReshapeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_values.push_back((*shape.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DynamicReshapeOp_0 = ::mlir::stablehlo::DynamicReshapeOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DynamicReshapeOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:394
*/
struct DynamicUpdateSliceOp_FoldToUpdateOperand : public ::mlir::RewritePattern {
  DynamicUpdateSliceOp_FoldToUpdateOperand(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.dynamic_update_slice", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Operation::operand_range update(op0->getOperands());
    ::mlir::Operation::operand_range start_indices(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicUpdateSliceOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_StablehloAggressiveSimplificationPatterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'stablehlo.dynamic_update_slice' failed to satisfy constraint: 'statically shaped tensor of any type values'"))) {
      return ::mlir::failure();
    }
    operand = castedOp0.getODSOperands(0);
    if(::mlir::failed(__mlir_ods_local_type_constraint_StablehloAggressiveSimplificationPatterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(1).begin()).getType(), "operand 1 of op 'stablehlo.dynamic_update_slice' failed to satisfy constraint: 'statically shaped tensor of any type values'"))) {
      return ::mlir::failure();
    }
    update = castedOp0.getODSOperands(1);
    start_indices = castedOp0.getODSOperands(2);
    if (!(((*operand.begin()).getType() == (*update.begin()).getType()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'operand, update' failed to satisfy constraint: 'operands are equal'";
      });
    }
    if (!((llvm::all_of(start_indices, [](Value operand) {return matchPattern(operand, m_Zero()); })))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'start_indices' failed to satisfy constraint: 'is all zero'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ update }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:388
*/
struct DynamicUpdateSliceOp_RemoveNoop : public ::mlir::RewritePattern {
  DynamicUpdateSliceOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.dynamic_update_slice", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Attribute update;
    ::mlir::Operation::operand_range start_indices(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::DynamicUpdateSliceOp>(op0); (void)castedOp0;
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
        update = arg1_0;
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns11(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'is zero extent'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }
    start_indices = castedOp0.getODSOperands(2);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ operand }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:619
*/
struct GetTupleElementOp_UnpackTuple : public ::mlir::RewritePattern {
  GetTupleElementOp_UnpackTuple(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.get_tuple_element", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::TupleOp tuple;
    ::mlir::Operation::operand_range operands(op0->getOperands());
    ::mlir::IntegerAttr idx;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::GetTupleElementOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::TupleOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::TupleOp type";
        });
      }
      tuple = castedOp1;
      operands = castedOp1.getODSOperands(0);
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIndex();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.get_tuple_element' to have attribute 'index' of type '::mlir::IntegerAttr'";
        });
      }
      idx = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = (*tuple.getODSResults(0).begin()).getDefiningOp()->getOperand(idx.getInt()); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:417
*/
struct ImagOp_CancelOutComposedOps : public ::mlir::RewritePattern {
  ImagOp_CancelOutComposedOps(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.imag", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::ImagOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_3(rewriter, op1, tblgen_ops, lhs, rhs))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ rhs }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:425
*/
struct IotaOp_FoldScalarToZero : public ::mlir::RewritePattern {
  IotaOp_FoldScalarToZero(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.iota", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::IotaOp iota;
    ::mlir::IntegerAttr dim;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::IotaOp>(op0); (void)castedOp0;
    iota = castedOp0;
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIotaDimension();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.iota' to have attribute 'iota_dimension' of type '::mlir::IntegerAttr'";
        });
      }
      dim = tblgen_attr;
    }
    if (!((llvm::cast<ShapedType>((*iota.getODSResults(0).begin()).getType()).getDimSize(dim.getInt()) == 1))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'iota, dim' failed to satisfy constraint: 'dim size is 1'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ::mlir::stablehlo::getConstantLike(rewriter, odsLoc, 0, (*iota.getODSResults(0).begin())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:435
*/
struct MaxOp_CanonicalizeConstantToRhs : public ::mlir::RewritePattern {
  MaxOp_CanonicalizeConstantToRhs(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.maximum", 2, context, {"stablehlo.maximum"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::MaxOp op;
    ::mlir::stablehlo::ConstantOp lhs;
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::MaxOp>(op0); (void)castedOp0;
    op = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, lhs, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    rhs = castedOp0.getODSOperands(1);
    if (!((llvm::isa<BlockArgument>((*rhs.begin())) || !llvm::isa<stablehlo::ConstantOp>((*rhs.begin()).getDefiningOp())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: 'is not a constant.'";
      });
    }
    if (!(((*op.getODSResults(0).begin()).getDefiningOp()->hasTrait<hlo::OpTrait::IsCommutative>()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op' failed to satisfy constraint: 'op is commutative'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::MaxOp new_op;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::MaxOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*rhs.begin()));
      tblgen_values.push_back((*lhs.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      new_op = ::mlir::stablehlo::MaxOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ new_op.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*new_op.getODSResults(0).begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:442
*/
struct MinOp_CanonicalizeConstantToRhs : public ::mlir::RewritePattern {
  MinOp_CanonicalizeConstantToRhs(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.minimum", 2, context, {"stablehlo.minimum"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::MinOp op;
    ::mlir::stablehlo::ConstantOp lhs;
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::MinOp>(op0); (void)castedOp0;
    op = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, lhs, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    rhs = castedOp0.getODSOperands(1);
    if (!((llvm::isa<BlockArgument>((*rhs.begin())) || !llvm::isa<stablehlo::ConstantOp>((*rhs.begin()).getDefiningOp())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: 'is not a constant.'";
      });
    }
    if (!(((*op.getODSResults(0).begin()).getDefiningOp()->hasTrait<hlo::OpTrait::IsCommutative>()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op' failed to satisfy constraint: 'op is commutative'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::MinOp new_op;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::MinOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*rhs.begin()));
      tblgen_values.push_back((*lhs.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      new_op = ::mlir::stablehlo::MinOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ new_op.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*new_op.getODSResults(0).begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:449
*/
struct MulOp_CanonicalizeConstantToRhs : public ::mlir::RewritePattern {
  MulOp_CanonicalizeConstantToRhs(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.multiply", 2, context, {"stablehlo.multiply"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::MulOp op;
    ::mlir::stablehlo::ConstantOp lhs;
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::MulOp>(op0); (void)castedOp0;
    op = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, lhs, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    rhs = castedOp0.getODSOperands(1);
    if (!((llvm::isa<BlockArgument>((*rhs.begin())) || !llvm::isa<stablehlo::ConstantOp>((*rhs.begin()).getDefiningOp())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: 'is not a constant.'";
      });
    }
    if (!(((*op.getODSResults(0).begin()).getDefiningOp()->hasTrait<hlo::OpTrait::IsCommutative>()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op' failed to satisfy constraint: 'op is commutative'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::MulOp new_op;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::MulOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*rhs.begin()));
      tblgen_values.push_back((*lhs.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      new_op = ::mlir::stablehlo::MulOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ new_op.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*new_op.getODSResults(0).begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:456
*/
struct MulOp_FoldToZero : public ::mlir::RewritePattern {
  MulOp_FoldToZero(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.multiply", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::MulOp mul_op;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::stablehlo::ConstantOp zero;
    ::mlir::ElementsAttr value;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::MulOp>(op0); (void)castedOp0;
    mul_op = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_1(rewriter, op1, tblgen_ops, zero, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ zero.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*mul_op.getODSResults(0).begin()), (*zero.getODSResults(0).begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:462
*/
struct MulOp_RemoveNoop : public ::mlir::RewritePattern {
  MulOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.multiply", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::MulOp mul_op;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::ElementsAttr value;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::MulOp>(op0); (void)castedOp0;
    mul_op = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ConstantOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::ConstantOp type";
        });
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'stablehlo.constant' to have attribute 'value' of type '::mlir::ElementsAttr'";
          });
        }
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns12(rewriter, castedOp1, tblgen_attr, "op 'stablehlo.constant' attribute 'value' failed to satisfy constraint: 'is integer one'"))) {
          return ::mlir::failure();
        }
        value = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ lhs }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*mul_op.getODSResults(0).begin()), (*lhs.begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:471
*/
struct OrOp_CanonicalizeConstantToRhs : public ::mlir::RewritePattern {
  OrOp_CanonicalizeConstantToRhs(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.or", 2, context, {"stablehlo.or"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::OrOp op;
    ::mlir::stablehlo::ConstantOp lhs;
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::OrOp>(op0); (void)castedOp0;
    op = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, lhs, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    rhs = castedOp0.getODSOperands(1);
    if (!((llvm::isa<BlockArgument>((*rhs.begin())) || !llvm::isa<stablehlo::ConstantOp>((*rhs.begin()).getDefiningOp())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: 'is not a constant.'";
      });
    }
    if (!(((*op.getODSResults(0).begin()).getDefiningOp()->hasTrait<hlo::OpTrait::IsCommutative>()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op' failed to satisfy constraint: 'op is commutative'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::OrOp new_op;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::OrOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*rhs.begin()));
      tblgen_values.push_back((*lhs.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      new_op = ::mlir::stablehlo::OrOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ new_op.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*new_op.getODSResults(0).begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:474
*/
struct OrOp_FoldToOne : public ::mlir::RewritePattern {
  OrOp_FoldToOne(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.or", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::OrOp op;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::stablehlo::ConstantOp one;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::OrOp>(op0); (void)castedOp0;
    op = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_2(rewriter, op1, tblgen_ops, one, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ one.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*one.getODSResults(0).begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:480
*/
struct OrOp_RemoveNoop : public ::mlir::RewritePattern {
  OrOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.or", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::OrOp op;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::stablehlo::ConstantOp zero;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::OrOp>(op0); (void)castedOp0;
    op = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_1(rewriter, op1, tblgen_ops, zero, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ lhs }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*lhs.begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:489
*/
struct PadOp_RemoveNoop : public ::mlir::RewritePattern {
  PadOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.pad", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::PadOp pad;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Operation::operand_range padding_value(op0->getOperands());
    ::mlir::DenseI64ArrayAttr interior_padding;
    ::mlir::DenseI64ArrayAttr edge_padding_low;
    ::mlir::DenseI64ArrayAttr edge_padding_high;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::PadOp>(op0); (void)castedOp0;
    pad = castedOp0;
    operand = castedOp0.getODSOperands(0);
    padding_value = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getEdgePaddingLow();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.pad' to have attribute 'edge_padding_low' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns13(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.pad' attribute 'edge_padding_low' failed to satisfy constraint: 'is an array of zeros'"))) {
        return ::mlir::failure();
      }
      edge_padding_low = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getEdgePaddingHigh();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.pad' to have attribute 'edge_padding_high' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns13(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.pad' attribute 'edge_padding_high' failed to satisfy constraint: 'is an array of zeros'"))) {
        return ::mlir::failure();
      }
      edge_padding_high = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getInteriorPadding();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.pad' to have attribute 'interior_padding' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns13(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.pad' attribute 'interior_padding' failed to satisfy constraint: 'is an array of zeros'"))) {
        return ::mlir::failure();
      }
      interior_padding = tblgen_attr;
    }
    if (!(((*pad.getODSResults(0).begin()).getType() == (*operand.begin()).getType()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'pad, operand' failed to satisfy constraint: 'operands are equal'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ operand }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:505
*/
struct RealDynamicSliceOp_ReplaceWithSlice : public ::mlir::RewritePattern {
  RealDynamicSliceOp_ReplaceWithSlice(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.real_dynamic_slice", 1, context, {"stablehlo.slice"}) {}
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
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::RealDynamicSliceOp>(op0); (void)castedOp0;
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
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns9(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'is dense int elements attr'"))) {
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
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns9(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'is dense int elements attr'"))) {
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
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns9(rewriter, op1, arg1_0, "operand 0 of native code call '::mlir::success(::mlir::matchPattern($_self->getResult(0), ::mlir::m_Constant(&$0)))' failed to satisfy constraint: 'is dense int elements attr'"))) {
          return ::mlir::failure();
        }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = convertToI64Array(rewriter, start_indices); (void)nativeVar_0;
    auto nativeVar_1 = convertToI64Array(rewriter, limit_indices); (void)nativeVar_1;
    auto nativeVar_2 = convertToI64Array(rewriter, strides); (void)nativeVar_2;
    ::mlir::stablehlo::SliceOp tblgen_SliceOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SliceOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      tblgen_props.start_indices = ::llvm::dyn_cast_if_present<decltype(tblgen_props.start_indices)>(nativeVar_0);
      tblgen_props.limit_indices = ::llvm::dyn_cast_if_present<decltype(tblgen_props.limit_indices)>(nativeVar_1);
      tblgen_props.strides = ::llvm::dyn_cast_if_present<decltype(tblgen_props.strides)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SliceOp_3 = ::mlir::stablehlo::SliceOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SliceOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:521
*/
struct RealOp_CancelOutComposedOps : public ::mlir::RewritePattern {
  RealOp_CancelOutComposedOps(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.real", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::RealOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_3(rewriter, op1, tblgen_ops, lhs, rhs))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ lhs }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:530
*/
struct ReduceOp_RemoveNoop : public ::mlir::RewritePattern {
  ReduceOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.reduce", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range operands(op0->getOperands());
    ::mlir::Operation::operand_range init(op0->getOperands());
    ::mlir::DenseI64ArrayAttr dims;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::ReduceOp>(op0); (void)castedOp0;
    operands = castedOp0.getODSOperands(0);
    init = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getDimensions();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.reduce' to have attribute 'dimensions' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns14(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.reduce' attribute 'dimensions' failed to satisfy constraint: 'is empty i64 array'"))) {
        return ::mlir::failure();
      }
      dims = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ operands }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:538
*/
struct ReshapeOp_MergeComposition : public ::mlir::RewritePattern {
  ReshapeOp_MergeComposition(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.reshape", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::ReshapeOp reshape;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::ReshapeOp>(op0); (void)castedOp0;
    reshape = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ReshapeOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::ReshapeOp type";
        });
      }
      operand = castedOp1.getODSOperands(0);
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = stablehlo::ReshapeOp::create(rewriter, odsLoc, (*reshape.getODSResults(0).begin()).getType(), (*operand.begin())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:543
*/
struct ReshapeOp_RemoveNoop : public ::mlir::RewritePattern {
  ReshapeOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.reshape", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::ReshapeOp reshape;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::ReshapeOp>(op0); (void)castedOp0;
    reshape = castedOp0;
    operand = castedOp0.getODSOperands(0);
    if (!(((*reshape.getODSResults(0).begin()).getType() == (*operand.begin()).getType()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'reshape, operand' failed to satisfy constraint: 'operands are equal'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ operand }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:558
*/
struct SelectOp_InvertBroadcastPredicateAndSwap : public ::mlir::RewritePattern {
  SelectOp_InvertBroadcastPredicateAndSwap(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.select", 3, context, {"stablehlo.broadcast_in_dim", "stablehlo.select"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range on_true(op0->getOperands());
    ::mlir::stablehlo::BroadcastInDimOp b;
    ::mlir::Operation::operand_range pred(op0->getOperands());
    ::mlir::DenseI64ArrayAttr broadcast_dimensions;
    ::mlir::Operation::operand_range on_false(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::SelectOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::BroadcastInDimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::BroadcastInDimOp type";
        });
      }
      b = castedOp1;
      {
        auto *op2 = (*castedOp1.getODSOperands(0).begin()).getDefiningOp();
        if (!(op2)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "There's no operation that defines operand 0 of castedOp1";
          });
        }
        if(::mlir::failed(static_dag_matcher_4(rewriter, op2, tblgen_ops, pred))) {
          return ::mlir::failure();
        }
        tblgen_ops.push_back(op2);
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getBroadcastDimensions();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'stablehlo.broadcast_in_dim' to have attribute 'broadcast_dimensions' of type '::mlir::DenseI64ArrayAttr'";
          });
        }
        broadcast_dimensions = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    on_true = castedOp0.getODSOperands(1);
    on_false = castedOp0.getODSOperands(2);
    if (!(((*b.getODSResults(0).begin()).hasOneUse()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'b' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::BroadcastInDimOp tblgen_BroadcastInDimOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::BroadcastInDimOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*pred.begin()));
      tblgen_props.broadcast_dimensions = ::llvm::dyn_cast_if_present<decltype(tblgen_props.broadcast_dimensions)>(broadcast_dimensions);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_types.push_back((*b.getODSResults(0).begin()).getType());
      tblgen_BroadcastInDimOp_0 = ::mlir::stablehlo::BroadcastInDimOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    ::mlir::stablehlo::SelectOp tblgen_SelectOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SelectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_BroadcastInDimOp_0.getODSResults(0).begin()));
      tblgen_values.push_back((*on_false.begin()));
      tblgen_values.push_back((*on_true.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SelectOp_1 = ::mlir::stablehlo::SelectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SelectOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:553
*/
struct SelectOp_InvertPredicateAndSwap : public ::mlir::RewritePattern {
  SelectOp_InvertPredicateAndSwap(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.select", 2, context, {"stablehlo.select"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range pred(op0->getOperands());
    ::mlir::Operation::operand_range on_true(op0->getOperands());
    ::mlir::Operation::operand_range on_false(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::SelectOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_4(rewriter, op1, tblgen_ops, pred))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    on_true = castedOp0.getODSOperands(1);
    on_false = castedOp0.getODSOperands(2);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::SelectOp tblgen_SelectOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::SelectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*pred.begin()));
      tblgen_values.push_back((*on_false.begin()));
      tblgen_values.push_back((*on_true.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_SelectOp_0 = ::mlir::stablehlo::SelectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_SelectOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:592
*/
struct SliceOp_RemoveNoop : public ::mlir::RewritePattern {
  SliceOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.slice", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::stablehlo::SliceOp op;
    ::mlir::DenseI64ArrayAttr limit_indices;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::DenseI64ArrayAttr start_indices;
    ::mlir::DenseI64ArrayAttr strides;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::SliceOp>(op0); (void)castedOp0;
    op = castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_StablehloAggressiveSimplificationPatterns1(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'stablehlo.slice' failed to satisfy constraint: 'statically shaped tensor of any type values'"))) {
      return ::mlir::failure();
    }
    operand = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getStartIndices();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.slice' to have attribute 'start_indices' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      start_indices = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLimitIndices();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.slice' to have attribute 'limit_indices' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      limit_indices = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getStrides();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.slice' to have attribute 'strides' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      strides = tblgen_attr;
    }
    if (!(((*operand.begin()).getType() == (*op.getODSResults(0).begin()).getType()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'operand, op' failed to satisfy constraint: 'operands are equal'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ operand }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:578
*/
struct SubtractOp_FoldToZero : public ::mlir::RewritePattern {
  SubtractOp_FoldToZero(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.subtract", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::mlir::Operation::operand_range operand0(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::SubtractOp>(op0); (void)castedOp0;
    if(::mlir::failed(__mlir_ods_local_type_constraint_StablehloAggressiveSimplificationPatterns2(rewriter, castedOp0, (*castedOp0.getODSOperands(0).begin()).getType(), "operand 0 of op 'stablehlo.subtract' failed to satisfy constraint: 'statically shaped tensor of 2/4/8/16/32/64-bit integer values'"))) {
      return ::mlir::failure();
    }
    operand = castedOp0.getODSOperands(0);
    operand0 = castedOp0.getODSOperands(1);
    if (!(*operand.begin() == *operand0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'operand' and 'operand0' must be equal";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ::mlir::stablehlo::getConstantLike(rewriter, odsLoc, 0, (*operand.begin())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:583
*/
struct SubtractOp_RemoveNoop : public ::mlir::RewritePattern {
  SubtractOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.subtract", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::SubtractOp op;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::SubtractOp>(op0); (void)castedOp0;
    op = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::ConstantOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::ConstantOp type";
        });
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'stablehlo.constant' to have attribute 'value' of type '::mlir::ElementsAttr'";
          });
        }
        if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns1(rewriter, castedOp1, tblgen_attr, "op 'stablehlo.constant' attribute 'value' failed to satisfy constraint: 'is int or float zero'"))) {
          return ::mlir::failure();
        }
        value = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ lhs }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*lhs.begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:605
*/
struct TransposeOp_RemoveNoop : public ::mlir::RewritePattern {
  TransposeOp_RemoveNoop(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.transpose", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::DenseI64ArrayAttr dims;
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::TransposeOp>(op0); (void)castedOp0;
    lhs = castedOp0.getODSOperands(0);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getPermutation();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.transpose' to have attribute 'permutation' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_StablehloAggressiveSimplificationPatterns4(rewriter, castedOp0, tblgen_attr, "op 'stablehlo.transpose' attribute 'permutation' failed to satisfy constraint: 'is iota dimensions'"))) {
        return ::mlir::failure();
      }
      dims = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ lhs }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:610
*/
struct TransposeOp_TransposeOfTranspose : public ::mlir::RewritePattern {
  TransposeOp_TransposeOfTranspose(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.transpose", 2, context, {"stablehlo.transpose"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range child(op0->getOperands());
    ::mlir::DenseI64ArrayAttr child_dims;
    ::mlir::DenseI64ArrayAttr dims;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::TransposeOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::mlir::stablehlo::TransposeOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::mlir::stablehlo::TransposeOp type";
        });
      }
      child = castedOp1.getODSOperands(0);
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getPermutation();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'stablehlo.transpose' to have attribute 'permutation' of type '::mlir::DenseI64ArrayAttr'";
          });
        }
        child_dims = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getPermutation();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'stablehlo.transpose' to have attribute 'permutation' of type '::mlir::DenseI64ArrayAttr'";
        });
      }
      dims = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getMergedTransposePermutation(rewriter, child_dims, dims); (void)nativeVar_0;
    ::mlir::stablehlo::TransposeOp tblgen_TransposeOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::TransposeOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*child.begin()));
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
    external/stablehlo/stablehlo/transforms/optimization/StablehloAggressiveSimplificationPatterns.td:629
*/
struct XorOp_CanonicalizeConstantToRhs : public ::mlir::RewritePattern {
  XorOp_CanonicalizeConstantToRhs(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("stablehlo.xor", 2, context, {"stablehlo.xor"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ElementsAttr value;
    ::mlir::stablehlo::XorOp op;
    ::mlir::stablehlo::ConstantOp lhs;
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::mlir::stablehlo::XorOp>(op0); (void)castedOp0;
    op = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, lhs, value))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    rhs = castedOp0.getODSOperands(1);
    if (!((llvm::isa<BlockArgument>((*rhs.begin())) || !llvm::isa<stablehlo::ConstantOp>((*rhs.begin()).getDefiningOp())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: 'is not a constant.'";
      });
    }
    if (!(((*op.getODSResults(0).begin()).getDefiningOp()->hasTrait<hlo::OpTrait::IsCommutative>()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op' failed to satisfy constraint: 'op is commutative'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::mlir::stablehlo::XorOp new_op;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::mlir::stablehlo::XorOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*rhs.begin()));
      tblgen_values.push_back((*lhs.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      new_op = ::mlir::stablehlo::XorOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ new_op.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }
    auto nativeVar_0 = mergeDiscardableAttributes((*op.getODSResults(0).begin()), (*new_op.getODSResults(0).begin())); (void)nativeVar_0;

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<AddOp_CanonicalizeConstantToRhs>(patterns.getContext());
  patterns.add<AddOp_RemoveNoop>(patterns.getContext());
  patterns.add<AndOp_CanonicalizeConstantToRhs>(patterns.getContext());
  patterns.add<AndOp_FoldToZero>(patterns.getContext());
  patterns.add<AndOp_RemoveNoop>(patterns.getContext());
  patterns.add<BroadcastInDimOp_MergeComposition>(patterns.getContext());
  patterns.add<BroadcastInDimOp_RemoveNoop>(patterns.getContext());
  patterns.add<BroadcastInDimOp_ReplaceWithReshape>(patterns.getContext());
  patterns.add<BroadcastInDimOp_ReplaceWithTranspose>(patterns.getContext());
  patterns.add<CompareOp_EqBooleanTrue>(patterns.getContext());
  patterns.add<CompareOp_NeBooleanFalse>(patterns.getContext());
  patterns.add<ComplexOp_CancelOutComposedOps>(patterns.getContext());
  patterns.add<ConvertOp_RemoveNoop>(patterns.getContext());
  patterns.add<DynamicBroadcastInDimOp_FoldToDynamicReshape>(patterns.getContext());
  patterns.add<DynamicBroadcastInDimOp_MergeComposition>(patterns.getContext());
  patterns.add<DynamicBroadcastInDimOp_RemoveNoop>(patterns.getContext());
  patterns.add<DynamicBroadcastInDimOp_ReplaceNoopWithConvert>(patterns.getContext());
  patterns.add<DynamicGatherOp_ReplaceWithGather>(patterns.getContext());
  patterns.add<DynamicPadOp_ReplaceWithPad>(patterns.getContext());
  patterns.add<DynamicReshapeOp_FoldComposedOpsToShapeOperand>(patterns.getContext());
  patterns.add<DynamicReshapeOp_MergeComposition>(patterns.getContext());
  patterns.add<DynamicUpdateSliceOp_FoldToUpdateOperand>(patterns.getContext());
  patterns.add<DynamicUpdateSliceOp_RemoveNoop>(patterns.getContext());
  patterns.add<GetTupleElementOp_UnpackTuple>(patterns.getContext());
  patterns.add<ImagOp_CancelOutComposedOps>(patterns.getContext());
  patterns.add<IotaOp_FoldScalarToZero>(patterns.getContext());
  patterns.add<MaxOp_CanonicalizeConstantToRhs>(patterns.getContext());
  patterns.add<MinOp_CanonicalizeConstantToRhs>(patterns.getContext());
  patterns.add<MulOp_CanonicalizeConstantToRhs>(patterns.getContext());
  patterns.add<MulOp_FoldToZero>(patterns.getContext());
  patterns.add<MulOp_RemoveNoop>(patterns.getContext());
  patterns.add<OrOp_CanonicalizeConstantToRhs>(patterns.getContext());
  patterns.add<OrOp_FoldToOne>(patterns.getContext());
  patterns.add<OrOp_RemoveNoop>(patterns.getContext());
  patterns.add<PadOp_RemoveNoop>(patterns.getContext());
  patterns.add<RealDynamicSliceOp_ReplaceWithSlice>(patterns.getContext());
  patterns.add<RealOp_CancelOutComposedOps>(patterns.getContext());
  patterns.add<ReduceOp_RemoveNoop>(patterns.getContext());
  patterns.add<ReshapeOp_MergeComposition>(patterns.getContext());
  patterns.add<ReshapeOp_RemoveNoop>(patterns.getContext());
  patterns.add<SelectOp_InvertBroadcastPredicateAndSwap>(patterns.getContext());
  patterns.add<SelectOp_InvertPredicateAndSwap>(patterns.getContext());
  patterns.add<SliceOp_RemoveNoop>(patterns.getContext());
  patterns.add<SubtractOp_FoldToZero>(patterns.getContext());
  patterns.add<SubtractOp_RemoveNoop>(patterns.getContext());
  patterns.add<TransposeOp_RemoveNoop>(patterns.getContext());
  patterns.add<TransposeOp_TransposeOfTranspose>(patterns.getContext());
  patterns.add<XorOp_CanonicalizeConstantToRhs>(patterns.getContext());
}
