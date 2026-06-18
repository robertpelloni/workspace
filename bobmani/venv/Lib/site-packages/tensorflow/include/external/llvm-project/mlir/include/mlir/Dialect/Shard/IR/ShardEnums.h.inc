/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ShardOps.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::shard {

// Reduction of an iterator/grid dimension.
enum class ReductionKind : uint32_t {
  Sum = 1,
  Max = 2,
  Min = 3,
  Product = 4,
  Average = 5,
  BitwiseAnd = 6,
  BitwiseOr = 7,
  BitwiseXor = 8,
  Generic = 100,
};

::std::optional<ReductionKind> symbolizeReductionKind(uint32_t);
::llvm::StringRef stringifyReductionKind(ReductionKind);
::std::optional<ReductionKind> symbolizeReductionKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForReductionKind() {
  return 100;
}


inline ::llvm::StringRef stringifyEnum(ReductionKind enumValue) {
  return stringifyReductionKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ReductionKind> symbolizeEnum<ReductionKind>(::llvm::StringRef str) {
  return symbolizeReductionKind(str);
}

} // namespace mlir::shard

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::shard::ReductionKind, ::mlir::shard::ReductionKind> {
  template <typename ParserT>
  static FailureOr<::mlir::shard::ReductionKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Reduction of an iterator/grid dimension.");

    // Symbolize the keyword.
    if (::std::optional<::mlir::shard::ReductionKind> attr = ::mlir::shard::symbolizeEnum<::mlir::shard::ReductionKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [sum, max, min, product, average, bitwise_and, bitwise_or, bitwise_xor, generic] for Reduction of an iterator/grid dimension., got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::shard::ReductionKind>, std::optional<::mlir::shard::ReductionKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::shard::ReductionKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::shard::ReductionKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::shard::ReductionKind> attr = ::mlir::shard::symbolizeEnum<::mlir::shard::ReductionKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [sum, max, min, product, average, bitwise_and, bitwise_or, bitwise_xor, generic] for Reduction of an iterator/grid dimension., got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::shard::ReductionKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::shard::ReductionKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::shard::ReductionKind getEmptyKey() {
    return static_cast<::mlir::shard::ReductionKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::shard::ReductionKind getTombstoneKey() {
    return static_cast<::mlir::shard::ReductionKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::shard::ReductionKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::shard::ReductionKind &lhs, const ::mlir::shard::ReductionKind &rhs) {
    return lhs == rhs;
  }
};
}

