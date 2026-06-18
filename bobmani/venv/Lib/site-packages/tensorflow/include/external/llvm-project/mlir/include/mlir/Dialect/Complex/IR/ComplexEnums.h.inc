/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ComplexAttributes.td                                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::complex {

// Complex range flags
enum class ComplexRangeFlags : uint32_t {
  improved = 1,
  basic = 2,
  none = 4,
};

::std::optional<ComplexRangeFlags> symbolizeComplexRangeFlags(uint32_t);
std::string stringifyComplexRangeFlags(ComplexRangeFlags);
::std::optional<ComplexRangeFlags> symbolizeComplexRangeFlags(::llvm::StringRef);

inline constexpr ComplexRangeFlags operator|(ComplexRangeFlags a, ComplexRangeFlags b) {
  return static_cast<ComplexRangeFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline constexpr ComplexRangeFlags operator&(ComplexRangeFlags a, ComplexRangeFlags b) {
  return static_cast<ComplexRangeFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
inline constexpr ComplexRangeFlags operator^(ComplexRangeFlags a, ComplexRangeFlags b) {
  return static_cast<ComplexRangeFlags>(static_cast<uint32_t>(a) ^ static_cast<uint32_t>(b));
}
inline constexpr ComplexRangeFlags &operator|=(ComplexRangeFlags &a, ComplexRangeFlags b) {
    return a = a | b;
}
inline constexpr ComplexRangeFlags &operator&=(ComplexRangeFlags &a, ComplexRangeFlags b) {
    return a = a & b;
}
inline constexpr ComplexRangeFlags &operator^=(ComplexRangeFlags &a, ComplexRangeFlags b) {
    return a = a ^ b;
}
inline constexpr ComplexRangeFlags operator~(ComplexRangeFlags bits) {
  // Ensure only bits that can be present in the enum are set
  return static_cast<ComplexRangeFlags>(~static_cast<uint32_t>(bits) & static_cast<uint32_t>(7u));
}
inline constexpr bool bitEnumContainsAll(ComplexRangeFlags bits, ComplexRangeFlags bit) {
  return (bits & bit) == bit;
}
inline constexpr bool bitEnumContainsAny(ComplexRangeFlags bits, ComplexRangeFlags bit) {
  return (static_cast<uint32_t>(bits) & static_cast<uint32_t>(bit)) != 0;
}
inline constexpr ComplexRangeFlags bitEnumClear(ComplexRangeFlags bits, ComplexRangeFlags bit) {
  return bits & ~bit;
}
inline constexpr ComplexRangeFlags bitEnumSet(ComplexRangeFlags bits, ComplexRangeFlags bit, /*optional*/bool value=true) {
  return value ? (bits | bit) : bitEnumClear(bits, bit);
}
  
inline std::string stringifyEnum(ComplexRangeFlags enumValue) {
  return stringifyComplexRangeFlags(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ComplexRangeFlags> symbolizeEnum<ComplexRangeFlags>(::llvm::StringRef str) {
  return symbolizeComplexRangeFlags(str);
}

class ComplexRangeFlagsAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ComplexRangeFlags;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ComplexRangeFlagsAttr get(::mlir::MLIRContext *context, ComplexRangeFlags val);
  ComplexRangeFlags getValue() const;
};

} // namespace mlir::complex

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::complex::ComplexRangeFlags, ::mlir::complex::ComplexRangeFlags> {
  template <typename ParserT>
  static FailureOr<::mlir::complex::ComplexRangeFlags> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Complex range flags");

    // Symbolize the keyword.
    if (::std::optional<::mlir::complex::ComplexRangeFlags> attr = ::mlir::complex::symbolizeEnum<::mlir::complex::ComplexRangeFlags>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [improved, basic, none] for Complex range flags, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::complex::ComplexRangeFlags>, std::optional<::mlir::complex::ComplexRangeFlags>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::complex::ComplexRangeFlags>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::complex::ComplexRangeFlags>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::complex::ComplexRangeFlags> attr = ::mlir::complex::symbolizeEnum<::mlir::complex::ComplexRangeFlags>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [improved, basic, none] for Complex range flags, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::complex::ComplexRangeFlags value) {
  auto valueStr = stringifyEnum(value);
  auto underlyingValue = static_cast<std::make_unsigned_t<::mlir::complex::ComplexRangeFlags>>(value);
  if (underlyingValue && !llvm::has_single_bit(underlyingValue))
    return p << '"' << valueStr << '"';
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::complex::ComplexRangeFlags> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::complex::ComplexRangeFlags getEmptyKey() {
    return static_cast<::mlir::complex::ComplexRangeFlags>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::complex::ComplexRangeFlags getTombstoneKey() {
    return static_cast<::mlir::complex::ComplexRangeFlags>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::complex::ComplexRangeFlags &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::complex::ComplexRangeFlags &lhs, const ::mlir::complex::ComplexRangeFlags &rhs) {
    return lhs == rhs;
  }
};
}

