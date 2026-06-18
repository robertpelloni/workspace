/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: OpenMPOps.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::omp {

// BindKind Clause
enum class ClauseBindKind : uint32_t {
  Parallel = 0,
  Teams = 1,
  Thread = 2,
};

::std::optional<ClauseBindKind> symbolizeClauseBindKind(uint32_t);
::llvm::StringRef stringifyClauseBindKind(ClauseBindKind);
::std::optional<ClauseBindKind> symbolizeClauseBindKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseBindKind() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(ClauseBindKind enumValue) {
  return stringifyClauseBindKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseBindKind> symbolizeEnum<ClauseBindKind>(::llvm::StringRef str) {
  return symbolizeClauseBindKind(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseBindKind, ::mlir::omp::ClauseBindKind> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseBindKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for BindKind Clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseBindKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseBindKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [parallel, teams, thread] for BindKind Clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseBindKind>, std::optional<::mlir::omp::ClauseBindKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseBindKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseBindKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseBindKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseBindKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [parallel, teams, thread] for BindKind Clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseBindKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseBindKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseBindKind getEmptyKey() {
    return static_cast<::mlir::omp::ClauseBindKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseBindKind getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseBindKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseBindKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseBindKind &lhs, const ::mlir::omp::ClauseBindKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// CancellationConstructType Clause
enum class ClauseCancellationConstructType : uint32_t {
  Parallel = 0,
  Loop = 1,
  Sections = 2,
  Taskgroup = 3,
};

::std::optional<ClauseCancellationConstructType> symbolizeClauseCancellationConstructType(uint32_t);
::llvm::StringRef stringifyClauseCancellationConstructType(ClauseCancellationConstructType);
::std::optional<ClauseCancellationConstructType> symbolizeClauseCancellationConstructType(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseCancellationConstructType() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(ClauseCancellationConstructType enumValue) {
  return stringifyClauseCancellationConstructType(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseCancellationConstructType> symbolizeEnum<ClauseCancellationConstructType>(::llvm::StringRef str) {
  return symbolizeClauseCancellationConstructType(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseCancellationConstructType, ::mlir::omp::ClauseCancellationConstructType> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseCancellationConstructType> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for CancellationConstructType Clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseCancellationConstructType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseCancellationConstructType>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [parallel, loop, sections, taskgroup] for CancellationConstructType Clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseCancellationConstructType>, std::optional<::mlir::omp::ClauseCancellationConstructType>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseCancellationConstructType>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseCancellationConstructType>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseCancellationConstructType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseCancellationConstructType>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [parallel, loop, sections, taskgroup] for CancellationConstructType Clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseCancellationConstructType value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseCancellationConstructType> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseCancellationConstructType getEmptyKey() {
    return static_cast<::mlir::omp::ClauseCancellationConstructType>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseCancellationConstructType getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseCancellationConstructType>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseCancellationConstructType &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseCancellationConstructType &lhs, const ::mlir::omp::ClauseCancellationConstructType &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// depend clause
enum class ClauseDepend : uint32_t {
  dependsource = 0,
  dependsink = 1,
};

::std::optional<ClauseDepend> symbolizeClauseDepend(uint32_t);
::llvm::StringRef stringifyClauseDepend(ClauseDepend);
::std::optional<ClauseDepend> symbolizeClauseDepend(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseDepend() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(ClauseDepend enumValue) {
  return stringifyClauseDepend(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseDepend> symbolizeEnum<ClauseDepend>(::llvm::StringRef str) {
  return symbolizeClauseDepend(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseDepend, ::mlir::omp::ClauseDepend> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseDepend> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for depend clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseDepend> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseDepend>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [dependsource, dependsink] for depend clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseDepend>, std::optional<::mlir::omp::ClauseDepend>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseDepend>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseDepend>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseDepend> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseDepend>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [dependsource, dependsink] for depend clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseDepend value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseDepend> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseDepend getEmptyKey() {
    return static_cast<::mlir::omp::ClauseDepend>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseDepend getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseDepend>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseDepend &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseDepend &lhs, const ::mlir::omp::ClauseDepend &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// Map types and modifiers tied to data maps
enum class ClauseMapFlags : uint32_t {
  none = 0,
  storage = 1,
  to = 2,
  from = 4,
  always = 8,
  del = 16,
  return_param = 32,
  priv = 64,
  literal = 128,
  implicit = 256,
  close = 512,
  present = 1024,
  ompx_hold = 2048,
  attach = 4096,
  attach_always = 8192,
  attach_never = 16384,
  attach_auto = 32768,
  ref_ptr = 65536,
  ref_ptee = 131072,
  ref_ptr_ptee = 262144,
  is_device_ptr = 524288,
};

::std::optional<ClauseMapFlags> symbolizeClauseMapFlags(uint32_t);
std::string stringifyClauseMapFlags(ClauseMapFlags);
::std::optional<ClauseMapFlags> symbolizeClauseMapFlags(::llvm::StringRef);

inline constexpr ClauseMapFlags operator|(ClauseMapFlags a, ClauseMapFlags b) {
  return static_cast<ClauseMapFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline constexpr ClauseMapFlags operator&(ClauseMapFlags a, ClauseMapFlags b) {
  return static_cast<ClauseMapFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
inline constexpr ClauseMapFlags operator^(ClauseMapFlags a, ClauseMapFlags b) {
  return static_cast<ClauseMapFlags>(static_cast<uint32_t>(a) ^ static_cast<uint32_t>(b));
}
inline constexpr ClauseMapFlags &operator|=(ClauseMapFlags &a, ClauseMapFlags b) {
    return a = a | b;
}
inline constexpr ClauseMapFlags &operator&=(ClauseMapFlags &a, ClauseMapFlags b) {
    return a = a & b;
}
inline constexpr ClauseMapFlags &operator^=(ClauseMapFlags &a, ClauseMapFlags b) {
    return a = a ^ b;
}
inline constexpr ClauseMapFlags operator~(ClauseMapFlags bits) {
  // Ensure only bits that can be present in the enum are set
  return static_cast<ClauseMapFlags>(~static_cast<uint32_t>(bits) & static_cast<uint32_t>(1048575u));
}
inline constexpr bool bitEnumContainsAll(ClauseMapFlags bits, ClauseMapFlags bit) {
  return (bits & bit) == bit;
}
inline constexpr bool bitEnumContainsAny(ClauseMapFlags bits, ClauseMapFlags bit) {
  return (static_cast<uint32_t>(bits) & static_cast<uint32_t>(bit)) != 0;
}
inline constexpr ClauseMapFlags bitEnumClear(ClauseMapFlags bits, ClauseMapFlags bit) {
  return bits & ~bit;
}
inline constexpr ClauseMapFlags bitEnumSet(ClauseMapFlags bits, ClauseMapFlags bit, /*optional*/bool value=true) {
  return value ? (bits | bit) : bitEnumClear(bits, bit);
}
  
inline std::string stringifyEnum(ClauseMapFlags enumValue) {
  return stringifyClauseMapFlags(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseMapFlags> symbolizeEnum<ClauseMapFlags>(::llvm::StringRef str) {
  return symbolizeClauseMapFlags(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseMapFlags, ::mlir::omp::ClauseMapFlags> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseMapFlags> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Map types and modifiers tied to data maps");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseMapFlags> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseMapFlags>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, storage, to, from, always, del, return_param, priv, literal, implicit, close, present, ompx_hold, attach, attach_always, attach_never, attach_auto, ref_ptr, ref_ptee, ref_ptr_ptee, is_device_ptr] for Map types and modifiers tied to data maps, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseMapFlags>, std::optional<::mlir::omp::ClauseMapFlags>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseMapFlags>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseMapFlags>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseMapFlags> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseMapFlags>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, storage, to, from, always, del, return_param, priv, literal, implicit, close, present, ompx_hold, attach, attach_always, attach_never, attach_auto, ref_ptr, ref_ptee, ref_ptr_ptee, is_device_ptr] for Map types and modifiers tied to data maps, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseMapFlags value) {
  auto valueStr = stringifyEnum(value);
  auto underlyingValue = static_cast<std::make_unsigned_t<::mlir::omp::ClauseMapFlags>>(value);
  if (underlyingValue && !llvm::has_single_bit(underlyingValue))
    return p << '"' << valueStr << '"';
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseMapFlags> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseMapFlags getEmptyKey() {
    return static_cast<::mlir::omp::ClauseMapFlags>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseMapFlags getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseMapFlags>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseMapFlags &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseMapFlags &lhs, const ::mlir::omp::ClauseMapFlags &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// requires clauses
enum class ClauseRequires : uint32_t {
  none = 0,
  reverse_offload = 1,
  unified_address = 2,
  unified_shared_memory = 4,
  dynamic_allocators = 8,
};

::std::optional<ClauseRequires> symbolizeClauseRequires(uint32_t);
std::string stringifyClauseRequires(ClauseRequires);
::std::optional<ClauseRequires> symbolizeClauseRequires(::llvm::StringRef);

inline constexpr ClauseRequires operator|(ClauseRequires a, ClauseRequires b) {
  return static_cast<ClauseRequires>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline constexpr ClauseRequires operator&(ClauseRequires a, ClauseRequires b) {
  return static_cast<ClauseRequires>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
inline constexpr ClauseRequires operator^(ClauseRequires a, ClauseRequires b) {
  return static_cast<ClauseRequires>(static_cast<uint32_t>(a) ^ static_cast<uint32_t>(b));
}
inline constexpr ClauseRequires &operator|=(ClauseRequires &a, ClauseRequires b) {
    return a = a | b;
}
inline constexpr ClauseRequires &operator&=(ClauseRequires &a, ClauseRequires b) {
    return a = a & b;
}
inline constexpr ClauseRequires &operator^=(ClauseRequires &a, ClauseRequires b) {
    return a = a ^ b;
}
inline constexpr ClauseRequires operator~(ClauseRequires bits) {
  // Ensure only bits that can be present in the enum are set
  return static_cast<ClauseRequires>(~static_cast<uint32_t>(bits) & static_cast<uint32_t>(15u));
}
inline constexpr bool bitEnumContainsAll(ClauseRequires bits, ClauseRequires bit) {
  return (bits & bit) == bit;
}
inline constexpr bool bitEnumContainsAny(ClauseRequires bits, ClauseRequires bit) {
  return (static_cast<uint32_t>(bits) & static_cast<uint32_t>(bit)) != 0;
}
inline constexpr ClauseRequires bitEnumClear(ClauseRequires bits, ClauseRequires bit) {
  return bits & ~bit;
}
inline constexpr ClauseRequires bitEnumSet(ClauseRequires bits, ClauseRequires bit, /*optional*/bool value=true) {
  return value ? (bits | bit) : bitEnumClear(bits, bit);
}
  
inline std::string stringifyEnum(ClauseRequires enumValue) {
  return stringifyClauseRequires(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseRequires> symbolizeEnum<ClauseRequires>(::llvm::StringRef str) {
  return symbolizeClauseRequires(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseRequires, ::mlir::omp::ClauseRequires> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseRequires> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for requires clauses");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseRequires> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseRequires>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, reverse_offload, unified_address, unified_shared_memory, dynamic_allocators] for requires clauses, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseRequires>, std::optional<::mlir::omp::ClauseRequires>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseRequires>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseRequires>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseRequires> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseRequires>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, reverse_offload, unified_address, unified_shared_memory, dynamic_allocators] for requires clauses, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseRequires value) {
  auto valueStr = stringifyEnum(value);
  auto underlyingValue = static_cast<std::make_unsigned_t<::mlir::omp::ClauseRequires>>(value);
  if (underlyingValue && !llvm::has_single_bit(underlyingValue))
    return p << '"' << valueStr << '"';
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseRequires> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseRequires getEmptyKey() {
    return static_cast<::mlir::omp::ClauseRequires>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseRequires getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseRequires>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseRequires &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseRequires &lhs, const ::mlir::omp::ClauseRequires &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// depend clause in a target or task construct
enum class ClauseTaskDepend : uint32_t {
  taskdependin = 0,
  taskdependout = 1,
  taskdependinout = 2,
  taskdependmutexinoutset = 3,
  taskdependinoutset = 4,
};

::std::optional<ClauseTaskDepend> symbolizeClauseTaskDepend(uint32_t);
::llvm::StringRef stringifyClauseTaskDepend(ClauseTaskDepend);
::std::optional<ClauseTaskDepend> symbolizeClauseTaskDepend(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseTaskDepend() {
  return 4;
}


inline ::llvm::StringRef stringifyEnum(ClauseTaskDepend enumValue) {
  return stringifyClauseTaskDepend(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseTaskDepend> symbolizeEnum<ClauseTaskDepend>(::llvm::StringRef str) {
  return symbolizeClauseTaskDepend(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseTaskDepend, ::mlir::omp::ClauseTaskDepend> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseTaskDepend> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for depend clause in a target or task construct");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseTaskDepend> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseTaskDepend>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [taskdependin, taskdependout, taskdependinout, taskdependmutexinoutset, taskdependinoutset] for depend clause in a target or task construct, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseTaskDepend>, std::optional<::mlir::omp::ClauseTaskDepend>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseTaskDepend>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseTaskDepend>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseTaskDepend> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseTaskDepend>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [taskdependin, taskdependout, taskdependinout, taskdependmutexinoutset, taskdependinoutset] for depend clause in a target or task construct, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseTaskDepend value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseTaskDepend> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseTaskDepend getEmptyKey() {
    return static_cast<::mlir::omp::ClauseTaskDepend>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseTaskDepend getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseTaskDepend>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseTaskDepend &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseTaskDepend &lhs, const ::mlir::omp::ClauseTaskDepend &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// Type of a data-sharing clause
enum class DataSharingClauseType : uint32_t {
  Private = 0,
  FirstPrivate = 1,
};

::std::optional<DataSharingClauseType> symbolizeDataSharingClauseType(uint32_t);
::llvm::StringRef stringifyDataSharingClauseType(DataSharingClauseType);
::std::optional<DataSharingClauseType> symbolizeDataSharingClauseType(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForDataSharingClauseType() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(DataSharingClauseType enumValue) {
  return stringifyDataSharingClauseType(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<DataSharingClauseType> symbolizeEnum<DataSharingClauseType>(::llvm::StringRef str) {
  return symbolizeDataSharingClauseType(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::DataSharingClauseType, ::mlir::omp::DataSharingClauseType> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::DataSharingClauseType> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Type of a data-sharing clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::DataSharingClauseType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::DataSharingClauseType>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [private, firstprivate] for Type of a data-sharing clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::DataSharingClauseType>, std::optional<::mlir::omp::DataSharingClauseType>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::DataSharingClauseType>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::DataSharingClauseType>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::DataSharingClauseType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::DataSharingClauseType>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [private, firstprivate] for Type of a data-sharing clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::DataSharingClauseType value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::DataSharingClauseType> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::DataSharingClauseType getEmptyKey() {
    return static_cast<::mlir::omp::DataSharingClauseType>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::DataSharingClauseType getTombstoneKey() {
    return static_cast<::mlir::omp::DataSharingClauseType>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::DataSharingClauseType &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::DataSharingClauseType &lhs, const ::mlir::omp::DataSharingClauseType &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// capture clause
enum class DeclareTargetCaptureClause : uint32_t {
  none = 0,
  to = 1,
  link = 2,
  enter = 3,
};

::std::optional<DeclareTargetCaptureClause> symbolizeDeclareTargetCaptureClause(uint32_t);
::llvm::StringRef stringifyDeclareTargetCaptureClause(DeclareTargetCaptureClause);
::std::optional<DeclareTargetCaptureClause> symbolizeDeclareTargetCaptureClause(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForDeclareTargetCaptureClause() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(DeclareTargetCaptureClause enumValue) {
  return stringifyDeclareTargetCaptureClause(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<DeclareTargetCaptureClause> symbolizeEnum<DeclareTargetCaptureClause>(::llvm::StringRef str) {
  return symbolizeDeclareTargetCaptureClause(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::DeclareTargetCaptureClause, ::mlir::omp::DeclareTargetCaptureClause> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::DeclareTargetCaptureClause> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for capture clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::DeclareTargetCaptureClause> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::DeclareTargetCaptureClause>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, to, link, enter] for capture clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::DeclareTargetCaptureClause>, std::optional<::mlir::omp::DeclareTargetCaptureClause>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::DeclareTargetCaptureClause>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::DeclareTargetCaptureClause>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::DeclareTargetCaptureClause> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::DeclareTargetCaptureClause>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, to, link, enter] for capture clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::DeclareTargetCaptureClause value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::DeclareTargetCaptureClause> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::DeclareTargetCaptureClause getEmptyKey() {
    return static_cast<::mlir::omp::DeclareTargetCaptureClause>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::DeclareTargetCaptureClause getTombstoneKey() {
    return static_cast<::mlir::omp::DeclareTargetCaptureClause>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::DeclareTargetCaptureClause &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::DeclareTargetCaptureClause &lhs, const ::mlir::omp::DeclareTargetCaptureClause &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// device_type clause
enum class DeclareTargetDeviceType : uint32_t {
  any = 0,
  host = 1,
  nohost = 2,
};

::std::optional<DeclareTargetDeviceType> symbolizeDeclareTargetDeviceType(uint32_t);
::llvm::StringRef stringifyDeclareTargetDeviceType(DeclareTargetDeviceType);
::std::optional<DeclareTargetDeviceType> symbolizeDeclareTargetDeviceType(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForDeclareTargetDeviceType() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(DeclareTargetDeviceType enumValue) {
  return stringifyDeclareTargetDeviceType(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<DeclareTargetDeviceType> symbolizeEnum<DeclareTargetDeviceType>(::llvm::StringRef str) {
  return symbolizeDeclareTargetDeviceType(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::DeclareTargetDeviceType, ::mlir::omp::DeclareTargetDeviceType> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::DeclareTargetDeviceType> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for device_type clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::DeclareTargetDeviceType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::DeclareTargetDeviceType>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [any, host, nohost] for device_type clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::DeclareTargetDeviceType>, std::optional<::mlir::omp::DeclareTargetDeviceType>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::DeclareTargetDeviceType>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::DeclareTargetDeviceType>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::DeclareTargetDeviceType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::DeclareTargetDeviceType>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [any, host, nohost] for device_type clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::DeclareTargetDeviceType value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::DeclareTargetDeviceType> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::DeclareTargetDeviceType getEmptyKey() {
    return static_cast<::mlir::omp::DeclareTargetDeviceType>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::DeclareTargetDeviceType getTombstoneKey() {
    return static_cast<::mlir::omp::DeclareTargetDeviceType>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::DeclareTargetDeviceType &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::DeclareTargetDeviceType &lhs, const ::mlir::omp::DeclareTargetDeviceType &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// GrainsizeType Clause
enum class ClauseGrainsizeType : uint32_t {
  Strict = 0,
};

::std::optional<ClauseGrainsizeType> symbolizeClauseGrainsizeType(uint32_t);
::llvm::StringRef stringifyClauseGrainsizeType(ClauseGrainsizeType);
::std::optional<ClauseGrainsizeType> symbolizeClauseGrainsizeType(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseGrainsizeType() {
  return 0;
}


inline ::llvm::StringRef stringifyEnum(ClauseGrainsizeType enumValue) {
  return stringifyClauseGrainsizeType(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseGrainsizeType> symbolizeEnum<ClauseGrainsizeType>(::llvm::StringRef str) {
  return symbolizeClauseGrainsizeType(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseGrainsizeType, ::mlir::omp::ClauseGrainsizeType> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseGrainsizeType> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for GrainsizeType Clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseGrainsizeType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseGrainsizeType>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [strict] for GrainsizeType Clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseGrainsizeType>, std::optional<::mlir::omp::ClauseGrainsizeType>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseGrainsizeType>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseGrainsizeType>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseGrainsizeType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseGrainsizeType>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [strict] for GrainsizeType Clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseGrainsizeType value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseGrainsizeType> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseGrainsizeType getEmptyKey() {
    return static_cast<::mlir::omp::ClauseGrainsizeType>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseGrainsizeType getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseGrainsizeType>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseGrainsizeType &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseGrainsizeType &lhs, const ::mlir::omp::ClauseGrainsizeType &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// MemoryOrderKind Clause
enum class ClauseMemoryOrderKind : uint32_t {
  Seq_cst = 0,
  Acq_rel = 1,
  Acquire = 2,
  Release = 3,
  Relaxed = 4,
};

::std::optional<ClauseMemoryOrderKind> symbolizeClauseMemoryOrderKind(uint32_t);
::llvm::StringRef stringifyClauseMemoryOrderKind(ClauseMemoryOrderKind);
::std::optional<ClauseMemoryOrderKind> symbolizeClauseMemoryOrderKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseMemoryOrderKind() {
  return 4;
}


inline ::llvm::StringRef stringifyEnum(ClauseMemoryOrderKind enumValue) {
  return stringifyClauseMemoryOrderKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseMemoryOrderKind> symbolizeEnum<ClauseMemoryOrderKind>(::llvm::StringRef str) {
  return symbolizeClauseMemoryOrderKind(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseMemoryOrderKind, ::mlir::omp::ClauseMemoryOrderKind> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseMemoryOrderKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for MemoryOrderKind Clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseMemoryOrderKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseMemoryOrderKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [seq_cst, acq_rel, acquire, release, relaxed] for MemoryOrderKind Clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseMemoryOrderKind>, std::optional<::mlir::omp::ClauseMemoryOrderKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseMemoryOrderKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseMemoryOrderKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseMemoryOrderKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseMemoryOrderKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [seq_cst, acq_rel, acquire, release, relaxed] for MemoryOrderKind Clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseMemoryOrderKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseMemoryOrderKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseMemoryOrderKind getEmptyKey() {
    return static_cast<::mlir::omp::ClauseMemoryOrderKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseMemoryOrderKind getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseMemoryOrderKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseMemoryOrderKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseMemoryOrderKind &lhs, const ::mlir::omp::ClauseMemoryOrderKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// NumTasksType Clause
enum class ClauseNumTasksType : uint32_t {
  Strict = 0,
};

::std::optional<ClauseNumTasksType> symbolizeClauseNumTasksType(uint32_t);
::llvm::StringRef stringifyClauseNumTasksType(ClauseNumTasksType);
::std::optional<ClauseNumTasksType> symbolizeClauseNumTasksType(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseNumTasksType() {
  return 0;
}


inline ::llvm::StringRef stringifyEnum(ClauseNumTasksType enumValue) {
  return stringifyClauseNumTasksType(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseNumTasksType> symbolizeEnum<ClauseNumTasksType>(::llvm::StringRef str) {
  return symbolizeClauseNumTasksType(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseNumTasksType, ::mlir::omp::ClauseNumTasksType> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseNumTasksType> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for NumTasksType Clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseNumTasksType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseNumTasksType>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [strict] for NumTasksType Clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseNumTasksType>, std::optional<::mlir::omp::ClauseNumTasksType>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseNumTasksType>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseNumTasksType>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseNumTasksType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseNumTasksType>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [strict] for NumTasksType Clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseNumTasksType value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseNumTasksType> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseNumTasksType getEmptyKey() {
    return static_cast<::mlir::omp::ClauseNumTasksType>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseNumTasksType getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseNumTasksType>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseNumTasksType &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseNumTasksType &lhs, const ::mlir::omp::ClauseNumTasksType &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// NumThreadsType Clause
enum class ClauseNumThreadsType : uint32_t {
  Strict = 0,
};

::std::optional<ClauseNumThreadsType> symbolizeClauseNumThreadsType(uint32_t);
::llvm::StringRef stringifyClauseNumThreadsType(ClauseNumThreadsType);
::std::optional<ClauseNumThreadsType> symbolizeClauseNumThreadsType(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseNumThreadsType() {
  return 0;
}


inline ::llvm::StringRef stringifyEnum(ClauseNumThreadsType enumValue) {
  return stringifyClauseNumThreadsType(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseNumThreadsType> symbolizeEnum<ClauseNumThreadsType>(::llvm::StringRef str) {
  return symbolizeClauseNumThreadsType(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseNumThreadsType, ::mlir::omp::ClauseNumThreadsType> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseNumThreadsType> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for NumThreadsType Clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseNumThreadsType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseNumThreadsType>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [strict] for NumThreadsType Clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseNumThreadsType>, std::optional<::mlir::omp::ClauseNumThreadsType>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseNumThreadsType>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseNumThreadsType>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseNumThreadsType> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseNumThreadsType>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [strict] for NumThreadsType Clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseNumThreadsType value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseNumThreadsType> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseNumThreadsType getEmptyKey() {
    return static_cast<::mlir::omp::ClauseNumThreadsType>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseNumThreadsType getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseNumThreadsType>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseNumThreadsType &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseNumThreadsType &lhs, const ::mlir::omp::ClauseNumThreadsType &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// OrderKind Clause
enum class ClauseOrderKind : uint32_t {
  Concurrent = 1,
};

::std::optional<ClauseOrderKind> symbolizeClauseOrderKind(uint32_t);
::llvm::StringRef stringifyClauseOrderKind(ClauseOrderKind);
::std::optional<ClauseOrderKind> symbolizeClauseOrderKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseOrderKind() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(ClauseOrderKind enumValue) {
  return stringifyClauseOrderKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseOrderKind> symbolizeEnum<ClauseOrderKind>(::llvm::StringRef str) {
  return symbolizeClauseOrderKind(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseOrderKind, ::mlir::omp::ClauseOrderKind> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseOrderKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for OrderKind Clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseOrderKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseOrderKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [concurrent] for OrderKind Clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseOrderKind>, std::optional<::mlir::omp::ClauseOrderKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseOrderKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseOrderKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseOrderKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseOrderKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [concurrent] for OrderKind Clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseOrderKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseOrderKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseOrderKind getEmptyKey() {
    return static_cast<::mlir::omp::ClauseOrderKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseOrderKind getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseOrderKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseOrderKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseOrderKind &lhs, const ::mlir::omp::ClauseOrderKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// OpenMP Order Modifier
enum class OrderModifier : uint32_t {
  reproducible = 0,
  unconstrained = 1,
};

::std::optional<OrderModifier> symbolizeOrderModifier(uint32_t);
::llvm::StringRef stringifyOrderModifier(OrderModifier);
::std::optional<OrderModifier> symbolizeOrderModifier(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForOrderModifier() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(OrderModifier enumValue) {
  return stringifyOrderModifier(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<OrderModifier> symbolizeEnum<OrderModifier>(::llvm::StringRef str) {
  return symbolizeOrderModifier(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::OrderModifier, ::mlir::omp::OrderModifier> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::OrderModifier> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for OpenMP Order Modifier");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::OrderModifier> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::OrderModifier>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [reproducible, unconstrained] for OpenMP Order Modifier, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::OrderModifier>, std::optional<::mlir::omp::OrderModifier>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::OrderModifier>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::OrderModifier>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::OrderModifier> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::OrderModifier>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [reproducible, unconstrained] for OpenMP Order Modifier, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::OrderModifier value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::OrderModifier> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::OrderModifier getEmptyKey() {
    return static_cast<::mlir::omp::OrderModifier>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::OrderModifier getTombstoneKey() {
    return static_cast<::mlir::omp::OrderModifier>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::OrderModifier &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::OrderModifier &lhs, const ::mlir::omp::OrderModifier &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// ProcBindKind Clause
enum class ClauseProcBindKind : uint32_t {
  Primary = 0,
  Master = 1,
  Close = 2,
  Spread = 3,
};

::std::optional<ClauseProcBindKind> symbolizeClauseProcBindKind(uint32_t);
::llvm::StringRef stringifyClauseProcBindKind(ClauseProcBindKind);
::std::optional<ClauseProcBindKind> symbolizeClauseProcBindKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseProcBindKind() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(ClauseProcBindKind enumValue) {
  return stringifyClauseProcBindKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseProcBindKind> symbolizeEnum<ClauseProcBindKind>(::llvm::StringRef str) {
  return symbolizeClauseProcBindKind(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseProcBindKind, ::mlir::omp::ClauseProcBindKind> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseProcBindKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for ProcBindKind Clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseProcBindKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseProcBindKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [primary, master, close, spread] for ProcBindKind Clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseProcBindKind>, std::optional<::mlir::omp::ClauseProcBindKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseProcBindKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseProcBindKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseProcBindKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseProcBindKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [primary, master, close, spread] for ProcBindKind Clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseProcBindKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseProcBindKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseProcBindKind getEmptyKey() {
    return static_cast<::mlir::omp::ClauseProcBindKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseProcBindKind getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseProcBindKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseProcBindKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseProcBindKind &lhs, const ::mlir::omp::ClauseProcBindKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// reduction modifier
enum class ReductionModifier : uint32_t {
  defaultmod = 0,
  inscan = 1,
  task = 2,
};

::std::optional<ReductionModifier> symbolizeReductionModifier(uint32_t);
::llvm::StringRef stringifyReductionModifier(ReductionModifier);
::std::optional<ReductionModifier> symbolizeReductionModifier(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForReductionModifier() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(ReductionModifier enumValue) {
  return stringifyReductionModifier(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ReductionModifier> symbolizeEnum<ReductionModifier>(::llvm::StringRef str) {
  return symbolizeReductionModifier(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ReductionModifier, ::mlir::omp::ReductionModifier> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ReductionModifier> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for reduction modifier");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ReductionModifier> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ReductionModifier>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [defaultmod, inscan, task] for reduction modifier, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ReductionModifier>, std::optional<::mlir::omp::ReductionModifier>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ReductionModifier>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ReductionModifier>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ReductionModifier> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ReductionModifier>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [defaultmod, inscan, task] for reduction modifier, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ReductionModifier value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ReductionModifier> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ReductionModifier getEmptyKey() {
    return static_cast<::mlir::omp::ReductionModifier>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ReductionModifier getTombstoneKey() {
    return static_cast<::mlir::omp::ReductionModifier>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ReductionModifier &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ReductionModifier &lhs, const ::mlir::omp::ReductionModifier &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// ScheduleKind Clause
enum class ClauseScheduleKind : uint32_t {
  Static = 0,
  Dynamic = 1,
  Guided = 2,
  Auto = 3,
  Runtime = 4,
  Distribute = 5,
};

::std::optional<ClauseScheduleKind> symbolizeClauseScheduleKind(uint32_t);
::llvm::StringRef stringifyClauseScheduleKind(ClauseScheduleKind);
::std::optional<ClauseScheduleKind> symbolizeClauseScheduleKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClauseScheduleKind() {
  return 5;
}


inline ::llvm::StringRef stringifyEnum(ClauseScheduleKind enumValue) {
  return stringifyClauseScheduleKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClauseScheduleKind> symbolizeEnum<ClauseScheduleKind>(::llvm::StringRef str) {
  return symbolizeClauseScheduleKind(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ClauseScheduleKind, ::mlir::omp::ClauseScheduleKind> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ClauseScheduleKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for ScheduleKind Clause");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseScheduleKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseScheduleKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [static, dynamic, guided, auto, runtime, distribute] for ScheduleKind Clause, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ClauseScheduleKind>, std::optional<::mlir::omp::ClauseScheduleKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ClauseScheduleKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ClauseScheduleKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ClauseScheduleKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ClauseScheduleKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [static, dynamic, guided, auto, runtime, distribute] for ScheduleKind Clause, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ClauseScheduleKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ClauseScheduleKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ClauseScheduleKind getEmptyKey() {
    return static_cast<::mlir::omp::ClauseScheduleKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ClauseScheduleKind getTombstoneKey() {
    return static_cast<::mlir::omp::ClauseScheduleKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ClauseScheduleKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ClauseScheduleKind &lhs, const ::mlir::omp::ClauseScheduleKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// OpenMP Schedule Modifier
enum class ScheduleModifier : uint32_t {
  none = 0,
  monotonic = 1,
  nonmonotonic = 2,
  simd = 3,
};

::std::optional<ScheduleModifier> symbolizeScheduleModifier(uint32_t);
::llvm::StringRef stringifyScheduleModifier(ScheduleModifier);
::std::optional<ScheduleModifier> symbolizeScheduleModifier(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForScheduleModifier() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(ScheduleModifier enumValue) {
  return stringifyScheduleModifier(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ScheduleModifier> symbolizeEnum<ScheduleModifier>(::llvm::StringRef str) {
  return symbolizeScheduleModifier(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::ScheduleModifier, ::mlir::omp::ScheduleModifier> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::ScheduleModifier> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for OpenMP Schedule Modifier");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ScheduleModifier> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ScheduleModifier>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, monotonic, nonmonotonic, simd] for OpenMP Schedule Modifier, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::ScheduleModifier>, std::optional<::mlir::omp::ScheduleModifier>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::ScheduleModifier>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::ScheduleModifier>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::ScheduleModifier> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::ScheduleModifier>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, monotonic, nonmonotonic, simd] for OpenMP Schedule Modifier, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::ScheduleModifier value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::ScheduleModifier> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::ScheduleModifier getEmptyKey() {
    return static_cast<::mlir::omp::ScheduleModifier>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::ScheduleModifier getTombstoneKey() {
    return static_cast<::mlir::omp::ScheduleModifier>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::ScheduleModifier &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::ScheduleModifier &lhs, const ::mlir::omp::ScheduleModifier &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// These flags describe properties of the target kernel. TargetRegionFlagsGeneric - denotes generic kernel. TargetRegionFlagsSpmd - denotes SPMD kernel. TargetRegionFlagsNoLoop - denotes kernel where num_teams * num_threads >= loop_trip_count. It allows the conversion of loops into sequential code by ensuring that each team/thread executes at most one iteration. TargetRegionFlagsTripCount - checks if the loop trip count should be calculated.
enum class TargetRegionFlags : uint32_t {
  none = 0,
  generic = 1,
  spmd = 2,
  trip_count = 4,
  no_loop = 8,
};

::std::optional<TargetRegionFlags> symbolizeTargetRegionFlags(uint32_t);
std::string stringifyTargetRegionFlags(TargetRegionFlags);
::std::optional<TargetRegionFlags> symbolizeTargetRegionFlags(::llvm::StringRef);

inline constexpr TargetRegionFlags operator|(TargetRegionFlags a, TargetRegionFlags b) {
  return static_cast<TargetRegionFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline constexpr TargetRegionFlags operator&(TargetRegionFlags a, TargetRegionFlags b) {
  return static_cast<TargetRegionFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
inline constexpr TargetRegionFlags operator^(TargetRegionFlags a, TargetRegionFlags b) {
  return static_cast<TargetRegionFlags>(static_cast<uint32_t>(a) ^ static_cast<uint32_t>(b));
}
inline constexpr TargetRegionFlags &operator|=(TargetRegionFlags &a, TargetRegionFlags b) {
    return a = a | b;
}
inline constexpr TargetRegionFlags &operator&=(TargetRegionFlags &a, TargetRegionFlags b) {
    return a = a & b;
}
inline constexpr TargetRegionFlags &operator^=(TargetRegionFlags &a, TargetRegionFlags b) {
    return a = a ^ b;
}
inline constexpr TargetRegionFlags operator~(TargetRegionFlags bits) {
  // Ensure only bits that can be present in the enum are set
  return static_cast<TargetRegionFlags>(~static_cast<uint32_t>(bits) & static_cast<uint32_t>(15u));
}
inline constexpr bool bitEnumContainsAll(TargetRegionFlags bits, TargetRegionFlags bit) {
  return (bits & bit) == bit;
}
inline constexpr bool bitEnumContainsAny(TargetRegionFlags bits, TargetRegionFlags bit) {
  return (static_cast<uint32_t>(bits) & static_cast<uint32_t>(bit)) != 0;
}
inline constexpr TargetRegionFlags bitEnumClear(TargetRegionFlags bits, TargetRegionFlags bit) {
  return bits & ~bit;
}
inline constexpr TargetRegionFlags bitEnumSet(TargetRegionFlags bits, TargetRegionFlags bit, /*optional*/bool value=true) {
  return value ? (bits | bit) : bitEnumClear(bits, bit);
}
  
inline std::string stringifyEnum(TargetRegionFlags enumValue) {
  return stringifyTargetRegionFlags(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<TargetRegionFlags> symbolizeEnum<TargetRegionFlags>(::llvm::StringRef str) {
  return symbolizeTargetRegionFlags(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::TargetRegionFlags, ::mlir::omp::TargetRegionFlags> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::TargetRegionFlags> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for These flags describe properties of the target kernel. TargetRegionFlagsGeneric - denotes generic kernel. TargetRegionFlagsSpmd - denotes SPMD kernel. TargetRegionFlagsNoLoop - denotes kernel where num_teams * num_threads >= loop_trip_count. It allows the conversion of loops into sequential code by ensuring that each team/thread executes at most one iteration. TargetRegionFlagsTripCount - checks if the loop trip count should be calculated.");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::TargetRegionFlags> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::TargetRegionFlags>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, generic, spmd, trip_count, no_loop] for These flags describe properties of the target kernel. TargetRegionFlagsGeneric - denotes generic kernel. TargetRegionFlagsSpmd - denotes SPMD kernel. TargetRegionFlagsNoLoop - denotes kernel where num_teams * num_threads >= loop_trip_count. It allows the conversion of loops into sequential code by ensuring that each team/thread executes at most one iteration. TargetRegionFlagsTripCount - checks if the loop trip count should be calculated., got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::TargetRegionFlags>, std::optional<::mlir::omp::TargetRegionFlags>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::TargetRegionFlags>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::TargetRegionFlags>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::TargetRegionFlags> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::TargetRegionFlags>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, generic, spmd, trip_count, no_loop] for These flags describe properties of the target kernel. TargetRegionFlagsGeneric - denotes generic kernel. TargetRegionFlagsSpmd - denotes SPMD kernel. TargetRegionFlagsNoLoop - denotes kernel where num_teams * num_threads >= loop_trip_count. It allows the conversion of loops into sequential code by ensuring that each team/thread executes at most one iteration. TargetRegionFlagsTripCount - checks if the loop trip count should be calculated., got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::TargetRegionFlags value) {
  auto valueStr = stringifyEnum(value);
  auto underlyingValue = static_cast<std::make_unsigned_t<::mlir::omp::TargetRegionFlags>>(value);
  if (underlyingValue && !llvm::has_single_bit(underlyingValue))
    return p << '"' << valueStr << '"';
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::TargetRegionFlags> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::TargetRegionFlags getEmptyKey() {
    return static_cast<::mlir::omp::TargetRegionFlags>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::TargetRegionFlags getTombstoneKey() {
    return static_cast<::mlir::omp::TargetRegionFlags>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::TargetRegionFlags &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::TargetRegionFlags &lhs, const ::mlir::omp::TargetRegionFlags &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::omp {

// variable capture kind
enum class VariableCaptureKind : uint32_t {
  This = 0,
  ByRef = 1,
  ByCopy = 2,
  VLAType = 3,
};

::std::optional<VariableCaptureKind> symbolizeVariableCaptureKind(uint32_t);
::llvm::StringRef stringifyVariableCaptureKind(VariableCaptureKind);
::std::optional<VariableCaptureKind> symbolizeVariableCaptureKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForVariableCaptureKind() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(VariableCaptureKind enumValue) {
  return stringifyVariableCaptureKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<VariableCaptureKind> symbolizeEnum<VariableCaptureKind>(::llvm::StringRef str) {
  return symbolizeVariableCaptureKind(str);
}

} // namespace mlir::omp

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::omp::VariableCaptureKind, ::mlir::omp::VariableCaptureKind> {
  template <typename ParserT>
  static FailureOr<::mlir::omp::VariableCaptureKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for variable capture kind");

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::VariableCaptureKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::VariableCaptureKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [This, ByRef, ByCopy, VLAType] for variable capture kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::omp::VariableCaptureKind>, std::optional<::mlir::omp::VariableCaptureKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::omp::VariableCaptureKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::omp::VariableCaptureKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::omp::VariableCaptureKind> attr = ::mlir::omp::symbolizeEnum<::mlir::omp::VariableCaptureKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [This, ByRef, ByCopy, VLAType] for variable capture kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::omp::VariableCaptureKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::omp::VariableCaptureKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::omp::VariableCaptureKind getEmptyKey() {
    return static_cast<::mlir::omp::VariableCaptureKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::omp::VariableCaptureKind getTombstoneKey() {
    return static_cast<::mlir::omp::VariableCaptureKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::omp::VariableCaptureKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::omp::VariableCaptureKind &lhs, const ::mlir::omp::VariableCaptureKind &rhs) {
    return lhs == rhs;
  }
};
}

