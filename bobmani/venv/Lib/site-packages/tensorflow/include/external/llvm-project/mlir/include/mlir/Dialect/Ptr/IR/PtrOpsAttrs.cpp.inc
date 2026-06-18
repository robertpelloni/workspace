/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::mlir::ptr::AddressAttr,
::mlir::ptr::GenericSpaceAttr,
::mlir::ptr::NullAttr,
::mlir::ptr::SpecAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::mlir::ptr::AddressAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::ptr::AddressAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::mlir::ptr::GenericSpaceAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::ptr::GenericSpaceAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::mlir::ptr::NullAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::ptr::NullAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::mlir::ptr::SpecAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::ptr::SpecAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::mlir::ptr::AddressAttr>([&](auto t) {
      printer << ::mlir::ptr::AddressAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::mlir::ptr::GenericSpaceAttr>([&](auto t) {
      printer << ::mlir::ptr::GenericSpaceAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::mlir::ptr::NullAttr>([&](auto t) {
      printer << ::mlir::ptr::NullAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::mlir::ptr::SpecAttr>([&](auto t) {
      printer << ::mlir::ptr::SpecAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace mlir::ptr {

namespace detail {

struct AddressAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<PtrType, ::llvm::APInt>;
  AddressAttrStorage(PtrType type, ::llvm::APInt value) : type(std::move(type)), value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(type, value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey)) && (value.getBitWidth() == std::get<1>(tblgenKey).getBitWidth() && value == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static AddressAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    auto value = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<AddressAttrStorage>()) AddressAttrStorage(std::move(type), std::move(value));
  }

  PtrType type;
  ::llvm::APInt value;
};

} // namespace detail
AddressAttr AddressAttr::get(::mlir::MLIRContext *context, PtrType type, ::llvm::APInt value) {
  return Base::get(context, std::move(type), std::move(value));
}

AddressAttr AddressAttr::get(PtrType type, const llvm::APInt &value) {
  return Base::get(type.getContext(), type, value);
}

::mlir::Attribute AddressAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<PtrType> _result_type;

  if (odsType) {
    if (auto reqType = ::llvm::dyn_cast<PtrType>(odsType)) {
      _result_type = reqType;
    } else {
      odsParser.emitError(odsLoc, "invalid kind of type specified");
      return {};
    }
  } else {
    odsParser.emitError(odsLoc, "expected a trailing type");
    return {};
  }
  ::mlir::FailureOr<::llvm::APInt> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<::llvm::APInt>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse Ptr_AddressAttr parameter 'value' which is to be a `::llvm::APInt`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_type));
  assert(::mlir::succeeded(_result_value));
  return AddressAttr::get(odsParser.getContext(),
      PtrType((*_result_type)),
      ::llvm::APInt((*_result_value)));
}

void AddressAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

PtrType AddressAttr::getType() const {
  return getImpl()->type;
}

::llvm::APInt AddressAttr::getValue() const {
  return getImpl()->value;
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::AddressAttr)
namespace mlir::ptr {

::mlir::Attribute GenericSpaceAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  return GenericSpaceAttr::get(odsParser.getContext());
}

void GenericSpaceAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::GenericSpaceAttr)
namespace mlir::ptr {

namespace detail {

struct NullAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<PtrType>;
  NullAttrStorage(PtrType type) : type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static NullAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<NullAttrStorage>()) NullAttrStorage(std::move(type));
  }

  PtrType type;
};

} // namespace detail
NullAttr NullAttr::get(::mlir::MLIRContext *context, PtrType type) {
  return Base::get(context, std::move(type));
}

NullAttr NullAttr::get(PtrType type) {
  return Base::get(type.getContext(), type);
}

::mlir::Attribute NullAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<PtrType> _result_type;

  if (odsType) {
    if (auto reqType = ::llvm::dyn_cast<PtrType>(odsType)) {
      _result_type = reqType;
    } else {
      odsParser.emitError(odsLoc, "invalid kind of type specified");
      return {};
    }
  } else {
    odsParser.emitError(odsLoc, "expected a trailing type");
    return {};
  }
  assert(::mlir::succeeded(_result_type));
  return NullAttr::get(odsParser.getContext(),
      PtrType((*_result_type)));
}

void NullAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}

PtrType NullAttr::getType() const {
  return getImpl()->type;
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::NullAttr)
namespace mlir::ptr {

namespace detail {

struct SpecAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<uint32_t, uint32_t, uint32_t, uint32_t>;
  SpecAttrStorage(uint32_t size, uint32_t abi, uint32_t preferred, uint32_t index) : size(std::move(size)), abi(std::move(abi)), preferred(std::move(preferred)), index(std::move(index)) {}

  KeyTy getAsKey() const {
    return KeyTy(size, abi, preferred, index);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (size == std::get<0>(tblgenKey)) && (abi == std::get<1>(tblgenKey)) && (preferred == std::get<2>(tblgenKey)) && (index == std::get<3>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey), std::get<3>(tblgenKey));
  }

  static SpecAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto size = std::move(std::get<0>(tblgenKey));
    auto abi = std::move(std::get<1>(tblgenKey));
    auto preferred = std::move(std::get<2>(tblgenKey));
    auto index = std::move(std::get<3>(tblgenKey));
    return new (allocator.allocate<SpecAttrStorage>()) SpecAttrStorage(std::move(size), std::move(abi), std::move(preferred), std::move(index));
  }

  uint32_t size;
  uint32_t abi;
  uint32_t preferred;
  uint32_t index;
};

} // namespace detail
SpecAttr SpecAttr::get(::mlir::MLIRContext *context, uint32_t size, uint32_t abi, uint32_t preferred, uint32_t index) {
  return Base::get(context, size, abi, preferred, index);
}

