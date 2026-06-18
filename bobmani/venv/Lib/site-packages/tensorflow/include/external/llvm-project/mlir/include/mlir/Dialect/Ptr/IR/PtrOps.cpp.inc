/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: PtrOps.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::mlir::ptr::ConstantOp,
::mlir::ptr::FromPtrOp,
::mlir::ptr::GatherOp,
::mlir::ptr::GetMetadataOp,
::mlir::ptr::LoadOp,
::mlir::ptr::MaskedLoadOp,
::mlir::ptr::MaskedStoreOp,
::mlir::ptr::PtrAddOp,
::mlir::ptr::PtrDiffOp,
::mlir::ptr::ScatterOp,
::mlir::ptr::StoreOp,
::mlir::ptr::ToPtrOp,
::mlir::ptr::TypeOffsetOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_PtrOps1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::ptr::PtrType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be pointer type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_PtrOps2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::ptr::PtrMetadataType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be Pointer metadata type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_PtrOps3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::PtrLikeTypeInterface>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be PtrLikeTypeInterface instance, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_PtrOps4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((type.hasTrait<::mlir::ValueSemantics>())) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank()
                         == 1)))) && ([](::mlir::Type elementType) { return (::llvm::isa<::mlir::ptr::PtrType>(elementType)); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A shaped type with value semantics and rank. of pointer type values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_PtrOps5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((type.hasTrait<::mlir::ValueSemantics>())) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank()
                         == 1)))) && ([](::mlir::Type elementType) { return (elementType.isSignlessInteger(1)); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A shaped type with value semantics and rank. of 1-bit signless integer values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_PtrOps6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((type.hasTrait<::mlir::ValueSemantics>())) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank()
                         == 1)))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A shaped type with value semantics and rank. of any type values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_PtrOps7(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((true))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_PtrOps8(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((((type.hasTrait<::mlir::ValueSemantics>())) && ((::llvm::cast<::mlir::ShapedType>(type).hasRank()))) && ([](::mlir::Type elementType) { return (::llvm::isa<::mlir::ptr::PtrType>(elementType)); }(::llvm::cast<::mlir::ShapedType>(type).getElementType()))) || ((::llvm::isa<::mlir::ptr::PtrType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A shaped type with value semantics and rank. of pointer type values or pointer type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_PtrOps9(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((((type.hasTrait<::mlir::ValueSemantics>())) && ((::llvm::cast<::mlir::ShapedType>(type).hasRank()))) && ([](::mlir::Type elementType) { return (elementType.isSignlessIntOrIndex()); }(::llvm::cast<::mlir::ShapedType>(type).getElementType()))) || ((type.isSignlessIntOrIndex())))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A shaped type with value semantics and rank. of signless integer or index values or signless integer or index, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_PtrOps10(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessIntOrIndex()))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be signless integer or index, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_PtrOps1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::TypedAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: TypedAttr instance";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_PtrOps1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_PtrOps1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_PtrOps2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_PtrOps2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_PtrOps2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_PtrOps3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<::mlir::Type>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && ((true))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: any type attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_PtrOps3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_PtrOps3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

  static ::llvm::LogicalResult __mlir_ods_local_prop_constraint_PtrOps1(
      ::mlir::ptr::AtomicOrdering prop, ::llvm::StringRef propName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    if (!(((prop == ::mlir::ptr::AtomicOrdering::not_atomic)) || ((prop == ::mlir::ptr::AtomicOrdering::unordered)) || ((prop == ::mlir::ptr::AtomicOrdering::monotonic)) || ((prop == ::mlir::ptr::AtomicOrdering::acquire)) || ((prop == ::mlir::ptr::AtomicOrdering::release)) || ((prop == ::mlir::ptr::AtomicOrdering::acq_rel)) || ((prop == ::mlir::ptr::AtomicOrdering::seq_cst))))
      return emitError() << "property '" << propName
          << "' failed to satisfy constraint: Atomic ordering for LLVM's memory model";
    return ::mlir::success();
  }
  static ::llvm::LogicalResult __mlir_ods_local_prop_constraint_PtrOps1(
      ::mlir::Operation *op, ::mlir::ptr::AtomicOrdering prop, ::llvm::StringRef propName) {
    return __mlir_ods_local_prop_constraint_PtrOps1(prop, propName, [op]() {
      return op->emitOpError();
    });
  }
  
  static ::llvm::LogicalResult __mlir_ods_local_prop_constraint_PtrOps2(
      ::mlir::ptr::PtrAddFlags prop, ::llvm::StringRef propName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    if (!(((prop == ::mlir::ptr::PtrAddFlags::none)) || ((prop == ::mlir::ptr::PtrAddFlags::nusw)) || ((prop == ::mlir::ptr::PtrAddFlags::nuw)) || ((prop == ::mlir::ptr::PtrAddFlags::inbounds))))
      return emitError() << "property '" << propName
          << "' failed to satisfy constraint: Pointer add flags";
    return ::mlir::success();
  }
  static ::llvm::LogicalResult __mlir_ods_local_prop_constraint_PtrOps2(
      ::mlir::Operation *op, ::mlir::ptr::PtrAddFlags prop, ::llvm::StringRef propName) {
    return __mlir_ods_local_prop_constraint_PtrOps2(prop, propName, [op]() {
      return op->emitOpError();
    });
  }
  
  static ::llvm::LogicalResult __mlir_ods_local_prop_constraint_PtrOps3(
      ::mlir::ptr::PtrDiffFlags prop, ::llvm::StringRef propName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    if (!(((static_cast<uint8_t>(prop) & ~3) == 0)))
      return emitError() << "property '" << propName
          << "' failed to satisfy constraint: Pointer difference flags";
    return ::mlir::success();
  }
  static ::llvm::LogicalResult __mlir_ods_local_prop_constraint_PtrOps3(
      ::mlir::Operation *op, ::mlir::ptr::PtrDiffFlags prop, ::llvm::StringRef propName) {
    return __mlir_ods_local_prop_constraint_PtrOps3(prop, propName, [op]() {
      return op->emitOpError();
    });
  }
  namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::ConstantOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ConstantOpGenericAdaptorBase::ConstantOpGenericAdaptorBase(ConstantOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::TypedAttr ConstantOpGenericAdaptorBase::getValue() {
  auto attr = getValueAttr();
  return attr;
}


} // namespace detail
ConstantOpAdaptor::ConstantOpAdaptor(ConstantOp op) : ConstantOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ConstantOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitError(loc, "'ptr.constant' op requires attribute 'value'");

  if (tblgen_value && !((::llvm::isa<::mlir::TypedAttr>(tblgen_value))))
    return emitError(loc, "'ptr.constant' op attribute 'value' failed to satisfy constraint: TypedAttr instance");
  return ::mlir::success();
}

::llvm::LogicalResult ConstantOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.value;
       auto attr = dict.get("value");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `value` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ConstantOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.value;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("value",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ConstantOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.value.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ConstantOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "value")
      return prop.value;
  return std::nullopt;
}

void ConstantOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "value") {
       prop.value = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.value)>>(value);
       return;
    }
}

void ConstantOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.value) attrs.append("value", prop.value);
}

::llvm::LogicalResult ConstantOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getValueAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_PtrOps1(attr, "value", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ConstantOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.value)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ConstantOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.value);
}

::mlir::TypedAttr ConstantOp::getValue() {
  auto attr = getValueAttr();
  return attr;
}

void ConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::TypedAttr value) {
  odsState.getOrAddProperties<Properties>().value = value;
  odsState.addTypes(result);
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::TypedAttr value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::TypedAttr value) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
}

void ConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypedAttr value) {
  odsState.getOrAddProperties<Properties>().value = value;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ConstantOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypedAttr value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypedAttr value) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value));
}

void ConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::TypedAttr value) {
  odsState.getOrAddProperties<Properties>().value = value;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::TypedAttr value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::TypedAttr value) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
}

void ConstantOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ConstantOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<ConstantOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ConstantOp::inferReturnTypes(odsBuilder.getContext(),
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

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ConstantOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ConstantOp::inferReturnTypes(odsBuilder.getContext(),
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

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ConstantOp::verifyInvariantsImpl() {
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitOpError("requires attribute 'value'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_PtrOps1(*this, tblgen_value, "value")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!(((getValue().getType()) == ((*this->getODSResults(0).begin()).getType()) && ((*this->getODSResults(0).begin()).getType()) == (getValue().getType()))))
    return emitOpError("failed to verify that all of {value, result} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult ConstantOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ConstantOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::TypedAttr odsInferredTypeAttr0 = (properties ? properties.as<Properties *>()->value : ::llvm::dyn_cast_or_null<::mlir::TypedAttr>(attributes.get("value")));
  if (!odsInferredTypeAttr0) return ::mlir::failure();
  ::mlir::Type odsInferredType0 = odsInferredTypeAttr0.getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ConstantOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::TypedAttr valueAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  if (parser.parseCustomAttributeWithFallback(valueAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (valueAttr) result.getOrAddProperties<ConstantOp::Properties>().value = valueAttr;
  result.addTypes(valueAttr.getType());
  return ::mlir::success();
}

void ConstantOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("value");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getValueAttr());
}

void ConstantOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::ConstantOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::FromPtrOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FromPtrOpGenericAdaptorBase::FromPtrOpGenericAdaptorBase(FromPtrOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> FromPtrOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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


} // namespace detail
FromPtrOpAdaptor::FromPtrOpAdaptor(FromPtrOp op) : FromPtrOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FromPtrOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> FromPtrOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange FromPtrOp::getMetadataMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult FromPtrOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute FromPtrOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FromPtrOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> FromPtrOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void FromPtrOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void FromPtrOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult FromPtrOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void FromPtrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value ptr, /*optional*/::mlir::Value metadata) {
  odsState.addOperands(ptr);
  if (metadata)
    odsState.addOperands(metadata);
  odsState.addTypes(result);
}

FromPtrOp FromPtrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value ptr, /*optional*/::mlir::Value metadata) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(ptr)>(ptr), std::forward<decltype(metadata)>(metadata));
  auto __res__ = ::llvm::dyn_cast<FromPtrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromPtrOp FromPtrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value ptr, /*optional*/::mlir::Value metadata) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(ptr)>(ptr), std::forward<decltype(metadata)>(metadata));
}

void FromPtrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/::mlir::Value metadata) {
  odsState.addOperands(ptr);
  if (metadata)
    odsState.addOperands(metadata);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FromPtrOp FromPtrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/::mlir::Value metadata) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptr)>(ptr), std::forward<decltype(metadata)>(metadata));
  auto __res__ = ::llvm::dyn_cast<FromPtrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromPtrOp FromPtrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/::mlir::Value metadata) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptr)>(ptr), std::forward<decltype(metadata)>(metadata));
}

void FromPtrOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FromPtrOp FromPtrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FromPtrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromPtrOp FromPtrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FromPtrOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FromPtrOp FromPtrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FromPtrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromPtrOp FromPtrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FromPtrOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((!getResult() || !getMetadata() || std::equal_to<>()(PtrMetadataType::get(cast<PtrLikeTypeInterface>((*this->getODSResults(0).begin()).getType())), (*this->getODSOperands(1).begin()).getType()))))
    return emitOpError("failed to verify that metadata type");
  return ::mlir::success();
}

