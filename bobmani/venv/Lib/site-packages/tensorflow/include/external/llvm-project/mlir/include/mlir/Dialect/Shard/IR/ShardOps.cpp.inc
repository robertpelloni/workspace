/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ShardOps.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::mlir::shard::AllGatherOp,
::mlir::shard::AllReduceOp,
::mlir::shard::AllSliceOp,
::mlir::shard::AllToAllOp,
::mlir::shard::BroadcastOp,
::mlir::shard::GatherOp,
::mlir::shard::GetShardingOp,
::mlir::shard::GridOp,
::mlir::shard::GridShapeOp,
::mlir::shard::NeighborsLinearIndicesOp,
::mlir::shard::ProcessLinearIndexOp,
::mlir::shard::ProcessMultiIndexOp,
::mlir::shard::RecvOp,
::mlir::shard::ReduceOp,
::mlir::shard::ReduceScatterOp,
::mlir::shard::ScatterOp,
::mlir::shard::SendOp,
::mlir::shard::ShardOp,
::mlir::shard::ShardShapeOp,
::mlir::shard::ShardingOp,
::mlir::shard::ShiftOp,
::mlir::shard::UpdateHaloOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ShardOps1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((::llvm::isa<::mlir::MemRefType>(type))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType()))) || (((::llvm::isa<::mlir::RankedTensorType>(type))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType()))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be memref of any type values or ranked tensor of any type values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ShardOps2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((::llvm::isa<::mlir::TensorType>(type))) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank() >= 1)))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be non-0-ranked.tensor of any type values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ShardOps3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::llvm::isa<::mlir::RankedTensorType>(type))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be ranked tensor of any type values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ShardOps4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::IndexType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of index, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ShardOps5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::shard::ShardingType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be sharding definition, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ShardOps6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::IndexType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be index, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ShardOps7(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(64)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of 64-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ShardOps8(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((((::llvm::isa<::mlir::MemRefType>(type))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType()))) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank() >= 1)))) || ((((::llvm::isa<::mlir::TensorType>(type))) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank() >= 1)))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType()))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be non-0-ranked.memref of any type values or non-0-ranked.tensor of any type values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: flat symbol reference attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ShardOps1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: i16 dense array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ShardOps2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(attr).getType())))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: index attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ShardOps3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::shard::ReductionKindAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Reduction of an iterator/grid dimension.";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ShardOps4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: i64 dense array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ShardOps5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ShardOps6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps7(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::UnitAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: unit attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps7(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ShardOps7(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps8(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::shard::GridAxesArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: ";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps8(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ShardOps8(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps9(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ShardOps9(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ShardOps9(attr, attrName, [op]() {
    return op->emitOpError();
  });
}
namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::AllGatherOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AllGatherOpGenericAdaptorBase::AllGatherOpGenericAdaptorBase(AllGatherOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef AllGatherOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr AllGatherOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> AllGatherOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt AllGatherOpGenericAdaptorBase::getGatherAxis() {
  auto attr = getGatherAxisAttr();
  return attr.getValue();
}


} // namespace detail
AllGatherOpAdaptor::AllGatherOpAdaptor(AllGatherOp op) : AllGatherOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AllGatherOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_gather_axis = getProperties().gather_axis; (void)tblgen_gather_axis;
  if (!tblgen_gather_axis) return emitError(loc, "'shard.all_gather' op requires attribute 'gather_axis'");
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.all_gather' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.all_gather' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.all_gather' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_gather_axis && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_gather_axis))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(tblgen_gather_axis).getType())))))
    return emitError(loc, "'shard.all_gather' op attribute 'gather_axis' failed to satisfy constraint: index attribute");
  return ::mlir::success();
}

::llvm::LogicalResult AllGatherOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.gather_axis;
       auto attr = dict.get("gather_axis");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `gather_axis` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AllGatherOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.gather_axis;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("gather_axis",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AllGatherOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.gather_axis.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AllGatherOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "gather_axis")
      return prop.gather_axis;

    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;
  return std::nullopt;
}

void AllGatherOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "gather_axis") {
       prop.gather_axis = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.gather_axis)>>(value);
       return;
    }

    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }
}

void AllGatherOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.gather_axis) attrs.append("gather_axis", prop.gather_axis);

    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);
}

::llvm::LogicalResult AllGatherOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGatherAxisAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(attr, "gather_axis", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AllGatherOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.gather_axis)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AllGatherOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.gather_axis);
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);
}

::llvm::StringRef AllGatherOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> AllGatherOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt AllGatherOp::getGatherAxis() {
  auto attr = getGatherAxisAttr();
  return attr.getValue();
}

void AllGatherOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void AllGatherOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void AllGatherOp::setGatherAxis(::llvm::APInt attrValue) {
  getProperties().gather_axis = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIndexType(), attrValue);
}

void AllGatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().gather_axis = gather_axis;
  odsState.addTypes(result);
}

AllGatherOp AllGatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis));
  auto __res__ = ::llvm::dyn_cast<AllGatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllGatherOp AllGatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis));
}

void AllGatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().gather_axis = gather_axis;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AllGatherOp AllGatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis));
  auto __res__ = ::llvm::dyn_cast<AllGatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllGatherOp AllGatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis));
}

void AllGatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().gather_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), gather_axis);
  odsState.addTypes(result);
}

AllGatherOp AllGatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis));
  auto __res__ = ::llvm::dyn_cast<AllGatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllGatherOp AllGatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis));
}

void AllGatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().gather_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), gather_axis);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AllGatherOp AllGatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis));
  auto __res__ = ::llvm::dyn_cast<AllGatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllGatherOp AllGatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis));
}

void AllGatherOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<AllGatherOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AllGatherOp AllGatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AllGatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllGatherOp AllGatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AllGatherOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AllGatherOp AllGatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AllGatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllGatherOp AllGatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void AllGatherOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult AllGatherOp::verifyInvariantsImpl() {
  auto tblgen_gather_axis = getProperties().gather_axis; (void)tblgen_gather_axis;
  if (!tblgen_gather_axis) return emitOpError("requires attribute 'gather_axis'");
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(*this, tblgen_gather_axis, "gather_axis")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AllGatherOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AllGatherOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::mlir::IntegerAttr gather_axisAttr;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<AllGatherOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<AllGatherOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (parser.parseKeyword("gather_axis"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gather_axisAttr, parser.getBuilder().getIndexType())) {
    return ::mlir::failure();
  }
  if (gather_axisAttr) result.getOrAddProperties<AllGatherOp::Properties>().gather_axis = gather_axisAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void AllGatherOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  _odsPrinter << ' ' << "gather_axis";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGatherAxisAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("gather_axis");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void AllGatherOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::AllGatherOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::AllReduceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AllReduceOpGenericAdaptorBase::AllReduceOpGenericAdaptorBase(AllReduceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef AllReduceOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr AllReduceOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> AllReduceOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::mlir::shard::ReductionKindAttr AllReduceOpGenericAdaptorBase::getReductionAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::shard::ReductionKindAttr>(getProperties().reduction);
  return attr;
}

::mlir::shard::ReductionKind AllReduceOpGenericAdaptorBase::getReduction() {
  auto attr = getReductionAttr();
  return attr.getValue();
}


} // namespace detail
AllReduceOpAdaptor::AllReduceOpAdaptor(AllReduceOp op) : AllReduceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AllReduceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.all_reduce' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_reduction = getProperties().reduction; (void)tblgen_reduction;

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.all_reduce' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.all_reduce' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_reduction && !((::llvm::isa<::mlir::shard::ReductionKindAttr>(tblgen_reduction))))
    return emitError(loc, "'shard.all_reduce' op attribute 'reduction' failed to satisfy constraint: Reduction of an iterator/grid dimension.");
  return ::mlir::success();
}

::llvm::LogicalResult AllReduceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.reduction;
       auto attr = dict.get("reduction");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `reduction` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AllReduceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.reduction;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("reduction",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AllReduceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.reduction.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AllReduceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;

    if (name == "reduction")
      return prop.reduction;
  return std::nullopt;
}

void AllReduceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }

    if (name == "reduction") {
       prop.reduction = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.reduction)>>(value);
       return;
    }
}

void AllReduceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);

    if (prop.reduction) attrs.append("reduction", prop.reduction);
}

::llvm::LogicalResult AllReduceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getReductionAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps4(attr, "reduction", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AllReduceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.reduction)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AllReduceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);

  writer.writeOptionalAttribute(prop.reduction);
}

::llvm::StringRef AllReduceOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> AllReduceOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::mlir::shard::ReductionKind AllReduceOp::getReduction() {
  auto attr = getReductionAttr();
  return attr.getValue();
}

void AllReduceOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void AllReduceOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void AllReduceOp::setReduction(::mlir::shard::ReductionKind attrValue) {
  getProperties().reduction = ::mlir::shard::ReductionKindAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

AllReduceOp AllReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringRef grid, ArrayRef<GridAxis> gridAxes, ReductionKind reduction) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(grid)>(grid), std::forward<decltype(gridAxes)>(gridAxes), std::forward<decltype(reduction)>(reduction));
  auto __res__ = ::llvm::dyn_cast<AllReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllReduceOp AllReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringRef grid, ArrayRef<GridAxis> gridAxes, ReductionKind reduction) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(grid)>(grid), std::forward<decltype(gridAxes)>(gridAxes), std::forward<decltype(reduction)>(reduction));
}

void AllReduceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  if (reduction) {
    odsState.getOrAddProperties<Properties>().reduction = reduction;
  }
  odsState.addTypes(result);
}

AllReduceOp AllReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction));
  auto __res__ = ::llvm::dyn_cast<AllReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllReduceOp AllReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction));
}

void AllReduceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  if (reduction) {
    odsState.getOrAddProperties<Properties>().reduction = reduction;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AllReduceOp AllReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction));
  auto __res__ = ::llvm::dyn_cast<AllReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllReduceOp AllReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction));
}

void AllReduceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().reduction = ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), reduction);
  odsState.addTypes(result);
}

AllReduceOp AllReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction));
  auto __res__ = ::llvm::dyn_cast<AllReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllReduceOp AllReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction));
}

void AllReduceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().reduction = ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), reduction);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AllReduceOp AllReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction));
  auto __res__ = ::llvm::dyn_cast<AllReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllReduceOp AllReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction));
}

void AllReduceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<AllReduceOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AllReduceOp AllReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AllReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllReduceOp AllReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AllReduceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AllReduceOp AllReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AllReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllReduceOp AllReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void AllReduceOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
  if (!properties.reduction)
    properties.reduction = ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), ::mlir::shard::ReductionKind::Sum);
}

::llvm::LogicalResult AllReduceOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_reduction = getProperties().reduction; (void)tblgen_reduction;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps4(*this, tblgen_reduction, "reduction")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AllReduceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AllReduceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::mlir::shard::ReductionKindAttr reductionAttr;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<AllReduceOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<AllReduceOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("reduction"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(reductionAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (reductionAttr) result.getOrAddProperties<AllReduceOp::Properties>().reduction = reductionAttr;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void AllReduceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  if (getReductionAttr() != ::mlir::shard::ReductionKindAttr::get(::mlir::OpBuilder((*this)->getContext()).getContext(), ::mlir::shard::ReductionKind::Sum)) {
    _odsPrinter << ' ' << "reduction";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getReductionAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("reduction");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getReductionAttr();
     if(attr && (attr == ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), ::mlir::shard::ReductionKind::Sum)))
       elidedAttrs.push_back("reduction");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void AllReduceOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::AllReduceOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::AllSliceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AllSliceOpGenericAdaptorBase::AllSliceOpGenericAdaptorBase(AllSliceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef AllSliceOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr AllSliceOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> AllSliceOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt AllSliceOpGenericAdaptorBase::getSliceAxis() {
  auto attr = getSliceAxisAttr();
  return attr.getValue();
}


} // namespace detail
AllSliceOpAdaptor::AllSliceOpAdaptor(AllSliceOp op) : AllSliceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AllSliceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.all_slice' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_slice_axis = getProperties().slice_axis; (void)tblgen_slice_axis;
  if (!tblgen_slice_axis) return emitError(loc, "'shard.all_slice' op requires attribute 'slice_axis'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.all_slice' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.all_slice' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_slice_axis && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_slice_axis))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(tblgen_slice_axis).getType())))))
    return emitError(loc, "'shard.all_slice' op attribute 'slice_axis' failed to satisfy constraint: index attribute");
  return ::mlir::success();
}

::llvm::LogicalResult AllSliceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.slice_axis;
       auto attr = dict.get("slice_axis");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `slice_axis` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AllSliceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.slice_axis;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("slice_axis",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AllSliceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.slice_axis.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AllSliceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;

    if (name == "slice_axis")
      return prop.slice_axis;
  return std::nullopt;
}

void AllSliceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }

    if (name == "slice_axis") {
       prop.slice_axis = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.slice_axis)>>(value);
       return;
    }
}

void AllSliceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);

    if (prop.slice_axis) attrs.append("slice_axis", prop.slice_axis);
}

::llvm::LogicalResult AllSliceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSliceAxisAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(attr, "slice_axis", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AllSliceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.slice_axis)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AllSliceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);
  writer.writeAttribute(prop.slice_axis);
}

::llvm::StringRef AllSliceOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> AllSliceOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt AllSliceOp::getSliceAxis() {
  auto attr = getSliceAxisAttr();
  return attr.getValue();
}

void AllSliceOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void AllSliceOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void AllSliceOp::setSliceAxis(::llvm::APInt attrValue) {
  getProperties().slice_axis = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIndexType(), attrValue);
}

AllSliceOp AllSliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, GridOp grid, ArrayRef<GridAxis> gridAxes, int64_t sliceAxis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(grid)>(grid), std::forward<decltype(gridAxes)>(gridAxes), std::forward<decltype(sliceAxis)>(sliceAxis));
  auto __res__ = ::llvm::dyn_cast<AllSliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllSliceOp AllSliceOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, GridOp grid, ArrayRef<GridAxis> gridAxes, int64_t sliceAxis) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(grid)>(grid), std::forward<decltype(gridAxes)>(gridAxes), std::forward<decltype(sliceAxis)>(sliceAxis));
}

AllSliceOp AllSliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Type result_type, Value input, StringRef grid, ArrayRef<GridAxis> gridAxes, int64_t sliceAxis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result_type)>(result_type), std::forward<decltype(input)>(input), std::forward<decltype(grid)>(grid), std::forward<decltype(gridAxes)>(gridAxes), std::forward<decltype(sliceAxis)>(sliceAxis));
  auto __res__ = ::llvm::dyn_cast<AllSliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllSliceOp AllSliceOp::create(::mlir::ImplicitLocOpBuilder &builder, Type result_type, Value input, StringRef grid, ArrayRef<GridAxis> gridAxes, int64_t sliceAxis) {
  return create(builder, builder.getLoc(), std::forward<decltype(result_type)>(result_type), std::forward<decltype(input)>(input), std::forward<decltype(grid)>(grid), std::forward<decltype(gridAxes)>(gridAxes), std::forward<decltype(sliceAxis)>(sliceAxis));
}

void AllSliceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().slice_axis = slice_axis;
  odsState.addTypes(result);
}

AllSliceOp AllSliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(slice_axis)>(slice_axis));
  auto __res__ = ::llvm::dyn_cast<AllSliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllSliceOp AllSliceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(slice_axis)>(slice_axis));
}

void AllSliceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().slice_axis = slice_axis;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AllSliceOp AllSliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(slice_axis)>(slice_axis));
  auto __res__ = ::llvm::dyn_cast<AllSliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllSliceOp AllSliceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(slice_axis)>(slice_axis));
}

void AllSliceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().slice_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), slice_axis);
  odsState.addTypes(result);
}

AllSliceOp AllSliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(slice_axis)>(slice_axis));
  auto __res__ = ::llvm::dyn_cast<AllSliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllSliceOp AllSliceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(slice_axis)>(slice_axis));
}

void AllSliceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().slice_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), slice_axis);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AllSliceOp AllSliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(slice_axis)>(slice_axis));
  auto __res__ = ::llvm::dyn_cast<AllSliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllSliceOp AllSliceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(slice_axis)>(slice_axis));
}

void AllSliceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<AllSliceOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AllSliceOp AllSliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AllSliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllSliceOp AllSliceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AllSliceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AllSliceOp AllSliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AllSliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllSliceOp AllSliceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void AllSliceOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult AllSliceOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_slice_axis = getProperties().slice_axis; (void)tblgen_slice_axis;
  if (!tblgen_slice_axis) return emitOpError("requires attribute 'slice_axis'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(*this, tblgen_slice_axis, "slice_axis")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AllSliceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AllSliceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::mlir::IntegerAttr slice_axisAttr;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<AllSliceOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<AllSliceOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (parser.parseKeyword("slice_axis"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(slice_axisAttr, parser.getBuilder().getIndexType())) {
    return ::mlir::failure();
  }
  if (slice_axisAttr) result.getOrAddProperties<AllSliceOp::Properties>().slice_axis = slice_axisAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::TensorType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::TensorType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void AllSliceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  _odsPrinter << ' ' << "slice_axis";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getSliceAxisAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("slice_axis");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::TensorType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::TensorType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void AllSliceOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::AllSliceOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::AllToAllOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AllToAllOpGenericAdaptorBase::AllToAllOpGenericAdaptorBase(AllToAllOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef AllToAllOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr AllToAllOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> AllToAllOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt AllToAllOpGenericAdaptorBase::getSplitAxis() {
  auto attr = getSplitAxisAttr();
  return attr.getValue();
}

::llvm::APInt AllToAllOpGenericAdaptorBase::getConcatAxis() {
  auto attr = getConcatAxisAttr();
  return attr.getValue();
}


} // namespace detail
AllToAllOpAdaptor::AllToAllOpAdaptor(AllToAllOp op) : AllToAllOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AllToAllOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_concat_axis = getProperties().concat_axis; (void)tblgen_concat_axis;
  if (!tblgen_concat_axis) return emitError(loc, "'shard.all_to_all' op requires attribute 'concat_axis'");
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.all_to_all' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_split_axis = getProperties().split_axis; (void)tblgen_split_axis;
  if (!tblgen_split_axis) return emitError(loc, "'shard.all_to_all' op requires attribute 'split_axis'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.all_to_all' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.all_to_all' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_split_axis && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_split_axis))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(tblgen_split_axis).getType())))))
    return emitError(loc, "'shard.all_to_all' op attribute 'split_axis' failed to satisfy constraint: index attribute");

  if (tblgen_concat_axis && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_concat_axis))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(tblgen_concat_axis).getType())))))
    return emitError(loc, "'shard.all_to_all' op attribute 'concat_axis' failed to satisfy constraint: index attribute");
  return ::mlir::success();
}

