/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LLVMOps.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::LLVM {

// ATT (0) or Intel (1) asm dialect
enum class AsmDialect : uint64_t {
  AD_ATT = 0,
  AD_Intel = 1,
};

::std::optional<AsmDialect> symbolizeAsmDialect(uint64_t);
::llvm::StringRef stringifyAsmDialect(AsmDialect);
::std::optional<AsmDialect> symbolizeAsmDialect(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForAsmDialect() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(AsmDialect enumValue) {
  return stringifyAsmDialect(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<AsmDialect> symbolizeEnum<AsmDialect>(::llvm::StringRef str) {
  return symbolizeAsmDialect(str);
}

class AsmDialectAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = AsmDialect;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static AsmDialectAttr get(::mlir::MLIRContext *context, AsmDialect val);
  AsmDialect getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::AsmDialect, ::mlir::LLVM::AsmDialect> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::AsmDialect> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for ATT (0) or Intel (1) asm dialect");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::AsmDialect> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::AsmDialect>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [att, intel] for ATT (0) or Intel (1) asm dialect, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::AsmDialect>, std::optional<::mlir::LLVM::AsmDialect>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::AsmDialect>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::AsmDialect>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::AsmDialect> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::AsmDialect>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [att, intel] for ATT (0) or Intel (1) asm dialect, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::AsmDialect value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::AsmDialect> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::AsmDialect getEmptyKey() {
    return static_cast<::mlir::LLVM::AsmDialect>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::AsmDialect getTombstoneKey() {
    return static_cast<::mlir::LLVM::AsmDialect>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::AsmDialect &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::AsmDialect &lhs, const ::mlir::LLVM::AsmDialect &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// llvm.atomicrmw binary operations
enum class AtomicBinOp : uint64_t {
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
  usub_cond = 17,
  usub_sat = 18,
  fmaximum = 19,
  fminimum = 20,
};

::std::optional<AtomicBinOp> symbolizeAtomicBinOp(uint64_t);
::llvm::StringRef stringifyAtomicBinOp(AtomicBinOp);
::std::optional<AtomicBinOp> symbolizeAtomicBinOp(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForAtomicBinOp() {
  return 20;
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

class AtomicBinOpAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = AtomicBinOp;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static AtomicBinOpAttr get(::mlir::MLIRContext *context, AtomicBinOp val);
  AtomicBinOp getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::AtomicBinOp, ::mlir::LLVM::AtomicBinOp> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::AtomicBinOp> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for llvm.atomicrmw binary operations");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::AtomicBinOp> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::AtomicBinOp>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [xchg, add, sub, _and, nand, _or, _xor, max, min, umax, umin, fadd, fsub, fmax, fmin, uinc_wrap, udec_wrap, usub_cond, usub_sat, fmaximum, fminimum] for llvm.atomicrmw binary operations, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::AtomicBinOp>, std::optional<::mlir::LLVM::AtomicBinOp>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::AtomicBinOp>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::AtomicBinOp>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::AtomicBinOp> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::AtomicBinOp>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [xchg, add, sub, _and, nand, _or, _xor, max, min, umax, umin, fadd, fsub, fmax, fmin, uinc_wrap, udec_wrap, usub_cond, usub_sat, fmaximum, fminimum] for llvm.atomicrmw binary operations, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::AtomicBinOp value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::AtomicBinOp> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::AtomicBinOp getEmptyKey() {
    return static_cast<::mlir::LLVM::AtomicBinOp>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::AtomicBinOp getTombstoneKey() {
    return static_cast<::mlir::LLVM::AtomicBinOp>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::AtomicBinOp &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::AtomicBinOp &lhs, const ::mlir::LLVM::AtomicBinOp &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// Atomic ordering for LLVM's memory model
enum class AtomicOrdering : uint64_t {
  not_atomic = 0,
  unordered = 1,
  monotonic = 2,
  acquire = 4,
  release = 5,
  acq_rel = 6,
  seq_cst = 7,
};

::std::optional<AtomicOrdering> symbolizeAtomicOrdering(uint64_t);
::llvm::StringRef stringifyAtomicOrdering(AtomicOrdering);
::std::optional<AtomicOrdering> symbolizeAtomicOrdering(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForAtomicOrdering() {
  return 7;
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

class AtomicOrderingAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = AtomicOrdering;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static AtomicOrderingAttr get(::mlir::MLIRContext *context, AtomicOrdering val);
  AtomicOrdering getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::AtomicOrdering, ::mlir::LLVM::AtomicOrdering> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::AtomicOrdering> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Atomic ordering for LLVM's memory model");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::AtomicOrdering> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::AtomicOrdering>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [not_atomic, unordered, monotonic, acquire, release, acq_rel, seq_cst] for Atomic ordering for LLVM's memory model, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::AtomicOrdering>, std::optional<::mlir::LLVM::AtomicOrdering>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::AtomicOrdering>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::AtomicOrdering>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::AtomicOrdering> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::AtomicOrdering>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [not_atomic, unordered, monotonic, acquire, release, acq_rel, seq_cst] for Atomic ordering for LLVM's memory model, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::AtomicOrdering value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::AtomicOrdering> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::AtomicOrdering getEmptyKey() {
    return static_cast<::mlir::LLVM::AtomicOrdering>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::AtomicOrdering getTombstoneKey() {
    return static_cast<::mlir::LLVM::AtomicOrdering>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::AtomicOrdering &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::AtomicOrdering &lhs, const ::mlir::LLVM::AtomicOrdering &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM::cconv {

// Calling Conventions
enum class CConv : uint64_t {
  C = 0,
  Fast = 8,
  Cold = 9,
  GHC = 10,
  HiPE = 11,
  AnyReg = 13,
  PreserveMost = 14,
  PreserveAll = 15,
  Swift = 16,
  CXX_FAST_TLS = 17,
  Tail = 18,
  CFGuard_Check = 19,
  SwiftTail = 20,
  X86_StdCall = 64,
  X86_FastCall = 65,
  ARM_APCS = 66,
  ARM_AAPCS = 67,
  ARM_AAPCS_VFP = 68,
  MSP430_INTR = 69,
  X86_ThisCall = 70,
  PTX_Kernel = 71,
  PTX_Device = 72,
  SPIR_FUNC = 75,
  SPIR_KERNEL = 76,
  Intel_OCL_BI = 77,
  X86_64_SysV = 78,
  Win64 = 79,
  X86_VectorCall = 80,
  DUMMY_HHVM = 81,
  DUMMY_HHVM_C = 82,
  X86_INTR = 83,
  AVR_INTR = 84,
  AVR_BUILTIN = 86,
  AMDGPU_VS = 87,
  AMDGPU_GS = 88,
  AMDGPU_CS = 90,
  AMDGPU_KERNEL = 91,
  X86_RegCall = 92,
  AMDGPU_HS = 93,
  MSP430_BUILTIN = 94,
  AMDGPU_LS = 95,
  AMDGPU_ES = 96,
  AArch64_VectorCall = 97,
  AArch64_SVE_VectorCall = 98,
  WASM_EmscriptenInvoke = 99,
  AMDGPU_Gfx = 100,
  M68k_INTR = 101,
};

::std::optional<CConv> symbolizeCConv(uint64_t);
::llvm::StringRef stringifyCConv(CConv);
::std::optional<CConv> symbolizeCConv(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForCConv() {
  return 101;
}


inline ::llvm::StringRef stringifyEnum(CConv enumValue) {
  return stringifyCConv(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<CConv> symbolizeEnum<CConv>(::llvm::StringRef str) {
  return symbolizeCConv(str);
}

class CConvAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = CConv;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static CConvAttr get(::mlir::MLIRContext *context, CConv val);
  CConv getValue() const;
};

} // namespace mlir::LLVM::cconv

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::cconv::CConv, ::mlir::LLVM::cconv::CConv> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::cconv::CConv> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Calling Conventions");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::cconv::CConv> attr = ::mlir::LLVM::cconv::symbolizeEnum<::mlir::LLVM::cconv::CConv>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [ccc, fastcc, coldcc, cc_10, cc_11, anyregcc, preserve_mostcc, preserve_allcc, swiftcc, cxx_fast_tlscc, tailcc, cfguard_checkcc, swifttailcc, x86_stdcallcc, x86_fastcallcc, arm_apcscc, arm_aapcscc, arm_aapcs_vfpcc, msp430_intrcc, x86_thiscallcc, ptx_kernelcc, ptx_devicecc, spir_funccc, spir_kernelcc, intel_ocl_bicc, x86_64_sysvcc, win64cc, x86_vectorcallcc, hhvmcc, hhvm_ccc, x86_intrcc, avr_intrcc, avr_builtincc, amdgpu_vscc, amdgpu_gscc, amdgpu_cscc, amdgpu_kernelcc, x86_regcallcc, amdgpu_hscc, msp430_builtincc, amdgpu_lscc, amdgpu_escc, aarch64_vectorcallcc, aarch64_sve_vectorcallcc, wasm_emscripten_invokecc, amdgpu_gfxcc, m68k_intrcc] for Calling Conventions, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::cconv::CConv>, std::optional<::mlir::LLVM::cconv::CConv>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::cconv::CConv>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::cconv::CConv>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::cconv::CConv> attr = ::mlir::LLVM::cconv::symbolizeEnum<::mlir::LLVM::cconv::CConv>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [ccc, fastcc, coldcc, cc_10, cc_11, anyregcc, preserve_mostcc, preserve_allcc, swiftcc, cxx_fast_tlscc, tailcc, cfguard_checkcc, swifttailcc, x86_stdcallcc, x86_fastcallcc, arm_apcscc, arm_aapcscc, arm_aapcs_vfpcc, msp430_intrcc, x86_thiscallcc, ptx_kernelcc, ptx_devicecc, spir_funccc, spir_kernelcc, intel_ocl_bicc, x86_64_sysvcc, win64cc, x86_vectorcallcc, hhvmcc, hhvm_ccc, x86_intrcc, avr_intrcc, avr_builtincc, amdgpu_vscc, amdgpu_gscc, amdgpu_cscc, amdgpu_kernelcc, x86_regcallcc, amdgpu_hscc, msp430_builtincc, amdgpu_lscc, amdgpu_escc, aarch64_vectorcallcc, aarch64_sve_vectorcallcc, wasm_emscripten_invokecc, amdgpu_gfxcc, m68k_intrcc] for Calling Conventions, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::cconv::CConv value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::cconv::CConv> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::cconv::CConv getEmptyKey() {
    return static_cast<::mlir::LLVM::cconv::CConv>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::cconv::CConv getTombstoneKey() {
    return static_cast<::mlir::LLVM::cconv::CConv>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::cconv::CConv &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::cconv::CConv &lhs, const ::mlir::LLVM::cconv::CConv &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM::comdat {

// LLVM Comdat Types
enum class Comdat : uint64_t {
  Any = 0,
  ExactMatch = 1,
  Largest = 2,
  NoDeduplicate = 3,
  SameSize = 4,
};

::std::optional<Comdat> symbolizeComdat(uint64_t);
::llvm::StringRef stringifyComdat(Comdat);
::std::optional<Comdat> symbolizeComdat(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForComdat() {
  return 4;
}


inline ::llvm::StringRef stringifyEnum(Comdat enumValue) {
  return stringifyComdat(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<Comdat> symbolizeEnum<Comdat>(::llvm::StringRef str) {
  return symbolizeComdat(str);
}

class ComdatAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = Comdat;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ComdatAttr get(::mlir::MLIRContext *context, Comdat val);
  Comdat getValue() const;
};

} // namespace mlir::LLVM::comdat

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::comdat::Comdat, ::mlir::LLVM::comdat::Comdat> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::comdat::Comdat> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM Comdat Types");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::comdat::Comdat> attr = ::mlir::LLVM::comdat::symbolizeEnum<::mlir::LLVM::comdat::Comdat>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [any, exactmatch, largest, nodeduplicate, samesize] for LLVM Comdat Types, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::comdat::Comdat>, std::optional<::mlir::LLVM::comdat::Comdat>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::comdat::Comdat>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::comdat::Comdat>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::comdat::Comdat> attr = ::mlir::LLVM::comdat::symbolizeEnum<::mlir::LLVM::comdat::Comdat>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [any, exactmatch, largest, nodeduplicate, samesize] for LLVM Comdat Types, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::comdat::Comdat value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::comdat::Comdat> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::comdat::Comdat getEmptyKey() {
    return static_cast<::mlir::LLVM::comdat::Comdat>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::comdat::Comdat getTombstoneKey() {
    return static_cast<::mlir::LLVM::comdat::Comdat>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::comdat::Comdat &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::comdat::Comdat &lhs, const ::mlir::LLVM::comdat::Comdat &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM DI flags
enum class DIFlags : uint32_t {
  Zero = 0,
  Bit0 = 1,
  Bit1 = 2,
  Private = 1,
  Protected = 2,
  Public = 3,
  FwdDecl = 4,
  AppleBlock = 8,
  ReservedBit4 = 16,
  Virtual = 32,
  Artificial = 64,
  Explicit = 128,
  Prototyped = 256,
  ObjcClassComplete = 512,
  ObjectPointer = 1024,
  Vector = 2048,
  StaticMember = 4096,
  LValueReference = 8192,
  RValueReference = 16384,
  ExportSymbols = 32768,
  SingleInheritance = 65536,
  MultipleInheritance = 65536,
  VirtualInheritance = 65536,
  IntroducedVirtual = 262144,
  BitField = 524288,
  NoReturn = 1048576,
  TypePassByValue = 4194304,
  TypePassByReference = 8388608,
  EnumClass = 16777216,
  Thunk = 33554432,
  NonTrivial = 67108864,
  BigEndian = 134217728,
  LittleEndian = 268435456,
  AllCallsDescribed = 536870912,
};

::std::optional<DIFlags> symbolizeDIFlags(uint32_t);
std::string stringifyDIFlags(DIFlags);
::std::optional<DIFlags> symbolizeDIFlags(::llvm::StringRef);

inline constexpr DIFlags operator|(DIFlags a, DIFlags b) {
  return static_cast<DIFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline constexpr DIFlags operator&(DIFlags a, DIFlags b) {
  return static_cast<DIFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
inline constexpr DIFlags operator^(DIFlags a, DIFlags b) {
  return static_cast<DIFlags>(static_cast<uint32_t>(a) ^ static_cast<uint32_t>(b));
}
inline constexpr DIFlags &operator|=(DIFlags &a, DIFlags b) {
    return a = a | b;
}
inline constexpr DIFlags &operator&=(DIFlags &a, DIFlags b) {
    return a = a & b;
}
inline constexpr DIFlags &operator^=(DIFlags &a, DIFlags b) {
    return a = a ^ b;
}
inline constexpr DIFlags operator~(DIFlags bits) {
  // Ensure only bits that can be present in the enum are set
  return static_cast<DIFlags>(~static_cast<uint32_t>(bits) & static_cast<uint32_t>(1071513599u));
}
inline constexpr bool bitEnumContainsAll(DIFlags bits, DIFlags bit) {
  return (bits & bit) == bit;
}
inline constexpr bool bitEnumContainsAny(DIFlags bits, DIFlags bit) {
  return (static_cast<uint32_t>(bits) & static_cast<uint32_t>(bit)) != 0;
}
inline constexpr DIFlags bitEnumClear(DIFlags bits, DIFlags bit) {
  return bits & ~bit;
}
inline constexpr DIFlags bitEnumSet(DIFlags bits, DIFlags bit, /*optional*/bool value=true) {
  return value ? (bits | bit) : bitEnumClear(bits, bit);
}
  
inline std::string stringifyEnum(DIFlags enumValue) {
  return stringifyDIFlags(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<DIFlags> symbolizeEnum<DIFlags>(::llvm::StringRef str) {
  return symbolizeDIFlags(str);
}

class DIFlagsAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = DIFlags;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static DIFlagsAttr get(::mlir::MLIRContext *context, DIFlags val);
  DIFlags getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::DIFlags, ::mlir::LLVM::DIFlags> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::DIFlags> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM DI flags");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::DIFlags> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::DIFlags>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [Zero, Bit0, Bit1, Private, Protected, Public, FwdDecl, AppleBlock, ReservedBit4, Virtual, Artificial, Explicit, Prototyped, ObjcClassComplete, ObjectPointer, Vector, StaticMember, LValueReference, RValueReference, ExportSymbols, SingleInheritance, MultipleInheritance, VirtualInheritance, IntroducedVirtual, BitField, NoReturn, TypePassByValue, TypePassByReference, EnumClass, Thunk, NonTrivial, BigEndian, LittleEndian, AllCallsDescribed] for LLVM DI flags, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::DIFlags>, std::optional<::mlir::LLVM::DIFlags>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::DIFlags>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::DIFlags>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::DIFlags> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::DIFlags>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [Zero, Bit0, Bit1, Private, Protected, Public, FwdDecl, AppleBlock, ReservedBit4, Virtual, Artificial, Explicit, Prototyped, ObjcClassComplete, ObjectPointer, Vector, StaticMember, LValueReference, RValueReference, ExportSymbols, SingleInheritance, MultipleInheritance, VirtualInheritance, IntroducedVirtual, BitField, NoReturn, TypePassByValue, TypePassByReference, EnumClass, Thunk, NonTrivial, BigEndian, LittleEndian, AllCallsDescribed] for LLVM DI flags, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::DIFlags value) {
  auto valueStr = stringifyEnum(value);
  switch (value) {
  case ::mlir::LLVM::DIFlags::Public:
    return p << valueStr;
  default:
    break;
  }
  auto underlyingValue = static_cast<std::make_unsigned_t<::mlir::LLVM::DIFlags>>(value);
  if (underlyingValue && !llvm::has_single_bit(underlyingValue))
    return p << '"' << valueStr << '"';
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::DIFlags> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::LLVM::DIFlags getEmptyKey() {
    return static_cast<::mlir::LLVM::DIFlags>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::DIFlags getTombstoneKey() {
    return static_cast<::mlir::LLVM::DIFlags>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::DIFlags &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::DIFlags &lhs, const ::mlir::LLVM::DIFlags &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM DISubprogram flags
enum class DISubprogramFlags : uint32_t {
  Virtual = 1,
  PureVirtual = 2,
  LocalToUnit = 4,
  Definition = 8,
  Optimized = 16,
  Pure = 32,
  Elemental = 64,
  Recursive = 128,
  MainSubprogram = 256,
  Deleted = 512,
  ObjCDirect = 2048,
};

::std::optional<DISubprogramFlags> symbolizeDISubprogramFlags(uint32_t);
std::string stringifyDISubprogramFlags(DISubprogramFlags);
::std::optional<DISubprogramFlags> symbolizeDISubprogramFlags(::llvm::StringRef);

inline constexpr DISubprogramFlags operator|(DISubprogramFlags a, DISubprogramFlags b) {
  return static_cast<DISubprogramFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline constexpr DISubprogramFlags operator&(DISubprogramFlags a, DISubprogramFlags b) {
  return static_cast<DISubprogramFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
inline constexpr DISubprogramFlags operator^(DISubprogramFlags a, DISubprogramFlags b) {
  return static_cast<DISubprogramFlags>(static_cast<uint32_t>(a) ^ static_cast<uint32_t>(b));
}
inline constexpr DISubprogramFlags &operator|=(DISubprogramFlags &a, DISubprogramFlags b) {
    return a = a | b;
}
inline constexpr DISubprogramFlags &operator&=(DISubprogramFlags &a, DISubprogramFlags b) {
    return a = a & b;
}
inline constexpr DISubprogramFlags &operator^=(DISubprogramFlags &a, DISubprogramFlags b) {
    return a = a ^ b;
}
inline constexpr DISubprogramFlags operator~(DISubprogramFlags bits) {
  // Ensure only bits that can be present in the enum are set
  return static_cast<DISubprogramFlags>(~static_cast<uint32_t>(bits) & static_cast<uint32_t>(3071u));
}
inline constexpr bool bitEnumContainsAll(DISubprogramFlags bits, DISubprogramFlags bit) {
  return (bits & bit) == bit;
}
inline constexpr bool bitEnumContainsAny(DISubprogramFlags bits, DISubprogramFlags bit) {
  return (static_cast<uint32_t>(bits) & static_cast<uint32_t>(bit)) != 0;
}
inline constexpr DISubprogramFlags bitEnumClear(DISubprogramFlags bits, DISubprogramFlags bit) {
  return bits & ~bit;
}
inline constexpr DISubprogramFlags bitEnumSet(DISubprogramFlags bits, DISubprogramFlags bit, /*optional*/bool value=true) {
  return value ? (bits | bit) : bitEnumClear(bits, bit);
}
  
inline std::string stringifyEnum(DISubprogramFlags enumValue) {
  return stringifyDISubprogramFlags(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<DISubprogramFlags> symbolizeEnum<DISubprogramFlags>(::llvm::StringRef str) {
  return symbolizeDISubprogramFlags(str);
}

class DISubprogramFlagsAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = DISubprogramFlags;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static DISubprogramFlagsAttr get(::mlir::MLIRContext *context, DISubprogramFlags val);
  DISubprogramFlags getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::DISubprogramFlags, ::mlir::LLVM::DISubprogramFlags> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::DISubprogramFlags> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM DISubprogram flags");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::DISubprogramFlags> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::DISubprogramFlags>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [Virtual, PureVirtual, LocalToUnit, Definition, Optimized, Pure, Elemental, Recursive, MainSubprogram, Deleted, ObjCDirect] for LLVM DISubprogram flags, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::DISubprogramFlags>, std::optional<::mlir::LLVM::DISubprogramFlags>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::DISubprogramFlags>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::DISubprogramFlags>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::DISubprogramFlags> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::DISubprogramFlags>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [Virtual, PureVirtual, LocalToUnit, Definition, Optimized, Pure, Elemental, Recursive, MainSubprogram, Deleted, ObjCDirect] for LLVM DISubprogram flags, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::DISubprogramFlags value) {
  auto valueStr = stringifyEnum(value);
  auto underlyingValue = static_cast<std::make_unsigned_t<::mlir::LLVM::DISubprogramFlags>>(value);
  if (underlyingValue && !llvm::has_single_bit(underlyingValue))
    return p << '"' << valueStr << '"';
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::DISubprogramFlags> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::LLVM::DISubprogramFlags getEmptyKey() {
    return static_cast<::mlir::LLVM::DISubprogramFlags>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::DISubprogramFlags getTombstoneKey() {
    return static_cast<::mlir::LLVM::DISubprogramFlags>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::DISubprogramFlags &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::DISubprogramFlags &lhs, const ::mlir::LLVM::DISubprogramFlags &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// llvm.fcmp comparison predicate
enum class FCmpPredicate : uint64_t {
  _false = 0,
  oeq = 1,
  ogt = 2,
  oge = 3,
  olt = 4,
  ole = 5,
  one = 6,
  ord = 7,
  ueq = 8,
  ugt = 9,
  uge = 10,
  ult = 11,
  ule = 12,
  une = 13,
  uno = 14,
  _true = 15,
};

::std::optional<FCmpPredicate> symbolizeFCmpPredicate(uint64_t);
::llvm::StringRef stringifyFCmpPredicate(FCmpPredicate);
::std::optional<FCmpPredicate> symbolizeFCmpPredicate(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForFCmpPredicate() {
  return 15;
}


inline ::llvm::StringRef stringifyEnum(FCmpPredicate enumValue) {
  return stringifyFCmpPredicate(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<FCmpPredicate> symbolizeEnum<FCmpPredicate>(::llvm::StringRef str) {
  return symbolizeFCmpPredicate(str);
}

class FCmpPredicateAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = FCmpPredicate;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static FCmpPredicateAttr get(::mlir::MLIRContext *context, FCmpPredicate val);
  FCmpPredicate getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::FCmpPredicate, ::mlir::LLVM::FCmpPredicate> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::FCmpPredicate> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for llvm.fcmp comparison predicate");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::FCmpPredicate> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::FCmpPredicate>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [_false, oeq, ogt, oge, olt, ole, one, ord, ueq, ugt, uge, ult, ule, une, uno, _true] for llvm.fcmp comparison predicate, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::FCmpPredicate>, std::optional<::mlir::LLVM::FCmpPredicate>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::FCmpPredicate>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::FCmpPredicate>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::FCmpPredicate> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::FCmpPredicate>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [_false, oeq, ogt, oge, olt, ole, one, ord, ueq, ugt, uge, ult, ule, une, uno, _true] for llvm.fcmp comparison predicate, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::FCmpPredicate value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::FCmpPredicate> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::FCmpPredicate getEmptyKey() {
    return static_cast<::mlir::LLVM::FCmpPredicate>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::FCmpPredicate getTombstoneKey() {
    return static_cast<::mlir::LLVM::FCmpPredicate>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::FCmpPredicate &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::FCmpPredicate &lhs, const ::mlir::LLVM::FCmpPredicate &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM Exception Behavior
enum class FPExceptionBehavior : uint64_t {
  Ignore = 0,
  MayTrap = 1,
  Strict = 2,
};

::std::optional<FPExceptionBehavior> symbolizeFPExceptionBehavior(uint64_t);
::llvm::StringRef stringifyFPExceptionBehavior(FPExceptionBehavior);
::std::optional<FPExceptionBehavior> symbolizeFPExceptionBehavior(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForFPExceptionBehavior() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(FPExceptionBehavior enumValue) {
  return stringifyFPExceptionBehavior(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<FPExceptionBehavior> symbolizeEnum<FPExceptionBehavior>(::llvm::StringRef str) {
  return symbolizeFPExceptionBehavior(str);
}

class FPExceptionBehaviorAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = FPExceptionBehavior;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static FPExceptionBehaviorAttr get(::mlir::MLIRContext *context, FPExceptionBehavior val);
  FPExceptionBehavior getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::FPExceptionBehavior, ::mlir::LLVM::FPExceptionBehavior> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::FPExceptionBehavior> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM Exception Behavior");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::FPExceptionBehavior> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::FPExceptionBehavior>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [ignore, maytrap, strict] for LLVM Exception Behavior, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::FPExceptionBehavior>, std::optional<::mlir::LLVM::FPExceptionBehavior>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::FPExceptionBehavior>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::FPExceptionBehavior>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::FPExceptionBehavior> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::FPExceptionBehavior>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [ignore, maytrap, strict] for LLVM Exception Behavior, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::FPExceptionBehavior value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::FPExceptionBehavior> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::FPExceptionBehavior getEmptyKey() {
    return static_cast<::mlir::LLVM::FPExceptionBehavior>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::FPExceptionBehavior getTombstoneKey() {
    return static_cast<::mlir::LLVM::FPExceptionBehavior>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::FPExceptionBehavior &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::FPExceptionBehavior &lhs, const ::mlir::LLVM::FPExceptionBehavior &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM fastmath flags
enum class FastmathFlags : uint32_t {
  none = 0,
  nnan = 1,
  ninf = 2,
  nsz = 4,
  arcp = 8,
  contract = 16,
  afn = 32,
  reassoc = 64,
  fast = 127,
};

::std::optional<FastmathFlags> symbolizeFastmathFlags(uint32_t);
std::string stringifyFastmathFlags(FastmathFlags);
::std::optional<FastmathFlags> symbolizeFastmathFlags(::llvm::StringRef);

inline constexpr FastmathFlags operator|(FastmathFlags a, FastmathFlags b) {
  return static_cast<FastmathFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline constexpr FastmathFlags operator&(FastmathFlags a, FastmathFlags b) {
  return static_cast<FastmathFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
inline constexpr FastmathFlags operator^(FastmathFlags a, FastmathFlags b) {
  return static_cast<FastmathFlags>(static_cast<uint32_t>(a) ^ static_cast<uint32_t>(b));
}
inline constexpr FastmathFlags &operator|=(FastmathFlags &a, FastmathFlags b) {
    return a = a | b;
}
inline constexpr FastmathFlags &operator&=(FastmathFlags &a, FastmathFlags b) {
    return a = a & b;
}
inline constexpr FastmathFlags &operator^=(FastmathFlags &a, FastmathFlags b) {
    return a = a ^ b;
}
inline constexpr FastmathFlags operator~(FastmathFlags bits) {
  // Ensure only bits that can be present in the enum are set
  return static_cast<FastmathFlags>(~static_cast<uint32_t>(bits) & static_cast<uint32_t>(127u));
}
inline constexpr bool bitEnumContainsAll(FastmathFlags bits, FastmathFlags bit) {
  return (bits & bit) == bit;
}
inline constexpr bool bitEnumContainsAny(FastmathFlags bits, FastmathFlags bit) {
  return (static_cast<uint32_t>(bits) & static_cast<uint32_t>(bit)) != 0;
}
inline constexpr FastmathFlags bitEnumClear(FastmathFlags bits, FastmathFlags bit) {
  return bits & ~bit;
}
inline constexpr FastmathFlags bitEnumSet(FastmathFlags bits, FastmathFlags bit, /*optional*/bool value=true) {
  return value ? (bits | bit) : bitEnumClear(bits, bit);
}
  
inline std::string stringifyEnum(FastmathFlags enumValue) {
  return stringifyFastmathFlags(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<FastmathFlags> symbolizeEnum<FastmathFlags>(::llvm::StringRef str) {
  return symbolizeFastmathFlags(str);
}

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::FastmathFlags, ::mlir::LLVM::FastmathFlags> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::FastmathFlags> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM fastmath flags");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::FastmathFlags> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::FastmathFlags>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, nnan, ninf, nsz, arcp, contract, afn, reassoc, fast] for LLVM fastmath flags, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::FastmathFlags>, std::optional<::mlir::LLVM::FastmathFlags>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::FastmathFlags>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::FastmathFlags>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::FastmathFlags> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::FastmathFlags>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, nnan, ninf, nsz, arcp, contract, afn, reassoc, fast] for LLVM fastmath flags, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::FastmathFlags value) {
  auto valueStr = stringifyEnum(value);
  switch (value) {
  case ::mlir::LLVM::FastmathFlags::fast:
    return p << valueStr;
  default:
    break;
  }
  auto underlyingValue = static_cast<std::make_unsigned_t<::mlir::LLVM::FastmathFlags>>(value);
  if (underlyingValue && !llvm::has_single_bit(underlyingValue))
    return p << '"' << valueStr << '"';
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::FastmathFlags> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::LLVM::FastmathFlags getEmptyKey() {
    return static_cast<::mlir::LLVM::FastmathFlags>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::FastmathFlags getTombstoneKey() {
    return static_cast<::mlir::LLVM::FastmathFlags>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::FastmathFlags &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::FastmathFlags &lhs, const ::mlir::LLVM::FastmathFlags &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM::framePointerKind {

// LLVM FramePointerKind
enum class FramePointerKind : uint64_t {
  None = 0,
  NonLeaf = 1,
  All = 2,
  Reserved = 3,
  NonLeafNoReserve = 4,
};

::std::optional<FramePointerKind> symbolizeFramePointerKind(uint64_t);
::llvm::StringRef stringifyFramePointerKind(FramePointerKind);
::std::optional<FramePointerKind> symbolizeFramePointerKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForFramePointerKind() {
  return 4;
}


inline ::llvm::StringRef stringifyEnum(FramePointerKind enumValue) {
  return stringifyFramePointerKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<FramePointerKind> symbolizeEnum<FramePointerKind>(::llvm::StringRef str) {
  return symbolizeFramePointerKind(str);
}

class FramePointerKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = FramePointerKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static FramePointerKindAttr get(::mlir::MLIRContext *context, FramePointerKind val);
  FramePointerKind getValue() const;
};

} // namespace mlir::LLVM::framePointerKind

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::framePointerKind::FramePointerKind, ::mlir::LLVM::framePointerKind::FramePointerKind> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::framePointerKind::FramePointerKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM FramePointerKind");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::framePointerKind::FramePointerKind> attr = ::mlir::LLVM::framePointerKind::symbolizeEnum<::mlir::LLVM::framePointerKind::FramePointerKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, \"non-leaf\"non-leaf, all, reserved, \"non-leaf-no-reserve\"non-leaf-no-reserve] for LLVM FramePointerKind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::framePointerKind::FramePointerKind>, std::optional<::mlir::LLVM::framePointerKind::FramePointerKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::framePointerKind::FramePointerKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::framePointerKind::FramePointerKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::framePointerKind::FramePointerKind> attr = ::mlir::LLVM::framePointerKind::symbolizeEnum<::mlir::LLVM::framePointerKind::FramePointerKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, \"non-leaf\"non-leaf, all, reserved, \"non-leaf-no-reserve\"non-leaf-no-reserve] for LLVM FramePointerKind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::framePointerKind::FramePointerKind value) {
  auto valueStr = stringifyEnum(value);
  switch (value) {
  case ::mlir::LLVM::framePointerKind::FramePointerKind::None:
  case ::mlir::LLVM::framePointerKind::FramePointerKind::All:
  case ::mlir::LLVM::framePointerKind::FramePointerKind::Reserved:
    break;
  default:
    return p << '"' << valueStr << '"';
  }
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::framePointerKind::FramePointerKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::framePointerKind::FramePointerKind getEmptyKey() {
    return static_cast<::mlir::LLVM::framePointerKind::FramePointerKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::framePointerKind::FramePointerKind getTombstoneKey() {
    return static_cast<::mlir::LLVM::framePointerKind::FramePointerKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::framePointerKind::FramePointerKind &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::framePointerKind::FramePointerKind &lhs, const ::mlir::LLVM::framePointerKind::FramePointerKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// ::mlir::LLVM::GEPNoWrapFlags
enum class GEPNoWrapFlags : uint32_t {
  none = 0,
  inboundsFlag = 1,
  nusw = 2,
  nuw = 4,
  inbounds = 3,
};

::std::optional<GEPNoWrapFlags> symbolizeGEPNoWrapFlags(uint32_t);
std::string stringifyGEPNoWrapFlags(GEPNoWrapFlags);
::std::optional<GEPNoWrapFlags> symbolizeGEPNoWrapFlags(::llvm::StringRef);

inline constexpr GEPNoWrapFlags operator|(GEPNoWrapFlags a, GEPNoWrapFlags b) {
  return static_cast<GEPNoWrapFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline constexpr GEPNoWrapFlags operator&(GEPNoWrapFlags a, GEPNoWrapFlags b) {
  return static_cast<GEPNoWrapFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
inline constexpr GEPNoWrapFlags operator^(GEPNoWrapFlags a, GEPNoWrapFlags b) {
  return static_cast<GEPNoWrapFlags>(static_cast<uint32_t>(a) ^ static_cast<uint32_t>(b));
}
inline constexpr GEPNoWrapFlags &operator|=(GEPNoWrapFlags &a, GEPNoWrapFlags b) {
    return a = a | b;
}
inline constexpr GEPNoWrapFlags &operator&=(GEPNoWrapFlags &a, GEPNoWrapFlags b) {
    return a = a & b;
}
inline constexpr GEPNoWrapFlags &operator^=(GEPNoWrapFlags &a, GEPNoWrapFlags b) {
    return a = a ^ b;
}
inline constexpr GEPNoWrapFlags operator~(GEPNoWrapFlags bits) {
  // Ensure only bits that can be present in the enum are set
  return static_cast<GEPNoWrapFlags>(~static_cast<uint32_t>(bits) & static_cast<uint32_t>(7u));
}
inline constexpr bool bitEnumContainsAll(GEPNoWrapFlags bits, GEPNoWrapFlags bit) {
  return (bits & bit) == bit;
}
inline constexpr bool bitEnumContainsAny(GEPNoWrapFlags bits, GEPNoWrapFlags bit) {
  return (static_cast<uint32_t>(bits) & static_cast<uint32_t>(bit)) != 0;
}
inline constexpr GEPNoWrapFlags bitEnumClear(GEPNoWrapFlags bits, GEPNoWrapFlags bit) {
  return bits & ~bit;
}
inline constexpr GEPNoWrapFlags bitEnumSet(GEPNoWrapFlags bits, GEPNoWrapFlags bit, /*optional*/bool value=true) {
  return value ? (bits | bit) : bitEnumClear(bits, bit);
}
  
inline std::string stringifyEnum(GEPNoWrapFlags enumValue) {
  return stringifyGEPNoWrapFlags(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<GEPNoWrapFlags> symbolizeEnum<GEPNoWrapFlags>(::llvm::StringRef str) {
  return symbolizeGEPNoWrapFlags(str);
}

} // namespace mlir::LLVM

  namespace mlir {
  template <typename T, typename>
  struct FieldParser;

  template<>
  struct FieldParser<::mlir::LLVM::GEPNoWrapFlags, ::mlir::LLVM::GEPNoWrapFlags> {
    template <typename ParserT>
    static FailureOr<::mlir::LLVM::GEPNoWrapFlags> parse(ParserT &parser) {
      ::mlir::LLVM::GEPNoWrapFlags flags = {};
      do {
        // Parse the keyword containing a part of the enum.
        ::llvm::StringRef enumKeyword;
        auto loc = parser.getCurrentLocation();
        if (failed(parser.parseOptionalKeyword(&enumKeyword))) {
          return parser.emitError(loc, "expected keyword for ::mlir::LLVM::GEPNoWrapFlags");
        }

        // Symbolize the keyword.
        if (::std::optional<::mlir::LLVM::GEPNoWrapFlags> flag = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::GEPNoWrapFlags>(enumKeyword)) {
          flags = flags | *flag;
        } else {
          return parser.emitError(loc, "expected one of [none, inbounds_flag, nusw, nuw, inbounds] for ::mlir::LLVM::GEPNoWrapFlags, got: ") << enumKeyword;
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
  struct FieldParser<std::optional<::mlir::LLVM::GEPNoWrapFlags>, std::optional<::mlir::LLVM::GEPNoWrapFlags>> {
    template <typename ParserT>
    static FailureOr<std::optional<::mlir::LLVM::GEPNoWrapFlags>> parse(ParserT &parser) {
      ::mlir::LLVM::GEPNoWrapFlags flags = {};
      bool firstIter = true;
      do {
        // Parse the keyword containing a part of the enum.
        ::llvm::StringRef enumKeyword;
        auto loc = parser.getCurrentLocation();
        if (failed(parser.parseOptionalKeyword(&enumKeyword))) {
          if (firstIter)
            return std::optional<::mlir::LLVM::GEPNoWrapFlags>{};
          return parser.emitError(loc, "expected keyword for ::mlir::LLVM::GEPNoWrapFlags after '|'");
        }
        firstIter = false;

        // Symbolize the keyword.
        if (::std::optional<::mlir::LLVM::GEPNoWrapFlags> flag = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::GEPNoWrapFlags>(enumKeyword)) {
          flags = flags | *flag;
        } else {
          return parser.emitError(loc, "expected one of [none, inbounds_flag, nusw, nuw, inbounds] for ::mlir::LLVM::GEPNoWrapFlags, got: ") << enumKeyword;
        }
      } while(::mlir::succeeded(parser.parseOptionalVerticalBar()));
      return std::optional<::mlir::LLVM::GEPNoWrapFlags>{flags};
    }
  };
  } // namespace mlir

  namespace llvm {
  inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::GEPNoWrapFlags value) {
    auto valueStr = stringifyEnum(value);
    return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::GEPNoWrapFlags> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::LLVM::GEPNoWrapFlags getEmptyKey() {
    return static_cast<::mlir::LLVM::GEPNoWrapFlags>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::GEPNoWrapFlags getTombstoneKey() {
    return static_cast<::mlir::LLVM::GEPNoWrapFlags>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::GEPNoWrapFlags &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::GEPNoWrapFlags &lhs, const ::mlir::LLVM::GEPNoWrapFlags &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// llvm.icmp comparison predicate
enum class ICmpPredicate : uint64_t {
  eq = 0,
  ne = 1,
  slt = 2,
  sle = 3,
  sgt = 4,
  sge = 5,
  ult = 6,
  ule = 7,
  ugt = 8,
  uge = 9,
};

::std::optional<ICmpPredicate> symbolizeICmpPredicate(uint64_t);
::llvm::StringRef stringifyICmpPredicate(ICmpPredicate);
::std::optional<ICmpPredicate> symbolizeICmpPredicate(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForICmpPredicate() {
  return 9;
}


inline ::llvm::StringRef stringifyEnum(ICmpPredicate enumValue) {
  return stringifyICmpPredicate(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ICmpPredicate> symbolizeEnum<ICmpPredicate>(::llvm::StringRef str) {
  return symbolizeICmpPredicate(str);
}

class ICmpPredicateAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ICmpPredicate;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ICmpPredicateAttr get(::mlir::MLIRContext *context, ICmpPredicate val);
  ICmpPredicate getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::ICmpPredicate, ::mlir::LLVM::ICmpPredicate> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::ICmpPredicate> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for llvm.icmp comparison predicate");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::ICmpPredicate> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::ICmpPredicate>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [eq, ne, slt, sle, sgt, sge, ult, ule, ugt, uge] for llvm.icmp comparison predicate, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::ICmpPredicate>, std::optional<::mlir::LLVM::ICmpPredicate>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::ICmpPredicate>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::ICmpPredicate>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::ICmpPredicate> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::ICmpPredicate>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [eq, ne, slt, sle, sgt, sge, ult, ule, ugt, uge] for llvm.icmp comparison predicate, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::ICmpPredicate value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::ICmpPredicate> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::ICmpPredicate getEmptyKey() {
    return static_cast<::mlir::LLVM::ICmpPredicate>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::ICmpPredicate getTombstoneKey() {
    return static_cast<::mlir::LLVM::ICmpPredicate>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::ICmpPredicate &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::ICmpPredicate &lhs, const ::mlir::LLVM::ICmpPredicate &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM integer overflow flags
enum class IntegerOverflowFlags : uint32_t {
  none = 0,
  nsw = 1,
  nuw = 2,
};

::std::optional<IntegerOverflowFlags> symbolizeIntegerOverflowFlags(uint32_t);
std::string stringifyIntegerOverflowFlags(IntegerOverflowFlags);
::std::optional<IntegerOverflowFlags> symbolizeIntegerOverflowFlags(::llvm::StringRef);

inline constexpr IntegerOverflowFlags operator|(IntegerOverflowFlags a, IntegerOverflowFlags b) {
  return static_cast<IntegerOverflowFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline constexpr IntegerOverflowFlags operator&(IntegerOverflowFlags a, IntegerOverflowFlags b) {
  return static_cast<IntegerOverflowFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
inline constexpr IntegerOverflowFlags operator^(IntegerOverflowFlags a, IntegerOverflowFlags b) {
  return static_cast<IntegerOverflowFlags>(static_cast<uint32_t>(a) ^ static_cast<uint32_t>(b));
}
inline constexpr IntegerOverflowFlags &operator|=(IntegerOverflowFlags &a, IntegerOverflowFlags b) {
    return a = a | b;
}
inline constexpr IntegerOverflowFlags &operator&=(IntegerOverflowFlags &a, IntegerOverflowFlags b) {
    return a = a & b;
}
inline constexpr IntegerOverflowFlags &operator^=(IntegerOverflowFlags &a, IntegerOverflowFlags b) {
    return a = a ^ b;
}
inline constexpr IntegerOverflowFlags operator~(IntegerOverflowFlags bits) {
  // Ensure only bits that can be present in the enum are set
  return static_cast<IntegerOverflowFlags>(~static_cast<uint32_t>(bits) & static_cast<uint32_t>(3u));
}
inline constexpr bool bitEnumContainsAll(IntegerOverflowFlags bits, IntegerOverflowFlags bit) {
  return (bits & bit) == bit;
}
inline constexpr bool bitEnumContainsAny(IntegerOverflowFlags bits, IntegerOverflowFlags bit) {
  return (static_cast<uint32_t>(bits) & static_cast<uint32_t>(bit)) != 0;
}
inline constexpr IntegerOverflowFlags bitEnumClear(IntegerOverflowFlags bits, IntegerOverflowFlags bit) {
  return bits & ~bit;
}
inline constexpr IntegerOverflowFlags bitEnumSet(IntegerOverflowFlags bits, IntegerOverflowFlags bit, /*optional*/bool value=true) {
  return value ? (bits | bit) : bitEnumClear(bits, bit);
}
  
inline std::string stringifyEnum(IntegerOverflowFlags enumValue) {
  return stringifyIntegerOverflowFlags(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<IntegerOverflowFlags> symbolizeEnum<IntegerOverflowFlags>(::llvm::StringRef str) {
  return symbolizeIntegerOverflowFlags(str);
}

} // namespace mlir::LLVM

  namespace mlir {
  template <typename T, typename>
  struct FieldParser;

  template<>
  struct FieldParser<::mlir::LLVM::IntegerOverflowFlags, ::mlir::LLVM::IntegerOverflowFlags> {
    template <typename ParserT>
    static FailureOr<::mlir::LLVM::IntegerOverflowFlags> parse(ParserT &parser) {
      ::mlir::LLVM::IntegerOverflowFlags flags = {};
      do {
        // Parse the keyword containing a part of the enum.
        ::llvm::StringRef enumKeyword;
        auto loc = parser.getCurrentLocation();
        if (failed(parser.parseOptionalKeyword(&enumKeyword))) {
          return parser.emitError(loc, "expected keyword for LLVM integer overflow flags");
        }

        // Symbolize the keyword.
        if (::std::optional<::mlir::LLVM::IntegerOverflowFlags> flag = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::IntegerOverflowFlags>(enumKeyword)) {
          flags = flags | *flag;
        } else {
          return parser.emitError(loc, "expected one of [none, nsw, nuw] for LLVM integer overflow flags, got: ") << enumKeyword;
        }
      } while (::mlir::succeeded(parser.parseOptionalComma()));
      return flags;
    }
  };

  /// Support for std::optional, useful in attribute/type definition where the enum is
  /// used as:
  ///
  ///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
  template<>
  struct FieldParser<std::optional<::mlir::LLVM::IntegerOverflowFlags>, std::optional<::mlir::LLVM::IntegerOverflowFlags>> {
    template <typename ParserT>
    static FailureOr<std::optional<::mlir::LLVM::IntegerOverflowFlags>> parse(ParserT &parser) {
      ::mlir::LLVM::IntegerOverflowFlags flags = {};
      bool firstIter = true;
      do {
        // Parse the keyword containing a part of the enum.
        ::llvm::StringRef enumKeyword;
        auto loc = parser.getCurrentLocation();
        if (failed(parser.parseOptionalKeyword(&enumKeyword))) {
          if (firstIter)
            return std::optional<::mlir::LLVM::IntegerOverflowFlags>{};
          return parser.emitError(loc, "expected keyword for LLVM integer overflow flags after ', '");
        }
        firstIter = false;

        // Symbolize the keyword.
        if (::std::optional<::mlir::LLVM::IntegerOverflowFlags> flag = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::IntegerOverflowFlags>(enumKeyword)) {
          flags = flags | *flag;
        } else {
          return parser.emitError(loc, "expected one of [none, nsw, nuw] for LLVM integer overflow flags, got: ") << enumKeyword;
        }
      } while(::mlir::succeeded(parser.parseOptionalComma()));
      return std::optional<::mlir::LLVM::IntegerOverflowFlags>{flags};
    }
  };
  } // namespace mlir

  namespace llvm {
  inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::IntegerOverflowFlags value) {
    auto valueStr = stringifyEnum(value);
    return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::IntegerOverflowFlags> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::LLVM::IntegerOverflowFlags getEmptyKey() {
    return static_cast<::mlir::LLVM::IntegerOverflowFlags>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::IntegerOverflowFlags getTombstoneKey() {
    return static_cast<::mlir::LLVM::IntegerOverflowFlags>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::IntegerOverflowFlags &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::IntegerOverflowFlags &lhs, const ::mlir::LLVM::IntegerOverflowFlags &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM debug emission kind
enum class DIEmissionKind : uint64_t {
  None = 0,
  Full = 1,
  LineTablesOnly = 2,
  DebugDirectivesOnly = 3,
};

::std::optional<DIEmissionKind> symbolizeDIEmissionKind(uint64_t);
::llvm::StringRef stringifyDIEmissionKind(DIEmissionKind);
::std::optional<DIEmissionKind> symbolizeDIEmissionKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForDIEmissionKind() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(DIEmissionKind enumValue) {
  return stringifyDIEmissionKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<DIEmissionKind> symbolizeEnum<DIEmissionKind>(::llvm::StringRef str) {
  return symbolizeDIEmissionKind(str);
}

class DIEmissionKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = DIEmissionKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static DIEmissionKindAttr get(::mlir::MLIRContext *context, DIEmissionKind val);
  DIEmissionKind getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::DIEmissionKind, ::mlir::LLVM::DIEmissionKind> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::DIEmissionKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM debug emission kind");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::DIEmissionKind> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::DIEmissionKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [None, Full, LineTablesOnly, DebugDirectivesOnly] for LLVM debug emission kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::DIEmissionKind>, std::optional<::mlir::LLVM::DIEmissionKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::DIEmissionKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::DIEmissionKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::DIEmissionKind> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::DIEmissionKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [None, Full, LineTablesOnly, DebugDirectivesOnly] for LLVM debug emission kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::DIEmissionKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::DIEmissionKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::DIEmissionKind getEmptyKey() {
    return static_cast<::mlir::LLVM::DIEmissionKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::DIEmissionKind getTombstoneKey() {
    return static_cast<::mlir::LLVM::DIEmissionKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::DIEmissionKind &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::DIEmissionKind &lhs, const ::mlir::LLVM::DIEmissionKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM debug name table kind
enum class DINameTableKind : uint64_t {
  Default = 0,
  GNU = 1,
  None = 2,
  Apple = 3,
};

::std::optional<DINameTableKind> symbolizeDINameTableKind(uint64_t);
::llvm::StringRef stringifyDINameTableKind(DINameTableKind);
::std::optional<DINameTableKind> symbolizeDINameTableKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForDINameTableKind() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(DINameTableKind enumValue) {
  return stringifyDINameTableKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<DINameTableKind> symbolizeEnum<DINameTableKind>(::llvm::StringRef str) {
  return symbolizeDINameTableKind(str);
}

class DINameTableKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = DINameTableKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static DINameTableKindAttr get(::mlir::MLIRContext *context, DINameTableKind val);
  DINameTableKind getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::DINameTableKind, ::mlir::LLVM::DINameTableKind> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::DINameTableKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM debug name table kind");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::DINameTableKind> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::DINameTableKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [Default, GNU, None, Apple] for LLVM debug name table kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::DINameTableKind>, std::optional<::mlir::LLVM::DINameTableKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::DINameTableKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::DINameTableKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::DINameTableKind> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::DINameTableKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [Default, GNU, None, Apple] for LLVM debug name table kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::DINameTableKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::DINameTableKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::DINameTableKind getEmptyKey() {
    return static_cast<::mlir::LLVM::DINameTableKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::DINameTableKind getTombstoneKey() {
    return static_cast<::mlir::LLVM::DINameTableKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::DINameTableKind &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::DINameTableKind &lhs, const ::mlir::LLVM::DINameTableKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM ProfileSummary format kinds
enum class ProfileSummaryFormatKind : uint64_t {
  SampleProfile = 0,
  InstrProf = 1,
  CSInstrProf = 2,
};

::std::optional<ProfileSummaryFormatKind> symbolizeProfileSummaryFormatKind(uint64_t);
::llvm::StringRef stringifyProfileSummaryFormatKind(ProfileSummaryFormatKind);
::std::optional<ProfileSummaryFormatKind> symbolizeProfileSummaryFormatKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForProfileSummaryFormatKind() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(ProfileSummaryFormatKind enumValue) {
  return stringifyProfileSummaryFormatKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ProfileSummaryFormatKind> symbolizeEnum<ProfileSummaryFormatKind>(::llvm::StringRef str) {
  return symbolizeProfileSummaryFormatKind(str);
}

class ProfileSummaryFormatKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ProfileSummaryFormatKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ProfileSummaryFormatKindAttr get(::mlir::MLIRContext *context, ProfileSummaryFormatKind val);
  ProfileSummaryFormatKind getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::ProfileSummaryFormatKind, ::mlir::LLVM::ProfileSummaryFormatKind> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::ProfileSummaryFormatKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM ProfileSummary format kinds");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::ProfileSummaryFormatKind> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::ProfileSummaryFormatKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [SampleProfile, InstrProf, CSInstrProf] for LLVM ProfileSummary format kinds, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::ProfileSummaryFormatKind>, std::optional<::mlir::LLVM::ProfileSummaryFormatKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::ProfileSummaryFormatKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::ProfileSummaryFormatKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::ProfileSummaryFormatKind> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::ProfileSummaryFormatKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [SampleProfile, InstrProf, CSInstrProf] for LLVM ProfileSummary format kinds, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::ProfileSummaryFormatKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::ProfileSummaryFormatKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::ProfileSummaryFormatKind getEmptyKey() {
    return static_cast<::mlir::LLVM::ProfileSummaryFormatKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::ProfileSummaryFormatKind getTombstoneKey() {
    return static_cast<::mlir::LLVM::ProfileSummaryFormatKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::ProfileSummaryFormatKind &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::ProfileSummaryFormatKind &lhs, const ::mlir::LLVM::ProfileSummaryFormatKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM::linkage {

// LLVM linkage types
enum class Linkage : uint64_t {
  External = 0,
  AvailableExternally = 1,
  Linkonce = 2,
  LinkonceODR = 3,
  Weak = 4,
  WeakODR = 5,
  Appending = 6,
  Internal = 7,
  Private = 8,
  ExternWeak = 9,
  Common = 10,
};

::std::optional<Linkage> symbolizeLinkage(uint64_t);
::llvm::StringRef stringifyLinkage(Linkage);
::std::optional<Linkage> symbolizeLinkage(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForLinkage() {
  return 10;
}


inline ::llvm::StringRef stringifyEnum(Linkage enumValue) {
  return stringifyLinkage(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<Linkage> symbolizeEnum<Linkage>(::llvm::StringRef str) {
  return symbolizeLinkage(str);
}

class LinkageAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = Linkage;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static LinkageAttr get(::mlir::MLIRContext *context, Linkage val);
  Linkage getValue() const;
};

} // namespace mlir::LLVM::linkage

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::linkage::Linkage, ::mlir::LLVM::linkage::Linkage> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::linkage::Linkage> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM linkage types");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::linkage::Linkage> attr = ::mlir::LLVM::linkage::symbolizeEnum<::mlir::LLVM::linkage::Linkage>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [external, available_externally, linkonce, linkonce_odr, weak, weak_odr, appending, internal, private, extern_weak, common] for LLVM linkage types, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::linkage::Linkage>, std::optional<::mlir::LLVM::linkage::Linkage>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::linkage::Linkage>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::linkage::Linkage>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::linkage::Linkage> attr = ::mlir::LLVM::linkage::symbolizeEnum<::mlir::LLVM::linkage::Linkage>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [external, available_externally, linkonce, linkonce_odr, weak, weak_odr, appending, internal, private, extern_weak, common] for LLVM linkage types, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::linkage::Linkage value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::linkage::Linkage> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::linkage::Linkage getEmptyKey() {
    return static_cast<::mlir::LLVM::linkage::Linkage>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::linkage::Linkage getTombstoneKey() {
    return static_cast<::mlir::LLVM::linkage::Linkage>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::linkage::Linkage &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::linkage::Linkage &lhs, const ::mlir::LLVM::linkage::Linkage &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM Module Flag Behavior
enum class ModFlagBehavior : uint64_t {
  Error = 1,
  Warning = 2,
  Require = 3,
  Override = 4,
  Append = 5,
  AppendUnique = 6,
  Max = 7,
  Min = 8,
};

::std::optional<ModFlagBehavior> symbolizeModFlagBehavior(uint64_t);
::llvm::StringRef stringifyModFlagBehavior(ModFlagBehavior);
::std::optional<ModFlagBehavior> symbolizeModFlagBehavior(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForModFlagBehavior() {
  return 8;
}


inline ::llvm::StringRef stringifyEnum(ModFlagBehavior enumValue) {
  return stringifyModFlagBehavior(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ModFlagBehavior> symbolizeEnum<ModFlagBehavior>(::llvm::StringRef str) {
  return symbolizeModFlagBehavior(str);
}

class ModFlagBehaviorAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ModFlagBehavior;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ModFlagBehaviorAttr get(::mlir::MLIRContext *context, ModFlagBehavior val);
  ModFlagBehavior getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::ModFlagBehavior, ::mlir::LLVM::ModFlagBehavior> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::ModFlagBehavior> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM Module Flag Behavior");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::ModFlagBehavior> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::ModFlagBehavior>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [error, warning, require, override, append, append_unique, max, min] for LLVM Module Flag Behavior, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::ModFlagBehavior>, std::optional<::mlir::LLVM::ModFlagBehavior>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::ModFlagBehavior>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::ModFlagBehavior>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::ModFlagBehavior> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::ModFlagBehavior>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [error, warning, require, override, append, append_unique, max, min] for LLVM Module Flag Behavior, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::ModFlagBehavior value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::ModFlagBehavior> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::ModFlagBehavior getEmptyKey() {
    return static_cast<::mlir::LLVM::ModFlagBehavior>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::ModFlagBehavior getTombstoneKey() {
    return static_cast<::mlir::LLVM::ModFlagBehavior>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::ModFlagBehavior &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::ModFlagBehavior &lhs, const ::mlir::LLVM::ModFlagBehavior &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM ModRefInfo
enum class ModRefInfo : uint64_t {
  NoModRef = 0,
  Ref = 1,
  Mod = 2,
  ModRef = 3,
};

::std::optional<ModRefInfo> symbolizeModRefInfo(uint64_t);
::llvm::StringRef stringifyModRefInfo(ModRefInfo);
::std::optional<ModRefInfo> symbolizeModRefInfo(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForModRefInfo() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(ModRefInfo enumValue) {
  return stringifyModRefInfo(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ModRefInfo> symbolizeEnum<ModRefInfo>(::llvm::StringRef str) {
  return symbolizeModRefInfo(str);
}

class ModRefInfoAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ModRefInfo;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ModRefInfoAttr get(::mlir::MLIRContext *context, ModRefInfo val);
  ModRefInfo getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::ModRefInfo, ::mlir::LLVM::ModRefInfo> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::ModRefInfo> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM ModRefInfo");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::ModRefInfo> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::ModRefInfo>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, read, write, readwrite] for LLVM ModRefInfo, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::ModRefInfo>, std::optional<::mlir::LLVM::ModRefInfo>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::ModRefInfo>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::ModRefInfo>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::ModRefInfo> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::ModRefInfo>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, read, write, readwrite] for LLVM ModRefInfo, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::ModRefInfo value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::ModRefInfo> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::ModRefInfo getEmptyKey() {
    return static_cast<::mlir::LLVM::ModRefInfo>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::ModRefInfo getTombstoneKey() {
    return static_cast<::mlir::LLVM::ModRefInfo>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::ModRefInfo &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::ModRefInfo &lhs, const ::mlir::LLVM::ModRefInfo &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM Rounding Mode
enum class RoundingMode : uint64_t {
  TowardZero = 0,
  NearestTiesToEven = 1,
  TowardPositive = 2,
  TowardNegative = 3,
  NearestTiesToAway = 4,
  Dynamic = 7,
  Invalid,
};

::llvm::StringRef stringifyRoundingMode(RoundingMode);
::std::optional<RoundingMode> symbolizeRoundingMode(::llvm::StringRef);

inline ::llvm::StringRef stringifyEnum(RoundingMode enumValue) {
  return stringifyRoundingMode(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<RoundingMode> symbolizeEnum<RoundingMode>(::llvm::StringRef str) {
  return symbolizeRoundingMode(str);
}

class RoundingModeAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = RoundingMode;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static RoundingModeAttr get(::mlir::MLIRContext *context, RoundingMode val);
  RoundingMode getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::RoundingMode, ::mlir::LLVM::RoundingMode> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::RoundingMode> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM Rounding Mode");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::RoundingMode> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::RoundingMode>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [towardzero, tonearest, upward, downward, tonearestaway, dynamic, invalid] for LLVM Rounding Mode, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::RoundingMode>, std::optional<::mlir::LLVM::RoundingMode>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::RoundingMode>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::RoundingMode>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::RoundingMode> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::RoundingMode>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [towardzero, tonearest, upward, downward, tonearestaway, dynamic, invalid] for LLVM Rounding Mode, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::RoundingMode value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::RoundingMode> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::RoundingMode getEmptyKey() {
    return static_cast<::mlir::LLVM::RoundingMode>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::RoundingMode getTombstoneKey() {
    return static_cast<::mlir::LLVM::RoundingMode>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::RoundingMode &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::RoundingMode &lhs, const ::mlir::LLVM::RoundingMode &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM::tailcallkind {

// Tail Call Kind
enum class TailCallKind : uint64_t {
  None = 0,
  NoTail = 3,
  MustTail = 2,
  Tail = 1,
};

::std::optional<TailCallKind> symbolizeTailCallKind(uint64_t);
::llvm::StringRef stringifyTailCallKind(TailCallKind);
::std::optional<TailCallKind> symbolizeTailCallKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForTailCallKind() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(TailCallKind enumValue) {
  return stringifyTailCallKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<TailCallKind> symbolizeEnum<TailCallKind>(::llvm::StringRef str) {
  return symbolizeTailCallKind(str);
}

class TailCallKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = TailCallKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static TailCallKindAttr get(::mlir::MLIRContext *context, TailCallKind val);
  TailCallKind getValue() const;
};

} // namespace mlir::LLVM::tailcallkind

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::tailcallkind::TailCallKind, ::mlir::LLVM::tailcallkind::TailCallKind> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::tailcallkind::TailCallKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Tail Call Kind");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::tailcallkind::TailCallKind> attr = ::mlir::LLVM::tailcallkind::symbolizeEnum<::mlir::LLVM::tailcallkind::TailCallKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, notail, musttail, tail] for Tail Call Kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::tailcallkind::TailCallKind>, std::optional<::mlir::LLVM::tailcallkind::TailCallKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::tailcallkind::TailCallKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::tailcallkind::TailCallKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::tailcallkind::TailCallKind> attr = ::mlir::LLVM::tailcallkind::symbolizeEnum<::mlir::LLVM::tailcallkind::TailCallKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, notail, musttail, tail] for Tail Call Kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::tailcallkind::TailCallKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::tailcallkind::TailCallKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::tailcallkind::TailCallKind getEmptyKey() {
    return static_cast<::mlir::LLVM::tailcallkind::TailCallKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::tailcallkind::TailCallKind getTombstoneKey() {
    return static_cast<::mlir::LLVM::tailcallkind::TailCallKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::tailcallkind::TailCallKind &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::tailcallkind::TailCallKind &lhs, const ::mlir::LLVM::tailcallkind::TailCallKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM::uwtable {

// LLVM Unwind Behavior
enum class UWTableKind : uint64_t {
  None = 0,
  Sync = 1,
  Async = 2,
};

::std::optional<UWTableKind> symbolizeUWTableKind(uint64_t);
::llvm::StringRef stringifyUWTableKind(UWTableKind);
::std::optional<UWTableKind> symbolizeUWTableKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForUWTableKind() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(UWTableKind enumValue) {
  return stringifyUWTableKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<UWTableKind> symbolizeEnum<UWTableKind>(::llvm::StringRef str) {
  return symbolizeUWTableKind(str);
}

class UWTableKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = UWTableKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static UWTableKindAttr get(::mlir::MLIRContext *context, UWTableKind val);
  UWTableKind getValue() const;
};

} // namespace mlir::LLVM::uwtable

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::uwtable::UWTableKind, ::mlir::LLVM::uwtable::UWTableKind> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::uwtable::UWTableKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM Unwind Behavior");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::uwtable::UWTableKind> attr = ::mlir::LLVM::uwtable::symbolizeEnum<::mlir::LLVM::uwtable::UWTableKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [none, sync, async] for LLVM Unwind Behavior, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::uwtable::UWTableKind>, std::optional<::mlir::LLVM::uwtable::UWTableKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::uwtable::UWTableKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::uwtable::UWTableKind>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::uwtable::UWTableKind> attr = ::mlir::LLVM::uwtable::symbolizeEnum<::mlir::LLVM::uwtable::UWTableKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [none, sync, async] for LLVM Unwind Behavior, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::uwtable::UWTableKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::uwtable::UWTableKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::uwtable::UWTableKind getEmptyKey() {
    return static_cast<::mlir::LLVM::uwtable::UWTableKind>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::uwtable::UWTableKind getTombstoneKey() {
    return static_cast<::mlir::LLVM::uwtable::UWTableKind>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::uwtable::UWTableKind &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::uwtable::UWTableKind &lhs, const ::mlir::LLVM::uwtable::UWTableKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM GlobalValue UnnamedAddr
enum class UnnamedAddr : uint64_t {
  None = 0,
  Local = 1,
  Global = 2,
};

::std::optional<UnnamedAddr> symbolizeUnnamedAddr(uint64_t);
::llvm::StringRef stringifyUnnamedAddr(UnnamedAddr);
::std::optional<UnnamedAddr> symbolizeUnnamedAddr(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForUnnamedAddr() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(UnnamedAddr enumValue) {
  return stringifyUnnamedAddr(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<UnnamedAddr> symbolizeEnum<UnnamedAddr>(::llvm::StringRef str) {
  return symbolizeUnnamedAddr(str);
}

class UnnamedAddrAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = UnnamedAddr;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static UnnamedAddrAttr get(::mlir::MLIRContext *context, UnnamedAddr val);
  UnnamedAddr getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::UnnamedAddr, ::mlir::LLVM::UnnamedAddr> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::UnnamedAddr> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM GlobalValue UnnamedAddr");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::UnnamedAddr> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::UnnamedAddr>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [\"\", local_unnamed_addr, unnamed_addr] for LLVM GlobalValue UnnamedAddr, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::UnnamedAddr>, std::optional<::mlir::LLVM::UnnamedAddr>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::UnnamedAddr>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::UnnamedAddr>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::UnnamedAddr> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::UnnamedAddr>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [\"\", local_unnamed_addr, unnamed_addr] for LLVM GlobalValue UnnamedAddr, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::UnnamedAddr value) {
  auto valueStr = stringifyEnum(value);
  switch (value) {
  case ::mlir::LLVM::UnnamedAddr::Local:
  case ::mlir::LLVM::UnnamedAddr::Global:
    break;
  default:
    return p << '"' << valueStr << '"';
  }
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::UnnamedAddr> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::UnnamedAddr getEmptyKey() {
    return static_cast<::mlir::LLVM::UnnamedAddr>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::UnnamedAddr getTombstoneKey() {
    return static_cast<::mlir::LLVM::UnnamedAddr>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::UnnamedAddr &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::UnnamedAddr &lhs, const ::mlir::LLVM::UnnamedAddr &rhs) {
    return lhs == rhs;
  }
};
}

namespace mlir::LLVM {

// LLVM GlobalValue Visibility
enum class Visibility : uint64_t {
  Default = 0,
  Hidden = 1,
  Protected = 2,
};

::std::optional<Visibility> symbolizeVisibility(uint64_t);
::llvm::StringRef stringifyVisibility(Visibility);
::std::optional<Visibility> symbolizeVisibility(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForVisibility() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(Visibility enumValue) {
  return stringifyVisibility(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<Visibility> symbolizeEnum<Visibility>(::llvm::StringRef str) {
  return symbolizeVisibility(str);
}

class VisibilityAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = Visibility;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static VisibilityAttr get(::mlir::MLIRContext *context, Visibility val);
  Visibility getValue() const;
};

} // namespace mlir::LLVM

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::LLVM::Visibility, ::mlir::LLVM::Visibility> {
  template <typename ParserT>
  static FailureOr<::mlir::LLVM::Visibility> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for LLVM GlobalValue Visibility");

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::Visibility> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::Visibility>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [\"\", hidden, protected] for LLVM GlobalValue Visibility, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::mlir::LLVM::Visibility>, std::optional<::mlir::LLVM::Visibility>> {
  template <typename ParserT>
  static FailureOr<std::optional<::mlir::LLVM::Visibility>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return std::optional<::mlir::LLVM::Visibility>{};

    // Symbolize the keyword.
    if (::std::optional<::mlir::LLVM::Visibility> attr = ::mlir::LLVM::symbolizeEnum<::mlir::LLVM::Visibility>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [\"\", hidden, protected] for LLVM GlobalValue Visibility, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::LLVM::Visibility value) {
  auto valueStr = stringifyEnum(value);
  switch (value) {
  case ::mlir::LLVM::Visibility::Hidden:
  case ::mlir::LLVM::Visibility::Protected:
    break;
  default:
    return p << '"' << valueStr << '"';
  }
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::LLVM::Visibility> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline ::mlir::LLVM::Visibility getEmptyKey() {
    return static_cast<::mlir::LLVM::Visibility>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::LLVM::Visibility getTombstoneKey() {
    return static_cast<::mlir::LLVM::Visibility>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::LLVM::Visibility &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const ::mlir::LLVM::Visibility &lhs, const ::mlir::LLVM::Visibility &rhs) {
    return lhs == rhs;
  }
};
}

