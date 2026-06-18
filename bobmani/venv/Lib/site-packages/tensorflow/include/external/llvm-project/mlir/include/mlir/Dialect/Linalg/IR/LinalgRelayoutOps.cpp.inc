/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LinalgRelayoutOps.td                                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::mlir::linalg::PackOp,
::mlir::linalg::UnPackOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_LinalgRelayoutOps1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((::llvm::isa<::mlir::TensorType>(type))) || ((::llvm::isa<::mlir::MemRefType>(type)))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be Tensor or MemRef of any type values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_LinalgRelayoutOps2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((true))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_LinalgRelayoutOps3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::IndexType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of index, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_LinalgRelayoutOps4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::llvm::isa<::mlir::RankedTensorType>(type))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be ranked tensor of any type values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_LinalgRelayoutOps1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: i64 dense array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_LinalgRelayoutOps1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_LinalgRelayoutOps1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}
namespace mlir::linalg {


//===----------------------------------------------------------------------===//
// ::mlir::linalg::PackOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PackOpGenericAdaptorBase::PackOpGenericAdaptorBase(PackOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> PackOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::DenseI64ArrayAttr PackOpGenericAdaptorBase::getOuterDimsPermAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().outer_dims_perm);
  if (!attr)
    attr = ::mlir::Builder(odsAttrs.getContext()).getDenseI64ArrayAttr({});
  return attr;
}

::llvm::ArrayRef<int64_t> PackOpGenericAdaptorBase::getOuterDimsPerm() {
  auto attr = getOuterDimsPermAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getDenseI64ArrayAttr({});
  return attr;
}