::llvm::LogicalResult AllToAllOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.concat_axis;
       auto attr = dict.get("concat_axis");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `concat_axis` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.split_axis;
       auto attr = dict.get("split_axis");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `split_axis` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AllToAllOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.concat_axis;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("concat_axis",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.split_axis;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("split_axis",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AllToAllOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.concat_axis.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.split_axis.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AllToAllOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "concat_axis")
      return prop.concat_axis;

    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;

    if (name == "split_axis")
      return prop.split_axis;
  return std::nullopt;
}

void AllToAllOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "concat_axis") {
       prop.concat_axis = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.concat_axis)>>(value);
       return;
    }

    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }

    if (name == "split_axis") {
       prop.split_axis = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.split_axis)>>(value);
       return;
    }
}

void AllToAllOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.concat_axis) attrs.append("concat_axis", prop.concat_axis);

    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);

    if (prop.split_axis) attrs.append("split_axis", prop.split_axis);
}

::llvm::LogicalResult AllToAllOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getConcatAxisAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(attr, "concat_axis", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSplitAxisAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(attr, "split_axis", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AllToAllOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.concat_axis)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.split_axis)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AllToAllOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.concat_axis);
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);
  writer.writeAttribute(prop.split_axis);
}

::llvm::StringRef AllToAllOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> AllToAllOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt AllToAllOp::getSplitAxis() {
  auto attr = getSplitAxisAttr();
  return attr.getValue();
}

::llvm::APInt AllToAllOp::getConcatAxis() {
  auto attr = getConcatAxisAttr();
  return attr.getValue();
}

void AllToAllOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void AllToAllOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void AllToAllOp::setSplitAxis(::llvm::APInt attrValue) {
  getProperties().split_axis = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIndexType(), attrValue);
}

void AllToAllOp::setConcatAxis(::llvm::APInt attrValue) {
  getProperties().concat_axis = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIndexType(), attrValue);
}

void AllToAllOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().split_axis = split_axis;
  odsState.getOrAddProperties<Properties>().concat_axis = concat_axis;
  odsState.addTypes(result);
}

AllToAllOp AllToAllOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(split_axis)>(split_axis), std::forward<decltype(concat_axis)>(concat_axis));
  auto __res__ = ::llvm::dyn_cast<AllToAllOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllToAllOp AllToAllOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(split_axis)>(split_axis), std::forward<decltype(concat_axis)>(concat_axis));
}

void AllToAllOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().split_axis = split_axis;
  odsState.getOrAddProperties<Properties>().concat_axis = concat_axis;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AllToAllOp AllToAllOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(split_axis)>(split_axis), std::forward<decltype(concat_axis)>(concat_axis));
  auto __res__ = ::llvm::dyn_cast<AllToAllOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllToAllOp AllToAllOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(split_axis)>(split_axis), std::forward<decltype(concat_axis)>(concat_axis));
}

void AllToAllOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().split_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), split_axis);
  odsState.getOrAddProperties<Properties>().concat_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), concat_axis);
  odsState.addTypes(result);
}

AllToAllOp AllToAllOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(split_axis)>(split_axis), std::forward<decltype(concat_axis)>(concat_axis));
  auto __res__ = ::llvm::dyn_cast<AllToAllOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllToAllOp AllToAllOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(split_axis)>(split_axis), std::forward<decltype(concat_axis)>(concat_axis));
}

void AllToAllOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().split_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), split_axis);
  odsState.getOrAddProperties<Properties>().concat_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), concat_axis);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AllToAllOp AllToAllOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(split_axis)>(split_axis), std::forward<decltype(concat_axis)>(concat_axis));
  auto __res__ = ::llvm::dyn_cast<AllToAllOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllToAllOp AllToAllOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(split_axis)>(split_axis), std::forward<decltype(concat_axis)>(concat_axis));
}

void AllToAllOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<AllToAllOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AllToAllOp AllToAllOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AllToAllOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllToAllOp AllToAllOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AllToAllOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AllToAllOp AllToAllOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AllToAllOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AllToAllOp AllToAllOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void AllToAllOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult AllToAllOp::verifyInvariantsImpl() {
  auto tblgen_concat_axis = getProperties().concat_axis; (void)tblgen_concat_axis;
  if (!tblgen_concat_axis) return emitOpError("requires attribute 'concat_axis'");
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_split_axis = getProperties().split_axis; (void)tblgen_split_axis;
  if (!tblgen_split_axis) return emitOpError("requires attribute 'split_axis'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(*this, tblgen_split_axis, "split_axis")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(*this, tblgen_concat_axis, "concat_axis")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AllToAllOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AllToAllOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::mlir::IntegerAttr split_axisAttr;
  ::mlir::IntegerAttr concat_axisAttr;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<AllToAllOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<AllToAllOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (parser.parseKeyword("split_axis"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(split_axisAttr, parser.getBuilder().getIndexType())) {
    return ::mlir::failure();
  }
  if (split_axisAttr) result.getOrAddProperties<AllToAllOp::Properties>().split_axis = split_axisAttr;
  if (parser.parseKeyword("concat_axis"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(concat_axisAttr, parser.getBuilder().getIndexType())) {
    return ::mlir::failure();
  }
  if (concat_axisAttr) result.getOrAddProperties<AllToAllOp::Properties>().concat_axis = concat_axisAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::TensorType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::TensorType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void AllToAllOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  _odsPrinter << ' ' << "split_axis";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getSplitAxisAttr());
  _odsPrinter << ' ' << "concat_axis";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getConcatAxisAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("split_axis");
  elidedAttrs.push_back("concat_axis");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::TensorType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::TensorType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void AllToAllOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::AllToAllOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::BroadcastOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

BroadcastOpGenericAdaptorBase::BroadcastOpGenericAdaptorBase(BroadcastOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> BroadcastOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef BroadcastOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr BroadcastOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> BroadcastOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> BroadcastOpGenericAdaptorBase::getRoot() {
  auto attr = getRootAttr();
  return attr;
}


} // namespace detail
BroadcastOpAdaptor::BroadcastOpAdaptor(BroadcastOp op) : BroadcastOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BroadcastOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.broadcast' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_root = getProperties().root; (void)tblgen_root;
  if (!tblgen_root) return emitError(loc, "'shard.broadcast' op requires attribute 'root'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.broadcast' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.broadcast' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_root && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_root))))
    return emitError(loc, "'shard.broadcast' op attribute 'root' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> BroadcastOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange BroadcastOp::getRootDynamicMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult BroadcastOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.root;
       auto attr = dict.get("root");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `root` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute BroadcastOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.root;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("root",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BroadcastOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.root.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> BroadcastOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;

    if (name == "root")
      return prop.root;
  return std::nullopt;
}

void BroadcastOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }

    if (name == "root") {
       prop.root = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.root)>>(value);
       return;
    }
}

void BroadcastOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);

    if (prop.root) attrs.append("root", prop.root);
}

::llvm::LogicalResult BroadcastOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRootAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "root", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult BroadcastOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.root)))
    return ::mlir::failure();
  return ::mlir::success();
}

void BroadcastOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);
  writer.writeAttribute(prop.root);
}

::llvm::StringRef BroadcastOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> BroadcastOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> BroadcastOp::getRoot() {
  auto attr = getRootAttr();
  return attr;
}

void BroadcastOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void BroadcastOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void BroadcastOp::setRoot(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().root = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void BroadcastOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().root = root;
  odsState.addTypes(result);
}

BroadcastOp BroadcastOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<BroadcastOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BroadcastOp BroadcastOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void BroadcastOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().root = root;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BroadcastOp BroadcastOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<BroadcastOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BroadcastOp BroadcastOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void BroadcastOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().root = odsBuilder.getDenseI64ArrayAttr(root);
  odsState.addTypes(result);
}

BroadcastOp BroadcastOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<BroadcastOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BroadcastOp BroadcastOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void BroadcastOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().root = odsBuilder.getDenseI64ArrayAttr(root);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BroadcastOp BroadcastOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<BroadcastOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BroadcastOp BroadcastOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void BroadcastOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<BroadcastOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

BroadcastOp BroadcastOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BroadcastOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BroadcastOp BroadcastOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BroadcastOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BroadcastOp BroadcastOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BroadcastOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BroadcastOp BroadcastOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void BroadcastOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult BroadcastOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_root = getProperties().root; (void)tblgen_root;
  if (!tblgen_root) return emitOpError("requires attribute 'root'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_root, "root")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!(((::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getShape()) && (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()))))
    return emitOpError("failed to verify that all of {input, result} have same shape");
  if (!(((getElementTypeOrSelf((*this->getODSOperands(0).begin()))) == (getElementTypeOrSelf((*this->getODSResults(0).begin()))) && (getElementTypeOrSelf((*this->getODSResults(0).begin()))) == (getElementTypeOrSelf((*this->getODSOperands(0).begin()))))))
    return emitOpError("failed to verify that all of {input, result} have same element type");
  return ::mlir::success();
}

::llvm::LogicalResult BroadcastOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult BroadcastOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> root_dynamicOperands;
  ::llvm::SMLoc root_dynamicOperandsLoc;
  (void)root_dynamicOperandsLoc;
  ::mlir::DenseI64ArrayAttr rootAttr;
  ::llvm::ArrayRef<::mlir::Type> allOperandTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<BroadcastOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<BroadcastOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (parser.parseKeyword("root"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    root_dynamicOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, root_dynamicOperands, rootAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<BroadcastOp::Properties>().root = rootAttr;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType allOperand__allResult_functionType;
  if (parser.parseType(allOperand__allResult_functionType))
    return ::mlir::failure();
  allOperandTypes = allOperand__allResult_functionType.getInputs();
  allResultTypes = allOperand__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(::llvm::concat<const ::mlir::OpAsmParser::UnresolvedOperand>(inputOperands, root_dynamicOperands), allOperandTypes, parser.getNameLoc(), result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void BroadcastOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  _odsPrinter << ' ' << "root";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  printDynamicIndexList(_odsPrinter, *this, getRootDynamic(), getRootAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("root");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperation()->getOperandTypes(), getOperation()->getResultTypes());
}

void BroadcastOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::BroadcastOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::GatherOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GatherOpGenericAdaptorBase::GatherOpGenericAdaptorBase(GatherOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> GatherOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef GatherOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr GatherOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> GatherOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt GatherOpGenericAdaptorBase::getGatherAxis() {
  auto attr = getGatherAxisAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int64_t> GatherOpGenericAdaptorBase::getRoot() {
  auto attr = getRootAttr();
  return attr;
}


} // namespace detail
GatherOpAdaptor::GatherOpAdaptor(GatherOp op) : GatherOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GatherOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_gather_axis = getProperties().gather_axis; (void)tblgen_gather_axis;
  if (!tblgen_gather_axis) return emitError(loc, "'shard.gather' op requires attribute 'gather_axis'");
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.gather' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_root = getProperties().root; (void)tblgen_root;
  if (!tblgen_root) return emitError(loc, "'shard.gather' op requires attribute 'root'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.gather' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.gather' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_gather_axis && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_gather_axis))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(tblgen_gather_axis).getType())))))
    return emitError(loc, "'shard.gather' op attribute 'gather_axis' failed to satisfy constraint: index attribute");

  if (tblgen_root && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_root))))
    return emitError(loc, "'shard.gather' op attribute 'root' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> GatherOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange GatherOp::getRootDynamicMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult GatherOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.gather_axis;
       auto attr = dict.get("gather_axis");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `gather_axis` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.root;
       auto attr = dict.get("root");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `root` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute GatherOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.gather_axis;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("gather_axis",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.root;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("root",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GatherOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.gather_axis.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.root.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> GatherOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "gather_axis")
      return prop.gather_axis;

    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;

    if (name == "root")
      return prop.root;
  return std::nullopt;
}

void GatherOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "gather_axis") {
       prop.gather_axis = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.gather_axis)>>(value);
       return;
    }

    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }

    if (name == "root") {
       prop.root = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.root)>>(value);
       return;
    }
}

void GatherOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.gather_axis) attrs.append("gather_axis", prop.gather_axis);

    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);

    if (prop.root) attrs.append("root", prop.root);
}

::llvm::LogicalResult GatherOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGatherAxisAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(attr, "gather_axis", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRootAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "root", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult GatherOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.gather_axis)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.root)))
    return ::mlir::failure();
  return ::mlir::success();
}

void GatherOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.gather_axis);
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);
  writer.writeAttribute(prop.root);
}

::llvm::StringRef GatherOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> GatherOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt GatherOp::getGatherAxis() {
  auto attr = getGatherAxisAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int64_t> GatherOp::getRoot() {
  auto attr = getRootAttr();
  return attr;
}

void GatherOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void GatherOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void GatherOp::setGatherAxis(::llvm::APInt attrValue) {
  getProperties().gather_axis = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIndexType(), attrValue);
}

void GatherOp::setRoot(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().root = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void GatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().gather_axis = gather_axis;
  odsState.getOrAddProperties<Properties>().root = root;
  odsState.addTypes(result);
}

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void GatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().gather_axis = gather_axis;
  odsState.getOrAddProperties<Properties>().root = root;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void GatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().gather_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), gather_axis);
  odsState.getOrAddProperties<Properties>().root = odsBuilder.getDenseI64ArrayAttr(root);
  odsState.addTypes(result);
}

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void GatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().gather_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), gather_axis);
  odsState.getOrAddProperties<Properties>().root = odsBuilder.getDenseI64ArrayAttr(root);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(gather_axis)>(gather_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void GatherOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<GatherOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GatherOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void GatherOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult GatherOp::verifyInvariantsImpl() {
  auto tblgen_gather_axis = getProperties().gather_axis; (void)tblgen_gather_axis;
  if (!tblgen_gather_axis) return emitOpError("requires attribute 'gather_axis'");
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_root = getProperties().root; (void)tblgen_root;
  if (!tblgen_root) return emitOpError("requires attribute 'root'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(*this, tblgen_gather_axis, "gather_axis")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_root, "root")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!(((::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getRank()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getRank()) && (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getRank()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getRank()))))
    return emitOpError("failed to verify that all of {input, result} have same rank");
  if (!(((getElementTypeOrSelf((*this->getODSOperands(0).begin()))) == (getElementTypeOrSelf((*this->getODSResults(0).begin()))) && (getElementTypeOrSelf((*this->getODSResults(0).begin()))) == (getElementTypeOrSelf((*this->getODSOperands(0).begin()))))))
    return emitOpError("failed to verify that all of {input, result} have same element type");
  return ::mlir::success();
}

::llvm::LogicalResult GatherOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult GatherOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::mlir::IntegerAttr gather_axisAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> root_dynamicOperands;
  ::llvm::SMLoc root_dynamicOperandsLoc;
  (void)root_dynamicOperandsLoc;
  ::mlir::DenseI64ArrayAttr rootAttr;
  ::llvm::ArrayRef<::mlir::Type> allOperandTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<GatherOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<GatherOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (parser.parseKeyword("gather_axis"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gather_axisAttr, parser.getBuilder().getIndexType())) {
    return ::mlir::failure();
  }
  if (gather_axisAttr) result.getOrAddProperties<GatherOp::Properties>().gather_axis = gather_axisAttr;
  if (parser.parseKeyword("root"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    root_dynamicOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, root_dynamicOperands, rootAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<GatherOp::Properties>().root = rootAttr;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType allOperand__allResult_functionType;
  if (parser.parseType(allOperand__allResult_functionType))
    return ::mlir::failure();
  allOperandTypes = allOperand__allResult_functionType.getInputs();
  allResultTypes = allOperand__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(::llvm::concat<const ::mlir::OpAsmParser::UnresolvedOperand>(inputOperands, root_dynamicOperands), allOperandTypes, parser.getNameLoc(), result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void GatherOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  _odsPrinter << ' ' << "gather_axis";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGatherAxisAttr());
  _odsPrinter << ' ' << "root";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  printDynamicIndexList(_odsPrinter, *this, getRootDynamic(), getRootAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("gather_axis");
  elidedAttrs.push_back("root");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperation()->getOperandTypes(), getOperation()->getResultTypes());
}

void GatherOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::GatherOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::GetShardingOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GetShardingOpGenericAdaptorBase::GetShardingOpGenericAdaptorBase(GetShardingOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
GetShardingOpAdaptor::GetShardingOpAdaptor(GetShardingOp op) : GetShardingOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GetShardingOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult GetShardingOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute GetShardingOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GetShardingOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> GetShardingOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void GetShardingOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void GetShardingOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult GetShardingOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void GetShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source) {
  odsState.addOperands(source);
  odsState.addTypes(result);
}

GetShardingOp GetShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(source)>(source));
  auto __res__ = ::llvm::dyn_cast<GetShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetShardingOp GetShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(source)>(source));
}

void GetShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source) {
  odsState.addOperands(source);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(GetShardingOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

GetShardingOp GetShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(source)>(source));
  auto __res__ = ::llvm::dyn_cast<GetShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetShardingOp GetShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source) {
  return create(builder, builder.getLoc(), std::forward<decltype(source)>(source));
}

void GetShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source) {
  odsState.addOperands(source);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GetShardingOp GetShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source));
  auto __res__ = ::llvm::dyn_cast<GetShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetShardingOp GetShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source));
}

void GetShardingOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GetShardingOp GetShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GetShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetShardingOp GetShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GetShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(GetShardingOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

GetShardingOp GetShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GetShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetShardingOp GetShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GetShardingOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GetShardingOp GetShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GetShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetShardingOp GetShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void GetShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(GetShardingOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

GetShardingOp GetShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GetShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetShardingOp GetShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GetShardingOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult GetShardingOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult GetShardingOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<::mlir::shard::ShardingType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult GetShardingOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand sourceRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> sourceOperands(&sourceRawOperand, 1);  ::llvm::SMLoc sourceOperandsLoc;
  (void)sourceOperandsLoc;
  ::mlir::Type sourceRawType{};
  ::llvm::ArrayRef<::mlir::Type> sourceTypes(&sourceRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  sourceOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(sourceRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::RankedTensorType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    sourceRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::shard::ShardingType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(sourceOperands, sourceTypes, sourceOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void GetShardingOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getSource();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getSource().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::RankedTensorType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::shard::ShardingType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void GetShardingOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::GetShardingOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::GridOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GridOpGenericAdaptorBase::GridOpGenericAdaptorBase(GridOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef GridOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int64_t> GridOpGenericAdaptorBase::getShape() {
  auto attr = getShapeAttr();
  return attr;
}


} // namespace detail
GridOpAdaptor::GridOpAdaptor(GridOp op) : GridOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GridOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_shape = getProperties().shape; (void)tblgen_shape;
  if (!tblgen_shape) return emitError(loc, "'shard.grid' op requires attribute 'shape'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'shard.grid' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'shard.grid' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_shape && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_shape))))
    return emitError(loc, "'shard.grid' op attribute 'shape' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult GridOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.shape;
       auto attr = dict.get("shape");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `shape` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sym_name;
       auto attr = dict.get("sym_name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute GridOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.shape;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("shape",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GridOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.shape.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> GridOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "shape")
      return prop.shape;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void GridOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "shape") {
       prop.shape = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.shape)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void GridOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.shape) attrs.append("shape", prop.shape);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult GridOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getShapeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "shape", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps6(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult GridOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.shape)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void GridOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.shape);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef GridOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int64_t> GridOp::getShape() {
  auto attr = getShapeAttr();
  return attr;
}

void GridOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void GridOp::setShape(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().shape = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void GridOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().shape = shape;
}

GridOp GridOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(shape)>(shape));
  auto __res__ = ::llvm::dyn_cast<GridOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridOp GridOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(shape)>(shape));
}

void GridOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().shape = shape;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GridOp GridOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(shape)>(shape));
  auto __res__ = ::llvm::dyn_cast<GridOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridOp GridOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(shape)>(shape));
}

void GridOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().shape = odsBuilder.getDenseI64ArrayAttr(shape);
}

GridOp GridOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(shape)>(shape));
  auto __res__ = ::llvm::dyn_cast<GridOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridOp GridOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(shape)>(shape));
}

void GridOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().shape = odsBuilder.getDenseI64ArrayAttr(shape);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GridOp GridOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(shape)>(shape));
  auto __res__ = ::llvm::dyn_cast<GridOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridOp GridOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(shape)>(shape));
}

void GridOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<GridOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

GridOp GridOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GridOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridOp GridOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GridOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GridOp GridOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GridOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridOp GridOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GridOp::verifyInvariantsImpl() {
  auto tblgen_shape = getProperties().shape; (void)tblgen_shape;
  if (!tblgen_shape) return emitOpError("requires attribute 'shape'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps6(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_shape, "shape")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult GridOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult GridOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::DenseI64ArrayAttr shapeAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<GridOp::Properties>().sym_name = sym_nameAttr;
  if (parser.parseLParen())
    return ::mlir::failure();
  if (parser.parseKeyword("shape"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    auto odsResult = parseDimensionList(parser, shapeAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<GridOp::Properties>().shape = shapeAttr;
  }
  if (parser.parseRParen())
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void GridOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << "(";
  _odsPrinter << "shape";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  printDimensionList(_odsPrinter, *this, getShapeAttr());
  _odsPrinter << ")";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("shape");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void GridOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::GridOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::GridShapeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GridShapeOpGenericAdaptorBase::GridShapeOpGenericAdaptorBase(GridShapeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef GridShapeOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr GridShapeOpGenericAdaptorBase::getAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().axes);
  return attr;
}

::llvm::ArrayRef<int16_t> GridShapeOpGenericAdaptorBase::getAxes() {
  auto attr = getAxesAttr();
  return attr;
}


} // namespace detail
GridShapeOpAdaptor::GridShapeOpAdaptor(GridShapeOp op) : GridShapeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GridShapeOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_axes = getProperties().axes; (void)tblgen_axes;
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.grid_shape' op requires attribute 'grid'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.grid_shape' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_axes))))
    return emitError(loc, "'shard.grid_shape' op attribute 'axes' failed to satisfy constraint: i16 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> GridShapeOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::LogicalResult GridShapeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.axes;
       auto attr = dict.get("axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute GridShapeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GridShapeOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> GridShapeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "axes")
      return prop.axes;

    if (name == "grid")
      return prop.grid;
  return std::nullopt;
}

void GridShapeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "axes") {
       prop.axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.axes)>>(value);
       return;
    }

    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }
}

void GridShapeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.axes) attrs.append("axes", prop.axes);

    if (prop.grid) attrs.append("grid", prop.grid);
}

::llvm::LogicalResult GridShapeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult GridShapeOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();
  return ::mlir::success();
}

void GridShapeOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.axes);
  writer.writeAttribute(prop.grid);
}

::llvm::StringRef GridShapeOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> GridShapeOp::getAxes() {
  auto attr = getAxesAttr();
  return attr;
}

void GridShapeOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void GridShapeOp::setAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

GridShapeOp GridShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::shard::GridOp grid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid));
  auto __res__ = ::llvm::dyn_cast<GridShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridShapeOp GridShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::shard::GridOp grid) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid));
}

GridShapeOp GridShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::shard::GridOp grid, ArrayRef<GridAxis> axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
  auto __res__ = ::llvm::dyn_cast<GridShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridShapeOp GridShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::shard::GridOp grid, ArrayRef<GridAxis> axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
}

GridShapeOp GridShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef grid, ArrayRef<GridAxis> axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
  auto __res__ = ::llvm::dyn_cast<GridShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridShapeOp GridShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef grid, ArrayRef<GridAxis> axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
}

void GridShapeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes) {
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (axes) {
    odsState.getOrAddProperties<Properties>().axes = axes;
  }
  odsState.addTypes(result);
}

GridShapeOp GridShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
  auto __res__ = ::llvm::dyn_cast<GridShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridShapeOp GridShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
}

void GridShapeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes) {
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().axes = odsBuilder.getDenseI16ArrayAttr(axes);
  odsState.addTypes(result);
}

GridShapeOp GridShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
  auto __res__ = ::llvm::dyn_cast<GridShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridShapeOp GridShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
}

void GridShapeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<GridShapeOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

GridShapeOp GridShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GridShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridShapeOp GridShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GridShapeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

GridShapeOp GridShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GridShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GridShapeOp GridShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void GridShapeOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.axes)
    properties.axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult GridShapeOp::verifyInvariantsImpl() {
  auto tblgen_axes = getProperties().axes; (void)tblgen_axes;
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_axes, "axes")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult GridShapeOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult GridShapeOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr axesAttr;
  ::llvm::SmallVector<::mlir::Type, 1> resultTypes;

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<GridShapeOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (axesAttr) result.getOrAddProperties<GridShapeOp::Properties>().axes = axesAttr;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(resultTypes))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  return ::mlir::success();
}

void GridShapeOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getAxesAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("axes");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("axes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getResult().getTypes();
}

void GridShapeOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::GridShapeOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::NeighborsLinearIndicesOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

NeighborsLinearIndicesOpGenericAdaptorBase::NeighborsLinearIndicesOpGenericAdaptorBase(NeighborsLinearIndicesOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> NeighborsLinearIndicesOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef NeighborsLinearIndicesOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> NeighborsLinearIndicesOpGenericAdaptorBase::getSplitAxes() {
  auto attr = getSplitAxesAttr();
  return attr;
}


} // namespace detail
NeighborsLinearIndicesOpAdaptor::NeighborsLinearIndicesOpAdaptor(NeighborsLinearIndicesOp op) : NeighborsLinearIndicesOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult NeighborsLinearIndicesOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.neighbors_linear_indices' op requires attribute 'grid'");
  auto tblgen_split_axes = getProperties().split_axes; (void)tblgen_split_axes;
  if (!tblgen_split_axes) return emitError(loc, "'shard.neighbors_linear_indices' op requires attribute 'split_axes'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.neighbors_linear_indices' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_split_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_split_axes))))
    return emitError(loc, "'shard.neighbors_linear_indices' op attribute 'split_axes' failed to satisfy constraint: i16 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> NeighborsLinearIndicesOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange NeighborsLinearIndicesOp::getDeviceMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult NeighborsLinearIndicesOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.split_axes;
       auto attr = dict.get("split_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `split_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute NeighborsLinearIndicesOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.split_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("split_axes",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code NeighborsLinearIndicesOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.split_axes.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> NeighborsLinearIndicesOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "split_axes")
      return prop.split_axes;
  return std::nullopt;
}

void NeighborsLinearIndicesOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "split_axes") {
       prop.split_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.split_axes)>>(value);
       return;
    }
}

void NeighborsLinearIndicesOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.split_axes) attrs.append("split_axes", prop.split_axes);
}

::llvm::LogicalResult NeighborsLinearIndicesOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSplitAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "split_axes", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult NeighborsLinearIndicesOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.split_axes)))
    return ::mlir::failure();
  return ::mlir::success();
}

void NeighborsLinearIndicesOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);
  writer.writeAttribute(prop.split_axes);
}

::llvm::StringRef NeighborsLinearIndicesOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> NeighborsLinearIndicesOp::getSplitAxes() {
  auto attr = getSplitAxesAttr();
  return attr;
}

void NeighborsLinearIndicesOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void NeighborsLinearIndicesOp::setSplitAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().split_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void NeighborsLinearIndicesOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes) {
  odsState.addOperands(device);
  odsState.getOrAddProperties<Properties>().grid = grid;
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  odsState.addTypes(neighbor_down);
  odsState.addTypes(neighbor_up);
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(neighbor_down)>(neighbor_down), std::forward<decltype(neighbor_up)>(neighbor_up), std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
  auto __res__ = ::llvm::dyn_cast<NeighborsLinearIndicesOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(neighbor_down)>(neighbor_down), std::forward<decltype(neighbor_up)>(neighbor_up), std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
}

void NeighborsLinearIndicesOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes) {
  odsState.addOperands(device);
  odsState.getOrAddProperties<Properties>().grid = grid;
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(NeighborsLinearIndicesOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
  auto __res__ = ::llvm::dyn_cast<NeighborsLinearIndicesOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
}

void NeighborsLinearIndicesOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes) {
  odsState.addOperands(device);
  odsState.getOrAddProperties<Properties>().grid = grid;
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
  auto __res__ = ::llvm::dyn_cast<NeighborsLinearIndicesOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
}

void NeighborsLinearIndicesOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes) {
  odsState.addOperands(device);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().split_axes = odsBuilder.getDenseI16ArrayAttr(split_axes);
  odsState.addTypes(neighbor_down);
  odsState.addTypes(neighbor_up);
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(neighbor_down)>(neighbor_down), std::forward<decltype(neighbor_up)>(neighbor_up), std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
  auto __res__ = ::llvm::dyn_cast<NeighborsLinearIndicesOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(neighbor_down)>(neighbor_down), std::forward<decltype(neighbor_up)>(neighbor_up), std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
}

void NeighborsLinearIndicesOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes) {
  odsState.addOperands(device);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().split_axes = odsBuilder.getDenseI16ArrayAttr(split_axes);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(NeighborsLinearIndicesOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
  auto __res__ = ::llvm::dyn_cast<NeighborsLinearIndicesOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
}

void NeighborsLinearIndicesOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes) {
  odsState.addOperands(device);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().split_axes = odsBuilder.getDenseI16ArrayAttr(split_axes);
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
  auto __res__ = ::llvm::dyn_cast<NeighborsLinearIndicesOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(device)>(device), std::forward<decltype(split_axes)>(split_axes));
}

void NeighborsLinearIndicesOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<NeighborsLinearIndicesOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<NeighborsLinearIndicesOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void NeighborsLinearIndicesOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<NeighborsLinearIndicesOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(NeighborsLinearIndicesOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 2u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<NeighborsLinearIndicesOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void NeighborsLinearIndicesOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<NeighborsLinearIndicesOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void NeighborsLinearIndicesOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(NeighborsLinearIndicesOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 2u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<NeighborsLinearIndicesOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeighborsLinearIndicesOp NeighborsLinearIndicesOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult NeighborsLinearIndicesOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_split_axes = getProperties().split_axes; (void)tblgen_split_axes;
  if (!tblgen_split_axes) return emitOpError("requires attribute 'split_axes'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_split_axes, "split_axes")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult NeighborsLinearIndicesOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult NeighborsLinearIndicesOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(2);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getIndexType();
  ::mlir::Type odsInferredType1 = odsBuilder.getIndexType();
  inferredReturnTypes[0] = odsInferredType0;
  inferredReturnTypes[1] = odsInferredType1;
  return ::mlir::success();
}

::mlir::ParseResult NeighborsLinearIndicesOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> deviceOperands;
  ::llvm::SMLoc deviceOperandsLoc;
  (void)deviceOperandsLoc;
  ::mlir::DenseI16ArrayAttr split_axesAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<NeighborsLinearIndicesOp::Properties>().grid = gridAttr;
  if (parser.parseLSquare())
    return ::mlir::failure();

  deviceOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(deviceOperands))
    return ::mlir::failure();
  if (parser.parseRSquare())
    return ::mlir::failure();
  if (parser.parseKeyword("split_axes"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(split_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (split_axesAttr) result.getOrAddProperties<NeighborsLinearIndicesOp::Properties>().split_axes = split_axesAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIndexType();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(deviceOperands, odsBuildableType0, deviceOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void NeighborsLinearIndicesOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  _odsPrinter << "[";
  _odsPrinter << getDevice();
  _odsPrinter << "]";
  _odsPrinter << ' ' << "split_axes";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getSplitAxesAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("split_axes");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}

void NeighborsLinearIndicesOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::NeighborsLinearIndicesOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ProcessLinearIndexOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ProcessLinearIndexOpGenericAdaptorBase::ProcessLinearIndexOpGenericAdaptorBase(ProcessLinearIndexOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ProcessLinearIndexOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}


} // namespace detail
ProcessLinearIndexOpAdaptor::ProcessLinearIndexOpAdaptor(ProcessLinearIndexOp op) : ProcessLinearIndexOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ProcessLinearIndexOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.process_linear_index' op requires attribute 'grid'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.process_linear_index' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ProcessLinearIndexOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ProcessLinearIndexOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ProcessLinearIndexOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ProcessLinearIndexOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;
  return std::nullopt;
}

void ProcessLinearIndexOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }
}

void ProcessLinearIndexOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);
}

::llvm::LogicalResult ProcessLinearIndexOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ProcessLinearIndexOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ProcessLinearIndexOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);
}

::llvm::StringRef ProcessLinearIndexOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

void ProcessLinearIndexOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::shard::GridOp grid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::shard::GridOp grid) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid));
}

void ProcessLinearIndexOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid) {
  odsState.getOrAddProperties<Properties>().grid = grid;
  odsState.addTypes(result);
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid));
}

void ProcessLinearIndexOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr grid) {
  odsState.getOrAddProperties<Properties>().grid = grid;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ProcessLinearIndexOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr grid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr grid) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid));
}

void ProcessLinearIndexOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid) {
  odsState.getOrAddProperties<Properties>().grid = grid;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid));
}

void ProcessLinearIndexOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid) {
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.addTypes(result);
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid));
}

void ProcessLinearIndexOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef grid) {
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ProcessLinearIndexOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef grid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef grid) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid));
}

void ProcessLinearIndexOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid) {
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid));
}

void ProcessLinearIndexOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ProcessLinearIndexOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ProcessLinearIndexOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ProcessLinearIndexOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ProcessLinearIndexOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ProcessLinearIndexOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ProcessLinearIndexOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ProcessLinearIndexOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ProcessLinearIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessLinearIndexOp ProcessLinearIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ProcessLinearIndexOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ProcessLinearIndexOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ProcessLinearIndexOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getIndexType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ProcessLinearIndexOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<ProcessLinearIndexOp::Properties>().grid = gridAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::IndexType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  return ::mlir::success();
}

void ProcessLinearIndexOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::IndexType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void ProcessLinearIndexOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ProcessLinearIndexOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ProcessMultiIndexOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ProcessMultiIndexOpGenericAdaptorBase::ProcessMultiIndexOpGenericAdaptorBase(ProcessMultiIndexOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ProcessMultiIndexOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr ProcessMultiIndexOpGenericAdaptorBase::getAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().axes);
  return attr;
}

::llvm::ArrayRef<int16_t> ProcessMultiIndexOpGenericAdaptorBase::getAxes() {
  auto attr = getAxesAttr();
  return attr;
}


} // namespace detail
ProcessMultiIndexOpAdaptor::ProcessMultiIndexOpAdaptor(ProcessMultiIndexOp op) : ProcessMultiIndexOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ProcessMultiIndexOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_axes = getProperties().axes; (void)tblgen_axes;
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.process_multi_index' op requires attribute 'grid'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.process_multi_index' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_axes))))
    return emitError(loc, "'shard.process_multi_index' op attribute 'axes' failed to satisfy constraint: i16 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ProcessMultiIndexOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::LogicalResult ProcessMultiIndexOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.axes;
       auto attr = dict.get("axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ProcessMultiIndexOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ProcessMultiIndexOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ProcessMultiIndexOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "axes")
      return prop.axes;

    if (name == "grid")
      return prop.grid;
  return std::nullopt;
}

void ProcessMultiIndexOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "axes") {
       prop.axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.axes)>>(value);
       return;
    }

    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }
}

void ProcessMultiIndexOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.axes) attrs.append("axes", prop.axes);

    if (prop.grid) attrs.append("grid", prop.grid);
}

::llvm::LogicalResult ProcessMultiIndexOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ProcessMultiIndexOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ProcessMultiIndexOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.axes);
  writer.writeAttribute(prop.grid);
}