::llvm::LogicalResult FromPtrOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult FromPtrOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand ptrRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> ptrOperands(&ptrRawOperand, 1);  ::llvm::SMLoc ptrOperandsLoc;
  (void)ptrOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> metadataOperands;
  ::llvm::SMLoc metadataOperandsLoc;
  (void)metadataOperandsLoc;
  ::mlir::Type ptrRawType{};
  ::llvm::ArrayRef<::mlir::Type> ptrTypes(&ptrRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  ptrOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(ptrRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("metadata"))) {

  {
    metadataOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      metadataOperands.push_back(operand);
    }
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
    ::mlir::ptr::PtrType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    ptrRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::PtrLikeTypeInterface type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  for (::mlir::Type type : resultTypes) {
    (void)type;
    if (!((::llvm::isa<::mlir::PtrLikeTypeInterface>(type)))) {
      return parser.emitError(parser.getNameLoc()) << "'result' must be PtrLikeTypeInterface instance, but got " << type;
    }
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(ptrOperands, ptrTypes, ptrOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(metadataOperands, PtrMetadataType::get(cast<PtrLikeTypeInterface>(resultTypes[0])), metadataOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void FromPtrOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getPtr();
  if (getMetadata()) {
    _odsPrinter << ' ' << "metadata";
    _odsPrinter << ' ';
    if (::mlir::Value value = getMetadata())
      _odsPrinter << value;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getPtr().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::ptr::PtrType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::PtrLikeTypeInterface>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void FromPtrOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::FromPtrOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::GatherOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GatherOpGenericAdaptorBase::GatherOpGenericAdaptorBase(GatherOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
GatherOpAdaptor::GatherOpAdaptor(GatherOp op) : GatherOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GatherOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult GatherOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
    {

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        auto arrayAttr = ::llvm::dyn_cast<::mlir::ArrayAttr>(propAttr);
    if (!arrayAttr)
      return emitError() << "expected optional properties to materialize as arrays";
    if (arrayAttr.size() > 1)
      return emitError() << "expected optional properties to become 0- or 1-element arrays";
    if (arrayAttr.empty()) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    ::mlir::Attribute presentAttr = arrayAttr[0];
    int64_t presentVal;
    auto presentRes = [&](::mlir::Attribute propAttr, int64_t& propStorage) -> ::mlir::LogicalResult {

    return convertFromAttribute(propStorage, propAttr, emitError);

    }(presentAttr, presentVal);
    if (::mlir::failed(presentRes))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
      };
         auto attr = dict.get("alignment");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.alignment, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.alignment = std::nullopt;
      }
  }
  return ::mlir::success();
}

::mlir::Attribute GatherOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.alignment;
      auto attr = [&]() -> ::mlir::Attribute {
        if (!propStorage.has_value()) {
      return ::mlir::ArrayAttr::get(ctx, {});
    }
    auto attr = [&]() -> ::mlir::Attribute {

    return convertToAttribute(ctx, (*(propStorage)));

    }();
    return ::mlir::ArrayAttr::get(ctx, {attr});
      }();
      attrs.push_back(odsBuilder.getNamedAttr("alignment", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GatherOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    hash_value(prop.alignment));
}

std::optional<mlir::Attribute> GatherOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void GatherOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void GatherOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult GatherOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

::llvm::LogicalResult GatherOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  {
    auto &propStorage = prop.alignment;
    auto readProp = [&]() {
      bool isPresent = false;
    if (::mlir::failed(reader.readBool(isPresent)))
      return ::mlir::failure();
    if (!isPresent) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto presentResult = [&](int64_t& propStorage) -> ::mlir::LogicalResult {

    uint64_t val;
    if (failed(reader.readVarInt(val)))
      return ::mlir::failure();
    propStorage = val;
  ;
      return ::mlir::success();
    }(presentVal);
    if (::mlir::failed(presentResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void GatherOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  {
    auto &propStorage = prop.alignment;
    writer.writeOwnedBool(propStorage.has_value());
    if (propStorage.has_value()) {

    writer.writeVarInt((*(propStorage)));

    };
  }
}

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value ptrs, Value mask, Value passthrough, unsigned alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultType)>(resultType), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value ptrs, Value mask, Value passthrough, unsigned alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultType)>(resultType), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
}

void GatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  odsState.addOperands(ptrs);
  odsState.addOperands(mask);
  odsState.addOperands(passthrough);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
  odsState.addTypes(result);
}

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
}

void GatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  odsState.addOperands(ptrs);
  odsState.addOperands(mask);
  odsState.addOperands(passthrough);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(GatherOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
}

void GatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  odsState.addOperands(ptrs);
  odsState.addOperands(mask);
  odsState.addOperands(passthrough);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
}

void GatherOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
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

void GatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<GatherOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(GatherOp::inferReturnTypes(odsBuilder.getContext(),
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

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GatherOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
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

void GatherOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(GatherOp::inferReturnTypes(odsBuilder.getContext(),
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

GatherOp GatherOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GatherOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GatherOp GatherOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GatherOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(
      ::llvm::cast<ShapedType>((*this->getODSResults(0).begin()).getType()).clone(
        IntegerType::get((*this->getODSResults(0).begin()).getType().getContext(), 1))
    , (*this->getODSOperands(1).begin()).getType()))))
    return emitOpError("failed to verify that result and mask must be compatible");
  if (!((((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(2).begin()).getType()) && ((*this->getODSOperands(2).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {result, passthrough} have same type");
  if (!(((::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()) && (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSResults(0).begin()).getType()).getShape()))))
    return emitOpError("failed to verify that all of {result, ptrs} have same shape");
  if (!((((*this->getODSResults(0).begin()).getType().getTypeID()) == ((*this->getODSOperands(0).begin()).getType().getTypeID()) && ((*this->getODSOperands(0).begin()).getType().getTypeID()) == ((*this->getODSResults(0).begin()).getType().getTypeID()))))
    return emitOpError("failed to verify that all of {result, ptrs} have same type IDs");
  return ::mlir::success();
}

::llvm::LogicalResult GatherOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult GatherOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 2)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[2].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult GatherOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand ptrsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> ptrsOperands(&ptrsRawOperand, 1);  ::llvm::SMLoc ptrsOperandsLoc;
  (void)ptrsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand maskRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> maskOperands(&maskRawOperand, 1);  ::llvm::SMLoc maskOperandsLoc;
  (void)maskOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand passthroughRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> passthroughOperands(&passthroughRawOperand, 1);  ::llvm::SMLoc passthroughOperandsLoc;
  (void)passthroughOperandsLoc;
  ::mlir::Type ptrsRawType{};
  ::llvm::ArrayRef<::mlir::Type> ptrsTypes(&ptrsRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  ptrsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(ptrsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  maskOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(maskRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  passthroughOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(passthroughRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("alignment"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  auto alignmentPropLoc = parser.getCurrentLocation();
  auto alignmentPropParseResult = [&](auto& propStorage) -> ::mlir::ParseResult {
    if (::mlir::succeeded(parser.parseOptionalKeyword("none"))) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto delegParseResult = [&](int64_t& propStorage) -> ::mlir::OptionalParseResult {

    return parser.parseOptionalInteger(propStorage);

        return ::mlir::success();
    }(presentVal);
    if (!delegParseResult.has_value()) {

    return ::mlir::failure();

    }
    if (delegParseResult.has_value() && ::mlir::failed(*delegParseResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
    return ::mlir::success();
  }(result.getOrAddProperties<GatherOp::Properties>().alignment);
  if (failed(alignmentPropParseResult)) {
    return parser.emitError(alignmentPropLoc, "invalid value for property alignment, expected optional int64_t");
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
    ::mlir::ShapedType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    ptrsRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::ShapedType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  for (::mlir::Type type : resultTypes) {
    (void)type;
    if (!((((type.hasTrait<::mlir::ValueSemantics>())) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank()
                         == 1)))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
      return parser.emitError(parser.getNameLoc()) << "'result' must be A shaped type with value semantics and rank. of any type values, but got " << type;
    }
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(ptrsOperands, ptrsTypes, ptrsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(maskOperands, 
      ::llvm::cast<ShapedType>(resultTypes[0]).clone(
        IntegerType::get(resultTypes[0].getContext(), 1))
    , maskOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(passthroughOperands, resultTypes[0], passthroughOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void GatherOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getPtrs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getMask();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getPassthrough();
  if (getAlignment() != std::nullopt) {
    _odsPrinter << ' ' << "alignment";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  [&]() {
        if (!getProperties().alignment.has_value()) {
          _odsPrinter << "none";
          return;
        }
        _odsPrinter.printInteger((*(getProperties().alignment)));
      }();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getPtrs().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::ShapedType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::ShapedType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::GatherOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::GetMetadataOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GetMetadataOpGenericAdaptorBase::GetMetadataOpGenericAdaptorBase(GetMetadataOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
GetMetadataOpAdaptor::GetMetadataOpAdaptor(GetMetadataOp op) : GetMetadataOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GetMetadataOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult GetMetadataOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute GetMetadataOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GetMetadataOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> GetMetadataOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void GetMetadataOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void GetMetadataOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult GetMetadataOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void GetMetadataOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value ptr) {
  odsState.addOperands(ptr);
  odsState.addTypes(result);
}

GetMetadataOp GetMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value ptr) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(ptr)>(ptr));
  auto __res__ = ::llvm::dyn_cast<GetMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetMetadataOp GetMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value ptr) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(ptr)>(ptr));
}

void GetMetadataOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value ptr) {
  odsState.addOperands(ptr);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(GetMetadataOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

GetMetadataOp GetMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value ptr) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(ptr)>(ptr));
  auto __res__ = ::llvm::dyn_cast<GetMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetMetadataOp GetMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value ptr) {
  return create(builder, builder.getLoc(), std::forward<decltype(ptr)>(ptr));
}

void GetMetadataOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptr) {
  odsState.addOperands(ptr);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GetMetadataOp GetMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptr) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptr)>(ptr));
  auto __res__ = ::llvm::dyn_cast<GetMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetMetadataOp GetMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptr) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptr)>(ptr));
}

void GetMetadataOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GetMetadataOp GetMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GetMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetMetadataOp GetMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GetMetadataOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(GetMetadataOp::inferReturnTypes(odsBuilder.getContext(),
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

GetMetadataOp GetMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GetMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetMetadataOp GetMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GetMetadataOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GetMetadataOp GetMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GetMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetMetadataOp GetMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void GetMetadataOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(GetMetadataOp::inferReturnTypes(odsBuilder.getContext(),
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

GetMetadataOp GetMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GetMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetMetadataOp GetMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GetMetadataOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(PtrMetadataType::get(cast<PtrLikeTypeInterface>((*this->getODSOperands(0).begin()).getType())), (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that metadata type");
  return ::mlir::success();
}

::llvm::LogicalResult GetMetadataOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult GetMetadataOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = PtrMetadataType::get(cast<PtrLikeTypeInterface>(operands[0].getType()));
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult GetMetadataOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand ptrRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> ptrOperands(&ptrRawOperand, 1);  ::llvm::SMLoc ptrOperandsLoc;
  (void)ptrOperandsLoc;
  ::mlir::Type ptrRawType{};
  ::llvm::ArrayRef<::mlir::Type> ptrTypes(&ptrRawType, 1);

  ptrOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(ptrRawOperand))
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
    ::mlir::PtrLikeTypeInterface type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    ptrRawType = type;
  }
  for (::mlir::Type type : ptrTypes) {
    (void)type;
    if (!((::llvm::isa<::mlir::PtrLikeTypeInterface>(type)))) {
      return parser.emitError(parser.getNameLoc()) << "'ptr' must be PtrLikeTypeInterface instance, but got " << type;
    }
  }
  result.addTypes(PtrMetadataType::get(cast<PtrLikeTypeInterface>(ptrTypes[0])));
  if (parser.resolveOperands(ptrOperands, ptrTypes, ptrOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void GetMetadataOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getPtr();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getPtr().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::PtrLikeTypeInterface>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void GetMetadataOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::GetMetadataOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::LoadOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LoadOpGenericAdaptorBase::LoadOpGenericAdaptorBase(LoadOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional< ::llvm::StringRef > LoadOpGenericAdaptorBase::getSyncscope() {
  auto attr = getSyncscopeAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
LoadOpAdaptor::LoadOpAdaptor(LoadOp op) : LoadOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LoadOpAdaptor::verify(::mlir::Location loc) {
{

    [[maybe_unused]] ::mlir::ptr::AtomicOrdering tblgen_ordering = this->getOrdering();

    if (!(((tblgen_ordering == ::mlir::ptr::AtomicOrdering::not_atomic)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::unordered)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::monotonic)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::acquire)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::release)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::acq_rel)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::seq_cst))))
      return emitError(loc, "'ptr.load' op property 'ordering' failed to satisfy constraint: Atomic ordering for LLVM's memory model");
}
  auto tblgen_syncscope = getProperties().syncscope; (void)tblgen_syncscope;

  if (tblgen_syncscope && !((::llvm::isa<::mlir::StringAttr>(tblgen_syncscope))))
    return emitError(loc, "'ptr.load' op attribute 'syncscope' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult LoadOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.syncscope;
       auto attr = dict.get("syncscope");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `syncscope` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        auto arrayAttr = ::llvm::dyn_cast<::mlir::ArrayAttr>(propAttr);
    if (!arrayAttr)
      return emitError() << "expected optional properties to materialize as arrays";
    if (arrayAttr.size() > 1)
      return emitError() << "expected optional properties to become 0- or 1-element arrays";
    if (arrayAttr.empty()) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    ::mlir::Attribute presentAttr = arrayAttr[0];
    int64_t presentVal;
    auto presentRes = [&](::mlir::Attribute propAttr, int64_t& propStorage) -> ::mlir::LogicalResult {

    return convertFromAttribute(propStorage, propAttr, emitError);

    }(presentAttr, presentVal);
    if (::mlir::failed(presentRes))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
      };
         auto attr = dict.get("alignment");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.alignment, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.alignment = std::nullopt;
      }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        if (::llvm::isa<::mlir::UnitAttr>(propAttr)) {
      propStorage = true;
      return ::mlir::success();
    }
    if (auto boolAttr = ::llvm::dyn_cast<::mlir::BoolAttr>(propAttr)) {
      propStorage = boolAttr.getValue();
      return ::mlir::success();
    }
    return ::mlir::failure();
      };
         auto attr = dict.get("volatile_");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.volatile_, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.volatile_ = false;
      }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        if (::llvm::isa<::mlir::UnitAttr>(propAttr)) {
      propStorage = true;
      return ::mlir::success();
    }
    if (auto boolAttr = ::llvm::dyn_cast<::mlir::BoolAttr>(propAttr)) {
      propStorage = boolAttr.getValue();
      return ::mlir::success();
    }
    return ::mlir::failure();
      };
         auto attr = dict.get("nontemporal");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.nontemporal, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.nontemporal = false;
      }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        if (::llvm::isa<::mlir::UnitAttr>(propAttr)) {
      propStorage = true;
      return ::mlir::success();
    }
    if (auto boolAttr = ::llvm::dyn_cast<::mlir::BoolAttr>(propAttr)) {
      propStorage = boolAttr.getValue();
      return ::mlir::success();
    }
    return ::mlir::failure();
      };
         auto attr = dict.get("invariant");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.invariant, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.invariant = false;
      }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        if (::llvm::isa<::mlir::UnitAttr>(propAttr)) {
      propStorage = true;
      return ::mlir::success();
    }
    if (auto boolAttr = ::llvm::dyn_cast<::mlir::BoolAttr>(propAttr)) {
      propStorage = boolAttr.getValue();
      return ::mlir::success();
    }
    return ::mlir::failure();
      };
         auto attr = dict.get("invariantGroup");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.invariantGroup, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.invariantGroup = false;
      }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        auto intAttr = ::mlir::dyn_cast_if_present<::mlir::IntegerAttr>(propAttr);
    if (!intAttr) {
      return emitError() << "expected IntegerAttr storage for ::mlir::ptr::AtomicOrdering";
    }
    propStorage = static_cast<::mlir::ptr::AtomicOrdering>(intAttr.getValue().getZExtValue());
    return ::mlir::success();
      };
         auto attr = dict.get("ordering");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.ordering, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.ordering = AtomicOrdering::not_atomic;
      }
  }
  return ::mlir::success();
}