::llvm::ArrayRef<int64_t> PackOpGenericAdaptorBase::getInnerDimsPos() {
  auto attr = getInnerDimsPosAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> PackOpGenericAdaptorBase::getStaticInnerTiles() {
  auto attr = getStaticInnerTilesAttr();
  return attr;
}


} // namespace detail
PackOpAdaptor::PackOpAdaptor(PackOp op) : PackOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PackOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_dims_pos = getProperties().inner_dims_pos; (void)tblgen_inner_dims_pos;
  if (!tblgen_inner_dims_pos) return emitError(loc, "'linalg.pack' op requires attribute 'inner_dims_pos'");
  auto tblgen_outer_dims_perm = getProperties().outer_dims_perm; (void)tblgen_outer_dims_perm;
  auto tblgen_static_inner_tiles = getProperties().static_inner_tiles; (void)tblgen_static_inner_tiles;
  if (!tblgen_static_inner_tiles) return emitError(loc, "'linalg.pack' op requires attribute 'static_inner_tiles'");

  if (tblgen_outer_dims_perm && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_outer_dims_perm))))
    return emitError(loc, "'linalg.pack' op attribute 'outer_dims_perm' failed to satisfy constraint: i64 dense array attribute");

  if (tblgen_inner_dims_pos && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_inner_dims_pos))))
    return emitError(loc, "'linalg.pack' op attribute 'inner_dims_pos' failed to satisfy constraint: i64 dense array attribute");

  if (tblgen_static_inner_tiles && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_static_inner_tiles))))
    return emitError(loc, "'linalg.pack' op attribute 'static_inner_tiles' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> PackOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange PackOp::getPaddingValueMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(2u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange PackOp::getInnerTilesMutable() {
  auto range = getODSOperandIndexAndLength(3);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(3u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

std::pair<unsigned, unsigned> PackOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult PackOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_dims_pos;
       auto attr = dict.get("inner_dims_pos");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_dims_pos` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.outer_dims_perm;
       auto attr = dict.get("outer_dims_perm");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `outer_dims_perm` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.static_inner_tiles;
       auto attr = dict.get("static_inner_tiles");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `static_inner_tiles` in property conversion: " << attr;
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

::mlir::Attribute PackOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_dims_pos;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_dims_pos",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.outer_dims_perm;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("outer_dims_perm",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.static_inner_tiles;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("static_inner_tiles",
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

llvm::hash_code PackOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_dims_pos.getAsOpaquePointer()), 
    llvm::hash_value(prop.outer_dims_perm.getAsOpaquePointer()), 
    llvm::hash_value(prop.static_inner_tiles.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> PackOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_dims_pos")
      return prop.inner_dims_pos;

    if (name == "outer_dims_perm")
      return prop.outer_dims_perm;

    if (name == "static_inner_tiles")
      return prop.static_inner_tiles;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void PackOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_dims_pos") {
       prop.inner_dims_pos = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_dims_pos)>>(value);
       return;
    }

    if (name == "outer_dims_perm") {
       prop.outer_dims_perm = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.outer_dims_perm)>>(value);
       return;
    }

    if (name == "static_inner_tiles") {
       prop.static_inner_tiles = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.static_inner_tiles)>>(value);
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

void PackOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_dims_pos) attrs.append("inner_dims_pos", prop.inner_dims_pos);

    if (prop.outer_dims_perm) attrs.append("outer_dims_perm", prop.outer_dims_perm);

    if (prop.static_inner_tiles) attrs.append("static_inner_tiles", prop.static_inner_tiles);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult PackOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerDimsPosAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(attr, "inner_dims_pos", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getOuterDimsPermAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(attr, "outer_dims_perm", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStaticInnerTilesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(attr, "static_inner_tiles", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult PackOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_dims_pos)))
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

  if (::mlir::failed(reader.readOptionalAttribute(prop.outer_dims_perm)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.static_inner_tiles)))
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

void PackOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_dims_pos);

if (writer.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
  auto &propStorage = prop.operandSegmentSizes;
  writer.writeAttribute(::mlir::DenseI32ArrayAttr::get(this->getContext(), propStorage));
}

  writer.writeOptionalAttribute(prop.outer_dims_perm);
  writer.writeAttribute(prop.static_inner_tiles);

  {
    auto &propStorage = prop.operandSegmentSizes;

  if (writer.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    writer.writeSparseArray(::llvm::ArrayRef(propStorage));
;
  }
}

::llvm::ArrayRef<int64_t> PackOp::getOuterDimsPerm() {
  auto attr = getOuterDimsPermAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr({});
  return attr;
}

::llvm::ArrayRef<int64_t> PackOp::getInnerDimsPos() {
  auto attr = getInnerDimsPosAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> PackOp::getStaticInnerTiles() {
  auto attr = getStaticInnerTilesAttr();
  return attr;
}

void PackOp::setOuterDimsPerm(::std::optional<::llvm::ArrayRef<int64_t>> attrValue) {
    auto &odsProp = getProperties().outer_dims_perm;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(*attrValue);
    else
      odsProp = nullptr;
}

void PackOp::setInnerDimsPos(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().inner_dims_pos = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void PackOp::setStaticInnerTiles(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().static_inner_tiles = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

PackOp PackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ArrayRef<int64_t> innerDimsPos, ArrayRef<OpFoldResult> innerTiles, std::optional<Value> paddingValue, ArrayRef<int64_t> outerDimsPerm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(innerDimsPos)>(innerDimsPos), std::forward<decltype(innerTiles)>(innerTiles), std::forward<decltype(paddingValue)>(paddingValue), std::forward<decltype(outerDimsPerm)>(outerDimsPerm));
  auto __res__ = ::llvm::dyn_cast<PackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PackOp PackOp::create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ArrayRef<int64_t> innerDimsPos, ArrayRef<OpFoldResult> innerTiles, std::optional<Value> paddingValue, ArrayRef<int64_t> outerDimsPerm) {
  return create(builder, builder.getLoc(), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(innerDimsPos)>(innerDimsPos), std::forward<decltype(innerTiles)>(innerTiles), std::forward<decltype(paddingValue)>(paddingValue), std::forward<decltype(outerDimsPerm)>(outerDimsPerm));
}

void PackOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  odsState.addOperands(source);
  odsState.addOperands(dest);
  if (padding_value)
    odsState.addOperands(padding_value);
  odsState.addOperands(inner_tiles);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, (padding_value ? 1 : 0), static_cast<int32_t>(inner_tiles.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  if (outer_dims_perm) {
    odsState.getOrAddProperties<Properties>().outer_dims_perm = outer_dims_perm;
  }
  odsState.getOrAddProperties<Properties>().inner_dims_pos = inner_dims_pos;
  odsState.getOrAddProperties<Properties>().static_inner_tiles = static_inner_tiles;
  if (result)
    odsState.addTypes(result);
}

PackOp PackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(padding_value)>(padding_value), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
  auto __res__ = ::llvm::dyn_cast<PackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PackOp PackOp::create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(padding_value)>(padding_value), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
}

void PackOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  odsState.addOperands(source);
  odsState.addOperands(dest);
  if (padding_value)
    odsState.addOperands(padding_value);
  odsState.addOperands(inner_tiles);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, (padding_value ? 1 : 0), static_cast<int32_t>(inner_tiles.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  if (outer_dims_perm) {
    odsState.getOrAddProperties<Properties>().outer_dims_perm = outer_dims_perm;
  }
  odsState.getOrAddProperties<Properties>().inner_dims_pos = inner_dims_pos;
  odsState.getOrAddProperties<Properties>().static_inner_tiles = static_inner_tiles;
  odsState.addTypes(resultTypes);
}

PackOp PackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(padding_value)>(padding_value), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
  auto __res__ = ::llvm::dyn_cast<PackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PackOp PackOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(padding_value)>(padding_value), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
}

void PackOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  odsState.addOperands(source);
  odsState.addOperands(dest);
  if (padding_value)
    odsState.addOperands(padding_value);
  odsState.addOperands(inner_tiles);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, (padding_value ? 1 : 0), static_cast<int32_t>(inner_tiles.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().outer_dims_perm = odsBuilder.getDenseI64ArrayAttr(outer_dims_perm);
  odsState.getOrAddProperties<Properties>().inner_dims_pos = odsBuilder.getDenseI64ArrayAttr(inner_dims_pos);
  odsState.getOrAddProperties<Properties>().static_inner_tiles = odsBuilder.getDenseI64ArrayAttr(static_inner_tiles);
  if (result)
    odsState.addTypes(result);
}

PackOp PackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(padding_value)>(padding_value), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
  auto __res__ = ::llvm::dyn_cast<PackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PackOp PackOp::create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(padding_value)>(padding_value), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
}

void PackOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  odsState.addOperands(source);
  odsState.addOperands(dest);
  if (padding_value)
    odsState.addOperands(padding_value);
  odsState.addOperands(inner_tiles);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, (padding_value ? 1 : 0), static_cast<int32_t>(inner_tiles.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().outer_dims_perm = odsBuilder.getDenseI64ArrayAttr(outer_dims_perm);
  odsState.getOrAddProperties<Properties>().inner_dims_pos = odsBuilder.getDenseI64ArrayAttr(inner_dims_pos);
  odsState.getOrAddProperties<Properties>().static_inner_tiles = odsBuilder.getDenseI64ArrayAttr(static_inner_tiles);
  odsState.addTypes(resultTypes);
}

PackOp PackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(padding_value)>(padding_value), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
  auto __res__ = ::llvm::dyn_cast<PackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PackOp PackOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(padding_value)>(padding_value), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
}

void PackOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<PackOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

PackOp PackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PackOp PackOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PackOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

PackOp PackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PackOp PackOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PackOp::verifyInvariantsImpl() {
  auto tblgen_inner_dims_pos = getProperties().inner_dims_pos; (void)tblgen_inner_dims_pos;
  if (!tblgen_inner_dims_pos) return emitOpError("requires attribute 'inner_dims_pos'");
  auto tblgen_outer_dims_perm = getProperties().outer_dims_perm; (void)tblgen_outer_dims_perm;
  auto tblgen_static_inner_tiles = getProperties().static_inner_tiles; (void)tblgen_static_inner_tiles;
  if (!tblgen_static_inner_tiles) return emitOpError("requires attribute 'static_inner_tiles'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(*this, tblgen_outer_dims_perm, "outer_dims_perm")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(*this, tblgen_inner_dims_pos, "inner_dims_pos")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(*this, tblgen_static_inner_tiles, "static_inner_tiles")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LinalgRelayoutOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LinalgRelayoutOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    if (valueGroup2.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup2.size();
    }

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LinalgRelayoutOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LinalgRelayoutOps3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    if (valueGroup0.size() > 1) {
      return emitOpError("result group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup0.size();
    }

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LinalgRelayoutOps4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((!getDest() || !getResult() || std::equal_to<>()((*this->getODSOperands(1).begin()).getType(), (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that result type matches type of dest");
  return ::mlir::success();
}

::llvm::LogicalResult PackOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void PackOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult PackOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.outer_dims_perm;
    auto outer_dims_permAttrName = ::mlir::StringAttr::get(ctx, "outer_dims_perm");
    auto attr = dict.get(outer_dims_permAttrName);
    usedKeys.insert(outer_dims_permAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for outer_dims_perm in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `outer_dims_perm` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.inner_dims_pos;
    auto inner_dims_posAttrName = ::mlir::StringAttr::get(ctx, "inner_dims_pos");
    auto attr = dict.get(inner_dims_posAttrName);
    usedKeys.insert(inner_dims_posAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for inner_dims_pos in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_dims_pos` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.static_inner_tiles;
    auto static_inner_tilesAttrName = ::mlir::StringAttr::get(ctx, "static_inner_tiles");
    auto attr = dict.get(static_inner_tilesAttrName);
    usedKeys.insert(static_inner_tilesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for static_inner_tiles in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `static_inner_tiles` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}


} // namespace mlir::linalg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::linalg::PackOp)

namespace mlir::linalg {


//===----------------------------------------------------------------------===//
// ::mlir::linalg::UnPackOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UnPackOpGenericAdaptorBase::UnPackOpGenericAdaptorBase(UnPackOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> UnPackOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 2) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::DenseI64ArrayAttr UnPackOpGenericAdaptorBase::getOuterDimsPermAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().outer_dims_perm);
  if (!attr)
    attr = ::mlir::Builder(odsAttrs.getContext()).getDenseI64ArrayAttr({});
  return attr;
}

::llvm::ArrayRef<int64_t> UnPackOpGenericAdaptorBase::getOuterDimsPerm() {
  auto attr = getOuterDimsPermAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getDenseI64ArrayAttr({});
  return attr;
}

::llvm::ArrayRef<int64_t> UnPackOpGenericAdaptorBase::getInnerDimsPos() {
  auto attr = getInnerDimsPosAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> UnPackOpGenericAdaptorBase::getStaticInnerTiles() {
  auto attr = getStaticInnerTilesAttr();
  return attr;
}


} // namespace detail
UnPackOpAdaptor::UnPackOpAdaptor(UnPackOp op) : UnPackOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UnPackOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_dims_pos = getProperties().inner_dims_pos; (void)tblgen_inner_dims_pos;
  if (!tblgen_inner_dims_pos) return emitError(loc, "'linalg.unpack' op requires attribute 'inner_dims_pos'");
  auto tblgen_outer_dims_perm = getProperties().outer_dims_perm; (void)tblgen_outer_dims_perm;
  auto tblgen_static_inner_tiles = getProperties().static_inner_tiles; (void)tblgen_static_inner_tiles;
  if (!tblgen_static_inner_tiles) return emitError(loc, "'linalg.unpack' op requires attribute 'static_inner_tiles'");

  if (tblgen_outer_dims_perm && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_outer_dims_perm))))
    return emitError(loc, "'linalg.unpack' op attribute 'outer_dims_perm' failed to satisfy constraint: i64 dense array attribute");

  if (tblgen_inner_dims_pos && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_inner_dims_pos))))
    return emitError(loc, "'linalg.unpack' op attribute 'inner_dims_pos' failed to satisfy constraint: i64 dense array attribute");

  if (tblgen_static_inner_tiles && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_static_inner_tiles))))
    return emitError(loc, "'linalg.unpack' op attribute 'static_inner_tiles' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> UnPackOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 2) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange UnPackOp::getInnerTilesMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> UnPackOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult UnPackOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_dims_pos;
       auto attr = dict.get("inner_dims_pos");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_dims_pos` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.outer_dims_perm;
       auto attr = dict.get("outer_dims_perm");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `outer_dims_perm` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.static_inner_tiles;
       auto attr = dict.get("static_inner_tiles");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `static_inner_tiles` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute UnPackOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_dims_pos;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_dims_pos",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.outer_dims_perm;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("outer_dims_perm",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.static_inner_tiles;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("static_inner_tiles",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UnPackOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_dims_pos.getAsOpaquePointer()), 
    llvm::hash_value(prop.outer_dims_perm.getAsOpaquePointer()), 
    llvm::hash_value(prop.static_inner_tiles.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> UnPackOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_dims_pos")
      return prop.inner_dims_pos;

    if (name == "outer_dims_perm")
      return prop.outer_dims_perm;

    if (name == "static_inner_tiles")
      return prop.static_inner_tiles;
  return std::nullopt;
}

void UnPackOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_dims_pos") {
       prop.inner_dims_pos = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_dims_pos)>>(value);
       return;
    }

    if (name == "outer_dims_perm") {
       prop.outer_dims_perm = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.outer_dims_perm)>>(value);
       return;
    }

    if (name == "static_inner_tiles") {
       prop.static_inner_tiles = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.static_inner_tiles)>>(value);
       return;
    }
}

void UnPackOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_dims_pos) attrs.append("inner_dims_pos", prop.inner_dims_pos);

    if (prop.outer_dims_perm) attrs.append("outer_dims_perm", prop.outer_dims_perm);

    if (prop.static_inner_tiles) attrs.append("static_inner_tiles", prop.static_inner_tiles);
}

::llvm::LogicalResult UnPackOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerDimsPosAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(attr, "inner_dims_pos", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getOuterDimsPermAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(attr, "outer_dims_perm", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStaticInnerTilesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(attr, "static_inner_tiles", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult UnPackOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_dims_pos)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.outer_dims_perm)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.static_inner_tiles)))
    return ::mlir::failure();
  return ::mlir::success();
}

void UnPackOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_dims_pos);

  writer.writeOptionalAttribute(prop.outer_dims_perm);
  writer.writeAttribute(prop.static_inner_tiles);
}

::llvm::ArrayRef<int64_t> UnPackOp::getOuterDimsPerm() {
  auto attr = getOuterDimsPermAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr({});
  return attr;
}

::llvm::ArrayRef<int64_t> UnPackOp::getInnerDimsPos() {
  auto attr = getInnerDimsPosAttr();
  return attr;
}

::llvm::ArrayRef<int64_t> UnPackOp::getStaticInnerTiles() {
  auto attr = getStaticInnerTilesAttr();
  return attr;
}

void UnPackOp::setOuterDimsPerm(::std::optional<::llvm::ArrayRef<int64_t>> attrValue) {
    auto &odsProp = getProperties().outer_dims_perm;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(*attrValue);
    else
      odsProp = nullptr;
}

void UnPackOp::setInnerDimsPos(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().inner_dims_pos = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void UnPackOp::setStaticInnerTiles(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().static_inner_tiles = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

UnPackOp UnPackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ArrayRef<int64_t> innerDimsPos, ArrayRef<OpFoldResult> innerTiles, ArrayRef<int64_t> outerDimsPerm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(innerDimsPos)>(innerDimsPos), std::forward<decltype(innerTiles)>(innerTiles), std::forward<decltype(outerDimsPerm)>(outerDimsPerm));
  auto __res__ = ::llvm::dyn_cast<UnPackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnPackOp UnPackOp::create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ArrayRef<int64_t> innerDimsPos, ArrayRef<OpFoldResult> innerTiles, ArrayRef<int64_t> outerDimsPerm) {
  return create(builder, builder.getLoc(), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(innerDimsPos)>(innerDimsPos), std::forward<decltype(innerTiles)>(innerTiles), std::forward<decltype(outerDimsPerm)>(outerDimsPerm));
}

void UnPackOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  odsState.addOperands(source);
  odsState.addOperands(dest);
  odsState.addOperands(inner_tiles);
  if (outer_dims_perm) {
    odsState.getOrAddProperties<Properties>().outer_dims_perm = outer_dims_perm;
  }
  odsState.getOrAddProperties<Properties>().inner_dims_pos = inner_dims_pos;
  odsState.getOrAddProperties<Properties>().static_inner_tiles = static_inner_tiles;
  if (result)
    odsState.addTypes(result);
}

UnPackOp UnPackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
  auto __res__ = ::llvm::dyn_cast<UnPackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnPackOp UnPackOp::create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
}

void UnPackOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  odsState.addOperands(source);
  odsState.addOperands(dest);
  odsState.addOperands(inner_tiles);
  if (outer_dims_perm) {
    odsState.getOrAddProperties<Properties>().outer_dims_perm = outer_dims_perm;
  }
  odsState.getOrAddProperties<Properties>().inner_dims_pos = inner_dims_pos;
  odsState.getOrAddProperties<Properties>().static_inner_tiles = static_inner_tiles;
  odsState.addTypes(resultTypes);
}

UnPackOp UnPackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
  auto __res__ = ::llvm::dyn_cast<UnPackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnPackOp UnPackOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
}

void UnPackOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  odsState.addOperands(source);
  odsState.addOperands(dest);
  odsState.addOperands(inner_tiles);
  odsState.getOrAddProperties<Properties>().outer_dims_perm = odsBuilder.getDenseI64ArrayAttr(outer_dims_perm);
  odsState.getOrAddProperties<Properties>().inner_dims_pos = odsBuilder.getDenseI64ArrayAttr(inner_dims_pos);
  odsState.getOrAddProperties<Properties>().static_inner_tiles = odsBuilder.getDenseI64ArrayAttr(static_inner_tiles);
  if (result)
    odsState.addTypes(result);
}

UnPackOp UnPackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
  auto __res__ = ::llvm::dyn_cast<UnPackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnPackOp UnPackOp::create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
}

void UnPackOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  odsState.addOperands(source);
  odsState.addOperands(dest);
  odsState.addOperands(inner_tiles);
  odsState.getOrAddProperties<Properties>().outer_dims_perm = odsBuilder.getDenseI64ArrayAttr(outer_dims_perm);
  odsState.getOrAddProperties<Properties>().inner_dims_pos = odsBuilder.getDenseI64ArrayAttr(inner_dims_pos);
  odsState.getOrAddProperties<Properties>().static_inner_tiles = odsBuilder.getDenseI64ArrayAttr(static_inner_tiles);
  odsState.addTypes(resultTypes);
}

UnPackOp UnPackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
  auto __res__ = ::llvm::dyn_cast<UnPackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnPackOp UnPackOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(outer_dims_perm)>(outer_dims_perm), std::forward<decltype(inner_dims_pos)>(inner_dims_pos), std::forward<decltype(inner_tiles)>(inner_tiles), std::forward<decltype(static_inner_tiles)>(static_inner_tiles));
}

void UnPackOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<UnPackOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

UnPackOp UnPackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnPackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnPackOp UnPackOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnPackOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

UnPackOp UnPackOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnPackOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnPackOp UnPackOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult UnPackOp::verifyInvariantsImpl() {
  auto tblgen_inner_dims_pos = getProperties().inner_dims_pos; (void)tblgen_inner_dims_pos;
  if (!tblgen_inner_dims_pos) return emitOpError("requires attribute 'inner_dims_pos'");
  auto tblgen_outer_dims_perm = getProperties().outer_dims_perm; (void)tblgen_outer_dims_perm;
  auto tblgen_static_inner_tiles = getProperties().static_inner_tiles; (void)tblgen_static_inner_tiles;
  if (!tblgen_static_inner_tiles) return emitOpError("requires attribute 'static_inner_tiles'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(*this, tblgen_outer_dims_perm, "outer_dims_perm")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(*this, tblgen_inner_dims_pos, "inner_dims_pos")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_LinalgRelayoutOps1(*this, tblgen_static_inner_tiles, "static_inner_tiles")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LinalgRelayoutOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LinalgRelayoutOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LinalgRelayoutOps3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    if (valueGroup0.size() > 1) {
      return emitOpError("result group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup0.size();
    }

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LinalgRelayoutOps4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((!getDest() || !getResult() || std::equal_to<>()((*this->getODSOperands(1).begin()).getType(), (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that result type matches type of dest");
  return ::mlir::success();
}

::llvm::LogicalResult UnPackOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void UnPackOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult UnPackOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.outer_dims_perm;
    auto outer_dims_permAttrName = ::mlir::StringAttr::get(ctx, "outer_dims_perm");
    auto attr = dict.get(outer_dims_permAttrName);
    usedKeys.insert(outer_dims_permAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for outer_dims_perm in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `outer_dims_perm` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.inner_dims_pos;
    auto inner_dims_posAttrName = ::mlir::StringAttr::get(ctx, "inner_dims_pos");
    auto attr = dict.get(inner_dims_posAttrName);
    usedKeys.insert(inner_dims_posAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for inner_dims_pos in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_dims_pos` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.static_inner_tiles;
    auto static_inner_tilesAttrName = ::mlir::StringAttr::get(ctx, "static_inner_tiles");
    auto attr = dict.get(static_inner_tilesAttrName);
    usedKeys.insert(static_inner_tilesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for static_inner_tiles in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `static_inner_tiles` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}


} // namespace mlir::linalg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::linalg::UnPackOp)


#endif // GET_OP_CLASSES