::llvm::StringRef ProcessMultiIndexOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> ProcessMultiIndexOp::getAxes() {
  auto attr = getAxesAttr();
  return attr;
}

void ProcessMultiIndexOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ProcessMultiIndexOp::setAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::shard::GridOp grid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid));
  auto __res__ = ::llvm::dyn_cast<ProcessMultiIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::shard::GridOp grid) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid));
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef grid, ArrayRef<GridAxis> axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
  auto __res__ = ::llvm::dyn_cast<ProcessMultiIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef grid, ArrayRef<GridAxis> axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
}

void ProcessMultiIndexOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes) {
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (axes) {
    odsState.getOrAddProperties<Properties>().axes = axes;
  }
  odsState.addTypes(result);
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
  auto __res__ = ::llvm::dyn_cast<ProcessMultiIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
}

void ProcessMultiIndexOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes) {
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().axes = odsBuilder.getDenseI16ArrayAttr(axes);
  odsState.addTypes(result);
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
  auto __res__ = ::llvm::dyn_cast<ProcessMultiIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(axes)>(axes));
}

void ProcessMultiIndexOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ProcessMultiIndexOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ProcessMultiIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ProcessMultiIndexOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ProcessMultiIndexOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProcessMultiIndexOp ProcessMultiIndexOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ProcessMultiIndexOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.axes)
    properties.axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult ProcessMultiIndexOp::verifyInvariantsImpl() {
  auto tblgen_axes = getProperties().axes; (void)tblgen_axes;
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_axes, "axes")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ProcessMultiIndexOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ProcessMultiIndexOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr axesAttr;
  ::llvm::SmallVector<::mlir::Type, 1> resultTypes;
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<ProcessMultiIndexOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (axesAttr) result.getOrAddProperties<ProcessMultiIndexOp::Properties>().axes = axesAttr;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(resultTypes))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  return ::mlir::success();
}

void ProcessMultiIndexOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getAxesAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("axes");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("axes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getResult().getTypes();
}

void ProcessMultiIndexOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ProcessMultiIndexOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::RecvOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RecvOpGenericAdaptorBase::RecvOpGenericAdaptorBase(RecvOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> RecvOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef RecvOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr RecvOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> RecvOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::std::optional<::llvm::ArrayRef<int64_t>> RecvOpGenericAdaptorBase::getSource() {
  auto attr = getSourceAttr();
  return attr ? ::std::optional<::llvm::ArrayRef<int64_t>>(attr) : (::std::nullopt);
}


} // namespace detail
RecvOpAdaptor::RecvOpAdaptor(RecvOp op) : RecvOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RecvOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.recv' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_source = getProperties().source; (void)tblgen_source;

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.recv' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.recv' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_source && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_source))))
    return emitError(loc, "'shard.recv' op attribute 'source' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> RecvOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange RecvOp::getSourceDynamicMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult RecvOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.source;
       auto attr = dict.get("source");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `source` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute RecvOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.source;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("source",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code RecvOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.source.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> RecvOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;

    if (name == "source")
      return prop.source;
  return std::nullopt;
}

void RecvOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }

    if (name == "source") {
       prop.source = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.source)>>(value);
       return;
    }
}

void RecvOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);

    if (prop.source) attrs.append("source", prop.source);
}

::llvm::LogicalResult RecvOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSourceAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "source", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult RecvOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.source)))
    return ::mlir::failure();
  return ::mlir::success();
}

void RecvOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);

  writer.writeOptionalAttribute(prop.source);
}

::llvm::StringRef RecvOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> RecvOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::std::optional<::llvm::ArrayRef<int64_t>> RecvOp::getSource() {
  auto attr = getSourceAttr();
  return attr ? ::std::optional<::llvm::ArrayRef<int64_t>>(attr) : (::std::nullopt);
}

void RecvOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void RecvOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void RecvOp::setSource(::std::optional<::llvm::ArrayRef<int64_t>> attrValue) {
    auto &odsProp = getProperties().source;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(*attrValue);
    else
      odsProp = nullptr;
}

void RecvOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(source_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  if (source) {
    odsState.getOrAddProperties<Properties>().source = source;
  }
  odsState.addTypes(result);
}

RecvOp RecvOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(source)>(source), std::forward<decltype(source_dynamic)>(source_dynamic));
  auto __res__ = ::llvm::dyn_cast<RecvOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RecvOp RecvOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(source)>(source), std::forward<decltype(source_dynamic)>(source_dynamic));
}

void RecvOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(source_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  if (source) {
    odsState.getOrAddProperties<Properties>().source = source;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

RecvOp RecvOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(source)>(source), std::forward<decltype(source_dynamic)>(source_dynamic));
  auto __res__ = ::llvm::dyn_cast<RecvOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RecvOp RecvOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(source)>(source), std::forward<decltype(source_dynamic)>(source_dynamic));
}

void RecvOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(source_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  if (source) {
    odsState.getOrAddProperties<Properties>().source = source;
  }
  odsState.addTypes(result);
}

RecvOp RecvOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(source)>(source), std::forward<decltype(source_dynamic)>(source_dynamic));
  auto __res__ = ::llvm::dyn_cast<RecvOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RecvOp RecvOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(source)>(source), std::forward<decltype(source_dynamic)>(source_dynamic));
}

void RecvOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(source_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  if (source) {
    odsState.getOrAddProperties<Properties>().source = source;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

RecvOp RecvOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(source)>(source), std::forward<decltype(source_dynamic)>(source_dynamic));
  auto __res__ = ::llvm::dyn_cast<RecvOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RecvOp RecvOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(source)>(source), std::forward<decltype(source_dynamic)>(source_dynamic));
}

void RecvOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<RecvOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

RecvOp RecvOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<RecvOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RecvOp RecvOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void RecvOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

RecvOp RecvOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<RecvOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RecvOp RecvOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void RecvOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult RecvOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_source = getProperties().source; (void)tblgen_source;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_source, "source")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!(((::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getShape()) && (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()))))
    return emitOpError("failed to verify that all of {input, result} have same shape");
  if (!(((getElementTypeOrSelf((*this->getODSOperands(0).begin()))) == (getElementTypeOrSelf((*this->getODSResults(0).begin()))) && (getElementTypeOrSelf((*this->getODSResults(0).begin()))) == (getElementTypeOrSelf((*this->getODSOperands(0).begin()))))))
    return emitOpError("failed to verify that all of {input, result} have same element type");
  return ::mlir::success();
}

::llvm::LogicalResult RecvOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RecvOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> source_dynamicOperands;
  ::llvm::SMLoc source_dynamicOperandsLoc;
  (void)source_dynamicOperandsLoc;
  ::mlir::DenseI64ArrayAttr sourceAttr;
  ::llvm::ArrayRef<::mlir::Type> allOperandTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<RecvOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<RecvOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("source"))) {
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    source_dynamicOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, source_dynamicOperands, sourceAttr);
    if (odsResult) return ::mlir::failure();
    if (sourceAttr)
      result.getOrAddProperties<RecvOp::Properties>().source = sourceAttr;
  }
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType allOperand__allResult_functionType;
  if (parser.parseType(allOperand__allResult_functionType))
    return ::mlir::failure();
  allOperandTypes = allOperand__allResult_functionType.getInputs();
  allResultTypes = allOperand__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(::llvm::concat<const ::mlir::OpAsmParser::UnresolvedOperand>(inputOperands, source_dynamicOperands), allOperandTypes, parser.getNameLoc(), result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void RecvOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  if (((!getSourceDynamic().empty()) || (getSourceAttr()))) {
    _odsPrinter << ' ' << "source";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
    printDynamicIndexList(_odsPrinter, *this, getSourceDynamic(), getSourceAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("source");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperation()->getOperandTypes(), getOperation()->getResultTypes());
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::RecvOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ReduceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ReduceOpGenericAdaptorBase::ReduceOpGenericAdaptorBase(ReduceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ReduceOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef ReduceOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr ReduceOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> ReduceOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::mlir::shard::ReductionKindAttr ReduceOpGenericAdaptorBase::getReductionAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::shard::ReductionKindAttr>(getProperties().reduction);
  return attr;
}

::mlir::shard::ReductionKind ReduceOpGenericAdaptorBase::getReduction() {
  auto attr = getReductionAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int64_t> ReduceOpGenericAdaptorBase::getRoot() {
  auto attr = getRootAttr();
  return attr;
}


} // namespace detail
ReduceOpAdaptor::ReduceOpAdaptor(ReduceOp op) : ReduceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ReduceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.reduce' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_reduction = getProperties().reduction; (void)tblgen_reduction;
  auto tblgen_root = getProperties().root; (void)tblgen_root;
  if (!tblgen_root) return emitError(loc, "'shard.reduce' op requires attribute 'root'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.reduce' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.reduce' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_reduction && !((::llvm::isa<::mlir::shard::ReductionKindAttr>(tblgen_reduction))))
    return emitError(loc, "'shard.reduce' op attribute 'reduction' failed to satisfy constraint: Reduction of an iterator/grid dimension.");

  if (tblgen_root && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_root))))
    return emitError(loc, "'shard.reduce' op attribute 'root' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ReduceOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange ReduceOp::getRootDynamicMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ReduceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.reduction;
       auto attr = dict.get("reduction");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `reduction` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.root;
       auto attr = dict.get("root");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `root` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ReduceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.reduction;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("reduction",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.root;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("root",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ReduceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.reduction.getAsOpaquePointer()), 
    llvm::hash_value(prop.root.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ReduceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;

    if (name == "reduction")
      return prop.reduction;

    if (name == "root")
      return prop.root;
  return std::nullopt;
}

void ReduceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }

    if (name == "reduction") {
       prop.reduction = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.reduction)>>(value);
       return;
    }

    if (name == "root") {
       prop.root = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.root)>>(value);
       return;
    }
}

void ReduceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);

    if (prop.reduction) attrs.append("reduction", prop.reduction);

    if (prop.root) attrs.append("root", prop.root);
}

::llvm::LogicalResult ReduceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getReductionAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps4(attr, "reduction", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRootAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "root", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ReduceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.reduction)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.root)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ReduceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);

  writer.writeOptionalAttribute(prop.reduction);
  writer.writeAttribute(prop.root);
}

::llvm::StringRef ReduceOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> ReduceOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::mlir::shard::ReductionKind ReduceOp::getReduction() {
  auto attr = getReductionAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int64_t> ReduceOp::getRoot() {
  auto attr = getRootAttr();
  return attr;
}

void ReduceOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ReduceOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void ReduceOp::setReduction(::mlir::shard::ReductionKind attrValue) {
  getProperties().reduction = ::mlir::shard::ReductionKindAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ReduceOp::setRoot(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().root = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void ReduceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  if (reduction) {
    odsState.getOrAddProperties<Properties>().reduction = reduction;
  }
  odsState.getOrAddProperties<Properties>().root = root;
  odsState.addTypes(result);
}

ReduceOp ReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<ReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceOp ReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void ReduceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  if (reduction) {
    odsState.getOrAddProperties<Properties>().reduction = reduction;
  }
  odsState.getOrAddProperties<Properties>().root = root;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ReduceOp ReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<ReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceOp ReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void ReduceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().reduction = ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), reduction);
  odsState.getOrAddProperties<Properties>().root = odsBuilder.getDenseI64ArrayAttr(root);
  odsState.addTypes(result);
}

ReduceOp ReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<ReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceOp ReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void ReduceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().reduction = ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), reduction);
  odsState.getOrAddProperties<Properties>().root = odsBuilder.getDenseI64ArrayAttr(root);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ReduceOp ReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<ReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceOp ReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void ReduceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ReduceOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ReduceOp ReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceOp ReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ReduceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ReduceOp ReduceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ReduceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceOp ReduceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ReduceOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
  if (!properties.reduction)
    properties.reduction = ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), ::mlir::shard::ReductionKind::Sum);
}

::llvm::LogicalResult ReduceOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_reduction = getProperties().reduction; (void)tblgen_reduction;
  auto tblgen_root = getProperties().root; (void)tblgen_root;
  if (!tblgen_root) return emitOpError("requires attribute 'root'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps4(*this, tblgen_reduction, "reduction")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_root, "root")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!(((::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getShape()) && (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()))))
    return emitOpError("failed to verify that all of {input, result} have same shape");
  return ::mlir::success();
}

::llvm::LogicalResult ReduceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ReduceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::mlir::shard::ReductionKindAttr reductionAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> root_dynamicOperands;
  ::llvm::SMLoc root_dynamicOperandsLoc;
  (void)root_dynamicOperandsLoc;
  ::mlir::DenseI64ArrayAttr rootAttr;
  ::llvm::ArrayRef<::mlir::Type> allOperandTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<ReduceOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<ReduceOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("reduction"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(reductionAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (reductionAttr) result.getOrAddProperties<ReduceOp::Properties>().reduction = reductionAttr;
  }
  if (parser.parseKeyword("root"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    root_dynamicOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, root_dynamicOperands, rootAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<ReduceOp::Properties>().root = rootAttr;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType allOperand__allResult_functionType;
  if (parser.parseType(allOperand__allResult_functionType))
    return ::mlir::failure();
  allOperandTypes = allOperand__allResult_functionType.getInputs();
  allResultTypes = allOperand__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(::llvm::concat<const ::mlir::OpAsmParser::UnresolvedOperand>(inputOperands, root_dynamicOperands), allOperandTypes, parser.getNameLoc(), result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ReduceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  if (getReductionAttr() != ::mlir::shard::ReductionKindAttr::get(::mlir::OpBuilder((*this)->getContext()).getContext(), ::mlir::shard::ReductionKind::Sum)) {
    _odsPrinter << ' ' << "reduction";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getReductionAttr());
  }
  _odsPrinter << ' ' << "root";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  printDynamicIndexList(_odsPrinter, *this, getRootDynamic(), getRootAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("reduction");
  elidedAttrs.push_back("root");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getReductionAttr();
     if(attr && (attr == ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), ::mlir::shard::ReductionKind::Sum)))
       elidedAttrs.push_back("reduction");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperation()->getOperandTypes(), getOperation()->getResultTypes());
}

void ReduceOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ReduceOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ReduceScatterOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ReduceScatterOpGenericAdaptorBase::ReduceScatterOpGenericAdaptorBase(ReduceScatterOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ReduceScatterOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr ReduceScatterOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> ReduceScatterOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::mlir::shard::ReductionKindAttr ReduceScatterOpGenericAdaptorBase::getReductionAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::shard::ReductionKindAttr>(getProperties().reduction);
  return attr;
}

::mlir::shard::ReductionKind ReduceScatterOpGenericAdaptorBase::getReduction() {
  auto attr = getReductionAttr();
  return attr.getValue();
}

::llvm::APInt ReduceScatterOpGenericAdaptorBase::getScatterAxis() {
  auto attr = getScatterAxisAttr();
  return attr.getValue();
}


} // namespace detail
ReduceScatterOpAdaptor::ReduceScatterOpAdaptor(ReduceScatterOp op) : ReduceScatterOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ReduceScatterOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.reduce_scatter' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_reduction = getProperties().reduction; (void)tblgen_reduction;
  auto tblgen_scatter_axis = getProperties().scatter_axis; (void)tblgen_scatter_axis;
  if (!tblgen_scatter_axis) return emitError(loc, "'shard.reduce_scatter' op requires attribute 'scatter_axis'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.reduce_scatter' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.reduce_scatter' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_reduction && !((::llvm::isa<::mlir::shard::ReductionKindAttr>(tblgen_reduction))))
    return emitError(loc, "'shard.reduce_scatter' op attribute 'reduction' failed to satisfy constraint: Reduction of an iterator/grid dimension.");

  if (tblgen_scatter_axis && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_scatter_axis))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(tblgen_scatter_axis).getType())))))
    return emitError(loc, "'shard.reduce_scatter' op attribute 'scatter_axis' failed to satisfy constraint: index attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ReduceScatterOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.reduction;
       auto attr = dict.get("reduction");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `reduction` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.scatter_axis;
       auto attr = dict.get("scatter_axis");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `scatter_axis` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ReduceScatterOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.reduction;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("reduction",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.scatter_axis;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("scatter_axis",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ReduceScatterOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.reduction.getAsOpaquePointer()), 
    llvm::hash_value(prop.scatter_axis.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ReduceScatterOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;

    if (name == "reduction")
      return prop.reduction;

    if (name == "scatter_axis")
      return prop.scatter_axis;
  return std::nullopt;
}

void ReduceScatterOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }

    if (name == "reduction") {
       prop.reduction = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.reduction)>>(value);
       return;
    }

    if (name == "scatter_axis") {
       prop.scatter_axis = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.scatter_axis)>>(value);
       return;
    }
}

void ReduceScatterOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);

    if (prop.reduction) attrs.append("reduction", prop.reduction);

    if (prop.scatter_axis) attrs.append("scatter_axis", prop.scatter_axis);
}

::llvm::LogicalResult ReduceScatterOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getReductionAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps4(attr, "reduction", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getScatterAxisAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(attr, "scatter_axis", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ReduceScatterOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.reduction)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.scatter_axis)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ReduceScatterOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);

  writer.writeOptionalAttribute(prop.reduction);
  writer.writeAttribute(prop.scatter_axis);
}

::llvm::StringRef ReduceScatterOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> ReduceScatterOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::mlir::shard::ReductionKind ReduceScatterOp::getReduction() {
  auto attr = getReductionAttr();
  return attr.getValue();
}

::llvm::APInt ReduceScatterOp::getScatterAxis() {
  auto attr = getScatterAxisAttr();
  return attr.getValue();
}

void ReduceScatterOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ReduceScatterOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void ReduceScatterOp::setReduction(::mlir::shard::ReductionKind attrValue) {
  getProperties().reduction = ::mlir::shard::ReductionKindAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ReduceScatterOp::setScatterAxis(::llvm::APInt attrValue) {
  getProperties().scatter_axis = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIndexType(), attrValue);
}

void ReduceScatterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  if (reduction) {
    odsState.getOrAddProperties<Properties>().reduction = reduction;
  }
  odsState.getOrAddProperties<Properties>().scatter_axis = scatter_axis;
  odsState.addTypes(result);
}

