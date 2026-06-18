/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: PtrEnums.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::ptr {

// ptr.atomicrmw binary operations
enum class AtomicBinOp : uint32_t {
  xchg = 0,
  add = 1,
  sub = 2,
  _and = 3,
  nand = 4,
  _or = 5,
  _xor = 6,
  max = 7,
  min = 8,
  umax = 9,
  umin = 10,
  fadd = 11,
  fsub = 12,
  fmax = 13,
  fmin = 14,
  uinc_wrap = 15,
  udec_wrap = 16,
};

::std::optional<AtomicBinOp> symbolizeAtomicBinOp(uint32_t);
::llvm::StringRef stringifyAtomicBinOp(AtomicBinOp);
::std::optional<AtomicBinOp> symbolizeAtomicBinOp(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForAtomicBinOp() {
  return 16;
}


inline ::llvm::StringRef stringifyEnum(AtomicBinOp enumValue) {
  return stringifyAtomicBinOp(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<AtomicBinOp> symbolizeEnum<AtomicBinOp>(::llvm::StringRef str) {
  return symbolizeAtomicBinOp(str);
}

} // namespace mlir::ptr

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::ptr::AtomicBinOp, ::mlir::ptr::AtomicBinOp> {
  template <typename ParserT>
  static FailureOr<::mlir::ptr::AtomicBinOp> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for ptr.atomicrmw binary operations");

    // Symbolize the keyword.
    if (::std::optional<::mlir::ptr::AtomicBinOp> attr = ::mlir::ptr::symbolizeEnum<::mlir::ptr::AtomicBinOp>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [xchg, add, sub, _and, nand, _or, _xor, max, min, umax, umin, fadd, fsub, fmax, fmin, uinc_wrap, udec_wrap] for ptr.atomicrmw binary operations, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::ptr::AtomicBinOp>, std::optional<::mlir::ptr::AtomicBinOp>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::ptr::AtomicBinOp>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::ptr::AtomicBinOp>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::ptr::AtomicBinOp> attr = ::mlir::ptr::symbolizeEnum<::mlir::ptr::AtomicBinOp>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [xchg, add, sub, _and, nand, _or, _xor, max, min, umax, umin, fadd, fsub, fmax, fmin, uinc_wrap, udec_wrap] for ptr.atomicrmw binary operations, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::ptr::AtomicBinOp value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::ptr::AtomicBinOp> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::ptr::AtomicBinOp getEmptyKey() {
    return static_cast<::mlir::ptr::AtomicBinOp>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::ptr::AtomicBinOp getTombstoneKey() {
    return static_cast<::mlir::ptr::AtomicBinOp>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::ptr::AtomicBinOp &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::ptr::AtomicBinOp &lhs, const ::mlir::ptr::AtomicBinOp &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::ptr {

// Atomic ordering for LLVM's memory model
enum class AtomicOrdering : uint32_t {
  not_atomic = 0,
  unordered = 1,
  monotonic = 2,
  acquire = 3,
  release = 4,
  acq_rel = 5,
  seq_cst = 6,
};

::std::optional<AtomicOrdering> symbolizeAtomicOrdering(uint32_t);
::llvm::StringRef stringifyAtomicOrdering(AtomicOrdering);
::std::optional<AtomicOrdering> symbolizeAtomicOrdering(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForAtomicOrdering() {
  return 6;
}


inline ::llvm::StringRef stringifyEnum(AtomicOrdering enumValue) {
  return stringifyAtomicOrdering(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<AtomicOrdering> symbolizeEnum<AtomicOrdering>(::llvm::StringRef str) {
  return symbolizeAtomicOrdering(str);
}

} // namespace mlir::ptr

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::ptr::AtomicOrdering, ::mlir::ptr::AtomicOrdering> {
  template <typename ParserT>
  static FailureOr<::mlir::ptr::AtomicOrdering> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Atomic ordering for LLVM's memory model");

    // Symbolize the keyword.
    if (::std::optional<::mlir::ptr::AtomicOrdering> attr = ::mlir::ptr::symbolizeEnum<::mlir::ptr::AtomicOrdering>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [not_atomic, unordered, monotonic, acquire, release, acq_rel, seq_cst] for Atomic ordering for LLVM's memory model, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::ptr::AtomicOrdering>, std::optional<::mlir::ptr::AtomicOrdering>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::ptr::AtomicOrdering>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::ptr::AtomicOrdering>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::ptr::AtomicOrdering> attr = ::mlir::ptr::symbolizeEnum<::mlir::ptr::AtomicOrdering>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [not_atomic, unordered, monotonic, acquire, release, acq_rel, seq_cst] for Atomic ordering for LLVM's memory model, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::ptr::AtomicOrdering value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::ptr::AtomicOrdering> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::ptr::AtomicOrdering getEmptyKey() {
    return static_cast<::mlir::ptr::AtomicOrdering>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::ptr::AtomicOrdering getTombstoneKey() {
    return static_cast<::mlir::ptr::AtomicOrdering>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::ptr::AtomicOrdering &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::ptr::AtomicOrdering &lhs, const ::mlir::ptr::AtomicOrdering &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::ptr {

// Pointer add flags
enum class PtrAddFlags : uint32_t {
  none = 0,
  nusw = 1,
  nuw = 2,
  inbounds = 3,
};

::std::optional<PtrAddFlags> symbolizePtrAddFlags(uint32_t);
::llvm::StringRef stringifyPtrAddFlags(PtrAddFlags);
::std::optional<PtrAddFlags> symbolizePtrAddFlags(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForPtrAddFlags() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(PtrAddFlags enumValue) {
  return stringifyPtrAddFlags(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<PtrAddFlags> symbolizeEnum<PtrAddFlags>(::llvm::StringRef str) {
  return symbolizePtrAddFlags(str);
}

} // namespace mlir::ptr

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::ptr::PtrAddFlags, ::mlir::ptr::PtrAddFlags> {
  template <typename ParserT>
  static FailureOr<::mlir::ptr::PtrAddFlags> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Pointer add flags");

    // Symbolize the keyword.
    if (::std::optional<::mlir::ptr::PtrAddFlags> attr = ::mlir::ptr::symbolizeEnum<::mlir::ptr::PtrAddFlags>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, nusw, nuw, inbounds] for Pointer add flags, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::ptr::PtrAddFlags>, std::optional<::mlir::ptr::PtrAddFlags>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::ptr::PtrAddFlags>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::ptr::PtrAddFlags>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::ptr::PtrAddFlags> attr = ::mlir::ptr::symbolizeEnum<::mlir::ptr::PtrAddFlags>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, nusw, nuw, inbounds] for Pointer add flags, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::ptr::PtrAddFlags value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::ptr::PtrAddFlags> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::ptr::PtrAddFlags getEmptyKey() {
    return static_cast<::mlir::ptr::PtrAddFlags>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::ptr::PtrAddFlags getTombstoneKey() {
    return static_cast<::mlir::ptr::PtrAddFlags>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::ptr::PtrAddFlags &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::ptr::PtrAddFlags &lhs, const ::mlir::ptr::PtrAddFlags &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::ptr {

// Pointer difference flags
enum class PtrDiffFlags : uint8_t {
  none = 0,
  nuw = 1,
  nsw = 2,
};

::std::optional<PtrDiffFlags> symbolizePtrDiffFlags(uint8_t);
std::string stringifyPtrDiffFlags(PtrDiffFlags);
::std::optional<PtrDiffFlags> symbolizePtrDiffFlags(::llvm::StringRef);

inline constexpr PtrDiffFlags operator|(PtrDiffFlags a, PtrDiffFlags b) {
  return static_cast<PtrDiffFlags>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}
inline constexpr PtrDiffFlags operator&(PtrDiffFlags a, PtrDiffFlags b) {
  return static_cast<PtrDiffFlags>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}
inline constexpr PtrDiffFlags operator^(PtrDiffFlags a, PtrDiffFlags b) {
  return static_cast<PtrDiffFlags>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
}
inline constexpr PtrDiffFlags &operator|=(PtrDiffFlags &a, PtrDiffFlags b) {
    return a = a | b;
}
inline constexpr PtrDiffFlags &operator&=(PtrDiffFlags &a, PtrDiffFlags b) {
    return a = a & b;
}
inline constexpr PtrDiffFlags &operator^=(PtrDiffFlags &a, PtrDiffFlags b) {
    return a = a ^ b;
}
inline constexpr PtrDiffFlags operator~(PtrDiffFlags bits) {
  // Ensure only bits that can be present in the enum are set
  return static_cast<PtrDiffFlags>(~static_cast<uint8_t>(bits) & static_cast<uint8_t>(3u));
}
inline constexpr bool bitEnumContainsAll(PtrDiffFlags bits, PtrDiffFlags bit) {
  return (bits & bit) == bit;
}
inline constexpr bool bitEnumContainsAny(PtrDiffFlags bits, PtrDiffFlags bit) {
  return (static_cast<uint8_t>(bits) & static_cast<uint8_t>(bit)) != 0;
}
inline constexpr PtrDiffFlags bitEnumClear(PtrDiffFlags bits, PtrDiffFlags bit) {
  return bits & ~bit;
}
inline constexpr PtrDiffFlags bitEnumSet(PtrDiffFlags bits, PtrDiffFlags bit, /*optional*/bool value=true) {
  return value ? (bits | bit) : bitEnumClear(bits, bit);
}
  
inline std::string stringifyEnum(PtrDiffFlags enumValue) {
  return stringifyPtrDiffFlags(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<PtrDiffFlags> symbolizeEnum<PtrDiffFlags>(::llvm::StringRef str) {
  return symbolizePtrDiffFlags(str);
}

} // namespace mlir::ptr

  namespace mlir {
  template <typename T, typename>
  struct FieldParser;

  template<>
  struct FieldParser<::mlir::ptr::PtrDiffFlags, ::mlir::ptr::PtrDiffFlags> {
    template <typename ParserT>
    static FailureOr<::mlir::ptr::PtrDiffFlags> parse(ParserT &parser) {
      ::mlir::ptr::PtrDiffFlags flags = {};
      do {
        // Parse the keyword containing a part of the enum.
        ::llvm::StringRef enumKeyword;
        auto loc = parser.getCurrentLocation();
        if (failed(parser.parseOptionalKeyword(&enumKeyword))) {
          return parser.emitError(loc, "expected keyword for Pointer difference flags");
        }

        // Symbolize the keyword.
        if (::std::optional<::mlir::ptr::PtrDiffFlags> flag = ::mlir::ptr::symbolizeEnum<::mlir::ptr::PtrDiffFlags>(enumKeyword)) {
          flags = flags | *flag;
        } else {
          return parser.emitError(loc, "expected one of [none, nuw, nsw] for Pointer difference flags, got: ") << enumKeyword;
        }
      } while (::mlir::succeeded(parser.parseOptionalVerticalBar()));
      return flags;
    }
  };

  /// Support for std::optional, useful in attribute/type definition where the enum is
  /// used as:
  ///
  ///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
  template<>
  struct FieldParser<std::optional<::mlir::ptr::PtrDiffFlags>, std::optional<::mlir::ptr::PtrDiffFlags>> {
    template <typename ParserT>
    static FailureOr<std::optional<::mlir::ptr::PtrDiffFlags>> parse(ParserT &parser) {
      ::mlir::ptr::PtrDiffFlags flags = {};
      bool firstIter = true;
      do {
        // Parse the keyword containing a part of the enum.
        ::llvm::StringRef enumKeyword;
        auto loc = parser.getCurrentLocation();
        if (failed(parser.parseOptionalKeyword(&enumKeyword))) {
          if (firstIter)
            return std::optional<::mlir::ptr::PtrDiffFlags>{};
          return parser.emitError(loc, "expected keyword for Pointer difference flags after '|'");
        }
        firstIter = false;

        // Symbolize the keyword.
        if (::std::optional<::mlir::ptr::PtrDiffFlags> flag = ::mlir::ptr::symbolizeEnum<::mlir::ptr::PtrDiffFlags>(enumKeyword)) {
          flags = flags | *flag;
        } else {
          return parser.emitError(loc, "expected one of [none, nuw, nsw] for Pointer difference flags, got: ") << enumKeyword;
        }
      } while(::mlir::succeeded(parser.parseOptionalVerticalBar()));
      return std::optional<::mlir::ptr::PtrDiffFlags>{flags};
    }
  };
  } // namespace mlir

  namespace llvm {
  inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::ptr::PtrDiffFlags value) {
    auto valueStr = stringifyEnum(value);
    return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::ptr::PtrDiffFlags> {
  using StorageInfo = ::llvm::DenseMapInfo<uint8_t>;

  static inline ::mlir::ptr::PtrDiffFlags getEmptyKey() {
    return static_cast<::mlir::ptr::PtrDiffFlags>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::ptr::PtrDiffFlags getTombstoneKey() {
    return static_cast<::mlir::ptr::PtrDiffFlags>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::ptr::PtrDiffFlags &val) {
    return StorageInfo::getHashValue(static_cast<uint8_t>(val));
  }

  static bool isEqual(const ::mlir::ptr::PtrDiffFlags &lhs, const ::mlir::ptr::PtrDiffFlags &rhs) {
    return lhs == rhs;
  }
};
}

