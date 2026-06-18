/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::mlir::transform::ParamOperandAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::mlir::transform::ParamOperandAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::transform::ParamOperandAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::mlir::transform::ParamOperandAttr>([&](auto t) {
      printer << ::mlir::transform::ParamOperandAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace mlir::transform {

namespace detail {

struct ParamOperandAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<IntegerAttr>;
  ParamOperandAttrStorage(IntegerAttr index) : index(std::move(index)) {}

  KeyTy getAsKey() const {
    return KeyTy(index);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (index == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ParamOperandAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto index = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ParamOperandAttrStorage>()) ParamOperandAttrStorage(std::move(index));
  }

  IntegerAttr index;
};

} // namespace detail
ParamOperandAttr ParamOperandAttr::get(::mlir::MLIRContext *context, IntegerAttr index) {
  return Base::get(context, std::move(index));
}

::mlir::Attribute ParamOperandAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<IntegerAttr> _result_index;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  // Parse literal 'index'
  if (odsParser.parseKeyword("index")) return {};
  // Parse literal '='
  if (odsParser.parseEqual()) return {};

  // Parse variable 'index'
  _result_index = ::mlir::FieldParser<IntegerAttr>::parse(odsParser);
  if (::mlir::failed(_result_index)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ParamOperandAttr parameter 'index' which is to be a `IntegerAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_index));
  return ParamOperandAttr::get(odsParser.getContext(),
      IntegerAttr((*_result_index)));
}

void ParamOperandAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter << "index";
  odsPrinter << ' ' << "=";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getIndex());
  odsPrinter << ">";
}

IntegerAttr ParamOperandAttr::getIndex() const {
  return getImpl()->index;
}


} // namespace mlir::transform
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::transform::ParamOperandAttr)
namespace mlir::transform {


/// Parse an attribute registered to this dialect.
::mlir::Attribute TransformDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void TransformDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace mlir::transform

#endif // GET_ATTRDEF_CLASSES