ReduceScatterOp ReduceScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(scatter_axis)>(scatter_axis));
  auto __res__ = ::llvm::dyn_cast<ReduceScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceScatterOp ReduceScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(scatter_axis)>(scatter_axis));
}

void ReduceScatterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  if (reduction) {
    odsState.getOrAddProperties<Properties>().reduction = reduction;
  }
  odsState.getOrAddProperties<Properties>().scatter_axis = scatter_axis;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ReduceScatterOp ReduceScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(scatter_axis)>(scatter_axis));
  auto __res__ = ::llvm::dyn_cast<ReduceScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceScatterOp ReduceScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(scatter_axis)>(scatter_axis));
}

void ReduceScatterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().reduction = ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), reduction);
  odsState.getOrAddProperties<Properties>().scatter_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), scatter_axis);
  odsState.addTypes(result);
}

ReduceScatterOp ReduceScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(scatter_axis)>(scatter_axis));
  auto __res__ = ::llvm::dyn_cast<ReduceScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceScatterOp ReduceScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(scatter_axis)>(scatter_axis));
}

void ReduceScatterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().reduction = ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), reduction);
  odsState.getOrAddProperties<Properties>().scatter_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), scatter_axis);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ReduceScatterOp ReduceScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(scatter_axis)>(scatter_axis));
  auto __res__ = ::llvm::dyn_cast<ReduceScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceScatterOp ReduceScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(reduction)>(reduction), std::forward<decltype(scatter_axis)>(scatter_axis));
}

void ReduceScatterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ReduceScatterOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ReduceScatterOp ReduceScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ReduceScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceScatterOp ReduceScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ReduceScatterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ReduceScatterOp ReduceScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ReduceScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReduceScatterOp ReduceScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ReduceScatterOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
  if (!properties.reduction)
    properties.reduction = ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), ::mlir::shard::ReductionKind::Sum);
}

::llvm::LogicalResult ReduceScatterOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_reduction = getProperties().reduction; (void)tblgen_reduction;
  auto tblgen_scatter_axis = getProperties().scatter_axis; (void)tblgen_scatter_axis;
  if (!tblgen_scatter_axis) return emitOpError("requires attribute 'scatter_axis'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps4(*this, tblgen_reduction, "reduction")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(*this, tblgen_scatter_axis, "scatter_axis")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ReduceScatterOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ReduceScatterOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::mlir::shard::ReductionKindAttr reductionAttr;
  ::mlir::IntegerAttr scatter_axisAttr;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<ReduceScatterOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<ReduceScatterOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("reduction"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(reductionAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (reductionAttr) result.getOrAddProperties<ReduceScatterOp::Properties>().reduction = reductionAttr;
  }
  if (parser.parseKeyword("scatter_axis"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(scatter_axisAttr, parser.getBuilder().getIndexType())) {
    return ::mlir::failure();
  }
  if (scatter_axisAttr) result.getOrAddProperties<ReduceScatterOp::Properties>().scatter_axis = scatter_axisAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::TensorType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::RankedTensorType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ReduceScatterOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  if (getReductionAttr() != ::mlir::shard::ReductionKindAttr::get(::mlir::OpBuilder((*this)->getContext()).getContext(), ::mlir::shard::ReductionKind::Sum)) {
    _odsPrinter << ' ' << "reduction";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getReductionAttr());
  }
  _odsPrinter << ' ' << "scatter_axis";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getScatterAxisAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("reduction");
  elidedAttrs.push_back("scatter_axis");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getReductionAttr();
     if(attr && (attr == ::mlir::shard::ReductionKindAttr::get(odsBuilder.getContext(), ::mlir::shard::ReductionKind::Sum)))
       elidedAttrs.push_back("reduction");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::TensorType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::RankedTensorType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void ReduceScatterOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ReduceScatterOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ScatterOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ScatterOpGenericAdaptorBase::ScatterOpGenericAdaptorBase(ScatterOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ScatterOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef ScatterOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr ScatterOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> ScatterOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt ScatterOpGenericAdaptorBase::getScatterAxis() {
  auto attr = getScatterAxisAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int64_t> ScatterOpGenericAdaptorBase::getRoot() {
  auto attr = getRootAttr();
  return attr;
}


} // namespace detail
ScatterOpAdaptor::ScatterOpAdaptor(ScatterOp op) : ScatterOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ScatterOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.scatter' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_root = getProperties().root; (void)tblgen_root;
  if (!tblgen_root) return emitError(loc, "'shard.scatter' op requires attribute 'root'");
  auto tblgen_scatter_axis = getProperties().scatter_axis; (void)tblgen_scatter_axis;
  if (!tblgen_scatter_axis) return emitError(loc, "'shard.scatter' op requires attribute 'scatter_axis'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.scatter' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.scatter' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_scatter_axis && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_scatter_axis))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(tblgen_scatter_axis).getType())))))
    return emitError(loc, "'shard.scatter' op attribute 'scatter_axis' failed to satisfy constraint: index attribute");

  if (tblgen_root && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_root))))
    return emitError(loc, "'shard.scatter' op attribute 'root' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ScatterOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange ScatterOp::getRootDynamicMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ScatterOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.root;
       auto attr = dict.get("root");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `root` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.scatter_axis;
       auto attr = dict.get("scatter_axis");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `scatter_axis` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ScatterOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.root;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("root",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.scatter_axis;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("scatter_axis",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ScatterOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.root.getAsOpaquePointer()), 
    llvm::hash_value(prop.scatter_axis.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ScatterOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;

    if (name == "root")
      return prop.root;

    if (name == "scatter_axis")
      return prop.scatter_axis;
  return std::nullopt;
}

void ScatterOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }

    if (name == "root") {
       prop.root = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.root)>>(value);
       return;
    }

    if (name == "scatter_axis") {
       prop.scatter_axis = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.scatter_axis)>>(value);
       return;
    }
}

void ScatterOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);

    if (prop.root) attrs.append("root", prop.root);

    if (prop.scatter_axis) attrs.append("scatter_axis", prop.scatter_axis);
}

::llvm::LogicalResult ScatterOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRootAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "root", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getScatterAxisAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(attr, "scatter_axis", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ScatterOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.root)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.scatter_axis)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ScatterOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);
  writer.writeAttribute(prop.root);
  writer.writeAttribute(prop.scatter_axis);
}

::llvm::StringRef ScatterOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> ScatterOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt ScatterOp::getScatterAxis() {
  auto attr = getScatterAxisAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int64_t> ScatterOp::getRoot() {
  auto attr = getRootAttr();
  return attr;
}

void ScatterOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ScatterOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void ScatterOp::setScatterAxis(::llvm::APInt attrValue) {
  getProperties().scatter_axis = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIndexType(), attrValue);
}

void ScatterOp::setRoot(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().root = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void ScatterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().scatter_axis = scatter_axis;
  odsState.getOrAddProperties<Properties>().root = root;
  odsState.addTypes(result);
}

ScatterOp ScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(scatter_axis)>(scatter_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<ScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScatterOp ScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(scatter_axis)>(scatter_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void ScatterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().scatter_axis = scatter_axis;
  odsState.getOrAddProperties<Properties>().root = root;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ScatterOp ScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(scatter_axis)>(scatter_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<ScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScatterOp ScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(scatter_axis)>(scatter_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void ScatterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().scatter_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), scatter_axis);
  odsState.getOrAddProperties<Properties>().root = odsBuilder.getDenseI64ArrayAttr(root);
  odsState.addTypes(result);
}

ScatterOp ScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(scatter_axis)>(scatter_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<ScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScatterOp ScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(scatter_axis)>(scatter_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void ScatterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(root_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().scatter_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), scatter_axis);
  odsState.getOrAddProperties<Properties>().root = odsBuilder.getDenseI64ArrayAttr(root);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ScatterOp ScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(scatter_axis)>(scatter_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
  auto __res__ = ::llvm::dyn_cast<ScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScatterOp ScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(scatter_axis)>(scatter_axis), std::forward<decltype(root)>(root), std::forward<decltype(root_dynamic)>(root_dynamic));
}

void ScatterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ScatterOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ScatterOp ScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScatterOp ScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ScatterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ScatterOp ScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScatterOp ScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ScatterOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult ScatterOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_root = getProperties().root; (void)tblgen_root;
  if (!tblgen_root) return emitOpError("requires attribute 'root'");
  auto tblgen_scatter_axis = getProperties().scatter_axis; (void)tblgen_scatter_axis;
  if (!tblgen_scatter_axis) return emitOpError("requires attribute 'scatter_axis'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(*this, tblgen_scatter_axis, "scatter_axis")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_root, "root")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!(((::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getRank()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getRank()) && (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getRank()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getRank()))))
    return emitOpError("failed to verify that all of {input, result} have same rank");
  if (!(((getElementTypeOrSelf((*this->getODSOperands(0).begin()))) == (getElementTypeOrSelf((*this->getODSResults(0).begin()))) && (getElementTypeOrSelf((*this->getODSResults(0).begin()))) == (getElementTypeOrSelf((*this->getODSOperands(0).begin()))))))
    return emitOpError("failed to verify that all of {input, result} have same element type");
  return ::mlir::success();
}

::llvm::LogicalResult ScatterOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ScatterOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::mlir::IntegerAttr scatter_axisAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> root_dynamicOperands;
  ::llvm::SMLoc root_dynamicOperandsLoc;
  (void)root_dynamicOperandsLoc;
  ::mlir::DenseI64ArrayAttr rootAttr;
  ::llvm::ArrayRef<::mlir::Type> allOperandTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<ScatterOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<ScatterOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (parser.parseKeyword("scatter_axis"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(scatter_axisAttr, parser.getBuilder().getIndexType())) {
    return ::mlir::failure();
  }
  if (scatter_axisAttr) result.getOrAddProperties<ScatterOp::Properties>().scatter_axis = scatter_axisAttr;
  if (parser.parseKeyword("root"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    root_dynamicOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, root_dynamicOperands, rootAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<ScatterOp::Properties>().root = rootAttr;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType allOperand__allResult_functionType;
  if (parser.parseType(allOperand__allResult_functionType))
    return ::mlir::failure();
  allOperandTypes = allOperand__allResult_functionType.getInputs();
  allResultTypes = allOperand__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(::llvm::concat<const ::mlir::OpAsmParser::UnresolvedOperand>(inputOperands, root_dynamicOperands), allOperandTypes, parser.getNameLoc(), result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ScatterOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  _odsPrinter << ' ' << "scatter_axis";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getScatterAxisAttr());
  _odsPrinter << ' ' << "root";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  printDynamicIndexList(_odsPrinter, *this, getRootDynamic(), getRootAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("scatter_axis");
  elidedAttrs.push_back("root");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperation()->getOperandTypes(), getOperation()->getResultTypes());
}

void ScatterOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ScatterOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::SendOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SendOpGenericAdaptorBase::SendOpGenericAdaptorBase(SendOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> SendOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef SendOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr SendOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> SendOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> SendOpGenericAdaptorBase::getDestination() {
  auto attr = getDestinationAttr();
  return attr;
}


} // namespace detail
SendOpAdaptor::SendOpAdaptor(SendOp op) : SendOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SendOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_destination = getProperties().destination; (void)tblgen_destination;
  if (!tblgen_destination) return emitError(loc, "'shard.send' op requires attribute 'destination'");
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.send' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.send' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.send' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_destination && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_destination))))
    return emitError(loc, "'shard.send' op attribute 'destination' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> SendOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange SendOp::getDestinationDynamicMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult SendOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.destination;
       auto attr = dict.get("destination");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `destination` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute SendOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.destination;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("destination",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SendOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.destination.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SendOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "destination")
      return prop.destination;

    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;
  return std::nullopt;
}

void SendOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "destination") {
       prop.destination = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.destination)>>(value);
       return;
    }

    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }
}

void SendOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.destination) attrs.append("destination", prop.destination);

    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);
}

::llvm::LogicalResult SendOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getDestinationAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "destination", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SendOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.destination)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SendOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.destination);
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);
}

::llvm::StringRef SendOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> SendOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> SendOp::getDestination() {
  auto attr = getDestinationAttr();
  return attr;
}

void SendOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void SendOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void SendOp::setDestination(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().destination = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void SendOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(destination_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().destination = destination;
  odsState.addTypes(result);
}

SendOp SendOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(destination)>(destination), std::forward<decltype(destination_dynamic)>(destination_dynamic));
  auto __res__ = ::llvm::dyn_cast<SendOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SendOp SendOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(destination)>(destination), std::forward<decltype(destination_dynamic)>(destination_dynamic));
}

void SendOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(destination_dynamic);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().destination = destination;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SendOp SendOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(destination)>(destination), std::forward<decltype(destination_dynamic)>(destination_dynamic));
  auto __res__ = ::llvm::dyn_cast<SendOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SendOp SendOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(destination)>(destination), std::forward<decltype(destination_dynamic)>(destination_dynamic));
}

void SendOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(destination_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().destination = odsBuilder.getDenseI64ArrayAttr(destination);
  odsState.addTypes(result);
}

SendOp SendOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(destination)>(destination), std::forward<decltype(destination_dynamic)>(destination_dynamic));
  auto __res__ = ::llvm::dyn_cast<SendOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SendOp SendOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(destination)>(destination), std::forward<decltype(destination_dynamic)>(destination_dynamic));
}

void SendOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic) {
  odsState.addOperands(input);
  odsState.addOperands(destination_dynamic);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().destination = odsBuilder.getDenseI64ArrayAttr(destination);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SendOp SendOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(destination)>(destination), std::forward<decltype(destination_dynamic)>(destination_dynamic));
  auto __res__ = ::llvm::dyn_cast<SendOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SendOp SendOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(destination)>(destination), std::forward<decltype(destination_dynamic)>(destination_dynamic));
}

void SendOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<SendOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

SendOp SendOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SendOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SendOp SendOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SendOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SendOp SendOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SendOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SendOp SendOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void SendOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult SendOp::verifyInvariantsImpl() {
  auto tblgen_destination = getProperties().destination; (void)tblgen_destination;
  if (!tblgen_destination) return emitOpError("requires attribute 'destination'");
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_destination, "destination")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!(((::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getShape()) && (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()))))
    return emitOpError("failed to verify that all of {input, result} have same shape");
  if (!(((getElementTypeOrSelf((*this->getODSOperands(0).begin()))) == (getElementTypeOrSelf((*this->getODSResults(0).begin()))) && (getElementTypeOrSelf((*this->getODSResults(0).begin()))) == (getElementTypeOrSelf((*this->getODSOperands(0).begin()))))))
    return emitOpError("failed to verify that all of {input, result} have same element type");
  return ::mlir::success();
}

::llvm::LogicalResult SendOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SendOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> destination_dynamicOperands;
  ::llvm::SMLoc destination_dynamicOperandsLoc;
  (void)destination_dynamicOperandsLoc;
  ::mlir::DenseI64ArrayAttr destinationAttr;
  ::llvm::ArrayRef<::mlir::Type> allOperandTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<SendOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<SendOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (parser.parseKeyword("destination"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    destination_dynamicOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, destination_dynamicOperands, destinationAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<SendOp::Properties>().destination = destinationAttr;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType allOperand__allResult_functionType;
  if (parser.parseType(allOperand__allResult_functionType))
    return ::mlir::failure();
  allOperandTypes = allOperand__allResult_functionType.getInputs();
  allResultTypes = allOperand__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(::llvm::concat<const ::mlir::OpAsmParser::UnresolvedOperand>(inputOperands, destination_dynamicOperands), allOperandTypes, parser.getNameLoc(), result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SendOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  _odsPrinter << ' ' << "destination";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  printDynamicIndexList(_odsPrinter, *this, getDestinationDynamic(), getDestinationAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("destination");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperation()->getOperandTypes(), getOperation()->getResultTypes());
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::SendOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ShardOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ShardOpGenericAdaptorBase::ShardOpGenericAdaptorBase(ShardOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr ShardOpGenericAdaptorBase::getAnnotateForUsersAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().annotate_for_users);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ShardOpGenericAdaptorBase::getAnnotateForUsers() {
  auto attr = getAnnotateForUsersAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
ShardOpAdaptor::ShardOpAdaptor(ShardOp op) : ShardOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ShardOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_annotate_for_users = getProperties().annotate_for_users; (void)tblgen_annotate_for_users;

  if (tblgen_annotate_for_users && !((::llvm::isa<::mlir::UnitAttr>(tblgen_annotate_for_users))))
    return emitError(loc, "'shard.shard' op attribute 'annotate_for_users' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ShardOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.annotate_for_users;
       auto attr = dict.get("annotate_for_users");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `annotate_for_users` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ShardOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.annotate_for_users;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("annotate_for_users",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ShardOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.annotate_for_users.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ShardOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "annotate_for_users")
      return prop.annotate_for_users;
  return std::nullopt;
}

void ShardOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "annotate_for_users") {
       prop.annotate_for_users = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.annotate_for_users)>>(value);
       return;
    }
}

void ShardOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.annotate_for_users) attrs.append("annotate_for_users", prop.annotate_for_users);
}

::llvm::LogicalResult ShardOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAnnotateForUsersAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps7(attr, "annotate_for_users", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ShardOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.annotate_for_users)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShardOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.annotate_for_users);
}

bool ShardOp::getAnnotateForUsers() {
  auto attr = getAnnotateForUsersAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void ShardOp::setAnnotateForUsers(bool attrValue) {
    auto &odsProp = getProperties().annotate_for_users;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ShardOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users) {
  odsState.addOperands(src);
  odsState.addOperands(sharding);
  if (annotate_for_users) {
    odsState.getOrAddProperties<Properties>().annotate_for_users = annotate_for_users;
  }
  odsState.addTypes(result);
}

ShardOp ShardOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
  auto __res__ = ::llvm::dyn_cast<ShardOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardOp ShardOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
}

void ShardOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users) {
  odsState.addOperands(src);
  odsState.addOperands(sharding);
  if (annotate_for_users) {
    odsState.getOrAddProperties<Properties>().annotate_for_users = annotate_for_users;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShardOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShardOp ShardOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
  auto __res__ = ::llvm::dyn_cast<ShardOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardOp ShardOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users) {
  return create(builder, builder.getLoc(), std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
}

void ShardOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users) {
  odsState.addOperands(src);
  odsState.addOperands(sharding);
  if (annotate_for_users) {
    odsState.getOrAddProperties<Properties>().annotate_for_users = annotate_for_users;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShardOp ShardOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
  auto __res__ = ::llvm::dyn_cast<ShardOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardOp ShardOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
}

void ShardOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users) {
  odsState.addOperands(src);
  odsState.addOperands(sharding);
  if (annotate_for_users) {
    odsState.getOrAddProperties<Properties>().annotate_for_users = ((annotate_for_users) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

ShardOp ShardOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
  auto __res__ = ::llvm::dyn_cast<ShardOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardOp ShardOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
}

void ShardOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users) {
  odsState.addOperands(src);
  odsState.addOperands(sharding);
  if (annotate_for_users) {
    odsState.getOrAddProperties<Properties>().annotate_for_users = ((annotate_for_users) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShardOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShardOp ShardOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
  auto __res__ = ::llvm::dyn_cast<ShardOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardOp ShardOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users) {
  return create(builder, builder.getLoc(), std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
}

void ShardOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users) {
  odsState.addOperands(src);
  odsState.addOperands(sharding);
  if (annotate_for_users) {
    odsState.getOrAddProperties<Properties>().annotate_for_users = ((annotate_for_users) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShardOp ShardOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
  auto __res__ = ::llvm::dyn_cast<ShardOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardOp ShardOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(src)>(src), std::forward<decltype(sharding)>(sharding), std::forward<decltype(annotate_for_users)>(annotate_for_users));
}

void ShardOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ShardOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ShardOp ShardOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShardOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardOp ShardOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShardOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ShardOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShardOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

ShardOp ShardOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShardOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardOp ShardOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShardOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ShardOp ShardOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShardOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardOp ShardOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ShardOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShardOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

ShardOp ShardOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShardOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardOp ShardOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ShardOp::verifyInvariantsImpl() {
  auto tblgen_annotate_for_users = getProperties().annotate_for_users; (void)tblgen_annotate_for_users;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps7(*this, tblgen_annotate_for_users, "annotate_for_users")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(0).begin()).getType()) && ((*this->getODSOperands(0).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {result, src} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult ShardOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ShardOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ShardOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand srcRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> srcOperands(&srcRawOperand, 1);  ::llvm::SMLoc srcOperandsLoc;
  (void)srcOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand shardingRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> shardingOperands(&shardingRawOperand, 1);  ::llvm::SMLoc shardingOperandsLoc;
  (void)shardingOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  srcOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(srcRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("to"))
    return ::mlir::failure();

  shardingOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(shardingRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("annotate_for_users"))) {
    result.getOrAddProperties<ShardOp::Properties>().annotate_for_users = parser.getBuilder().getUnitAttr();  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::RankedTensorType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::mlir::shard::ShardingType>();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(srcOperands, resultTypes[0], srcOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(shardingOperands, odsBuildableType0, shardingOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShardOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getSrc();
  _odsPrinter << ' ' << "to";
  _odsPrinter << ' ';
  _odsPrinter << getSharding();
  if ((getAnnotateForUsersAttr() && getAnnotateForUsersAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "annotate_for_users";
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("annotate_for_users");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getAnnotateForUsersAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("annotate_for_users");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::RankedTensorType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void ShardOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ShardOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ShardShapeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ShardShapeOpGenericAdaptorBase::ShardShapeOpGenericAdaptorBase(ShardShapeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ShardShapeOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::llvm::ArrayRef<int64_t> ShardShapeOpGenericAdaptorBase::getDims() {
  auto attr = getDimsAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> ShardShapeOpGenericAdaptorBase::getDevice() {
  auto attr = getDeviceAttr();
  return attr;
}


} // namespace detail
ShardShapeOpAdaptor::ShardShapeOpAdaptor(ShardShapeOp op) : ShardShapeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ShardShapeOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_device = getProperties().device; (void)tblgen_device;
  if (!tblgen_device) return emitError(loc, "'shard.shard_shape' op requires attribute 'device'");
  auto tblgen_dims = getProperties().dims; (void)tblgen_dims;
  if (!tblgen_dims) return emitError(loc, "'shard.shard_shape' op requires attribute 'dims'");

  if (tblgen_dims && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_dims))))
    return emitError(loc, "'shard.shard_shape' op attribute 'dims' failed to satisfy constraint: i64 dense array attribute");

  if (tblgen_device && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_device))))
    return emitError(loc, "'shard.shard_shape' op attribute 'device' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ShardShapeOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange ShardShapeOp::getDimsDynamicMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(0u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange ShardShapeOp::getDeviceDynamicMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(2u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

std::pair<unsigned, unsigned> ShardShapeOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::LogicalResult ShardShapeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.device;
       auto attr = dict.get("device");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `device` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.dims;
       auto attr = dict.get("dims");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `dims` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        return convertFromAttribute(propStorage, propAttr, emitError);
      };
         auto attr = dict.get("operandSegmentSizes");   if (!attr) attr = dict.get("operand_segment_sizes");;
;
      if (attr && ::mlir::failed(setFromAttr(prop.operandSegmentSizes, attr, emitError)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::mlir::Attribute ShardShapeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.device;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("device",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.dims;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("dims",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.operandSegmentSizes;
      auto attr = [&]() -> ::mlir::Attribute {
        return ::mlir::DenseI32ArrayAttr::get(ctx, propStorage);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("operandSegmentSizes", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ShardShapeOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.device.getAsOpaquePointer()), 
    llvm::hash_value(prop.dims.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> ShardShapeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "device")
      return prop.device;

    if (name == "dims")
      return prop.dims;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void ShardShapeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "device") {
       prop.device = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.device)>>(value);
       return;
    }

    if (name == "dims") {
       prop.dims = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.dims)>>(value);
       return;
    }
        if (name == "operand_segment_sizes" || name == "operandSegmentSizes") {
       auto arrAttr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(value);
       if (!arrAttr) return;
       if (arrAttr.size() != sizeof(prop.operandSegmentSizes) / sizeof(int32_t))
         return;
       llvm::copy(arrAttr.asArrayRef(), prop.operandSegmentSizes.begin());
       return;
    }
}

void ShardShapeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.device) attrs.append("device", prop.device);

    if (prop.dims) attrs.append("dims", prop.dims);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult ShardShapeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getDeviceAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "device", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getDimsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "dims", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ShardShapeOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.device)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.dims)))
    return ::mlir::failure();

  if (reader.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
    auto &propStorage = prop.operandSegmentSizes;
    ::mlir::DenseI32ArrayAttr attr;
    if (::mlir::failed(reader.readAttribute(attr))) return ::mlir::failure();
    if (attr.size() > static_cast<int64_t>(sizeof(propStorage) / sizeof(int32_t))) {
      reader.emitError("size mismatch for operand/result_segment_size");
      return ::mlir::failure();
    }
    ::llvm::copy(::llvm::ArrayRef<int32_t>(attr), propStorage.begin());
  }

  {
    auto &propStorage = prop.operandSegmentSizes;
    auto readProp = [&]() {

  if (reader.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    return reader.readSparseArray(::llvm::MutableArrayRef(propStorage));
;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void ShardShapeOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.device);
  writer.writeAttribute(prop.dims);

if (writer.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
  auto &propStorage = prop.operandSegmentSizes;
  writer.writeAttribute(::mlir::DenseI32ArrayAttr::get(this->getContext(), propStorage));
}

  {
    auto &propStorage = prop.operandSegmentSizes;

  if (writer.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    writer.writeSparseArray(::llvm::ArrayRef(propStorage));
;
  }
}

::llvm::ArrayRef<int64_t> ShardShapeOp::getDims() {
  auto attr = getDimsAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> ShardShapeOp::getDevice() {
  auto attr = getDeviceAttr();
  return attr;
}

void ShardShapeOp::setDims(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().dims = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void ShardShapeOp::setDevice(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().device = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

ShardShapeOp ShardShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<int64_t> dims, ArrayRef<Value> dims_dyn, Value sharding, ValueRange device) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dims)>(dims), std::forward<decltype(dims_dyn)>(dims_dyn), std::forward<decltype(sharding)>(sharding), std::forward<decltype(device)>(device));
  auto __res__ = ::llvm::dyn_cast<ShardShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardShapeOp ShardShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<int64_t> dims, ArrayRef<Value> dims_dyn, Value sharding, ValueRange device) {
  return create(builder, builder.getLoc(), std::forward<decltype(dims)>(dims), std::forward<decltype(dims_dyn)>(dims_dyn), std::forward<decltype(sharding)>(sharding), std::forward<decltype(device)>(device));
}

void ShardShapeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::DenseI64ArrayAttr dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::mlir::DenseI64ArrayAttr device, ::mlir::ValueRange device_dynamic) {
  odsState.addOperands(dims_dynamic);
  odsState.addOperands(sharding);
  odsState.addOperands(device_dynamic);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(dims_dynamic.size()), 1, static_cast<int32_t>(device_dynamic.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().dims = dims;
  odsState.getOrAddProperties<Properties>().device = device;
  odsState.addTypes(result);
}

ShardShapeOp ShardShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::DenseI64ArrayAttr dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::mlir::DenseI64ArrayAttr device, ::mlir::ValueRange device_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(dims)>(dims), std::forward<decltype(dims_dynamic)>(dims_dynamic), std::forward<decltype(sharding)>(sharding), std::forward<decltype(device)>(device), std::forward<decltype(device_dynamic)>(device_dynamic));
  auto __res__ = ::llvm::dyn_cast<ShardShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardShapeOp ShardShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::DenseI64ArrayAttr dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::mlir::DenseI64ArrayAttr device, ::mlir::ValueRange device_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(dims)>(dims), std::forward<decltype(dims_dynamic)>(dims_dynamic), std::forward<decltype(sharding)>(sharding), std::forward<decltype(device)>(device), std::forward<decltype(device_dynamic)>(device_dynamic));
}

void ShardShapeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::llvm::ArrayRef<int64_t> dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::llvm::ArrayRef<int64_t> device, ::mlir::ValueRange device_dynamic) {
  odsState.addOperands(dims_dynamic);
  odsState.addOperands(sharding);
  odsState.addOperands(device_dynamic);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(dims_dynamic.size()), 1, static_cast<int32_t>(device_dynamic.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().dims = odsBuilder.getDenseI64ArrayAttr(dims);
  odsState.getOrAddProperties<Properties>().device = odsBuilder.getDenseI64ArrayAttr(device);
  odsState.addTypes(result);
}

ShardShapeOp ShardShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::llvm::ArrayRef<int64_t> dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::llvm::ArrayRef<int64_t> device, ::mlir::ValueRange device_dynamic) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(dims)>(dims), std::forward<decltype(dims_dynamic)>(dims_dynamic), std::forward<decltype(sharding)>(sharding), std::forward<decltype(device)>(device), std::forward<decltype(device_dynamic)>(device_dynamic));
  auto __res__ = ::llvm::dyn_cast<ShardShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardShapeOp ShardShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::llvm::ArrayRef<int64_t> dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::llvm::ArrayRef<int64_t> device, ::mlir::ValueRange device_dynamic) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(dims)>(dims), std::forward<decltype(dims_dynamic)>(dims_dynamic), std::forward<decltype(sharding)>(sharding), std::forward<decltype(device)>(device), std::forward<decltype(device_dynamic)>(device_dynamic));
}

void ShardShapeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ShardShapeOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ShardShapeOp ShardShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShardShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardShapeOp ShardShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShardShapeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

ShardShapeOp ShardShapeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShardShapeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardShapeOp ShardShapeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ShardShapeOp::verifyInvariantsImpl() {
  auto tblgen_device = getProperties().device; (void)tblgen_device;
  if (!tblgen_device) return emitOpError("requires attribute 'device'");
  auto tblgen_dims = getProperties().dims; (void)tblgen_dims;
  if (!tblgen_dims) return emitOpError("requires attribute 'dims'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_dims, "dims")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_device, "device")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ShardShapeOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ShardShapeOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> dims_dynamicOperands;
  ::llvm::SMLoc dims_dynamicOperandsLoc;
  (void)dims_dynamicOperandsLoc;
  ::mlir::DenseI64ArrayAttr dimsAttr;
  ::mlir::OpAsmParser::UnresolvedOperand shardingRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> shardingOperands(&shardingRawOperand, 1);  ::llvm::SMLoc shardingOperandsLoc;
  (void)shardingOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> device_dynamicOperands;
  ::llvm::SMLoc device_dynamicOperandsLoc;
  (void)device_dynamicOperandsLoc;
  ::mlir::DenseI64ArrayAttr deviceAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;
  if (parser.parseKeyword("dims"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    dims_dynamicOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, dims_dynamicOperands, dimsAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<ShardShapeOp::Properties>().dims = dimsAttr;
  }
  if (parser.parseKeyword("sharding"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  shardingOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(shardingRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("device"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    device_dynamicOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, device_dynamicOperands, deviceAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<ShardShapeOp::Properties>().device = deviceAttr;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(dims_dynamicOperands.size()), 1, static_cast<int32_t>(device_dynamicOperands.size())}), result.getOrAddProperties<ShardShapeOp::Properties>().operandSegmentSizes.begin());
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIndexType();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getType<::mlir::shard::ShardingType>();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(dims_dynamicOperands, odsBuildableType0, dims_dynamicOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(shardingOperands, odsBuildableType1, shardingOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(device_dynamicOperands, odsBuildableType0, device_dynamicOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShardShapeOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "dims";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  printDynamicIndexList(_odsPrinter, *this, getDimsDynamic(), getDimsAttr());
  _odsPrinter << ' ' << "sharding";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter << getSharding();
  _odsPrinter << ' ' << "device";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  printDynamicIndexList(_odsPrinter, *this, getDeviceDynamic(), getDeviceAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("operandSegmentSizes");
  elidedAttrs.push_back("dims");
  elidedAttrs.push_back("device");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}

void ShardShapeOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ShardShapeOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ShardingOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ShardingOpGenericAdaptorBase::ShardingOpGenericAdaptorBase(ShardingOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ShardingOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::llvm::StringRef ShardingOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::shard::GridAxesArrayAttr ShardingOpGenericAdaptorBase::getSplitAxes() {
  auto attr = getSplitAxesAttr();
  return ::llvm::cast<::mlir::shard::GridAxesArrayAttr>(attr);
}

::mlir::DenseI64ArrayAttr ShardingOpGenericAdaptorBase::getStaticShardedDimsOffsetsAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().static_sharded_dims_offsets);
  return attr;
}

::llvm::ArrayRef<int64_t> ShardingOpGenericAdaptorBase::getStaticShardedDimsOffsets() {
  auto attr = getStaticShardedDimsOffsetsAttr();
  return attr;
}

::mlir::DenseI64ArrayAttr ShardingOpGenericAdaptorBase::getStaticHaloSizesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().static_halo_sizes);
  return attr;
}

::llvm::ArrayRef<int64_t> ShardingOpGenericAdaptorBase::getStaticHaloSizes() {
  auto attr = getStaticHaloSizesAttr();
  return attr;
}


} // namespace detail
ShardingOpAdaptor::ShardingOpAdaptor(ShardingOp op) : ShardingOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ShardingOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.sharding' op requires attribute 'grid'");
  auto tblgen_split_axes = getProperties().split_axes; (void)tblgen_split_axes;
  if (!tblgen_split_axes) return emitError(loc, "'shard.sharding' op requires attribute 'split_axes'");
  auto tblgen_static_halo_sizes = getProperties().static_halo_sizes; (void)tblgen_static_halo_sizes;
  auto tblgen_static_sharded_dims_offsets = getProperties().static_sharded_dims_offsets; (void)tblgen_static_sharded_dims_offsets;

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.sharding' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_split_axes && !((::llvm::isa<::mlir::shard::GridAxesArrayAttr>(tblgen_split_axes))))
    return emitError(loc, "'shard.sharding' op attribute 'split_axes' failed to satisfy constraint: ");

  if (tblgen_static_sharded_dims_offsets && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_static_sharded_dims_offsets))))
    return emitError(loc, "'shard.sharding' op attribute 'static_sharded_dims_offsets' failed to satisfy constraint: i64 dense array attribute");

  if (tblgen_static_halo_sizes && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_static_halo_sizes))))
    return emitError(loc, "'shard.sharding' op attribute 'static_halo_sizes' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ShardingOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange ShardingOp::getDynamicShardedDimsOffsetsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(0u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange ShardingOp::getDynamicHaloSizesMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(1u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::llvm::LogicalResult ShardingOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.split_axes;
       auto attr = dict.get("split_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `split_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.static_halo_sizes;
       auto attr = dict.get("static_halo_sizes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `static_halo_sizes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.static_sharded_dims_offsets;
       auto attr = dict.get("static_sharded_dims_offsets");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `static_sharded_dims_offsets` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        return convertFromAttribute(propStorage, propAttr, emitError);
      };
         auto attr = dict.get("operandSegmentSizes");   if (!attr) attr = dict.get("operand_segment_sizes");;
;
      if (attr && ::mlir::failed(setFromAttr(prop.operandSegmentSizes, attr, emitError)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::mlir::Attribute ShardingOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.split_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("split_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.static_halo_sizes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("static_halo_sizes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.static_sharded_dims_offsets;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("static_sharded_dims_offsets",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.operandSegmentSizes;
      auto attr = [&]() -> ::mlir::Attribute {
        return ::mlir::DenseI32ArrayAttr::get(ctx, propStorage);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("operandSegmentSizes", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ShardingOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.split_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.static_halo_sizes.getAsOpaquePointer()), 
    llvm::hash_value(prop.static_sharded_dims_offsets.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> ShardingOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "split_axes")
      return prop.split_axes;

    if (name == "static_halo_sizes")
      return prop.static_halo_sizes;

    if (name == "static_sharded_dims_offsets")
      return prop.static_sharded_dims_offsets;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void ShardingOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "split_axes") {
       prop.split_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.split_axes)>>(value);
       return;
    }

    if (name == "static_halo_sizes") {
       prop.static_halo_sizes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.static_halo_sizes)>>(value);
       return;
    }

    if (name == "static_sharded_dims_offsets") {
       prop.static_sharded_dims_offsets = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.static_sharded_dims_offsets)>>(value);
       return;
    }
        if (name == "operand_segment_sizes" || name == "operandSegmentSizes") {
       auto arrAttr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(value);
       if (!arrAttr) return;
       if (arrAttr.size() != sizeof(prop.operandSegmentSizes) / sizeof(int32_t))
         return;
       llvm::copy(arrAttr.asArrayRef(), prop.operandSegmentSizes.begin());
       return;
    }
}

void ShardingOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.split_axes) attrs.append("split_axes", prop.split_axes);

    if (prop.static_halo_sizes) attrs.append("static_halo_sizes", prop.static_halo_sizes);

    if (prop.static_sharded_dims_offsets) attrs.append("static_sharded_dims_offsets", prop.static_sharded_dims_offsets);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult ShardingOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSplitAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps8(attr, "split_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStaticHaloSizesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "static_halo_sizes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStaticShardedDimsOffsetsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "static_sharded_dims_offsets", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ShardingOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (reader.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
    auto &propStorage = prop.operandSegmentSizes;
    ::mlir::DenseI32ArrayAttr attr;
    if (::mlir::failed(reader.readAttribute(attr))) return ::mlir::failure();
    if (attr.size() > static_cast<int64_t>(sizeof(propStorage) / sizeof(int32_t))) {
      reader.emitError("size mismatch for operand/result_segment_size");
      return ::mlir::failure();
    }
    ::llvm::copy(::llvm::ArrayRef<int32_t>(attr), propStorage.begin());
  }

  if (::mlir::failed(reader.readAttribute(prop.split_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.static_halo_sizes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.static_sharded_dims_offsets)))
    return ::mlir::failure();

  {
    auto &propStorage = prop.operandSegmentSizes;
    auto readProp = [&]() {

  if (reader.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    return reader.readSparseArray(::llvm::MutableArrayRef(propStorage));
;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void ShardingOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);

if (writer.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
  auto &propStorage = prop.operandSegmentSizes;
  writer.writeAttribute(::mlir::DenseI32ArrayAttr::get(this->getContext(), propStorage));
}
  writer.writeAttribute(prop.split_axes);

  writer.writeOptionalAttribute(prop.static_halo_sizes);

  writer.writeOptionalAttribute(prop.static_sharded_dims_offsets);

  {
    auto &propStorage = prop.operandSegmentSizes;

  if (writer.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    writer.writeSparseArray(::llvm::ArrayRef(propStorage));
;
  }
}

::llvm::StringRef ShardingOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::shard::GridAxesArrayAttr ShardingOp::getSplitAxes() {
  auto attr = getSplitAxesAttr();
  return ::llvm::cast<::mlir::shard::GridAxesArrayAttr>(attr);
}

::llvm::ArrayRef<int64_t> ShardingOp::getStaticShardedDimsOffsets() {
  auto attr = getStaticShardedDimsOffsetsAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> ShardingOp::getStaticHaloSizes() {
  auto attr = getStaticHaloSizesAttr();
  return attr;
}

void ShardingOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ShardingOp::setStaticShardedDimsOffsets(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().static_sharded_dims_offsets = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void ShardingOp::setStaticHaloSizes(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().static_halo_sizes = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, FlatSymbolRefAttr grid, ArrayRef<GridAxesAttr> split_axes, ArrayRef<int64_t> static_halo_sizes, ArrayRef<int64_t> static_sharded_dims_offsets) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, FlatSymbolRefAttr grid, ArrayRef<GridAxesAttr> split_axes, ArrayRef<int64_t> static_halo_sizes, ArrayRef<int64_t> static_sharded_dims_offsets) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets));
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, FlatSymbolRefAttr grid, ArrayRef<GridAxesAttr> split_axes, ::mlir::ArrayRef<::mlir::OpFoldResult> halo_sizes, ::mlir::ArrayRef<::mlir::OpFoldResult> sharded_dims_offsets) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(halo_sizes)>(halo_sizes), std::forward<decltype(sharded_dims_offsets)>(sharded_dims_offsets));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, FlatSymbolRefAttr grid, ArrayRef<GridAxesAttr> split_axes, ::mlir::ArrayRef<::mlir::OpFoldResult> halo_sizes, ::mlir::ArrayRef<::mlir::OpFoldResult> sharded_dims_offsets) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(halo_sizes)>(halo_sizes), std::forward<decltype(sharded_dims_offsets)>(sharded_dims_offsets));
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, llvm::StringRef grid, ArrayRef<GridAxesAttr> split_axes, ArrayRef<int64_t> static_halo_sizes, ArrayRef<int64_t> static_sharded_dims_offsets) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, llvm::StringRef grid, ArrayRef<GridAxesAttr> split_axes, ArrayRef<int64_t> static_halo_sizes, ArrayRef<int64_t> static_sharded_dims_offsets) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets));
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::shard::Sharding from) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(from)>(from));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, mlir::shard::Sharding from) {
  return create(builder, builder.getLoc(), std::forward<decltype(from)>(from));
}

void ShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  odsState.addOperands(dynamic_sharded_dims_offsets);
  odsState.addOperands(dynamic_halo_sizes);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(dynamic_sharded_dims_offsets.size()), static_cast<int32_t>(dynamic_halo_sizes.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().grid = grid;
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  if (static_sharded_dims_offsets) {
    odsState.getOrAddProperties<Properties>().static_sharded_dims_offsets = static_sharded_dims_offsets;
  }
  if (static_halo_sizes) {
    odsState.getOrAddProperties<Properties>().static_halo_sizes = static_halo_sizes;
  }
  odsState.addTypes(result);
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
}

void ShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  odsState.addOperands(dynamic_sharded_dims_offsets);
  odsState.addOperands(dynamic_halo_sizes);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(dynamic_sharded_dims_offsets.size()), static_cast<int32_t>(dynamic_halo_sizes.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().grid = grid;
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  if (static_sharded_dims_offsets) {
    odsState.getOrAddProperties<Properties>().static_sharded_dims_offsets = static_sharded_dims_offsets;
  }
  if (static_halo_sizes) {
    odsState.getOrAddProperties<Properties>().static_halo_sizes = static_halo_sizes;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShardingOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
}

void ShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  odsState.addOperands(dynamic_sharded_dims_offsets);
  odsState.addOperands(dynamic_halo_sizes);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(dynamic_sharded_dims_offsets.size()), static_cast<int32_t>(dynamic_halo_sizes.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().grid = grid;
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  if (static_sharded_dims_offsets) {
    odsState.getOrAddProperties<Properties>().static_sharded_dims_offsets = static_sharded_dims_offsets;
  }
  if (static_halo_sizes) {
    odsState.getOrAddProperties<Properties>().static_halo_sizes = static_halo_sizes;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
}

void ShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  odsState.addOperands(dynamic_sharded_dims_offsets);
  odsState.addOperands(dynamic_halo_sizes);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(dynamic_sharded_dims_offsets.size()), static_cast<int32_t>(dynamic_halo_sizes.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  odsState.getOrAddProperties<Properties>().static_sharded_dims_offsets = odsBuilder.getDenseI64ArrayAttr(static_sharded_dims_offsets);
  odsState.getOrAddProperties<Properties>().static_halo_sizes = odsBuilder.getDenseI64ArrayAttr(static_halo_sizes);
  odsState.addTypes(result);
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
}

void ShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  odsState.addOperands(dynamic_sharded_dims_offsets);
  odsState.addOperands(dynamic_halo_sizes);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(dynamic_sharded_dims_offsets.size()), static_cast<int32_t>(dynamic_halo_sizes.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  odsState.getOrAddProperties<Properties>().static_sharded_dims_offsets = odsBuilder.getDenseI64ArrayAttr(static_sharded_dims_offsets);
  odsState.getOrAddProperties<Properties>().static_halo_sizes = odsBuilder.getDenseI64ArrayAttr(static_halo_sizes);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShardingOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
}

void ShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  odsState.addOperands(dynamic_sharded_dims_offsets);
  odsState.addOperands(dynamic_halo_sizes);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(dynamic_sharded_dims_offsets.size()), static_cast<int32_t>(dynamic_halo_sizes.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  odsState.getOrAddProperties<Properties>().static_sharded_dims_offsets = odsBuilder.getDenseI64ArrayAttr(static_sharded_dims_offsets);
  odsState.getOrAddProperties<Properties>().static_halo_sizes = odsBuilder.getDenseI64ArrayAttr(static_halo_sizes);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(static_sharded_dims_offsets)>(static_sharded_dims_offsets), std::forward<decltype(dynamic_sharded_dims_offsets)>(dynamic_sharded_dims_offsets), std::forward<decltype(static_halo_sizes)>(static_halo_sizes), std::forward<decltype(dynamic_halo_sizes)>(dynamic_halo_sizes));
}

void ShardingOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ShardingOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ShardingOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShardingOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShardingOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ShardingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShardingOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

ShardingOp ShardingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShardingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShardingOp ShardingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ShardingOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.static_sharded_dims_offsets)
    properties.static_sharded_dims_offsets = odsBuilder.getDenseI64ArrayAttr({});
  if (!properties.static_halo_sizes)
    properties.static_halo_sizes = odsBuilder.getDenseI64ArrayAttr({});
}

::llvm::LogicalResult ShardingOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_split_axes = getProperties().split_axes; (void)tblgen_split_axes;
  if (!tblgen_split_axes) return emitOpError("requires attribute 'split_axes'");
  auto tblgen_static_halo_sizes = getProperties().static_halo_sizes; (void)tblgen_static_halo_sizes;
  auto tblgen_static_sharded_dims_offsets = getProperties().static_sharded_dims_offsets; (void)tblgen_static_sharded_dims_offsets;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps8(*this, tblgen_split_axes, "split_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_static_sharded_dims_offsets, "static_sharded_dims_offsets")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_static_halo_sizes, "static_halo_sizes")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ShardingOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult ShardingOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<::mlir::shard::ShardingType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ShardingOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::shard::GridAxesArrayAttr split_axesAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> dynamic_halo_sizesOperands;
  ::llvm::SMLoc dynamic_halo_sizesOperandsLoc;
  (void)dynamic_halo_sizesOperandsLoc;
  ::mlir::DenseI64ArrayAttr static_halo_sizesAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> dynamic_sharded_dims_offsetsOperands;
  ::llvm::SMLoc dynamic_sharded_dims_offsetsOperandsLoc;
  (void)dynamic_sharded_dims_offsetsOperandsLoc;
  ::mlir::DenseI64ArrayAttr static_sharded_dims_offsetsAttr;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<ShardingOp::Properties>().grid = gridAttr;
  if (parser.parseKeyword("split_axes"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(split_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (split_axesAttr) result.getOrAddProperties<ShardingOp::Properties>().split_axes = split_axesAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("halo_sizes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    dynamic_halo_sizesOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, dynamic_halo_sizesOperands, static_halo_sizesAttr);
    if (odsResult) return ::mlir::failure();
    if (static_halo_sizesAttr)
      result.getOrAddProperties<ShardingOp::Properties>().static_halo_sizes = static_halo_sizesAttr;
  }
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("sharded_dims_offsets"))) {
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    dynamic_sharded_dims_offsetsOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, dynamic_sharded_dims_offsetsOperands, static_sharded_dims_offsetsAttr);
    if (odsResult) return ::mlir::failure();
    if (static_sharded_dims_offsetsAttr)
      result.getOrAddProperties<ShardingOp::Properties>().static_sharded_dims_offsets = static_sharded_dims_offsetsAttr;
  }
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::shard::ShardingType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(dynamic_sharded_dims_offsetsOperands.size()), static_cast<int32_t>(dynamic_halo_sizesOperands.size())}), result.getOrAddProperties<ShardingOp::Properties>().operandSegmentSizes.begin());
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(64);
  result.addTypes(resultTypes);
  if (parser.resolveOperands(dynamic_sharded_dims_offsetsOperands, odsBuildableType0, dynamic_sharded_dims_offsetsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(dynamic_halo_sizesOperands, odsBuildableType0, dynamic_halo_sizesOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShardingOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  _odsPrinter << ' ' << "split_axes";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getSplitAxesAttr());
  if (((!getDynamicHaloSizes().empty()) || (getStaticHaloSizesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI64ArrayAttr({})))) {
    _odsPrinter << ' ' << "halo_sizes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
    printDynamicIndexList(_odsPrinter, *this, getDynamicHaloSizes(), getStaticHaloSizesAttr());
  }
  if (((!getDynamicShardedDimsOffsets().empty()) || (getStaticShardedDimsOffsetsAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI64ArrayAttr({})))) {
    _odsPrinter << ' ' << "sharded_dims_offsets";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
    printDynamicIndexList(_odsPrinter, *this, getDynamicShardedDimsOffsets(), getStaticShardedDimsOffsetsAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("operandSegmentSizes");
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("split_axes");
  elidedAttrs.push_back("static_halo_sizes");
  elidedAttrs.push_back("static_sharded_dims_offsets");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getStaticShardedDimsOffsetsAttr();
     if(attr && (attr == odsBuilder.getDenseI64ArrayAttr({})))
       elidedAttrs.push_back("static_sharded_dims_offsets");
  }
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getStaticHaloSizesAttr();
     if(attr && (attr == odsBuilder.getDenseI64ArrayAttr({})))
       elidedAttrs.push_back("static_halo_sizes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::shard::ShardingType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void ShardingOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ShardingOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ShiftOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ShiftOpGenericAdaptorBase::ShiftOpGenericAdaptorBase(ShiftOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ShiftOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::DenseI16ArrayAttr ShiftOpGenericAdaptorBase::getGridAxesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  return attr;
}

::llvm::ArrayRef<int16_t> ShiftOpGenericAdaptorBase::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt ShiftOpGenericAdaptorBase::getShiftAxis() {
  auto attr = getShiftAxisAttr();
  return attr.getValue();
}

uint64_t ShiftOpGenericAdaptorBase::getOffset() {
  auto attr = getOffsetAttr();
  return attr.getValue().getZExtValue();
}

::mlir::UnitAttr ShiftOpGenericAdaptorBase::getRotateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().rotate);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ShiftOpGenericAdaptorBase::getRotate() {
  auto attr = getRotateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
ShiftOpAdaptor::ShiftOpAdaptor(ShiftOp op) : ShiftOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ShiftOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.shift' op requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_offset = getProperties().offset; (void)tblgen_offset;
  if (!tblgen_offset) return emitError(loc, "'shard.shift' op requires attribute 'offset'");
  auto tblgen_rotate = getProperties().rotate; (void)tblgen_rotate;
  auto tblgen_shift_axis = getProperties().shift_axis; (void)tblgen_shift_axis;
  if (!tblgen_shift_axis) return emitError(loc, "'shard.shift' op requires attribute 'shift_axis'");

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.shift' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_grid_axes && !((::llvm::isa<::mlir::DenseI16ArrayAttr>(tblgen_grid_axes))))
    return emitError(loc, "'shard.shift' op attribute 'grid_axes' failed to satisfy constraint: i16 dense array attribute");

  if (tblgen_shift_axis && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_shift_axis))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(tblgen_shift_axis).getType())))))
    return emitError(loc, "'shard.shift' op attribute 'shift_axis' failed to satisfy constraint: index attribute");

  if (tblgen_offset && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_offset))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_offset).getType().isSignlessInteger(64)))))
    return emitError(loc, "'shard.shift' op attribute 'offset' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_rotate && !((::llvm::isa<::mlir::UnitAttr>(tblgen_rotate))))
    return emitError(loc, "'shard.shift' op attribute 'rotate' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ShiftOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.grid_axes;
       auto attr = dict.get("grid_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.offset;
       auto attr = dict.get("offset");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `offset` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.rotate;
       auto attr = dict.get("rotate");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `rotate` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.shift_axis;
       auto attr = dict.get("shift_axis");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `shift_axis` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ShiftOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.grid_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.offset;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("offset",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.rotate;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("rotate",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.shift_axis;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("shift_axis",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ShiftOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.grid_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.offset.getAsOpaquePointer()), 
    llvm::hash_value(prop.rotate.getAsOpaquePointer()), 
    llvm::hash_value(prop.shift_axis.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ShiftOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "grid_axes")
      return prop.grid_axes;

    if (name == "offset")
      return prop.offset;

    if (name == "rotate")
      return prop.rotate;

    if (name == "shift_axis")
      return prop.shift_axis;
  return std::nullopt;
}

void ShiftOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "grid_axes") {
       prop.grid_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid_axes)>>(value);
       return;
    }

    if (name == "offset") {
       prop.offset = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.offset)>>(value);
       return;
    }

    if (name == "rotate") {
       prop.rotate = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.rotate)>>(value);
       return;
    }

    if (name == "shift_axis") {
       prop.shift_axis = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.shift_axis)>>(value);
       return;
    }
}

void ShiftOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.grid_axes) attrs.append("grid_axes", prop.grid_axes);

    if (prop.offset) attrs.append("offset", prop.offset);

    if (prop.rotate) attrs.append("rotate", prop.rotate);

    if (prop.shift_axis) attrs.append("shift_axis", prop.shift_axis);
}

::llvm::LogicalResult ShiftOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGridAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(attr, "grid_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getOffsetAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps9(attr, "offset", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRotateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps7(attr, "rotate", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getShiftAxisAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(attr, "shift_axis", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ShiftOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.grid_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.offset)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.rotate)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.shift_axis)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShiftOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);

  writer.writeOptionalAttribute(prop.grid_axes);
  writer.writeAttribute(prop.offset);

  writer.writeOptionalAttribute(prop.rotate);
  writer.writeAttribute(prop.shift_axis);
}

::llvm::StringRef ShiftOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::llvm::ArrayRef<int16_t> ShiftOp::getGridAxes() {
  auto attr = getGridAxesAttr();
  return attr;
}

::llvm::APInt ShiftOp::getShiftAxis() {
  auto attr = getShiftAxisAttr();
  return attr.getValue();
}