::mlir::Attribute LoadOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.syncscope;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("syncscope",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.alignment;
      auto attr = [&]() -> ::mlir::Attribute {
        if (!propStorage.has_value()) {
      return ::mlir::ArrayAttr::get(ctx, {});
    }
    auto attr = [&]() -> ::mlir::Attribute {

    return convertToAttribute(ctx, (*(propStorage)));

    }();
    return ::mlir::ArrayAttr::get(ctx, {attr});
      }();
      attrs.push_back(odsBuilder.getNamedAttr("alignment", attr));
    }

    {
      const auto &propStorage = prop.volatile_;
      auto attr = [&]() -> ::mlir::Attribute {
        if (propStorage)
      return ::mlir::UnitAttr::get(ctx);
    else
      return ::mlir::BoolAttr::get(ctx, false);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("volatile_", attr));
    }

    {
      const auto &propStorage = prop.nontemporal;
      auto attr = [&]() -> ::mlir::Attribute {
        if (propStorage)
      return ::mlir::UnitAttr::get(ctx);
    else
      return ::mlir::BoolAttr::get(ctx, false);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("nontemporal", attr));
    }

    {
      const auto &propStorage = prop.invariant;
      auto attr = [&]() -> ::mlir::Attribute {
        if (propStorage)
      return ::mlir::UnitAttr::get(ctx);
    else
      return ::mlir::BoolAttr::get(ctx, false);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("invariant", attr));
    }

    {
      const auto &propStorage = prop.invariantGroup;
      auto attr = [&]() -> ::mlir::Attribute {
        if (propStorage)
      return ::mlir::UnitAttr::get(ctx);
    else
      return ::mlir::BoolAttr::get(ctx, false);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("invariantGroup", attr));
    }

    {
      const auto &propStorage = prop.ordering;
      auto attr = [&]() -> ::mlir::Attribute {
        return ::mlir::IntegerAttr::get(::mlir::IntegerType::get(ctx, 32), static_cast<uint32_t>(propStorage));
      }();
      attrs.push_back(odsBuilder.getNamedAttr("ordering", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LoadOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.syncscope.getAsOpaquePointer()), 
    hash_value(prop.alignment), 
    hash_value(prop.volatile_), 
    hash_value(prop.nontemporal), 
    hash_value(prop.invariant), 
    hash_value(prop.invariantGroup), 
    hash_value(prop.ordering));
}

std::optional<mlir::Attribute> LoadOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "syncscope")
      return prop.syncscope;
  return std::nullopt;
}

void LoadOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "syncscope") {
       prop.syncscope = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.syncscope)>>(value);
       return;
    }
}

void LoadOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.syncscope) attrs.append("syncscope", prop.syncscope);
}

