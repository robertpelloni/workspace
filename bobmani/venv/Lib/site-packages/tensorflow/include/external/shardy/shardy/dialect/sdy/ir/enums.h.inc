/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: enums.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::sdy {

// edge node type enum
enum class EdgeNodeType : uint32_t {
  OPERAND = 0,
  RESULT = 1,
};

::std::optional<EdgeNodeType> symbolizeEdgeNodeType(uint32_t);
::llvm::StringRef stringifyEdgeNodeType(EdgeNodeType);
::std::optional<EdgeNodeType> symbolizeEdgeNodeType(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForEdgeNodeType() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(EdgeNodeType enumValue) {
  return stringifyEdgeNodeType(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<EdgeNodeType> symbolizeEnum<EdgeNodeType>(::llvm::StringRef str) {
  return symbolizeEdgeNodeType(str);
}

class EdgeNodeTypeAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = EdgeNodeType;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static EdgeNodeTypeAttr get(::mlir::MLIRContext *context, EdgeNodeType val);
  EdgeNodeType getValue() const;
};

} // namespace mlir::sdy

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::sdy::EdgeNodeType, ::mlir::sdy::EdgeNodeType> {
  template <typename ParserT>
  static FailureOr<::mlir::sdy::EdgeNodeType> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for edge node type enum");

    // Symbolize the keyword.
    if (::std::optional<::mlir::sdy::EdgeNodeType> attr = ::mlir::sdy::symbolizeEnum<::mlir::sdy::EdgeNodeType>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [operand, result] for edge node type enum, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::sdy::EdgeNodeType>, std::optional<::mlir::sdy::EdgeNodeType>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::sdy::EdgeNodeType>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::sdy::EdgeNodeType>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::sdy::EdgeNodeType> attr = ::mlir::sdy::symbolizeEnum<::mlir::sdy::EdgeNodeType>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [operand, result] for edge node type enum, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::sdy::EdgeNodeType value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::sdy::EdgeNodeType> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::sdy::EdgeNodeType getEmptyKey() {
    return static_cast<::mlir::sdy::EdgeNodeType>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::sdy::EdgeNodeType getTombstoneKey() {
    return static_cast<::mlir::sdy::EdgeNodeType>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::sdy::EdgeNodeType &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::sdy::EdgeNodeType &lhs, const ::mlir::sdy::EdgeNodeType &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::sdy {

// propagation direction enum
enum class PropagationDirection : uint32_t {
  NONE = 0,
  FORWARD = 1,
  BACKWARD = 2,
  BOTH = 3,
};

::std::optional<PropagationDirection> symbolizePropagationDirection(uint32_t);
::llvm::StringRef stringifyPropagationDirection(PropagationDirection);
::std::optional<PropagationDirection> symbolizePropagationDirection(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForPropagationDirection() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(PropagationDirection enumValue) {
  return stringifyPropagationDirection(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<PropagationDirection> symbolizeEnum<PropagationDirection>(::llvm::StringRef str) {
  return symbolizePropagationDirection(str);
}

class PropagationDirectionAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = PropagationDirection;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static PropagationDirectionAttr get(::mlir::MLIRContext *context, PropagationDirection val);
  PropagationDirection getValue() const;
};

} // namespace mlir::sdy

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::sdy::PropagationDirection, ::mlir::sdy::PropagationDirection> {
  template <typename ParserT>
  static FailureOr<::mlir::sdy::PropagationDirection> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for propagation direction enum");

    // Symbolize the keyword.
    if (::std::optional<::mlir::sdy::PropagationDirection> attr = ::mlir::sdy::symbolizeEnum<::mlir::sdy::PropagationDirection>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [NONE, FORWARD, BACKWARD, BOTH] for propagation direction enum, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::sdy::PropagationDirection>, std::optional<::mlir::sdy::PropagationDirection>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::sdy::PropagationDirection>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::sdy::PropagationDirection>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::sdy::PropagationDirection> attr = ::mlir::sdy::symbolizeEnum<::mlir::sdy::PropagationDirection>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [NONE, FORWARD, BACKWARD, BOTH] for propagation direction enum, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::sdy::PropagationDirection value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::sdy::PropagationDirection> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::sdy::PropagationDirection getEmptyKey() {
    return static_cast<::mlir::sdy::PropagationDirection>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::sdy::PropagationDirection getTombstoneKey() {
    return static_cast<::mlir::sdy::PropagationDirection>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::sdy::PropagationDirection &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::sdy::PropagationDirection &lhs, const ::mlir::sdy::PropagationDirection &rhs) {
    return lhs == rhs;
  }
};
}