uint64_t ShiftOp::getOffset() {
  auto attr = getOffsetAttr();
  return attr.getValue().getZExtValue();
}

bool ShiftOp::getRotate() {
  auto attr = getRotateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void ShiftOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ShiftOp::setGridAxes(::llvm::ArrayRef<int16_t> attrValue) {
  getProperties().grid_axes = ::mlir::Builder((*this)->getContext()).getDenseI16ArrayAttr(attrValue);
}

void ShiftOp::setShiftAxis(::llvm::APInt attrValue) {
  getProperties().shift_axis = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIndexType(), attrValue);
}

void ShiftOp::setOffset(uint64_t attrValue) {
  getProperties().offset = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

void ShiftOp::setRotate(bool attrValue) {
    auto &odsProp = getProperties().rotate;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ShiftOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().shift_axis = shift_axis;
  odsState.getOrAddProperties<Properties>().offset = offset;
  if (rotate) {
    odsState.getOrAddProperties<Properties>().rotate = rotate;
  }
  odsState.addTypes(result);
}

ShiftOp ShiftOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(shift_axis)>(shift_axis), std::forward<decltype(offset)>(offset), std::forward<decltype(rotate)>(rotate));
  auto __res__ = ::llvm::dyn_cast<ShiftOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftOp ShiftOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(shift_axis)>(shift_axis), std::forward<decltype(offset)>(offset), std::forward<decltype(rotate)>(rotate));
}

void ShiftOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = grid;
  if (grid_axes) {
    odsState.getOrAddProperties<Properties>().grid_axes = grid_axes;
  }
  odsState.getOrAddProperties<Properties>().shift_axis = shift_axis;
  odsState.getOrAddProperties<Properties>().offset = offset;
  if (rotate) {
    odsState.getOrAddProperties<Properties>().rotate = rotate;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShiftOp ShiftOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(shift_axis)>(shift_axis), std::forward<decltype(offset)>(offset), std::forward<decltype(rotate)>(rotate));
  auto __res__ = ::llvm::dyn_cast<ShiftOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftOp ShiftOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(shift_axis)>(shift_axis), std::forward<decltype(offset)>(offset), std::forward<decltype(rotate)>(rotate));
}

void ShiftOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().shift_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), shift_axis);
  odsState.getOrAddProperties<Properties>().offset = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), offset);
  if (rotate) {
    odsState.getOrAddProperties<Properties>().rotate = ((rotate) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

ShiftOp ShiftOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(shift_axis)>(shift_axis), std::forward<decltype(offset)>(offset), std::forward<decltype(rotate)>(rotate));
  auto __res__ = ::llvm::dyn_cast<ShiftOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftOp ShiftOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(shift_axis)>(shift_axis), std::forward<decltype(offset)>(offset), std::forward<decltype(rotate)>(rotate));
}

void ShiftOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().grid_axes = odsBuilder.getDenseI16ArrayAttr(grid_axes);
  odsState.getOrAddProperties<Properties>().shift_axis = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), shift_axis);
  odsState.getOrAddProperties<Properties>().offset = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), offset);
  if (rotate) {
    odsState.getOrAddProperties<Properties>().rotate = ((rotate) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShiftOp ShiftOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(shift_axis)>(shift_axis), std::forward<decltype(offset)>(offset), std::forward<decltype(rotate)>(rotate));
  auto __res__ = ::llvm::dyn_cast<ShiftOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftOp ShiftOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(grid)>(grid), std::forward<decltype(grid_axes)>(grid_axes), std::forward<decltype(input)>(input), std::forward<decltype(shift_axis)>(shift_axis), std::forward<decltype(offset)>(offset), std::forward<decltype(rotate)>(rotate));
}

void ShiftOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ShiftOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ShiftOp ShiftOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShiftOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftOp ShiftOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShiftOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ShiftOp ShiftOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShiftOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftOp ShiftOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ShiftOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.grid_axes)
    properties.grid_axes = odsBuilder.getDenseI16ArrayAttr({});
}

::llvm::LogicalResult ShiftOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_grid_axes = getProperties().grid_axes; (void)tblgen_grid_axes;
  auto tblgen_offset = getProperties().offset; (void)tblgen_offset;
  if (!tblgen_offset) return emitOpError("requires attribute 'offset'");
  auto tblgen_rotate = getProperties().rotate; (void)tblgen_rotate;
  auto tblgen_shift_axis = getProperties().shift_axis; (void)tblgen_shift_axis;
  if (!tblgen_shift_axis) return emitOpError("requires attribute 'shift_axis'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps2(*this, tblgen_grid_axes, "grid_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps3(*this, tblgen_shift_axis, "shift_axis")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps9(*this, tblgen_offset, "offset")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps7(*this, tblgen_rotate, "rotate")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ShiftOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ShiftOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::DenseI16ArrayAttr grid_axesAttr;
  ::mlir::IntegerAttr shift_axisAttr;
  ::mlir::IntegerAttr offsetAttr;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<ShiftOp::Properties>().grid = gridAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("grid_axes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(grid_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (grid_axesAttr) result.getOrAddProperties<ShiftOp::Properties>().grid_axes = grid_axesAttr;
  }
  if (parser.parseKeyword("shift_axis"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(shift_axisAttr, parser.getBuilder().getIndexType())) {
    return ::mlir::failure();
  }
  if (shift_axisAttr) result.getOrAddProperties<ShiftOp::Properties>().shift_axis = shift_axisAttr;
  if (parser.parseKeyword("offset"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(offsetAttr, parser.getBuilder().getIntegerType(64))) {
    return ::mlir::failure();
  }
  if (offsetAttr) result.getOrAddProperties<ShiftOp::Properties>().offset = offsetAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("rotate"))) {
    result.getOrAddProperties<ShiftOp::Properties>().rotate = parser.getBuilder().getUnitAttr();  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::TensorType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::RankedTensorType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShiftOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  if (getGridAxesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI16ArrayAttr({})) {
    _odsPrinter << ' ' << "grid_axes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getGridAxesAttr());
  }
  _odsPrinter << ' ' << "shift_axis";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getShiftAxisAttr());
  _odsPrinter << ' ' << "offset";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getOffsetAttr());
  if ((getRotateAttr() && getRotateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "rotate";
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("grid_axes");
  elidedAttrs.push_back("shift_axis");
  elidedAttrs.push_back("offset");
  elidedAttrs.push_back("rotate");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getGridAxesAttr();
     if(attr && (attr == odsBuilder.getDenseI16ArrayAttr({})))
       elidedAttrs.push_back("grid_axes");
  }
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getRotateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("rotate");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::TensorType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::RankedTensorType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void ShiftOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ShiftOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::UpdateHaloOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UpdateHaloOpGenericAdaptorBase::UpdateHaloOpGenericAdaptorBase(UpdateHaloOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> UpdateHaloOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef UpdateHaloOpGenericAdaptorBase::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::shard::GridAxesArrayAttr UpdateHaloOpGenericAdaptorBase::getSplitAxes() {
  auto attr = getSplitAxesAttr();
  return ::llvm::cast<::mlir::shard::GridAxesArrayAttr>(attr);
}

::mlir::DenseI64ArrayAttr UpdateHaloOpGenericAdaptorBase::getStaticHaloSizesAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().static_halo_sizes);
  return attr;
}

::llvm::ArrayRef<int64_t> UpdateHaloOpGenericAdaptorBase::getStaticHaloSizes() {
  auto attr = getStaticHaloSizesAttr();
  return attr;
}


} // namespace detail
UpdateHaloOpAdaptor::UpdateHaloOpAdaptor(UpdateHaloOp op) : UpdateHaloOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UpdateHaloOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitError(loc, "'shard.update_halo' op requires attribute 'grid'");
  auto tblgen_split_axes = getProperties().split_axes; (void)tblgen_split_axes;
  if (!tblgen_split_axes) return emitError(loc, "'shard.update_halo' op requires attribute 'split_axes'");
  auto tblgen_static_halo_sizes = getProperties().static_halo_sizes; (void)tblgen_static_halo_sizes;

  if (tblgen_grid && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_grid))))
    return emitError(loc, "'shard.update_halo' op attribute 'grid' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_split_axes && !((::llvm::isa<::mlir::shard::GridAxesArrayAttr>(tblgen_split_axes))))
    return emitError(loc, "'shard.update_halo' op attribute 'split_axes' failed to satisfy constraint: ");

  if (tblgen_static_halo_sizes && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_static_halo_sizes))))
    return emitError(loc, "'shard.update_halo' op attribute 'static_halo_sizes' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> UpdateHaloOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange UpdateHaloOp::getHaloSizesMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult UpdateHaloOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.grid;
       auto attr = dict.get("grid");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `grid` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.split_axes;
       auto attr = dict.get("split_axes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `split_axes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.static_halo_sizes;
       auto attr = dict.get("static_halo_sizes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `static_halo_sizes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute UpdateHaloOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.grid;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("grid",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.split_axes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("split_axes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.static_halo_sizes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("static_halo_sizes",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UpdateHaloOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.grid.getAsOpaquePointer()), 
    llvm::hash_value(prop.split_axes.getAsOpaquePointer()), 
    llvm::hash_value(prop.static_halo_sizes.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> UpdateHaloOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "grid")
      return prop.grid;

    if (name == "split_axes")
      return prop.split_axes;

    if (name == "static_halo_sizes")
      return prop.static_halo_sizes;
  return std::nullopt;
}

void UpdateHaloOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "grid") {
       prop.grid = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.grid)>>(value);
       return;
    }

    if (name == "split_axes") {
       prop.split_axes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.split_axes)>>(value);
       return;
    }

    if (name == "static_halo_sizes") {
       prop.static_halo_sizes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.static_halo_sizes)>>(value);
       return;
    }
}

void UpdateHaloOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.grid) attrs.append("grid", prop.grid);

    if (prop.split_axes) attrs.append("split_axes", prop.split_axes);

    if (prop.static_halo_sizes) attrs.append("static_halo_sizes", prop.static_halo_sizes);
}

::llvm::LogicalResult UpdateHaloOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGridAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(attr, "grid", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSplitAxesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps8(attr, "split_axes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStaticHaloSizesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(attr, "static_halo_sizes", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult UpdateHaloOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.grid)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.split_axes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.static_halo_sizes)))
    return ::mlir::failure();
  return ::mlir::success();
}

void UpdateHaloOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.grid);
  writer.writeAttribute(prop.split_axes);

  writer.writeOptionalAttribute(prop.static_halo_sizes);
}

::llvm::StringRef UpdateHaloOp::getGrid() {
  auto attr = getGridAttr();
  return attr.getValue();
}

::mlir::shard::GridAxesArrayAttr UpdateHaloOp::getSplitAxes() {
  auto attr = getSplitAxesAttr();
  return ::llvm::cast<::mlir::shard::GridAxesArrayAttr>(attr);
}

::llvm::ArrayRef<int64_t> UpdateHaloOp::getStaticHaloSizes() {
  auto attr = getStaticHaloSizesAttr();
  return attr;
}

void UpdateHaloOp::setGrid(::llvm::StringRef attrValue) {
  getProperties().grid = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void UpdateHaloOp::setStaticHaloSizes(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().static_halo_sizes = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void UpdateHaloOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes) {
  odsState.addOperands(destination);
  odsState.addOperands(halo_sizes);
  odsState.getOrAddProperties<Properties>().grid = grid;
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  if (static_halo_sizes) {
    odsState.getOrAddProperties<Properties>().static_halo_sizes = static_halo_sizes;
  }
  odsState.addTypes(result);
}

UpdateHaloOp UpdateHaloOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(destination)>(destination), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(halo_sizes)>(halo_sizes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes));
  auto __res__ = ::llvm::dyn_cast<UpdateHaloOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UpdateHaloOp UpdateHaloOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(destination)>(destination), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(halo_sizes)>(halo_sizes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes));
}

void UpdateHaloOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes) {
  odsState.addOperands(destination);
  odsState.addOperands(halo_sizes);
  odsState.getOrAddProperties<Properties>().grid = grid;
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  if (static_halo_sizes) {
    odsState.getOrAddProperties<Properties>().static_halo_sizes = static_halo_sizes;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UpdateHaloOp UpdateHaloOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(destination)>(destination), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(halo_sizes)>(halo_sizes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes));
  auto __res__ = ::llvm::dyn_cast<UpdateHaloOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UpdateHaloOp UpdateHaloOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(destination)>(destination), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(halo_sizes)>(halo_sizes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes));
}

void UpdateHaloOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes) {
  odsState.addOperands(destination);
  odsState.addOperands(halo_sizes);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  odsState.getOrAddProperties<Properties>().static_halo_sizes = odsBuilder.getDenseI64ArrayAttr(static_halo_sizes);
  odsState.addTypes(result);
}

UpdateHaloOp UpdateHaloOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(destination)>(destination), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(halo_sizes)>(halo_sizes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes));
  auto __res__ = ::llvm::dyn_cast<UpdateHaloOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UpdateHaloOp UpdateHaloOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(destination)>(destination), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(halo_sizes)>(halo_sizes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes));
}

void UpdateHaloOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes) {
  odsState.addOperands(destination);
  odsState.addOperands(halo_sizes);
  odsState.getOrAddProperties<Properties>().grid = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), grid);
  odsState.getOrAddProperties<Properties>().split_axes = split_axes;
  odsState.getOrAddProperties<Properties>().static_halo_sizes = odsBuilder.getDenseI64ArrayAttr(static_halo_sizes);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UpdateHaloOp UpdateHaloOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(destination)>(destination), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(halo_sizes)>(halo_sizes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes));
  auto __res__ = ::llvm::dyn_cast<UpdateHaloOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UpdateHaloOp UpdateHaloOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(destination)>(destination), std::forward<decltype(grid)>(grid), std::forward<decltype(split_axes)>(split_axes), std::forward<decltype(halo_sizes)>(halo_sizes), std::forward<decltype(static_halo_sizes)>(static_halo_sizes));
}

void UpdateHaloOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<UpdateHaloOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

UpdateHaloOp UpdateHaloOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UpdateHaloOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UpdateHaloOp UpdateHaloOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UpdateHaloOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UpdateHaloOp UpdateHaloOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UpdateHaloOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UpdateHaloOp UpdateHaloOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void UpdateHaloOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.static_halo_sizes)
    properties.static_halo_sizes = odsBuilder.getDenseI64ArrayAttr({});
}

::llvm::LogicalResult UpdateHaloOp::verifyInvariantsImpl() {
  auto tblgen_grid = getProperties().grid; (void)tblgen_grid;
  if (!tblgen_grid) return emitOpError("requires attribute 'grid'");
  auto tblgen_split_axes = getProperties().split_axes; (void)tblgen_split_axes;
  if (!tblgen_split_axes) return emitOpError("requires attribute 'split_axes'");
  auto tblgen_static_halo_sizes = getProperties().static_halo_sizes; (void)tblgen_static_halo_sizes;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps1(*this, tblgen_grid, "grid")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps8(*this, tblgen_split_axes, "split_axes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ShardOps5(*this, tblgen_static_halo_sizes, "static_halo_sizes")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ShardOps8(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()((*this->getODSResults(0).begin()).getType(), (*this->getODSOperands(0).begin()).getType()))))
    return emitOpError("failed to verify that result has same type as destination");
  return ::mlir::success();
}

::llvm::LogicalResult UpdateHaloOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult UpdateHaloOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand destinationRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> destinationOperands(&destinationRawOperand, 1);  ::llvm::SMLoc destinationOperandsLoc;
  (void)destinationOperandsLoc;
  ::mlir::FlatSymbolRefAttr gridAttr;
  ::mlir::shard::GridAxesArrayAttr split_axesAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> halo_sizesOperands;
  ::llvm::SMLoc halo_sizesOperandsLoc;
  (void)halo_sizesOperandsLoc;
  ::mlir::DenseI64ArrayAttr static_halo_sizesAttr;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  destinationOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(destinationRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("on"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(gridAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (gridAttr) result.getOrAddProperties<UpdateHaloOp::Properties>().grid = gridAttr;
  if (parser.parseKeyword("split_axes"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(split_axesAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (split_axesAttr) result.getOrAddProperties<UpdateHaloOp::Properties>().split_axes = split_axesAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("halo_sizes"))) {
  if (parser.parseEqual())
    return ::mlir::failure();
  {
    halo_sizesOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseDynamicIndexList(parser, halo_sizesOperands, static_halo_sizesAttr);
    if (odsResult) return ::mlir::failure();
    if (static_halo_sizesAttr)
      result.getOrAddProperties<UpdateHaloOp::Properties>().static_halo_sizes = static_halo_sizesAttr;
  }
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  for (::mlir::Type type : resultTypes) {
    (void)type;
    if (!(((((::llvm::isa<::mlir::MemRefType>(type))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType()))) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank() >= 1)))) || ((((::llvm::isa<::mlir::TensorType>(type))) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank() >= 1)))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType()))))) {
      return parser.emitError(parser.getNameLoc()) << "'result' must be non-0-ranked.memref of any type values or non-0-ranked.tensor of any type values, but got " << type;
    }
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(64);
  result.addTypes(resultTypes);
  if (parser.resolveOperands(destinationOperands, resultTypes[0], destinationOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(halo_sizesOperands, odsBuildableType0, halo_sizesOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void UpdateHaloOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getDestination();
  _odsPrinter << ' ' << "on";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGridAttr());
  _odsPrinter << ' ' << "split_axes";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getSplitAxesAttr());
  if (((!getHaloSizes().empty()) || (getStaticHaloSizesAttr() != ::mlir::OpBuilder((*this)->getContext()).getDenseI64ArrayAttr({})))) {
    _odsPrinter << ' ' << "halo_sizes";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
    printDynamicIndexList(_odsPrinter, *this, getHaloSizes(), getStaticHaloSizesAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("grid");
  elidedAttrs.push_back("split_axes");
  elidedAttrs.push_back("static_halo_sizes");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getStaticHaloSizesAttr();
     if(attr && (attr == odsBuilder.getDenseI64ArrayAttr({})))
       elidedAttrs.push_back("static_halo_sizes");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void UpdateHaloOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::UpdateHaloOp)


#endif // GET_OP_CLASSES

