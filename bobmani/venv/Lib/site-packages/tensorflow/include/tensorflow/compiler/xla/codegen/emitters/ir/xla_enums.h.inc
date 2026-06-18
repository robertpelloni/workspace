/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: xla_attrs.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace xla {

// a dimension, either 'x', 'y', or 'z'
enum class WorkGroupDimension : uint32_t {
  x = 0,
  y = 1,
  z = 2,
};

::std::optional<WorkGroupDimension> symbolizeWorkGroupDimension(uint32_t);
::llvm::StringRef stringifyWorkGroupDimension(WorkGroupDimension);
::std::optional<WorkGroupDimension> symbolizeWorkGroupDimension(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForWorkGroupDimension() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(WorkGroupDimension enumValue) {
  return stringifyWorkGroupDimension(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<WorkGroupDimension> symbolizeEnum<WorkGroupDimension>(::llvm::StringRef str) {
  return symbolizeWorkGroupDimension(str);
}

} // namespace xla

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::xla::WorkGroupDimension, ::xla::WorkGroupDimension> {
  template <typename ParserT>
  static FailureOr<::xla::WorkGroupDimension> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for a dimension, either 'x', 'y', or 'z'");

    // Symbolize the keyword.
    if (::std::optional<::xla::WorkGroupDimension> attr = ::xla::symbolizeEnum<::xla::WorkGroupDimension>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [x, y, z] for a dimension, either 'x', 'y', or 'z', got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::xla::WorkGroupDimension>, std::optional<::xla::WorkGroupDimension>> {
  template <typename ParserT>
  static FailureOr<std::optional<::xla::WorkGroupDimension>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::xla::WorkGroupDimension>{};

    // Symbolize the keyword.
    if (::std::optional<::xla::WorkGroupDimension> attr = ::xla::symbolizeEnum<::xla::WorkGroupDimension>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [x, y, z] for a dimension, either 'x', 'y', or 'z', got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::xla::WorkGroupDimension value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::xla::WorkGroupDimension> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::xla::WorkGroupDimension getEmptyKey() {
    return static_cast<::xla::WorkGroupDimension>(StorageInfo::getEmptyKey());
  }

  static inline ::xla::WorkGroupDimension getTombstoneKey() {
    return static_cast<::xla::WorkGroupDimension>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::xla::WorkGroupDimension &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::xla::WorkGroupDimension &lhs, const ::xla::WorkGroupDimension &rhs) {
    return lhs == rhs;
  }
};
}

namespace xla {

// XLA Backend kind (or type)
enum class BackendKind : uint32_t {
  kCpu = 0,
  kGpu = 1,
  kTpu = 2,
};

::std::optional<BackendKind> symbolizeBackendKind(uint32_t);
::llvm::StringRef stringifyBackendKind(BackendKind);
::std::optional<BackendKind> symbolizeBackendKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForBackendKind() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(BackendKind enumValue) {
  return stringifyBackendKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<BackendKind> symbolizeEnum<BackendKind>(::llvm::StringRef str) {
  return symbolizeBackendKind(str);
}

} // namespace xla

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::xla::BackendKind, ::xla::BackendKind> {
  template <typename ParserT>
  static FailureOr<::xla::BackendKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for XLA Backend kind (or type)");

    // Symbolize the keyword.
    if (::std::optional<::xla::BackendKind> attr = ::xla::symbolizeEnum<::xla::BackendKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [cpu, gpu, tpu] for XLA Backend kind (or type), got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::xla::BackendKind>, std::optional<::xla::BackendKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::xla::BackendKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::xla::BackendKind>{};

    // Symbolize the keyword.
    if (::std::optional<::xla::BackendKind> attr = ::xla::symbolizeEnum<::xla::BackendKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [cpu, gpu, tpu] for XLA Backend kind (or type), got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::xla::BackendKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::xla::BackendKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::xla::BackendKind getEmptyKey() {
    return static_cast<::xla::BackendKind>(StorageInfo::getEmptyKey());
  }

  static inline ::xla::BackendKind getTombstoneKey() {
    return static_cast<::xla::BackendKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::xla::BackendKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::xla::BackendKind &lhs, const ::xla::BackendKind &rhs) {
    return lhs == rhs;
  }
};
}

