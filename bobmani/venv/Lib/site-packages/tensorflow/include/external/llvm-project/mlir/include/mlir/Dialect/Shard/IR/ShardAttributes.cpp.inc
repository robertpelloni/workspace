/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::mlir::shard::ReductionKindAttr,
::mlir::shard::GridAxesArrayAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::mlir::shard::ReductionKindAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::shard::ReductionKindAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::mlir::shard::GridAxesArrayAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::shard::GridAxesArrayAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::mlir::shard::ReductionKindAttr>([&](auto t) {
      printer << ::mlir::shard::ReductionKindAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::mlir::shard::GridAxesArrayAttr>([&](auto t) {
      printer << ::mlir::shard::GridAxesArrayAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace mlir::shard {

namespace detail {

struct ReductionKindAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::shard::ReductionKind>;
  ReductionKindAttrStorage(::mlir::shard::ReductionKind value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ReductionKindAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ReductionKindAttrStorage>()) ReductionKindAttrStorage(std::move(value));
  }

  ::mlir::shard::ReductionKind value;
};

} // namespace detail
ReductionKindAttr ReductionKindAttr::get(::mlir::MLIRContext *context, ::mlir::shard::ReductionKind value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute ReductionKindAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::shard::ReductionKind> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<::mlir::shard::ReductionKind> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = ::mlir::shard::symbolizeReductionKind(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "::mlir::shard::ReductionKind" << " to be one of: " << "sum" << ", " << "max" << ", " << "min" << ", " << "product" << ", " << "average" << ", " << "bitwise_and" << ", " << "bitwise_or" << ", " << "bitwise_xor" << ", " << "generic")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse Shard_ReductionKindAttr parameter 'value' which is to be a `::mlir::shard::ReductionKind`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return ReductionKindAttr::get(odsParser.getContext(),
      ::mlir::shard::ReductionKind((*_result_value)));
}

void ReductionKindAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << ' ';
  odsPrinter << stringifyReductionKind(getValue());
}

::mlir::shard::ReductionKind ReductionKindAttr::getValue() const {
  return getImpl()->value;
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ReductionKindAttr)
namespace mlir::shard {

namespace detail {

struct GridAxesArrayAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<GridAxesAttr>>;
  GridAxesArrayAttrStorage(::llvm::ArrayRef<GridAxesAttr> axes) : axes(std::move(axes)) {}

  KeyTy getAsKey() const {
    return KeyTy(axes);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (axes == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static GridAxesArrayAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto axes = std::move(std::get<0>(tblgenKey));
    axes = allocator.copyInto(axes);
    return new (allocator.allocate<GridAxesArrayAttrStorage>()) GridAxesArrayAttrStorage(std::move(axes));
  }

  ::llvm::ArrayRef<GridAxesAttr> axes;
};

} // namespace detail
GridAxesArrayAttr GridAxesArrayAttr::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<GridAxesAttr> axes) {
  return Base::get(context, std::move(axes));
}

::mlir::Attribute GridAxesArrayAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::llvm::SmallVector<GridAxesAttr>> _result_axes;
  // Parse literal '['
  if (odsParser.parseLSquare()) return {};

  // Parse variable 'axes'
  _result_axes = ::mlir::FieldParser<::llvm::SmallVector<GridAxesAttr>>::parse(odsParser);
  if (::mlir::failed(_result_axes)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse Shard_GridAxesArrayAttr parameter 'axes' which is to be a `::llvm::ArrayRef<GridAxesAttr>`");
    return {};
  }
  // Parse literal ']'
  if (odsParser.parseRSquare()) return {};
  assert(::mlir::succeeded(_result_axes));
  return GridAxesArrayAttr::get(odsParser.getContext(),
      ::llvm::ArrayRef<GridAxesAttr>((*_result_axes)));
}

void GridAxesArrayAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "[";
  odsPrinter.printStrippedAttrOrType(getAxes());
  odsPrinter << "]";
}

::llvm::ArrayRef<GridAxesAttr> GridAxesArrayAttr::getAxes() const {
  return getImpl()->axes;
}


} // namespace mlir::shard
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::GridAxesArrayAttr)
namespace mlir::shard {


/// Parse an attribute registered to this dialect.
::mlir::Attribute ShardDialect::parseAttribute(::mlir::DialectAsmParser &parser,
                                      ::mlir::Type type) const {
  ::llvm::SMLoc typeLoc = parser.getCurrentLocation();
  ::llvm::StringRef attrTag;
  {
    ::mlir::Attribute attr;
    auto parseResult = generatedAttributeParser(parser, &attrTag, type, attr);
    if (parseResult.has_value())
      return attr;
  }
  
  parser.emitError(typeLoc) << "unknown attribute `"
      << attrTag << "` in dialect `" << getNamespace() << "`";
  return {};
}
/// Print an attribute registered to this dialect.
void ShardDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace mlir::shard

#endif // GET_ATTRDEF_CLASSES