::llvm::LogicalResult LoadOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSyncscopeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_PtrOps2(attr, "syncscope", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult LoadOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.syncscope)))
    return ::mlir::failure();

  {
    auto &propStorage = prop.alignment;
    auto readProp = [&]() {
      bool isPresent = false;
    if (::mlir::failed(reader.readBool(isPresent)))
      return ::mlir::failure();
    if (!isPresent) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto presentResult = [&](int64_t& propStorage) -> ::mlir::LogicalResult {

    uint64_t val;
    if (failed(reader.readVarInt(val)))
      return ::mlir::failure();
    propStorage = val;
  ;
      return ::mlir::success();
    }(presentVal);
    if (::mlir::failed(presentResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }

  {
    auto &propStorage = prop.volatile_;
    auto readProp = [&]() {
      if (::mlir::failed(reader.readBool(propStorage)))
      return ::mlir::failure();;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }

  {
    auto &propStorage = prop.nontemporal;
    auto readProp = [&]() {
      if (::mlir::failed(reader.readBool(propStorage)))
      return ::mlir::failure();;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }

  {
    auto &propStorage = prop.invariant;
    auto readProp = [&]() {
      if (::mlir::failed(reader.readBool(propStorage)))
      return ::mlir::failure();;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }

  {
    auto &propStorage = prop.invariantGroup;
    auto readProp = [&]() {
      if (::mlir::failed(reader.readBool(propStorage)))
      return ::mlir::failure();;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }

  {
    auto &propStorage = prop.ordering;
    auto readProp = [&]() {
      uint64_t rawValue;
    if (::mlir::failed(reader.readVarInt(rawValue)))
      return ::mlir::failure();
    if (rawValue > std::numeric_limits<uint32_t>::max())
      return ::mlir::failure();
    propStorage = static_cast<::mlir::ptr::AtomicOrdering>(rawValue);;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void LoadOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.syncscope);

  {
    auto &propStorage = prop.alignment;
    writer.writeOwnedBool(propStorage.has_value());
    if (propStorage.has_value()) {

    writer.writeVarInt((*(propStorage)));

    };
  }

  {
    auto &propStorage = prop.volatile_;
    writer.writeOwnedBool(propStorage);;
  }

  {
    auto &propStorage = prop.nontemporal;
    writer.writeOwnedBool(propStorage);;
  }

  {
    auto &propStorage = prop.invariant;
    writer.writeOwnedBool(propStorage);;
  }

  {
    auto &propStorage = prop.invariantGroup;
    writer.writeOwnedBool(propStorage);;
  }

  {
    auto &propStorage = prop.ordering;
    writer.writeVarInt(static_cast<uint64_t>(propStorage));;
  }
}

::std::optional< ::llvm::StringRef > LoadOp::getSyncscope() {
  auto attr = getSyncscopeAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void LoadOp::setSyncscope(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().syncscope;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

LoadOp LoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Type type, Value ptr, unsigned alignment, bool isVolatile, bool isNonTemporal, bool isInvariant, bool isInvariantGroup, AtomicOrdering ordering, StringRef syncscope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(type)>(type), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(isVolatile)>(isVolatile), std::forward<decltype(isNonTemporal)>(isNonTemporal), std::forward<decltype(isInvariant)>(isInvariant), std::forward<decltype(isInvariantGroup)>(isInvariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
  auto __res__ = ::llvm::dyn_cast<LoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoadOp LoadOp::create(::mlir::ImplicitLocOpBuilder &builder, Type type, Value ptr, unsigned alignment, bool isVolatile, bool isNonTemporal, bool isInvariant, bool isInvariantGroup, AtomicOrdering ordering, StringRef syncscope) {
  return create(builder, builder.getLoc(), std::forward<decltype(type)>(type), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(isVolatile)>(isVolatile), std::forward<decltype(isNonTemporal)>(isNonTemporal), std::forward<decltype(isInvariant)>(isInvariant), std::forward<decltype(isInvariantGroup)>(isInvariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
}

void LoadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  odsState.addOperands(ptr);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
  odsState.getOrAddProperties<Properties>().setVolatile_(volatile_);
  odsState.getOrAddProperties<Properties>().setNontemporal(nontemporal);
  odsState.getOrAddProperties<Properties>().setInvariant(invariant);
  odsState.getOrAddProperties<Properties>().setInvariantGroup(invariantGroup);
  odsState.getOrAddProperties<Properties>().setOrdering(ordering);
  if (syncscope) {
    odsState.getOrAddProperties<Properties>().syncscope = syncscope;
  }
  odsState.addTypes(value);
}

LoadOp LoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(volatile_)>(volatile_), std::forward<decltype(nontemporal)>(nontemporal), std::forward<decltype(invariant)>(invariant), std::forward<decltype(invariantGroup)>(invariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
  auto __res__ = ::llvm::dyn_cast<LoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoadOp LoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(volatile_)>(volatile_), std::forward<decltype(nontemporal)>(nontemporal), std::forward<decltype(invariant)>(invariant), std::forward<decltype(invariantGroup)>(invariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
}

void LoadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  odsState.addOperands(ptr);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
  odsState.getOrAddProperties<Properties>().setVolatile_(volatile_);
  odsState.getOrAddProperties<Properties>().setNontemporal(nontemporal);
  odsState.getOrAddProperties<Properties>().setInvariant(invariant);
  odsState.getOrAddProperties<Properties>().setInvariantGroup(invariantGroup);
  odsState.getOrAddProperties<Properties>().setOrdering(ordering);
  if (syncscope) {
    odsState.getOrAddProperties<Properties>().syncscope = syncscope;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

LoadOp LoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(volatile_)>(volatile_), std::forward<decltype(nontemporal)>(nontemporal), std::forward<decltype(invariant)>(invariant), std::forward<decltype(invariantGroup)>(invariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
  auto __res__ = ::llvm::dyn_cast<LoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoadOp LoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(volatile_)>(volatile_), std::forward<decltype(nontemporal)>(nontemporal), std::forward<decltype(invariant)>(invariant), std::forward<decltype(invariantGroup)>(invariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
}

void LoadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<LoadOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

LoadOp LoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoadOp LoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LoadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LoadOp LoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoadOp LoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LoadOp::verifyInvariantsImpl() {
{

    [[maybe_unused]] ::mlir::ptr::AtomicOrdering tblgen_ordering = this->getOrdering();

      if (::mlir::failed(__mlir_ods_local_prop_constraint_PtrOps1(*this, tblgen_ordering, "ordering")))
        return ::mlir::failure();
}
  auto tblgen_syncscope = getProperties().syncscope; (void)tblgen_syncscope;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_PtrOps2(*this, tblgen_syncscope, "syncscope")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LoadOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult LoadOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand ptrRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> ptrOperands(&ptrRawOperand, 1);  ::llvm::SMLoc ptrOperandsLoc;
  (void)ptrOperandsLoc;
  ::mlir::StringAttr syncscopeAttr;
  ::mlir::Type ptrRawType{};
  ::llvm::ArrayRef<::mlir::Type> ptrTypes(&ptrRawType, 1);
  ::mlir::Type valueRawType{};
  ::llvm::ArrayRef<::mlir::Type> valueTypes(&valueRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("volatile"))) {
    result.getOrAddProperties<LoadOp::Properties>().volatile_ = true;  }

  ptrOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(ptrRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("atomic"))) {
  if (::mlir::succeeded(parser.parseOptionalKeyword("syncscope"))) {
  if (parser.parseLParen())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(syncscopeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (syncscopeAttr) result.getOrAddProperties<LoadOp::Properties>().syncscope = syncscopeAttr;
  if (parser.parseRParen())
    return ::mlir::failure();
  }

  auto orderingPropLoc = parser.getCurrentLocation();
  auto orderingPropParseResult = [&](auto& propStorage) -> ::mlir::ParseResult {
    auto value = ::mlir::FieldParser<::mlir::ptr::AtomicOrdering>::parse(parser);
    if (::mlir::failed(value))
      return ::mlir::failure();
    propStorage = std::move(*value);
    return ::mlir::success();
  }(result.getOrAddProperties<LoadOp::Properties>().ordering);
  if (failed(orderingPropParseResult)) {
    return parser.emitError(orderingPropLoc, "invalid value for property ordering, expected Atomic ordering for LLVM's memory model");
  }
  }
  bool nontemporalClause = false;
  bool invariantClause = false;
  bool invariant_groupClause = false;
  bool alignmentClause = false;
  while(true) {
if (succeeded(parser.parseOptionalKeyword("nontemporal"))) {

  if (nontemporalClause) {
    return parser.emitError(parser.getNameLoc())
          << "`nontemporal` clause can appear at most once in the expansion of the "
             "oilist directive";
  }
  nontemporalClause = true;
    result.getOrAddProperties<LoadOp::Properties>().nontemporal = true;    } else if (succeeded(parser.parseOptionalKeyword("invariant"))) {

  if (invariantClause) {
    return parser.emitError(parser.getNameLoc())
          << "`invariant` clause can appear at most once in the expansion of the "
             "oilist directive";
  }
  invariantClause = true;
    result.getOrAddProperties<LoadOp::Properties>().invariant = true;    } else if (succeeded(parser.parseOptionalKeyword("invariant_group"))) {

  if (invariant_groupClause) {
    return parser.emitError(parser.getNameLoc())
          << "`invariant_group` clause can appear at most once in the expansion of the "
             "oilist directive";
  }
  invariant_groupClause = true;
    result.getOrAddProperties<LoadOp::Properties>().invariantGroup = true;    } else if (succeeded(parser.parseOptionalKeyword("alignment"))) {

  if (alignmentClause) {
    return parser.emitError(parser.getNameLoc())
          << "`alignment` clause can appear at most once in the expansion of the "
             "oilist directive";
  }
  alignmentClause = true;
  if (parser.parseEqual())
    return ::mlir::failure();

  auto alignmentPropLoc = parser.getCurrentLocation();
  auto alignmentPropParseResult = [&](auto& propStorage) -> ::mlir::ParseResult {
    if (::mlir::succeeded(parser.parseOptionalKeyword("none"))) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto delegParseResult = [&](int64_t& propStorage) -> ::mlir::OptionalParseResult {

    return parser.parseOptionalInteger(propStorage);

        return ::mlir::success();
    }(presentVal);
    if (!delegParseResult.has_value()) {

    return ::mlir::failure();

    }
    if (delegParseResult.has_value() && ::mlir::failed(*delegParseResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
    return ::mlir::success();
  }(result.getOrAddProperties<LoadOp::Properties>().alignment);
  if (failed(alignmentPropParseResult)) {
    return parser.emitError(alignmentPropLoc, "invalid value for property alignment, expected optional int64_t");
  }
    } else  {
    break;
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

  if (parser.parseType(ptrRawType))
    return ::mlir::failure();
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    valueRawType = type;
  }
  result.addTypes(valueTypes);
  if (parser.resolveOperands(ptrOperands, ptrTypes, ptrOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LoadOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getVolatile_() != false) {
    _odsPrinter << ' ' << "volatile";
  }
  _odsPrinter << ' ';
  _odsPrinter << getPtr();
  if (getOrdering() != AtomicOrdering::not_atomic) {
    _odsPrinter << ' ' << "atomic";
    if (getSyncscopeAttr()) {
      _odsPrinter << ' ' << "syncscope";
      _odsPrinter << "(";
      _odsPrinter.printAttributeWithoutType(getSyncscopeAttr());
      _odsPrinter << ")";
    }
    _odsPrinter << ' ';
  _odsPrinter << getProperties().ordering;
  }
  if (false || (getNontemporal() != false)) {
  _odsPrinter << ' ' << "nontemporal";
  }
  if (false || (getInvariant() != false)) {
  _odsPrinter << ' ' << "invariant";
  }
  if (false || (getInvariantGroup() != false)) {
  _odsPrinter << ' ' << "invariant_group";
  }
  if (false || (getAlignment() != std::nullopt)) {
  _odsPrinter << ' ' << "alignment";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
[&]() {
      if (!getProperties().alignment.has_value()) {
        _odsPrinter << "none";
        return;
      }
      _odsPrinter.printInteger((*(getProperties().alignment)));
    }();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("syncscope");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getPtr().getType();
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getValue().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::LoadOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::MaskedLoadOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MaskedLoadOpGenericAdaptorBase::MaskedLoadOpGenericAdaptorBase(MaskedLoadOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
MaskedLoadOpAdaptor::MaskedLoadOpAdaptor(MaskedLoadOp op) : MaskedLoadOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MaskedLoadOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult MaskedLoadOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
    {

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        auto arrayAttr = ::llvm::dyn_cast<::mlir::ArrayAttr>(propAttr);
    if (!arrayAttr)
      return emitError() << "expected optional properties to materialize as arrays";
    if (arrayAttr.size() > 1)
      return emitError() << "expected optional properties to become 0- or 1-element arrays";
    if (arrayAttr.empty()) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    ::mlir::Attribute presentAttr = arrayAttr[0];
    int64_t presentVal;
    auto presentRes = [&](::mlir::Attribute propAttr, int64_t& propStorage) -> ::mlir::LogicalResult {

    return convertFromAttribute(propStorage, propAttr, emitError);

    }(presentAttr, presentVal);
    if (::mlir::failed(presentRes))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
      };
         auto attr = dict.get("alignment");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.alignment, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.alignment = std::nullopt;
      }
  }
  return ::mlir::success();
}

::mlir::Attribute MaskedLoadOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.alignment;
      auto attr = [&]() -> ::mlir::Attribute {
        if (!propStorage.has_value()) {
      return ::mlir::ArrayAttr::get(ctx, {});
    }
    auto attr = [&]() -> ::mlir::Attribute {

    return convertToAttribute(ctx, (*(propStorage)));

    }();
    return ::mlir::ArrayAttr::get(ctx, {attr});
      }();
      attrs.push_back(odsBuilder.getNamedAttr("alignment", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MaskedLoadOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    hash_value(prop.alignment));
}

std::optional<mlir::Attribute> MaskedLoadOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void MaskedLoadOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void MaskedLoadOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult MaskedLoadOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

::llvm::LogicalResult MaskedLoadOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  {
    auto &propStorage = prop.alignment;
    auto readProp = [&]() {
      bool isPresent = false;
    if (::mlir::failed(reader.readBool(isPresent)))
      return ::mlir::failure();
    if (!isPresent) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto presentResult = [&](int64_t& propStorage) -> ::mlir::LogicalResult {

    uint64_t val;
    if (failed(reader.readVarInt(val)))
      return ::mlir::failure();
    propStorage = val;
  ;
      return ::mlir::success();
    }(presentVal);
    if (::mlir::failed(presentResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void MaskedLoadOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  {
    auto &propStorage = prop.alignment;
    writer.writeOwnedBool(propStorage.has_value());
    if (propStorage.has_value()) {

    writer.writeVarInt((*(propStorage)));

    };
  }
}

MaskedLoadOp MaskedLoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value ptr, Value mask, Value passthrough, unsigned alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultType)>(resultType), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<MaskedLoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedLoadOp MaskedLoadOp::create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value ptr, Value mask, Value passthrough, unsigned alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultType)>(resultType), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
}

void MaskedLoadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  odsState.addOperands(ptr);
  odsState.addOperands(mask);
  odsState.addOperands(passthrough);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
  odsState.addTypes(result);
}

MaskedLoadOp MaskedLoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<MaskedLoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedLoadOp MaskedLoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
}

void MaskedLoadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  odsState.addOperands(ptr);
  odsState.addOperands(mask);
  odsState.addOperands(passthrough);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(MaskedLoadOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

MaskedLoadOp MaskedLoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<MaskedLoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedLoadOp MaskedLoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
}

void MaskedLoadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  odsState.addOperands(ptr);
  odsState.addOperands(mask);
  odsState.addOperands(passthrough);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MaskedLoadOp MaskedLoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<MaskedLoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedLoadOp MaskedLoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(passthrough)>(passthrough), std::forward<decltype(alignment)>(alignment));
}

void MaskedLoadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<MaskedLoadOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MaskedLoadOp MaskedLoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MaskedLoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedLoadOp MaskedLoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MaskedLoadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<MaskedLoadOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(MaskedLoadOp::inferReturnTypes(odsBuilder.getContext(),
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

MaskedLoadOp MaskedLoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MaskedLoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedLoadOp MaskedLoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MaskedLoadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MaskedLoadOp MaskedLoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MaskedLoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedLoadOp MaskedLoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void MaskedLoadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(MaskedLoadOp::inferReturnTypes(odsBuilder.getContext(),
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

MaskedLoadOp MaskedLoadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MaskedLoadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedLoadOp MaskedLoadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MaskedLoadOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(
      ::llvm::cast<ShapedType>((*this->getODSResults(0).begin()).getType()).clone(
        IntegerType::get((*this->getODSResults(0).begin()).getType().getContext(), 1))
    , (*this->getODSOperands(1).begin()).getType()))))
    return emitOpError("failed to verify that result and mask must be compatible");
  if (!((((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(2).begin()).getType()) && ((*this->getODSOperands(2).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {result, passthrough} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult MaskedLoadOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult MaskedLoadOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 2)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[2].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult MaskedLoadOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand ptrRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> ptrOperands(&ptrRawOperand, 1);  ::llvm::SMLoc ptrOperandsLoc;
  (void)ptrOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand maskRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> maskOperands(&maskRawOperand, 1);  ::llvm::SMLoc maskOperandsLoc;
  (void)maskOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand passthroughRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> passthroughOperands(&passthroughRawOperand, 1);  ::llvm::SMLoc passthroughOperandsLoc;
  (void)passthroughOperandsLoc;
  ::mlir::Type ptrRawType{};
  ::llvm::ArrayRef<::mlir::Type> ptrTypes(&ptrRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  ptrOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(ptrRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  maskOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(maskRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  passthroughOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(passthroughRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("alignment"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  auto alignmentPropLoc = parser.getCurrentLocation();
  auto alignmentPropParseResult = [&](auto& propStorage) -> ::mlir::ParseResult {
    if (::mlir::succeeded(parser.parseOptionalKeyword("none"))) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto delegParseResult = [&](int64_t& propStorage) -> ::mlir::OptionalParseResult {

    return parser.parseOptionalInteger(propStorage);

        return ::mlir::success();
    }(presentVal);
    if (!delegParseResult.has_value()) {

    return ::mlir::failure();

    }
    if (delegParseResult.has_value() && ::mlir::failed(*delegParseResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
    return ::mlir::success();
  }(result.getOrAddProperties<MaskedLoadOp::Properties>().alignment);
  if (failed(alignmentPropParseResult)) {
    return parser.emitError(alignmentPropLoc, "invalid value for property alignment, expected optional int64_t");
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

  if (parser.parseType(ptrRawType))
    return ::mlir::failure();
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::ShapedType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  for (::mlir::Type type : resultTypes) {
    (void)type;
    if (!((((type.hasTrait<::mlir::ValueSemantics>())) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank()
                         == 1)))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
      return parser.emitError(parser.getNameLoc()) << "'result' must be A shaped type with value semantics and rank. of any type values, but got " << type;
    }
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(ptrOperands, ptrTypes, ptrOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(maskOperands, 
      ::llvm::cast<ShapedType>(resultTypes[0]).clone(
        IntegerType::get(resultTypes[0].getContext(), 1))
    , maskOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(passthroughOperands, resultTypes[0], passthroughOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MaskedLoadOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getPtr();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getMask();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getPassthrough();
  if (getAlignment() != std::nullopt) {
    _odsPrinter << ' ' << "alignment";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  [&]() {
        if (!getProperties().alignment.has_value()) {
          _odsPrinter << "none";
          return;
        }
        _odsPrinter.printInteger((*(getProperties().alignment)));
      }();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getPtr().getType();
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::ShapedType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::MaskedLoadOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::MaskedStoreOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MaskedStoreOpGenericAdaptorBase::MaskedStoreOpGenericAdaptorBase(MaskedStoreOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
MaskedStoreOpAdaptor::MaskedStoreOpAdaptor(MaskedStoreOp op) : MaskedStoreOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MaskedStoreOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult MaskedStoreOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
    {

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        auto arrayAttr = ::llvm::dyn_cast<::mlir::ArrayAttr>(propAttr);
    if (!arrayAttr)
      return emitError() << "expected optional properties to materialize as arrays";
    if (arrayAttr.size() > 1)
      return emitError() << "expected optional properties to become 0- or 1-element arrays";
    if (arrayAttr.empty()) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    ::mlir::Attribute presentAttr = arrayAttr[0];
    int64_t presentVal;
    auto presentRes = [&](::mlir::Attribute propAttr, int64_t& propStorage) -> ::mlir::LogicalResult {

    return convertFromAttribute(propStorage, propAttr, emitError);

    }(presentAttr, presentVal);
    if (::mlir::failed(presentRes))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
      };
         auto attr = dict.get("alignment");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.alignment, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.alignment = std::nullopt;
      }
  }
  return ::mlir::success();
}

::mlir::Attribute MaskedStoreOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.alignment;
      auto attr = [&]() -> ::mlir::Attribute {
        if (!propStorage.has_value()) {
      return ::mlir::ArrayAttr::get(ctx, {});
    }
    auto attr = [&]() -> ::mlir::Attribute {

    return convertToAttribute(ctx, (*(propStorage)));

    }();
    return ::mlir::ArrayAttr::get(ctx, {attr});
      }();
      attrs.push_back(odsBuilder.getNamedAttr("alignment", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MaskedStoreOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    hash_value(prop.alignment));
}

std::optional<mlir::Attribute> MaskedStoreOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void MaskedStoreOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void MaskedStoreOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult MaskedStoreOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

::llvm::LogicalResult MaskedStoreOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  {
    auto &propStorage = prop.alignment;
    auto readProp = [&]() {
      bool isPresent = false;
    if (::mlir::failed(reader.readBool(isPresent)))
      return ::mlir::failure();
    if (!isPresent) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto presentResult = [&](int64_t& propStorage) -> ::mlir::LogicalResult {

    uint64_t val;
    if (failed(reader.readVarInt(val)))
      return ::mlir::failure();
    propStorage = val;
  ;
      return ::mlir::success();
    }(presentVal);
    if (::mlir::failed(presentResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void MaskedStoreOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  {
    auto &propStorage = prop.alignment;
    writer.writeOwnedBool(propStorage.has_value());
    if (propStorage.has_value()) {

    writer.writeVarInt((*(propStorage)));

    };
  }
}

MaskedStoreOp MaskedStoreOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value, Value ptr, Value mask, unsigned alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<MaskedStoreOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedStoreOp MaskedStoreOp::create(::mlir::ImplicitLocOpBuilder &builder, Value value, Value ptr, Value mask, unsigned alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
}

void MaskedStoreOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  odsState.addOperands(value);
  odsState.addOperands(ptr);
  odsState.addOperands(mask);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
}

MaskedStoreOp MaskedStoreOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<MaskedStoreOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedStoreOp MaskedStoreOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
}

void MaskedStoreOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  odsState.addOperands(value);
  odsState.addOperands(ptr);
  odsState.addOperands(mask);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MaskedStoreOp MaskedStoreOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<MaskedStoreOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedStoreOp MaskedStoreOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
}

void MaskedStoreOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<MaskedStoreOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MaskedStoreOp MaskedStoreOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MaskedStoreOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedStoreOp MaskedStoreOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MaskedStoreOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MaskedStoreOp MaskedStoreOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MaskedStoreOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MaskedStoreOp MaskedStoreOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MaskedStoreOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(
      ::llvm::cast<ShapedType>((*this->getODSOperands(0).begin()).getType()).clone(
        IntegerType::get((*this->getODSOperands(0).begin()).getType().getContext(), 1))
    , (*this->getODSOperands(2).begin()).getType()))))
    return emitOpError("failed to verify that value and mask must be compatible");
  return ::mlir::success();
}

::llvm::LogicalResult MaskedStoreOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult MaskedStoreOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand valueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> valueOperands(&valueRawOperand, 1);  ::llvm::SMLoc valueOperandsLoc;
  (void)valueOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand ptrRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> ptrOperands(&ptrRawOperand, 1);  ::llvm::SMLoc ptrOperandsLoc;
  (void)ptrOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand maskRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> maskOperands(&maskRawOperand, 1);  ::llvm::SMLoc maskOperandsLoc;
  (void)maskOperandsLoc;
  ::mlir::Type valueRawType{};
  ::llvm::ArrayRef<::mlir::Type> valueTypes(&valueRawType, 1);
  ::mlir::Type ptrRawType{};
  ::llvm::ArrayRef<::mlir::Type> ptrTypes(&ptrRawType, 1);

  valueOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(valueRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  ptrOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(ptrRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  maskOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(maskRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("alignment"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  auto alignmentPropLoc = parser.getCurrentLocation();
  auto alignmentPropParseResult = [&](auto& propStorage) -> ::mlir::ParseResult {
    if (::mlir::succeeded(parser.parseOptionalKeyword("none"))) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto delegParseResult = [&](int64_t& propStorage) -> ::mlir::OptionalParseResult {

    return parser.parseOptionalInteger(propStorage);

        return ::mlir::success();
    }(presentVal);
    if (!delegParseResult.has_value()) {

    return ::mlir::failure();

    }
    if (delegParseResult.has_value() && ::mlir::failed(*delegParseResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
    return ::mlir::success();
  }(result.getOrAddProperties<MaskedStoreOp::Properties>().alignment);
  if (failed(alignmentPropParseResult)) {
    return parser.emitError(alignmentPropLoc, "invalid value for property alignment, expected optional int64_t");
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
    ::mlir::ShapedType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    valueRawType = type;
  }
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseType(ptrRawType))
    return ::mlir::failure();
  for (::mlir::Type type : valueTypes) {
    (void)type;
    if (!((((type.hasTrait<::mlir::ValueSemantics>())) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank()
                         == 1)))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
      return parser.emitError(parser.getNameLoc()) << "'value' must be A shaped type with value semantics and rank. of any type values, but got " << type;
    }
  }
  if (parser.resolveOperands(valueOperands, valueTypes, valueOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(ptrOperands, ptrTypes, ptrOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(maskOperands, 
      ::llvm::cast<ShapedType>(valueTypes[0]).clone(
        IntegerType::get(valueTypes[0].getContext(), 1))
    , maskOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MaskedStoreOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getValue();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getPtr();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getMask();
  if (getAlignment() != std::nullopt) {
    _odsPrinter << ' ' << "alignment";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  [&]() {
        if (!getProperties().alignment.has_value()) {
          _odsPrinter << "none";
          return;
        }
        _odsPrinter.printInteger((*(getProperties().alignment)));
      }();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getValue().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::ShapedType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';
   _odsPrinter << getPtr().getType();
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::MaskedStoreOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::PtrAddOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PtrAddOpGenericAdaptorBase::PtrAddOpGenericAdaptorBase(PtrAddOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
PtrAddOpAdaptor::PtrAddOpAdaptor(PtrAddOp op) : PtrAddOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PtrAddOpAdaptor::verify(::mlir::Location loc) {
{

    [[maybe_unused]] ::mlir::ptr::PtrAddFlags tblgen_flags = this->getFlags();

    if (!(((tblgen_flags == ::mlir::ptr::PtrAddFlags::none)) || ((tblgen_flags == ::mlir::ptr::PtrAddFlags::nusw)) || ((tblgen_flags == ::mlir::ptr::PtrAddFlags::nuw)) || ((tblgen_flags == ::mlir::ptr::PtrAddFlags::inbounds))))
      return emitError(loc, "'ptr.ptr_add' op property 'flags' failed to satisfy constraint: Pointer add flags");
}
  return ::mlir::success();
}

::llvm::LogicalResult PtrAddOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
    {

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        auto intAttr = ::mlir::dyn_cast_if_present<::mlir::IntegerAttr>(propAttr);
    if (!intAttr) {
      return emitError() << "expected IntegerAttr storage for ::mlir::ptr::PtrAddFlags";
    }
    propStorage = static_cast<::mlir::ptr::PtrAddFlags>(intAttr.getValue().getZExtValue());
    return ::mlir::success();
      };
         auto attr = dict.get("flags");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.flags, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.flags = PtrAddFlags::none;
      }
  }
  return ::mlir::success();
}

::mlir::Attribute PtrAddOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.flags;
      auto attr = [&]() -> ::mlir::Attribute {
        return ::mlir::IntegerAttr::get(::mlir::IntegerType::get(ctx, 32), static_cast<uint32_t>(propStorage));
      }();
      attrs.push_back(odsBuilder.getNamedAttr("flags", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PtrAddOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    hash_value(prop.flags));
}

std::optional<mlir::Attribute> PtrAddOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void PtrAddOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void PtrAddOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult PtrAddOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

::llvm::LogicalResult PtrAddOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  {
    auto &propStorage = prop.flags;
    auto readProp = [&]() {
      uint64_t rawValue;
    if (::mlir::failed(reader.readVarInt(rawValue)))
      return ::mlir::failure();
    if (rawValue > std::numeric_limits<uint32_t>::max())
      return ::mlir::failure();
    propStorage = static_cast<::mlir::ptr::PtrAddFlags>(rawValue);;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void PtrAddOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  {
    auto &propStorage = prop.flags;
    writer.writeVarInt(static_cast<uint64_t>(propStorage));;
  }
}

void PtrAddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags) {
  odsState.addOperands(base);
  odsState.addOperands(offset);
  odsState.getOrAddProperties<Properties>().setFlags(flags);
  odsState.addTypes(result);
}

PtrAddOp PtrAddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(base)>(base), std::forward<decltype(offset)>(offset), std::forward<decltype(flags)>(flags));
  auto __res__ = ::llvm::dyn_cast<PtrAddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrAddOp PtrAddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(base)>(base), std::forward<decltype(offset)>(offset), std::forward<decltype(flags)>(flags));
}

void PtrAddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags) {
  odsState.addOperands(base);
  odsState.addOperands(offset);
  odsState.getOrAddProperties<Properties>().setFlags(flags);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(PtrAddOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

PtrAddOp PtrAddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(base)>(base), std::forward<decltype(offset)>(offset), std::forward<decltype(flags)>(flags));
  auto __res__ = ::llvm::dyn_cast<PtrAddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrAddOp PtrAddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags) {
  return create(builder, builder.getLoc(), std::forward<decltype(base)>(base), std::forward<decltype(offset)>(offset), std::forward<decltype(flags)>(flags));
}

void PtrAddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags) {
  odsState.addOperands(base);
  odsState.addOperands(offset);
  odsState.getOrAddProperties<Properties>().setFlags(flags);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PtrAddOp PtrAddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(base)>(base), std::forward<decltype(offset)>(offset), std::forward<decltype(flags)>(flags));
  auto __res__ = ::llvm::dyn_cast<PtrAddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrAddOp PtrAddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(base)>(base), std::forward<decltype(offset)>(offset), std::forward<decltype(flags)>(flags));
}

void PtrAddOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<PtrAddOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

PtrAddOp PtrAddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PtrAddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrAddOp PtrAddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PtrAddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<PtrAddOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(PtrAddOp::inferReturnTypes(odsBuilder.getContext(),
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

PtrAddOp PtrAddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PtrAddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrAddOp PtrAddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PtrAddOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PtrAddOp PtrAddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PtrAddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrAddOp PtrAddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void PtrAddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(PtrAddOp::inferReturnTypes(odsBuilder.getContext(),
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

PtrAddOp PtrAddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PtrAddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrAddOp PtrAddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PtrAddOp::verifyInvariantsImpl() {
{

    [[maybe_unused]] ::mlir::ptr::PtrAddFlags tblgen_flags = this->getFlags();

      if (::mlir::failed(__mlir_ods_local_prop_constraint_PtrOps2(*this, tblgen_flags, "flags")))
        return ::mlir::failure();
}
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps9(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps8(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult PtrAddOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult PtrAddOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand baseRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> baseOperands(&baseRawOperand, 1);  ::llvm::SMLoc baseOperandsLoc;
  (void)baseOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand offsetRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> offsetOperands(&offsetRawOperand, 1);  ::llvm::SMLoc offsetOperandsLoc;
  (void)offsetOperandsLoc;
  ::mlir::Type baseRawType{};
  ::llvm::ArrayRef<::mlir::Type> baseTypes(&baseRawType, 1);
  ::mlir::Type offsetRawType{};
  ::llvm::ArrayRef<::mlir::Type> offsetTypes(&offsetRawType, 1);

  auto flagsPropParseResult = [&](auto& propStorage) -> ::mlir::OptionalParseResult {
    auto value = ::mlir::FieldParser<std::optional<::mlir::ptr::PtrAddFlags>>::parse(parser);
    if (::mlir::failed(value))
      return ::mlir::failure();
    if (!(value->has_value()))
      return std::nullopt;
    propStorage = std::move(**value);
    return ::mlir::success();
  }(result.getOrAddProperties<PtrAddOp::Properties>().flags);
  if (flagsPropParseResult.has_value() && failed(*flagsPropParseResult)) {
    return ::mlir::failure();
  }
if (flagsPropParseResult.has_value() && succeeded(*flagsPropParseResult))  {
  }

  baseOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(baseRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  offsetOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(offsetRawOperand))
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
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    baseRawType = type;
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    offsetRawType = type;
  }
  if (parser.resolveOperands(baseOperands, baseTypes, baseOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(offsetOperands, offsetTypes, offsetOperandsLoc, result.operands))
    return ::mlir::failure();

  ::llvm::SmallVector<::mlir::Type> inferredReturnTypes;
  if (::mlir::failed(PtrAddOp::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void PtrAddOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getFlags() != PtrAddFlags::none) {
    _odsPrinter << ' ';
  _odsPrinter << getProperties().flags;
  }
  _odsPrinter << ' ';
  _odsPrinter << getBase();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getOffset();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getBase().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';
  {
    auto type = getOffset().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void PtrAddOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::PtrAddOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::PtrDiffOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PtrDiffOpGenericAdaptorBase::PtrDiffOpGenericAdaptorBase(PtrDiffOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
PtrDiffOpAdaptor::PtrDiffOpAdaptor(PtrDiffOp op) : PtrDiffOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PtrDiffOpAdaptor::verify(::mlir::Location loc) {
{

    [[maybe_unused]] ::mlir::ptr::PtrDiffFlags tblgen_flags = this->getFlags();

    if (!(((static_cast<uint8_t>(tblgen_flags) & ~3) == 0)))
      return emitError(loc, "'ptr.ptr_diff' op property 'flags' failed to satisfy constraint: Pointer difference flags");
}
  return ::mlir::success();
}

::llvm::LogicalResult PtrDiffOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
    {

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        auto intAttr = ::mlir::dyn_cast_if_present<::mlir::IntegerAttr>(propAttr);
    if (!intAttr) {
      return emitError() << "expected IntegerAttr storage for ::mlir::ptr::PtrDiffFlags";
    }
    propStorage = static_cast<::mlir::ptr::PtrDiffFlags>(intAttr.getValue().getZExtValue());
    return ::mlir::success();
      };
         auto attr = dict.get("flags");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.flags, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.flags = PtrDiffFlags::none;
      }
  }
  return ::mlir::success();
}

::mlir::Attribute PtrDiffOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.flags;
      auto attr = [&]() -> ::mlir::Attribute {
        return ::mlir::IntegerAttr::get(::mlir::IntegerType::get(ctx, 8), static_cast<uint8_t>(propStorage));
      }();
      attrs.push_back(odsBuilder.getNamedAttr("flags", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PtrDiffOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    hash_value(prop.flags));
}

std::optional<mlir::Attribute> PtrDiffOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void PtrDiffOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void PtrDiffOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult PtrDiffOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

::llvm::LogicalResult PtrDiffOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  {
    auto &propStorage = prop.flags;
    auto readProp = [&]() {
      uint64_t rawValue;
    if (::mlir::failed(reader.readVarInt(rawValue)))
      return ::mlir::failure();
    if (rawValue > std::numeric_limits<uint8_t>::max())
      return ::mlir::failure();
    propStorage = static_cast<::mlir::ptr::PtrDiffFlags>(rawValue);;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void PtrDiffOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  {
    auto &propStorage = prop.flags;
    writer.writeVarInt(static_cast<uint64_t>(propStorage));;
  }
}

void PtrDiffOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.getOrAddProperties<Properties>().setFlags(flags);
  odsState.addTypes(result);
}

PtrDiffOp PtrDiffOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(flags)>(flags));
  auto __res__ = ::llvm::dyn_cast<PtrDiffOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrDiffOp PtrDiffOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(flags)>(flags));
}

void PtrDiffOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.getOrAddProperties<Properties>().setFlags(flags);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PtrDiffOp PtrDiffOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(flags)>(flags));
  auto __res__ = ::llvm::dyn_cast<PtrDiffOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrDiffOp PtrDiffOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(flags)>(flags));
}

void PtrDiffOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<PtrDiffOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

PtrDiffOp PtrDiffOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PtrDiffOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrDiffOp PtrDiffOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PtrDiffOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PtrDiffOp PtrDiffOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PtrDiffOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PtrDiffOp PtrDiffOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PtrDiffOp::verifyInvariantsImpl() {
{

    [[maybe_unused]] ::mlir::ptr::PtrDiffFlags tblgen_flags = this->getFlags();

      if (::mlir::failed(__mlir_ods_local_prop_constraint_PtrOps3(*this, tblgen_flags, "flags")))
        return ::mlir::failure();
}
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps9(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSOperands(0).begin()).getType()) == ((*this->getODSOperands(1).begin()).getType()) && ((*this->getODSOperands(1).begin()).getType()) == ((*this->getODSOperands(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {lhs, rhs} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult PtrDiffOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult PtrDiffOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type lhsRawType{};
  ::llvm::ArrayRef<::mlir::Type> lhsTypes(&lhsRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  auto flagsPropParseResult = [&](auto& propStorage) -> ::mlir::OptionalParseResult {
    auto value = ::mlir::FieldParser<std::optional<::mlir::ptr::PtrDiffFlags>>::parse(parser);
    if (::mlir::failed(value))
      return ::mlir::failure();
    if (!(value->has_value()))
      return std::nullopt;
    propStorage = std::move(**value);
    return ::mlir::success();
  }(result.getOrAddProperties<PtrDiffOp::Properties>().flags);
  if (flagsPropParseResult.has_value() && failed(*flagsPropParseResult)) {
    return ::mlir::failure();
  }
if (flagsPropParseResult.has_value() && succeeded(*flagsPropParseResult))  {
  }

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
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
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    lhsRawType = type;
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
  if (parser.resolveOperands(lhsOperands, lhsTypes, lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, lhsTypes[0], rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void PtrDiffOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getFlags() != PtrDiffFlags::none) {
    _odsPrinter << ' ';
  _odsPrinter << getProperties().flags;
  }
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getLhs().getType();
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

void PtrDiffOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::PtrDiffOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::ScatterOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ScatterOpGenericAdaptorBase::ScatterOpGenericAdaptorBase(ScatterOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ScatterOpAdaptor::ScatterOpAdaptor(ScatterOp op) : ScatterOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ScatterOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ScatterOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
    {

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        auto arrayAttr = ::llvm::dyn_cast<::mlir::ArrayAttr>(propAttr);
    if (!arrayAttr)
      return emitError() << "expected optional properties to materialize as arrays";
    if (arrayAttr.size() > 1)
      return emitError() << "expected optional properties to become 0- or 1-element arrays";
    if (arrayAttr.empty()) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    ::mlir::Attribute presentAttr = arrayAttr[0];
    int64_t presentVal;
    auto presentRes = [&](::mlir::Attribute propAttr, int64_t& propStorage) -> ::mlir::LogicalResult {

    return convertFromAttribute(propStorage, propAttr, emitError);

    }(presentAttr, presentVal);
    if (::mlir::failed(presentRes))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
      };
         auto attr = dict.get("alignment");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.alignment, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.alignment = std::nullopt;
      }
  }
  return ::mlir::success();
}

::mlir::Attribute ScatterOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.alignment;
      auto attr = [&]() -> ::mlir::Attribute {
        if (!propStorage.has_value()) {
      return ::mlir::ArrayAttr::get(ctx, {});
    }
    auto attr = [&]() -> ::mlir::Attribute {

    return convertToAttribute(ctx, (*(propStorage)));

    }();
    return ::mlir::ArrayAttr::get(ctx, {attr});
      }();
      attrs.push_back(odsBuilder.getNamedAttr("alignment", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ScatterOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    hash_value(prop.alignment));
}

std::optional<mlir::Attribute> ScatterOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ScatterOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ScatterOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ScatterOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

::llvm::LogicalResult ScatterOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  {
    auto &propStorage = prop.alignment;
    auto readProp = [&]() {
      bool isPresent = false;
    if (::mlir::failed(reader.readBool(isPresent)))
      return ::mlir::failure();
    if (!isPresent) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto presentResult = [&](int64_t& propStorage) -> ::mlir::LogicalResult {

    uint64_t val;
    if (failed(reader.readVarInt(val)))
      return ::mlir::failure();
    propStorage = val;
  ;
      return ::mlir::success();
    }(presentVal);
    if (::mlir::failed(presentResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void ScatterOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  {
    auto &propStorage = prop.alignment;
    writer.writeOwnedBool(propStorage.has_value());
    if (propStorage.has_value()) {

    writer.writeVarInt((*(propStorage)));

    };
  }
}

ScatterOp ScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value, Value ptrs, Value mask, unsigned alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<ScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScatterOp ScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, Value value, Value ptrs, Value mask, unsigned alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
}

void ScatterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  odsState.addOperands(value);
  odsState.addOperands(ptrs);
  odsState.addOperands(mask);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
}

ScatterOp ScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<ScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScatterOp ScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
}

void ScatterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  odsState.addOperands(value);
  odsState.addOperands(ptrs);
  odsState.addOperands(mask);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ScatterOp ScatterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
  auto __res__ = ::llvm::dyn_cast<ScatterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScatterOp ScatterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(ptrs)>(ptrs), std::forward<decltype(mask)>(mask), std::forward<decltype(alignment)>(alignment));
}

void ScatterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
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
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
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

::llvm::LogicalResult ScatterOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(
      ::llvm::cast<ShapedType>((*this->getODSOperands(0).begin()).getType()).clone(
        IntegerType::get((*this->getODSOperands(0).begin()).getType().getContext(), 1))
    , (*this->getODSOperands(2).begin()).getType()))))
    return emitOpError("failed to verify that value and mask must be compatible");
  if (!(((::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(1).begin()).getType()).getShape()) && (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(1).begin()).getType()).getShape()) == (::llvm::cast<::mlir::ShapedType>((*this->getODSOperands(0).begin()).getType()).getShape()))))
    return emitOpError("failed to verify that all of {value, ptrs} have same shape");
  if (!((((*this->getODSOperands(0).begin()).getType().getTypeID()) == ((*this->getODSOperands(1).begin()).getType().getTypeID()) && ((*this->getODSOperands(1).begin()).getType().getTypeID()) == ((*this->getODSOperands(0).begin()).getType().getTypeID()))))
    return emitOpError("failed to verify that all of {value, ptrs} have same type IDs");
  return ::mlir::success();
}

::llvm::LogicalResult ScatterOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ScatterOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand valueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> valueOperands(&valueRawOperand, 1);  ::llvm::SMLoc valueOperandsLoc;
  (void)valueOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand ptrsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> ptrsOperands(&ptrsRawOperand, 1);  ::llvm::SMLoc ptrsOperandsLoc;
  (void)ptrsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand maskRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> maskOperands(&maskRawOperand, 1);  ::llvm::SMLoc maskOperandsLoc;
  (void)maskOperandsLoc;
  ::mlir::Type valueRawType{};
  ::llvm::ArrayRef<::mlir::Type> valueTypes(&valueRawType, 1);
  ::mlir::Type ptrsRawType{};
  ::llvm::ArrayRef<::mlir::Type> ptrsTypes(&ptrsRawType, 1);

  valueOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(valueRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  ptrsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(ptrsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  maskOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(maskRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("alignment"))) {
  if (parser.parseEqual())
    return ::mlir::failure();

  auto alignmentPropLoc = parser.getCurrentLocation();
  auto alignmentPropParseResult = [&](auto& propStorage) -> ::mlir::ParseResult {
    if (::mlir::succeeded(parser.parseOptionalKeyword("none"))) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto delegParseResult = [&](int64_t& propStorage) -> ::mlir::OptionalParseResult {

    return parser.parseOptionalInteger(propStorage);

        return ::mlir::success();
    }(presentVal);
    if (!delegParseResult.has_value()) {

    return ::mlir::failure();

    }
    if (delegParseResult.has_value() && ::mlir::failed(*delegParseResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
    return ::mlir::success();
  }(result.getOrAddProperties<ScatterOp::Properties>().alignment);
  if (failed(alignmentPropParseResult)) {
    return parser.emitError(alignmentPropLoc, "invalid value for property alignment, expected optional int64_t");
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
    ::mlir::ShapedType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    valueRawType = type;
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::mlir::ShapedType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    ptrsRawType = type;
  }
  for (::mlir::Type type : valueTypes) {
    (void)type;
    if (!((((type.hasTrait<::mlir::ValueSemantics>())) && (((::llvm::cast<::mlir::ShapedType>(type).hasRank())) && ((::llvm::cast<::mlir::ShapedType>(type).getRank()
                         == 1)))) && ([](::mlir::Type elementType) { return (true); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
      return parser.emitError(parser.getNameLoc()) << "'value' must be A shaped type with value semantics and rank. of any type values, but got " << type;
    }
  }
  if (parser.resolveOperands(valueOperands, valueTypes, valueOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(ptrsOperands, ptrsTypes, ptrsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(maskOperands, 
      ::llvm::cast<ShapedType>(valueTypes[0]).clone(
        IntegerType::get(valueTypes[0].getContext(), 1))
    , maskOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ScatterOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getValue();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getPtrs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getMask();
  if (getAlignment() != std::nullopt) {
    _odsPrinter << ' ' << "alignment";
    _odsPrinter << ' ' << "=";
    _odsPrinter << ' ';
  [&]() {
        if (!getProperties().alignment.has_value()) {
          _odsPrinter << "none";
          return;
        }
        _odsPrinter.printInteger((*(getProperties().alignment)));
      }();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getValue().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::ShapedType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';
  {
    auto type = getPtrs().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::ShapedType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::ScatterOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::StoreOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StoreOpGenericAdaptorBase::StoreOpGenericAdaptorBase(StoreOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional< ::llvm::StringRef > StoreOpGenericAdaptorBase::getSyncscope() {
  auto attr = getSyncscopeAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
StoreOpAdaptor::StoreOpAdaptor(StoreOp op) : StoreOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StoreOpAdaptor::verify(::mlir::Location loc) {
{

    [[maybe_unused]] ::mlir::ptr::AtomicOrdering tblgen_ordering = this->getOrdering();

    if (!(((tblgen_ordering == ::mlir::ptr::AtomicOrdering::not_atomic)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::unordered)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::monotonic)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::acquire)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::release)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::acq_rel)) || ((tblgen_ordering == ::mlir::ptr::AtomicOrdering::seq_cst))))
      return emitError(loc, "'ptr.store' op property 'ordering' failed to satisfy constraint: Atomic ordering for LLVM's memory model");
}
  auto tblgen_syncscope = getProperties().syncscope; (void)tblgen_syncscope;

  if (tblgen_syncscope && !((::llvm::isa<::mlir::StringAttr>(tblgen_syncscope))))
    return emitError(loc, "'ptr.store' op attribute 'syncscope' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult StoreOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.syncscope;
       auto attr = dict.get("syncscope");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `syncscope` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        auto arrayAttr = ::llvm::dyn_cast<::mlir::ArrayAttr>(propAttr);
    if (!arrayAttr)
      return emitError() << "expected optional properties to materialize as arrays";
    if (arrayAttr.size() > 1)
      return emitError() << "expected optional properties to become 0- or 1-element arrays";
    if (arrayAttr.empty()) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    ::mlir::Attribute presentAttr = arrayAttr[0];
    int64_t presentVal;
    auto presentRes = [&](::mlir::Attribute propAttr, int64_t& propStorage) -> ::mlir::LogicalResult {

    return convertFromAttribute(propStorage, propAttr, emitError);

    }(presentAttr, presentVal);
    if (::mlir::failed(presentRes))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
      };
         auto attr = dict.get("alignment");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.alignment, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.alignment = std::nullopt;
      }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        if (::llvm::isa<::mlir::UnitAttr>(propAttr)) {
      propStorage = true;
      return ::mlir::success();
    }
    if (auto boolAttr = ::llvm::dyn_cast<::mlir::BoolAttr>(propAttr)) {
      propStorage = boolAttr.getValue();
      return ::mlir::success();
    }
    return ::mlir::failure();
      };
         auto attr = dict.get("volatile_");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.volatile_, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.volatile_ = false;
      }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        if (::llvm::isa<::mlir::UnitAttr>(propAttr)) {
      propStorage = true;
      return ::mlir::success();
    }
    if (auto boolAttr = ::llvm::dyn_cast<::mlir::BoolAttr>(propAttr)) {
      propStorage = boolAttr.getValue();
      return ::mlir::success();
    }
    return ::mlir::failure();
      };
         auto attr = dict.get("nontemporal");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.nontemporal, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.nontemporal = false;
      }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        if (::llvm::isa<::mlir::UnitAttr>(propAttr)) {
      propStorage = true;
      return ::mlir::success();
    }
    if (auto boolAttr = ::llvm::dyn_cast<::mlir::BoolAttr>(propAttr)) {
      propStorage = boolAttr.getValue();
      return ::mlir::success();
    }
    return ::mlir::failure();
      };
         auto attr = dict.get("invariantGroup");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.invariantGroup, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.invariantGroup = false;
      }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        auto intAttr = ::mlir::dyn_cast_if_present<::mlir::IntegerAttr>(propAttr);
    if (!intAttr) {
      return emitError() << "expected IntegerAttr storage for ::mlir::ptr::AtomicOrdering";
    }
    propStorage = static_cast<::mlir::ptr::AtomicOrdering>(intAttr.getValue().getZExtValue());
    return ::mlir::success();
      };
         auto attr = dict.get("ordering");;
;
      if (attr) {
        if (::mlir::failed(setFromAttr(prop.ordering, attr, emitError)))
          return ::mlir::failure();
      } else {
        prop.ordering = AtomicOrdering::not_atomic;
      }
  }
  return ::mlir::success();
}

::mlir::Attribute StoreOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.syncscope;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("syncscope",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.alignment;
      auto attr = [&]() -> ::mlir::Attribute {
        if (!propStorage.has_value()) {
      return ::mlir::ArrayAttr::get(ctx, {});
    }
    auto attr = [&]() -> ::mlir::Attribute {

    return convertToAttribute(ctx, (*(propStorage)));

    }();
    return ::mlir::ArrayAttr::get(ctx, {attr});
      }();
      attrs.push_back(odsBuilder.getNamedAttr("alignment", attr));
    }

    {
      const auto &propStorage = prop.volatile_;
      auto attr = [&]() -> ::mlir::Attribute {
        if (propStorage)
      return ::mlir::UnitAttr::get(ctx);
    else
      return ::mlir::BoolAttr::get(ctx, false);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("volatile_", attr));
    }

    {
      const auto &propStorage = prop.nontemporal;
      auto attr = [&]() -> ::mlir::Attribute {
        if (propStorage)
      return ::mlir::UnitAttr::get(ctx);
    else
      return ::mlir::BoolAttr::get(ctx, false);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("nontemporal", attr));
    }

    {
      const auto &propStorage = prop.invariantGroup;
      auto attr = [&]() -> ::mlir::Attribute {
        if (propStorage)
      return ::mlir::UnitAttr::get(ctx);
    else
      return ::mlir::BoolAttr::get(ctx, false);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("invariantGroup", attr));
    }

    {
      const auto &propStorage = prop.ordering;
      auto attr = [&]() -> ::mlir::Attribute {
        return ::mlir::IntegerAttr::get(::mlir::IntegerType::get(ctx, 32), static_cast<uint32_t>(propStorage));
      }();
      attrs.push_back(odsBuilder.getNamedAttr("ordering", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StoreOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.syncscope.getAsOpaquePointer()), 
    hash_value(prop.alignment), 
    hash_value(prop.volatile_), 
    hash_value(prop.nontemporal), 
    hash_value(prop.invariantGroup), 
    hash_value(prop.ordering));
}

std::optional<mlir::Attribute> StoreOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "syncscope")
      return prop.syncscope;
  return std::nullopt;
}

void StoreOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "syncscope") {
       prop.syncscope = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.syncscope)>>(value);
       return;
    }
}

void StoreOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.syncscope) attrs.append("syncscope", prop.syncscope);
}

::llvm::LogicalResult StoreOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSyncscopeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_PtrOps2(attr, "syncscope", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult StoreOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.syncscope)))
    return ::mlir::failure();

  {
    auto &propStorage = prop.alignment;
    auto readProp = [&]() {
      bool isPresent = false;
    if (::mlir::failed(reader.readBool(isPresent)))
      return ::mlir::failure();
    if (!isPresent) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto presentResult = [&](int64_t& propStorage) -> ::mlir::LogicalResult {

    uint64_t val;
    if (failed(reader.readVarInt(val)))
      return ::mlir::failure();
    propStorage = val;
  ;
      return ::mlir::success();
    }(presentVal);
    if (::mlir::failed(presentResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }

  {
    auto &propStorage = prop.volatile_;
    auto readProp = [&]() {
      if (::mlir::failed(reader.readBool(propStorage)))
      return ::mlir::failure();;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }

  {
    auto &propStorage = prop.nontemporal;
    auto readProp = [&]() {
      if (::mlir::failed(reader.readBool(propStorage)))
      return ::mlir::failure();;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }

  {
    auto &propStorage = prop.invariantGroup;
    auto readProp = [&]() {
      if (::mlir::failed(reader.readBool(propStorage)))
      return ::mlir::failure();;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }

  {
    auto &propStorage = prop.ordering;
    auto readProp = [&]() {
      uint64_t rawValue;
    if (::mlir::failed(reader.readVarInt(rawValue)))
      return ::mlir::failure();
    if (rawValue > std::numeric_limits<uint32_t>::max())
      return ::mlir::failure();
    propStorage = static_cast<::mlir::ptr::AtomicOrdering>(rawValue);;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void StoreOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.syncscope);

  {
    auto &propStorage = prop.alignment;
    writer.writeOwnedBool(propStorage.has_value());
    if (propStorage.has_value()) {

    writer.writeVarInt((*(propStorage)));

    };
  }

  {
    auto &propStorage = prop.volatile_;
    writer.writeOwnedBool(propStorage);;
  }

  {
    auto &propStorage = prop.nontemporal;
    writer.writeOwnedBool(propStorage);;
  }

  {
    auto &propStorage = prop.invariantGroup;
    writer.writeOwnedBool(propStorage);;
  }

  {
    auto &propStorage = prop.ordering;
    writer.writeVarInt(static_cast<uint64_t>(propStorage));;
  }
}

::std::optional< ::llvm::StringRef > StoreOp::getSyncscope() {
  auto attr = getSyncscopeAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void StoreOp::setSyncscope(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().syncscope;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

StoreOp StoreOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value, Value ptr, unsigned alignment, bool isVolatile, bool isNonTemporal, bool isInvariantGroup, AtomicOrdering ordering, StringRef syncscope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(isVolatile)>(isVolatile), std::forward<decltype(isNonTemporal)>(isNonTemporal), std::forward<decltype(isInvariantGroup)>(isInvariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
  auto __res__ = ::llvm::dyn_cast<StoreOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StoreOp StoreOp::create(::mlir::ImplicitLocOpBuilder &builder, Value value, Value ptr, unsigned alignment, bool isVolatile, bool isNonTemporal, bool isInvariantGroup, AtomicOrdering ordering, StringRef syncscope) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(isVolatile)>(isVolatile), std::forward<decltype(isNonTemporal)>(isNonTemporal), std::forward<decltype(isInvariantGroup)>(isInvariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
}

void StoreOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  odsState.addOperands(value);
  odsState.addOperands(ptr);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
  odsState.getOrAddProperties<Properties>().setVolatile_(volatile_);
  odsState.getOrAddProperties<Properties>().setNontemporal(nontemporal);
  odsState.getOrAddProperties<Properties>().setInvariantGroup(invariantGroup);
  odsState.getOrAddProperties<Properties>().setOrdering(ordering);
  if (syncscope) {
    odsState.getOrAddProperties<Properties>().syncscope = syncscope;
  }
}

StoreOp StoreOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(volatile_)>(volatile_), std::forward<decltype(nontemporal)>(nontemporal), std::forward<decltype(invariantGroup)>(invariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
  auto __res__ = ::llvm::dyn_cast<StoreOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StoreOp StoreOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(volatile_)>(volatile_), std::forward<decltype(nontemporal)>(nontemporal), std::forward<decltype(invariantGroup)>(invariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
}

void StoreOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  odsState.addOperands(value);
  odsState.addOperands(ptr);
  odsState.getOrAddProperties<Properties>().setAlignment(alignment);
  odsState.getOrAddProperties<Properties>().setVolatile_(volatile_);
  odsState.getOrAddProperties<Properties>().setNontemporal(nontemporal);
  odsState.getOrAddProperties<Properties>().setInvariantGroup(invariantGroup);
  odsState.getOrAddProperties<Properties>().setOrdering(ordering);
  if (syncscope) {
    odsState.getOrAddProperties<Properties>().syncscope = syncscope;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

StoreOp StoreOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(volatile_)>(volatile_), std::forward<decltype(nontemporal)>(nontemporal), std::forward<decltype(invariantGroup)>(invariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
  auto __res__ = ::llvm::dyn_cast<StoreOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StoreOp StoreOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(ptr)>(ptr), std::forward<decltype(alignment)>(alignment), std::forward<decltype(volatile_)>(volatile_), std::forward<decltype(nontemporal)>(nontemporal), std::forward<decltype(invariantGroup)>(invariantGroup), std::forward<decltype(ordering)>(ordering), std::forward<decltype(syncscope)>(syncscope));
}

void StoreOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<StoreOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

StoreOp StoreOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<StoreOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StoreOp StoreOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void StoreOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

StoreOp StoreOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<StoreOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StoreOp StoreOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult StoreOp::verifyInvariantsImpl() {
{

    [[maybe_unused]] ::mlir::ptr::AtomicOrdering tblgen_ordering = this->getOrdering();

      if (::mlir::failed(__mlir_ods_local_prop_constraint_PtrOps1(*this, tblgen_ordering, "ordering")))
        return ::mlir::failure();
}
  auto tblgen_syncscope = getProperties().syncscope; (void)tblgen_syncscope;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_PtrOps2(*this, tblgen_syncscope, "syncscope")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult StoreOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult StoreOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand valueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> valueOperands(&valueRawOperand, 1);  ::llvm::SMLoc valueOperandsLoc;
  (void)valueOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand ptrRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> ptrOperands(&ptrRawOperand, 1);  ::llvm::SMLoc ptrOperandsLoc;
  (void)ptrOperandsLoc;
  ::mlir::StringAttr syncscopeAttr;
  ::mlir::Type valueRawType{};
  ::llvm::ArrayRef<::mlir::Type> valueTypes(&valueRawType, 1);
  ::mlir::Type ptrRawType{};
  ::llvm::ArrayRef<::mlir::Type> ptrTypes(&ptrRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("volatile"))) {
    result.getOrAddProperties<StoreOp::Properties>().volatile_ = true;  }

  valueOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(valueRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  ptrOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(ptrRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("atomic"))) {
  if (::mlir::succeeded(parser.parseOptionalKeyword("syncscope"))) {
  if (parser.parseLParen())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(syncscopeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (syncscopeAttr) result.getOrAddProperties<StoreOp::Properties>().syncscope = syncscopeAttr;
  if (parser.parseRParen())
    return ::mlir::failure();
  }

  auto orderingPropLoc = parser.getCurrentLocation();
  auto orderingPropParseResult = [&](auto& propStorage) -> ::mlir::ParseResult {
    auto value = ::mlir::FieldParser<::mlir::ptr::AtomicOrdering>::parse(parser);
    if (::mlir::failed(value))
      return ::mlir::failure();
    propStorage = std::move(*value);
    return ::mlir::success();
  }(result.getOrAddProperties<StoreOp::Properties>().ordering);
  if (failed(orderingPropParseResult)) {
    return parser.emitError(orderingPropLoc, "invalid value for property ordering, expected Atomic ordering for LLVM's memory model");
  }
  }
  bool nontemporalClause = false;
  bool invariant_groupClause = false;
  bool alignmentClause = false;
  while(true) {
if (succeeded(parser.parseOptionalKeyword("nontemporal"))) {

  if (nontemporalClause) {
    return parser.emitError(parser.getNameLoc())
          << "`nontemporal` clause can appear at most once in the expansion of the "
             "oilist directive";
  }
  nontemporalClause = true;
    result.getOrAddProperties<StoreOp::Properties>().nontemporal = true;    } else if (succeeded(parser.parseOptionalKeyword("invariant_group"))) {

  if (invariant_groupClause) {
    return parser.emitError(parser.getNameLoc())
          << "`invariant_group` clause can appear at most once in the expansion of the "
             "oilist directive";
  }
  invariant_groupClause = true;
    result.getOrAddProperties<StoreOp::Properties>().invariantGroup = true;    } else if (succeeded(parser.parseOptionalKeyword("alignment"))) {

  if (alignmentClause) {
    return parser.emitError(parser.getNameLoc())
          << "`alignment` clause can appear at most once in the expansion of the "
             "oilist directive";
  }
  alignmentClause = true;
  if (parser.parseEqual())
    return ::mlir::failure();

  auto alignmentPropLoc = parser.getCurrentLocation();
  auto alignmentPropParseResult = [&](auto& propStorage) -> ::mlir::ParseResult {
    if (::mlir::succeeded(parser.parseOptionalKeyword("none"))) {
      propStorage = std::nullopt;
      return ::mlir::success();
    }
    int64_t presentVal;
    auto delegParseResult = [&](int64_t& propStorage) -> ::mlir::OptionalParseResult {

    return parser.parseOptionalInteger(propStorage);

        return ::mlir::success();
    }(presentVal);
    if (!delegParseResult.has_value()) {

    return ::mlir::failure();

    }
    if (delegParseResult.has_value() && ::mlir::failed(*delegParseResult))
      return ::mlir::failure();
    propStorage = std::move(presentVal);
    return ::mlir::success();
    return ::mlir::success();
  }(result.getOrAddProperties<StoreOp::Properties>().alignment);
  if (failed(alignmentPropParseResult)) {
    return parser.emitError(alignmentPropLoc, "invalid value for property alignment, expected optional int64_t");
  }
    } else  {
    break;
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
    valueRawType = type;
  }
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseType(ptrRawType))
    return ::mlir::failure();
  if (parser.resolveOperands(valueOperands, valueTypes, valueOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(ptrOperands, ptrTypes, ptrOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void StoreOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getVolatile_() != false) {
    _odsPrinter << ' ' << "volatile";
  }
  _odsPrinter << ' ';
  _odsPrinter << getValue();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getPtr();
  if (getOrdering() != AtomicOrdering::not_atomic) {
    _odsPrinter << ' ' << "atomic";
    if (getSyncscopeAttr()) {
      _odsPrinter << ' ' << "syncscope";
      _odsPrinter << "(";
      _odsPrinter.printAttributeWithoutType(getSyncscopeAttr());
      _odsPrinter << ")";
    }
    _odsPrinter << ' ';
  _odsPrinter << getProperties().ordering;
  }
  if (false || (getNontemporal() != false)) {
  _odsPrinter << ' ' << "nontemporal";
  }
  if (false || (getInvariantGroup() != false)) {
  _odsPrinter << ' ' << "invariant_group";
  }
  if (false || (getAlignment() != std::nullopt)) {
  _odsPrinter << ' ' << "alignment";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
[&]() {
      if (!getProperties().alignment.has_value()) {
        _odsPrinter << "none";
        return;
      }
      _odsPrinter.printInteger((*(getProperties().alignment)));
    }();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("syncscope");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getValue().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';
   _odsPrinter << getPtr().getType();
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::StoreOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::ToPtrOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ToPtrOpGenericAdaptorBase::ToPtrOpGenericAdaptorBase(ToPtrOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ToPtrOpAdaptor::ToPtrOpAdaptor(ToPtrOp op) : ToPtrOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ToPtrOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ToPtrOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ToPtrOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ToPtrOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ToPtrOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ToPtrOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ToPtrOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ToPtrOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ToPtrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value ptr) {
  odsState.addOperands(ptr);
  odsState.addTypes(result);
}

ToPtrOp ToPtrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value ptr) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(ptr)>(ptr));
  auto __res__ = ::llvm::dyn_cast<ToPtrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToPtrOp ToPtrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value ptr) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(ptr)>(ptr));
}

void ToPtrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptr) {
  odsState.addOperands(ptr);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ToPtrOp ToPtrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptr) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptr)>(ptr));
  auto __res__ = ::llvm::dyn_cast<ToPtrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToPtrOp ToPtrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptr) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ptr)>(ptr));
}

void ToPtrOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ToPtrOp ToPtrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ToPtrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToPtrOp ToPtrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ToPtrOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ToPtrOp ToPtrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ToPtrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToPtrOp ToPtrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ToPtrOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ToPtrOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ToPtrOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand ptrRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> ptrOperands(&ptrRawOperand, 1);  ::llvm::SMLoc ptrOperandsLoc;
  (void)ptrOperandsLoc;
  ::mlir::Type ptrRawType{};
  ::llvm::ArrayRef<::mlir::Type> ptrTypes(&ptrRawType, 1);
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  ptrOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(ptrRawOperand))
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
    ::mlir::PtrLikeTypeInterface type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    ptrRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::mlir::ptr::PtrType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(ptrOperands, ptrTypes, ptrOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ToPtrOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getPtr();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getPtr().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::PtrLikeTypeInterface>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::ptr::PtrType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void ToPtrOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::ToPtrOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::TypeOffsetOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

TypeOffsetOpGenericAdaptorBase::TypeOffsetOpGenericAdaptorBase(TypeOffsetOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::Type TypeOffsetOpGenericAdaptorBase::getElementType() {
  auto attr = getElementTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}


} // namespace detail
TypeOffsetOpAdaptor::TypeOffsetOpAdaptor(TypeOffsetOp op) : TypeOffsetOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult TypeOffsetOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_elementType = getProperties().elementType; (void)tblgen_elementType;
  if (!tblgen_elementType) return emitError(loc, "'ptr.type_offset' op requires attribute 'elementType'");

  if (tblgen_elementType && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_elementType))) && ((::llvm::isa<::mlir::Type>(::llvm::cast<::mlir::TypeAttr>(tblgen_elementType).getValue()))) && ((true))))
    return emitError(loc, "'ptr.type_offset' op attribute 'elementType' failed to satisfy constraint: any type attribute");
  return ::mlir::success();
}

::llvm::LogicalResult TypeOffsetOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.elementType;
       auto attr = dict.get("elementType");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `elementType` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute TypeOffsetOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.elementType;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("elementType",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code TypeOffsetOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.elementType.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> TypeOffsetOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "elementType")
      return prop.elementType;
  return std::nullopt;
}

void TypeOffsetOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "elementType") {
       prop.elementType = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.elementType)>>(value);
       return;
    }
}

void TypeOffsetOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.elementType) attrs.append("elementType", prop.elementType);
}

