/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LinalgEnums.td                                                       *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::linalg {

// allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
enum class BinaryFn : uint32_t {
  add = 0,
  sub = 1,
  mul = 2,
  div = 3,
  div_unsigned = 4,
  max_signed = 5,
  min_signed = 6,
  max_unsigned = 7,
  min_unsigned = 8,
  powf = 9,
};

::std::optional<BinaryFn> symbolizeBinaryFn(uint32_t);
::llvm::StringRef stringifyBinaryFn(BinaryFn);
::std::optional<BinaryFn> symbolizeBinaryFn(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForBinaryFn() {
  return 9;
}


inline ::llvm::StringRef stringifyEnum(BinaryFn enumValue) {
  return stringifyBinaryFn(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<BinaryFn> symbolizeEnum<BinaryFn>(::llvm::StringRef str) {
  return symbolizeBinaryFn(str);
}

} // namespace mlir::linalg

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::linalg::BinaryFn, ::mlir::linalg::BinaryFn> {
  template <typename ParserT>
  static FailureOr<::mlir::linalg::BinaryFn> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9");

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::BinaryFn> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::BinaryFn>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [add, sub, mul, div, div_unsigned, max_signed, min_signed, max_unsigned, min_unsigned, powf] for allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::linalg::BinaryFn>, std::optional<::mlir::linalg::BinaryFn>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::linalg::BinaryFn>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::linalg::BinaryFn>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::BinaryFn> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::BinaryFn>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [add, sub, mul, div, div_unsigned, max_signed, min_signed, max_unsigned, min_unsigned, powf] for allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::linalg::BinaryFn value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::linalg::BinaryFn> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::linalg::BinaryFn getEmptyKey() {
    return static_cast<::mlir::linalg::BinaryFn>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::linalg::BinaryFn getTombstoneKey() {
    return static_cast<::mlir::linalg::BinaryFn>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::linalg::BinaryFn &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::linalg::BinaryFn &lhs, const ::mlir::linalg::BinaryFn &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::linalg {

// allowed 32-bit signless integer cases: 1, 2, 3
enum class ElementwiseArityGroup : uint32_t {
  Unary = 1,
  Binary = 2,
  Ternary = 3,
};

::std::optional<ElementwiseArityGroup> symbolizeElementwiseArityGroup(uint32_t);
::llvm::StringRef stringifyElementwiseArityGroup(ElementwiseArityGroup);
::std::optional<ElementwiseArityGroup> symbolizeElementwiseArityGroup(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForElementwiseArityGroup() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(ElementwiseArityGroup enumValue) {
  return stringifyElementwiseArityGroup(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ElementwiseArityGroup> symbolizeEnum<ElementwiseArityGroup>(::llvm::StringRef str) {
  return symbolizeElementwiseArityGroup(str);
}

} // namespace mlir::linalg

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::linalg::ElementwiseArityGroup, ::mlir::linalg::ElementwiseArityGroup> {
  template <typename ParserT>
  static FailureOr<::mlir::linalg::ElementwiseArityGroup> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for allowed 32-bit signless integer cases: 1, 2, 3");

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::ElementwiseArityGroup> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::ElementwiseArityGroup>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [Unary, Binary, Ternary] for allowed 32-bit signless integer cases: 1, 2, 3, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::linalg::ElementwiseArityGroup>, std::optional<::mlir::linalg::ElementwiseArityGroup>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::linalg::ElementwiseArityGroup>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::linalg::ElementwiseArityGroup>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::ElementwiseArityGroup> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::ElementwiseArityGroup>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [Unary, Binary, Ternary] for allowed 32-bit signless integer cases: 1, 2, 3, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::linalg::ElementwiseArityGroup value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::linalg::ElementwiseArityGroup> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::linalg::ElementwiseArityGroup getEmptyKey() {
    return static_cast<::mlir::linalg::ElementwiseArityGroup>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::linalg::ElementwiseArityGroup getTombstoneKey() {
    return static_cast<::mlir::linalg::ElementwiseArityGroup>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::linalg::ElementwiseArityGroup &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::linalg::ElementwiseArityGroup &lhs, const ::mlir::linalg::ElementwiseArityGroup &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::linalg {

// allowed 32-bit signless integer cases: 
enum class ElementwiseCaseLimits : uint32_t {
  LastUnary = 13,
  LastBinary = 23,
  LastTernary = 24,
};

::std::optional<ElementwiseCaseLimits> symbolizeElementwiseCaseLimits(uint32_t);
::llvm::StringRef stringifyElementwiseCaseLimits(ElementwiseCaseLimits);
::std::optional<ElementwiseCaseLimits> symbolizeElementwiseCaseLimits(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForElementwiseCaseLimits() {
  return 24;
}


inline ::llvm::StringRef stringifyEnum(ElementwiseCaseLimits enumValue) {
  return stringifyElementwiseCaseLimits(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ElementwiseCaseLimits> symbolizeEnum<ElementwiseCaseLimits>(::llvm::StringRef str) {
  return symbolizeElementwiseCaseLimits(str);
}

} // namespace mlir::linalg

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::linalg::ElementwiseCaseLimits, ::mlir::linalg::ElementwiseCaseLimits> {
  template <typename ParserT>
  static FailureOr<::mlir::linalg::ElementwiseCaseLimits> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for allowed 32-bit signless integer cases: ");

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::ElementwiseCaseLimits> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::ElementwiseCaseLimits>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [LastUnary, LastBinary, LastTernary] for allowed 32-bit signless integer cases: , got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::linalg::ElementwiseCaseLimits>, std::optional<::mlir::linalg::ElementwiseCaseLimits>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::linalg::ElementwiseCaseLimits>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::linalg::ElementwiseCaseLimits>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::ElementwiseCaseLimits> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::ElementwiseCaseLimits>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [LastUnary, LastBinary, LastTernary] for allowed 32-bit signless integer cases: , got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::linalg::ElementwiseCaseLimits value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::linalg::ElementwiseCaseLimits> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::linalg::ElementwiseCaseLimits getEmptyKey() {
    return static_cast<::mlir::linalg::ElementwiseCaseLimits>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::linalg::ElementwiseCaseLimits getTombstoneKey() {
    return static_cast<::mlir::linalg::ElementwiseCaseLimits>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::linalg::ElementwiseCaseLimits &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::linalg::ElementwiseCaseLimits &lhs, const ::mlir::linalg::ElementwiseCaseLimits &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::linalg {

// allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23
enum class ElementwiseKind : uint32_t {
  exp = 0,
  log = 1,
  abs = 2,
  ceil = 3,
  floor = 4,
  negf = 5,
  reciprocal = 6,
  round = 7,
  sqrt = 8,
  rsqrt = 9,
  square = 10,
  tanh = 11,
  erf = 12,
  add = 13,
  sub = 14,
  mul = 15,
  div = 16,
  div_unsigned = 17,
  max_signed = 18,
  min_signed = 19,
  max_unsigned = 20,
  min_unsigned = 21,
  powf = 22,
  select = 23,
};

::std::optional<ElementwiseKind> symbolizeElementwiseKind(uint32_t);
::llvm::StringRef stringifyElementwiseKind(ElementwiseKind);
::std::optional<ElementwiseKind> symbolizeElementwiseKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForElementwiseKind() {
  return 23;
}


inline ::llvm::StringRef stringifyEnum(ElementwiseKind enumValue) {
  return stringifyElementwiseKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ElementwiseKind> symbolizeEnum<ElementwiseKind>(::llvm::StringRef str) {
  return symbolizeElementwiseKind(str);
}

} // namespace mlir::linalg

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::linalg::ElementwiseKind, ::mlir::linalg::ElementwiseKind> {
  template <typename ParserT>
  static FailureOr<::mlir::linalg::ElementwiseKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23");

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::ElementwiseKind> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::ElementwiseKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [exp, log, abs, ceil, floor, negf, reciprocal, round, sqrt, rsqrt, square, tanh, erf, add, sub, mul, div, div_unsigned, max_signed, min_signed, max_unsigned, min_unsigned, powf, select] for allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::linalg::ElementwiseKind>, std::optional<::mlir::linalg::ElementwiseKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::linalg::ElementwiseKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::linalg::ElementwiseKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::ElementwiseKind> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::ElementwiseKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [exp, log, abs, ceil, floor, negf, reciprocal, round, sqrt, rsqrt, square, tanh, erf, add, sub, mul, div, div_unsigned, max_signed, min_signed, max_unsigned, min_unsigned, powf, select] for allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::linalg::ElementwiseKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::linalg::ElementwiseKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::linalg::ElementwiseKind getEmptyKey() {
    return static_cast<::mlir::linalg::ElementwiseKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::linalg::ElementwiseKind getTombstoneKey() {
    return static_cast<::mlir::linalg::ElementwiseKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::linalg::ElementwiseKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::linalg::ElementwiseKind &lhs, const ::mlir::linalg::ElementwiseKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::linalg {

// allowed 32-bit signless integer cases: 0
enum class TernaryFn : uint32_t {
  select = 0,
};

::std::optional<TernaryFn> symbolizeTernaryFn(uint32_t);
::llvm::StringRef stringifyTernaryFn(TernaryFn);
::std::optional<TernaryFn> symbolizeTernaryFn(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForTernaryFn() {
  return 0;
}


inline ::llvm::StringRef stringifyEnum(TernaryFn enumValue) {
  return stringifyTernaryFn(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<TernaryFn> symbolizeEnum<TernaryFn>(::llvm::StringRef str) {
  return symbolizeTernaryFn(str);
}

} // namespace mlir::linalg

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::linalg::TernaryFn, ::mlir::linalg::TernaryFn> {
  template <typename ParserT>
  static FailureOr<::mlir::linalg::TernaryFn> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for allowed 32-bit signless integer cases: 0");

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::TernaryFn> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::TernaryFn>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [select] for allowed 32-bit signless integer cases: 0, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::linalg::TernaryFn>, std::optional<::mlir::linalg::TernaryFn>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::linalg::TernaryFn>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::linalg::TernaryFn>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::TernaryFn> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::TernaryFn>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [select] for allowed 32-bit signless integer cases: 0, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::linalg::TernaryFn value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::linalg::TernaryFn> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::linalg::TernaryFn getEmptyKey() {
    return static_cast<::mlir::linalg::TernaryFn>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::linalg::TernaryFn getTombstoneKey() {
    return static_cast<::mlir::linalg::TernaryFn>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::linalg::TernaryFn &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::linalg::TernaryFn &lhs, const ::mlir::linalg::TernaryFn &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::linalg {

// allowed 32-bit signless integer cases: 0, 1
enum class TypeFn : uint32_t {
  cast_signed = 0,
  cast_unsigned = 1,
};

::std::optional<TypeFn> symbolizeTypeFn(uint32_t);
::llvm::StringRef stringifyTypeFn(TypeFn);
::std::optional<TypeFn> symbolizeTypeFn(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForTypeFn() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(TypeFn enumValue) {
  return stringifyTypeFn(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<TypeFn> symbolizeEnum<TypeFn>(::llvm::StringRef str) {
  return symbolizeTypeFn(str);
}

} // namespace mlir::linalg

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::linalg::TypeFn, ::mlir::linalg::TypeFn> {
  template <typename ParserT>
  static FailureOr<::mlir::linalg::TypeFn> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for allowed 32-bit signless integer cases: 0, 1");

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::TypeFn> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::TypeFn>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [cast_signed, cast_unsigned] for allowed 32-bit signless integer cases: 0, 1, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::linalg::TypeFn>, std::optional<::mlir::linalg::TypeFn>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::linalg::TypeFn>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::linalg::TypeFn>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::TypeFn> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::TypeFn>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [cast_signed, cast_unsigned] for allowed 32-bit signless integer cases: 0, 1, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::linalg::TypeFn value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::linalg::TypeFn> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::linalg::TypeFn getEmptyKey() {
    return static_cast<::mlir::linalg::TypeFn>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::linalg::TypeFn getTombstoneKey() {
    return static_cast<::mlir::linalg::TypeFn>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::linalg::TypeFn &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::linalg::TypeFn &lhs, const ::mlir::linalg::TypeFn &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::linalg {

// allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
enum class UnaryFn : uint32_t {
  exp = 0,
  log = 1,
  abs = 2,
  ceil = 3,
  floor = 4,
  negf = 5,
  reciprocal = 6,
  round = 7,
  sqrt = 8,
  rsqrt = 9,
  square = 10,
  tanh = 11,
  erf = 12,
};

::std::optional<UnaryFn> symbolizeUnaryFn(uint32_t);
::llvm::StringRef stringifyUnaryFn(UnaryFn);
::std::optional<UnaryFn> symbolizeUnaryFn(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForUnaryFn() {
  return 12;
}


inline ::llvm::StringRef stringifyEnum(UnaryFn enumValue) {
  return stringifyUnaryFn(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<UnaryFn> symbolizeEnum<UnaryFn>(::llvm::StringRef str) {
  return symbolizeUnaryFn(str);
}

} // namespace mlir::linalg

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::linalg::UnaryFn, ::mlir::linalg::UnaryFn> {
  template <typename ParserT>
  static FailureOr<::mlir::linalg::UnaryFn> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12");

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::UnaryFn> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::UnaryFn>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [exp, log, abs, ceil, floor, negf, reciprocal, round, sqrt, rsqrt, square, tanh, erf] for allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::linalg::UnaryFn>, std::optional<::mlir::linalg::UnaryFn>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::linalg::UnaryFn>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::linalg::UnaryFn>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::linalg::UnaryFn> attr = ::mlir::linalg::symbolizeEnum<::mlir::linalg::UnaryFn>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [exp, log, abs, ceil, floor, negf, reciprocal, round, sqrt, rsqrt, square, tanh, erf] for allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::linalg::UnaryFn value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::linalg::UnaryFn> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::linalg::UnaryFn getEmptyKey() {
    return static_cast<::mlir::linalg::UnaryFn>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::linalg::UnaryFn getTombstoneKey() {
    return static_cast<::mlir::linalg::UnaryFn>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::linalg::UnaryFn &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::linalg::UnaryFn &lhs, const ::mlir::linalg::UnaryFn &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::linalg {

// allowed 32-bit signless integer cases: 0, 1, 2
enum class WinogradConv2DFmr : uint32_t {
  F_2_3 = 0,
  F_4_3 = 1,
  F_2_5 = 2,
};

::std::optional<WinogradConv2DFmr> symbolizeWinogradConv2DFmr(uint32_t);
::llvm::StringRef stringifyWinogradConv2DFmr(WinogradConv2DFmr);
::std::optional<WinogradConv2DFmr> symbolizeWinogradConv2DFmr(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForWinogradConv2DFmr() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(WinogradConv2DFmr enumValue) {
  return stringifyWinogradConv2DFmr(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<WinogradConv2DFmr> symbolizeEnum<WinogradConv2DFmr>(::llvm::StringRef str) {
  return symbolizeWinogradConv2DFmr(str);
}

class WinogradConv2DFmrAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = WinogradConv2DFmr;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static WinogradConv2DFmrAttr get(::mlir::MLIRContext *context, WinogradConv2DFmr val);
  WinogradConv2DFmr getValue() const;
};

} // namespace mlir::linalg

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<mlir::linalg::WinogradConv2DFmr, mlir::linalg::WinogradConv2DFmr> {
  template <typename ParserT>
  static FailureOr<mlir::linalg::WinogradConv2DFmr> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for allowed 32-bit signless integer cases: 0, 1, 2");

    // Symbolize the keyword.
    if (::std::optional<mlir::linalg::WinogradConv2DFmr> attr = mlir::linalg::symbolizeEnum<mlir::linalg::WinogradConv2DFmr>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [F_2_3, F_4_3, F_2_5] for allowed 32-bit signless integer cases: 0, 1, 2, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<mlir::linalg::WinogradConv2DFmr>, std::optional<mlir::linalg::WinogradConv2DFmr>> {
  template <typename ParserT>
  static FailureOr<std::optional<mlir::linalg::WinogradConv2DFmr>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<mlir::linalg::WinogradConv2DFmr>{};

    // Symbolize the keyword.
    if (::std::optional<mlir::linalg::WinogradConv2DFmr> attr = mlir::linalg::symbolizeEnum<mlir::linalg::WinogradConv2DFmr>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [F_2_3, F_4_3, F_2_5] for allowed 32-bit signless integer cases: 0, 1, 2, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, mlir::linalg::WinogradConv2DFmr value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<mlir::linalg::WinogradConv2DFmr> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline mlir::linalg::WinogradConv2DFmr getEmptyKey() {
    return static_cast<mlir::linalg::WinogradConv2DFmr>(StorageInfo::getEmptyKey());
  }

  static inline mlir::linalg::WinogradConv2DFmr getTombstoneKey() {
    return static_cast<mlir::linalg::WinogradConv2DFmr>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const mlir::linalg::WinogradConv2DFmr &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const mlir::linalg::WinogradConv2DFmr &lhs, const mlir::linalg::WinogradConv2DFmr &rhs) {
    return lhs == rhs;
  }
};
}