SpecAttr SpecAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, uint32_t size, uint32_t abi, uint32_t preferred, uint32_t index) {
  return Base::getChecked(emitError, context, size, abi, preferred, index);
}

::llvm::LogicalResult SpecAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, uint32_t size, uint32_t abi, uint32_t preferred, uint32_t index) {
  if (::mlir::failed(verify(emitError, size, abi, preferred, index)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Attribute SpecAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<uint32_t> _result_size;
  ::mlir::FailureOr<uint32_t> _result_abi;
  ::mlir::FailureOr<uint32_t> _result_preferred;
  ::mlir::FailureOr<uint32_t> _result_index;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  // Parse parameter struct
  bool _seen_size = false;
  bool _seen_abi = false;
  bool _seen_preferred = false;
  bool _seen_index = false;
  {
    const auto _loop_body = [&](::llvm::StringRef _paramKey) -> bool {
      // Parse literal '='
      if (odsParser.parseEqual()) return {};
      if (!_seen_size && _paramKey == "size") {
        _seen_size = true;

        // Parse variable 'size'
        _result_size = ::mlir::FieldParser<uint32_t>::parse(odsParser);
        if (::mlir::failed(_result_size)) {
          odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse Ptr_SpecAttr parameter 'size' which is to be a `uint32_t`");
          return {};
        }
      } else if (!_seen_abi && _paramKey == "abi") {
        _seen_abi = true;

        // Parse variable 'abi'
        _result_abi = ::mlir::FieldParser<uint32_t>::parse(odsParser);
        if (::mlir::failed(_result_abi)) {
          odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse Ptr_SpecAttr parameter 'abi' which is to be a `uint32_t`");
          return {};
        }
      } else if (!_seen_preferred && _paramKey == "preferred") {
        _seen_preferred = true;

        // Parse variable 'preferred'
        _result_preferred = ::mlir::FieldParser<uint32_t>::parse(odsParser);
        if (::mlir::failed(_result_preferred)) {
          odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse Ptr_SpecAttr parameter 'preferred' which is to be a `uint32_t`");
          return {};
        }
      } else if (!_seen_index && _paramKey == "index") {
        _seen_index = true;

        // Parse variable 'index'
        _result_index = ::mlir::FieldParser<uint32_t>::parse(odsParser);
        if (::mlir::failed(_result_index)) {
          odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse Ptr_SpecAttr parameter 'index' which is to be a `uint32_t`");
          return {};
        }
      } else {
        odsParser.emitError(odsParser.getCurrentLocation(), "duplicate or unknown struct parameter name: ") << _paramKey;
        return {};
      }
      return true;
    };
    do {
      ::llvm::StringRef _paramKey;
      if (odsParser.parseKeyword(&_paramKey)) {
        odsParser.emitError(odsParser.getCurrentLocation(),
                           "expected a parameter name in struct");
        return {};
      }
      if (!_loop_body(_paramKey)) return {};
    } while(!odsParser.parseOptionalComma());
    if (!_seen_size) {
      odsParser.emitError(odsParser.getCurrentLocation(), "struct is missing required parameter: ") << "size";
      return {};
    }
    if (!_seen_abi) {
      odsParser.emitError(odsParser.getCurrentLocation(), "struct is missing required parameter: ") << "abi";
      return {};
    }
    if (!_seen_preferred) {
      odsParser.emitError(odsParser.getCurrentLocation(), "struct is missing required parameter: ") << "preferred";
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_size));
  assert(::mlir::succeeded(_result_abi));
  assert(::mlir::succeeded(_result_preferred));
  return odsParser.getChecked<SpecAttr>(odsLoc, odsParser.getContext(),
      uint32_t((*_result_size)),
      uint32_t((*_result_abi)),
      uint32_t((*_result_preferred)),
      uint32_t((_result_index.value_or(kOptionalSpecValue))));
}

void SpecAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  {
    bool _firstPrinted = true;
    if (!_firstPrinted) odsPrinter << ", ";
    _firstPrinted = false;
    odsPrinter << "size = ";
    odsPrinter.printStrippedAttrOrType(getSize());
    if (!_firstPrinted) odsPrinter << ", ";
    _firstPrinted = false;
    odsPrinter << "abi = ";
    odsPrinter.printStrippedAttrOrType(getAbi());
    if (!_firstPrinted) odsPrinter << ", ";
    _firstPrinted = false;
    odsPrinter << "preferred = ";
    odsPrinter.printStrippedAttrOrType(getPreferred());
    if (!(getIndex() == kOptionalSpecValue)) {
      if (!_firstPrinted) odsPrinter << ", ";
      _firstPrinted = false;
      odsPrinter << "index = ";
      if (!(getIndex() == kOptionalSpecValue)) {
        odsPrinter.printStrippedAttrOrType(getIndex());
      }
    }
  }
  odsPrinter << ">";
}

uint32_t SpecAttr::getSize() const {
  return getImpl()->size;
}

uint32_t SpecAttr::getAbi() const {
  return getImpl()->abi;
}

uint32_t SpecAttr::getPreferred() const {
  return getImpl()->preferred;
}

uint32_t SpecAttr::getIndex() const {
  return getImpl()->index;
}


} // namespace mlir::ptr
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::ptr::SpecAttr)
namespace mlir::ptr {


/// Parse an attribute registered to this dialect.
::mlir::Attribute PtrDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void PtrDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace mlir::ptr

#endif // GET_ATTRDEF_CLASSES