::llvm::LogicalResult TypeOffsetOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getElementTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_PtrOps3(attr, "elementType", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult TypeOffsetOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.elementType)))
    return ::mlir::failure();
  return ::mlir::success();
}

void TypeOffsetOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.elementType);
}

::mlir::Type TypeOffsetOp::getElementType() {
  auto attr = getElementTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}

void TypeOffsetOp::setElementType(::mlir::Type attrValue) {
  getProperties().elementType = ::mlir::TypeAttr::get(attrValue);
}

void TypeOffsetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::TypeAttr elementType) {
  odsState.getOrAddProperties<Properties>().elementType = elementType;
  odsState.addTypes(result);
}

TypeOffsetOp TypeOffsetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::TypeAttr elementType) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(elementType)>(elementType));
  auto __res__ = ::llvm::dyn_cast<TypeOffsetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeOffsetOp TypeOffsetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::TypeAttr elementType) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(elementType)>(elementType));
}

void TypeOffsetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr elementType) {
  odsState.getOrAddProperties<Properties>().elementType = elementType;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TypeOffsetOp TypeOffsetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr elementType) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(elementType)>(elementType));
  auto __res__ = ::llvm::dyn_cast<TypeOffsetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeOffsetOp TypeOffsetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr elementType) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(elementType)>(elementType));
}

void TypeOffsetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Type elementType) {
  odsState.getOrAddProperties<Properties>().elementType = ::mlir::TypeAttr::get(elementType);
  odsState.addTypes(result);
}

TypeOffsetOp TypeOffsetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Type elementType) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(elementType)>(elementType));
  auto __res__ = ::llvm::dyn_cast<TypeOffsetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeOffsetOp TypeOffsetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Type elementType) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(elementType)>(elementType));
}

void TypeOffsetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Type elementType) {
  odsState.getOrAddProperties<Properties>().elementType = ::mlir::TypeAttr::get(elementType);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TypeOffsetOp TypeOffsetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Type elementType) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(elementType)>(elementType));
  auto __res__ = ::llvm::dyn_cast<TypeOffsetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeOffsetOp TypeOffsetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Type elementType) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(elementType)>(elementType));
}

void TypeOffsetOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    ::mlir::OpaqueProperties properties =
      &odsState.getOrAddProperties<TypeOffsetOp::Properties>();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

TypeOffsetOp TypeOffsetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<TypeOffsetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeOffsetOp TypeOffsetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void TypeOffsetOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

TypeOffsetOp TypeOffsetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<TypeOffsetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeOffsetOp TypeOffsetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult TypeOffsetOp::verifyInvariantsImpl() {
  auto tblgen_elementType = getProperties().elementType; (void)tblgen_elementType;
  if (!tblgen_elementType) return emitOpError("requires attribute 'elementType'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_PtrOps3(*this, tblgen_elementType, "elementType")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_PtrOps10(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult TypeOffsetOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult TypeOffsetOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::TypeAttr elementTypeAttr;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  if (parser.parseCustomAttributeWithFallback(elementTypeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (elementTypeAttr) result.getOrAddProperties<TypeOffsetOp::Properties>().elementType = elementTypeAttr;
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
  result.addTypes(resultTypes);
  return ::mlir::success();
}

void TypeOffsetOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getElementTypeAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("elementType");
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

void TypeOffsetOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::TypeOffsetOp)


#endif // GET_OP_CLASSES

