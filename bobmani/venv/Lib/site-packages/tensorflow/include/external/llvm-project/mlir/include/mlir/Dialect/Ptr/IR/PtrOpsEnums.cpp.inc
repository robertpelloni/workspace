/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: PtrEnums.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::ptr {

::llvm::StringRef stringifyAtomicBinOp(AtomicBinOp val) {
  switch (val) {
    case AtomicBinOp::xchg: return "xchg";
    case AtomicBinOp::add: return "add";
    case AtomicBinOp::sub: return "sub";
    case AtomicBinOp::_and: return "_and";
    case AtomicBinOp::nand: return "nand";
    case AtomicBinOp::_or: return "_or";
    case AtomicBinOp::_xor: return "_xor";
    case AtomicBinOp::max: return "max";
    case AtomicBinOp::min: return "min";
    case AtomicBinOp::umax: return "umax";
    case AtomicBinOp::umin: return "umin";
    case AtomicBinOp::fadd: return "fadd";
    case AtomicBinOp::fsub: return "fsub";
    case AtomicBinOp::fmax: return "fmax";
    case AtomicBinOp::fmin: return "fmin";
    case AtomicBinOp::uinc_wrap: return "uinc_wrap";
    case AtomicBinOp::udec_wrap: return "udec_wrap";
  }
  return "";
}

::std::optional<AtomicBinOp> symbolizeAtomicBinOp(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<AtomicBinOp>>(str)
      .Case("xchg", AtomicBinOp::xchg)
      .Case("add", AtomicBinOp::add)
      .Case("sub", AtomicBinOp::sub)
      .Case("_and", AtomicBinOp::_and)
      .Case("nand", AtomicBinOp::nand)
      .Case("_or", AtomicBinOp::_or)
      .Case("_xor", AtomicBinOp::_xor)
      .Case("max", AtomicBinOp::max)
      .Case("min", AtomicBinOp::min)
      .Case("umax", AtomicBinOp::umax)
      .Case("umin", AtomicBinOp::umin)
      .Case("fadd", AtomicBinOp::fadd)
      .Case("fsub", AtomicBinOp::fsub)
      .Case("fmax", AtomicBinOp::fmax)
      .Case("fmin", AtomicBinOp::fmin)
      .Case("uinc_wrap", AtomicBinOp::uinc_wrap)
      .Case("udec_wrap", AtomicBinOp::udec_wrap)
      .Default(::std::nullopt);
}
::std::optional<AtomicBinOp> symbolizeAtomicBinOp(uint32_t value) {
  switch (value) {
  case 0: return AtomicBinOp::xchg;
  case 1: return AtomicBinOp::add;
  case 2: return AtomicBinOp::sub;
  case 3: return AtomicBinOp::_and;
  case 4: return AtomicBinOp::nand;
  case 5: return AtomicBinOp::_or;
  case 6: return AtomicBinOp::_xor;
  case 7: return AtomicBinOp::max;
  case 8: return AtomicBinOp::min;
  case 9: return AtomicBinOp::umax;
  case 10: return AtomicBinOp::umin;
  case 11: return AtomicBinOp::fadd;
  case 12: return AtomicBinOp::fsub;
  case 13: return AtomicBinOp::fmax;
  case 14: return AtomicBinOp::fmin;
  case 15: return AtomicBinOp::uinc_wrap;
  case 16: return AtomicBinOp::udec_wrap;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::ptr
namespace mlir::ptr {

::llvm::StringRef stringifyAtomicOrdering(AtomicOrdering val) {
  switch (val) {
    case AtomicOrdering::not_atomic: return "not_atomic";
    case AtomicOrdering::unordered: return "unordered";
    case AtomicOrdering::monotonic: return "monotonic";
    case AtomicOrdering::acquire: return "acquire";
    case AtomicOrdering::release: return "release";
    case AtomicOrdering::acq_rel: return "acq_rel";
    case AtomicOrdering::seq_cst: return "seq_cst";
  }
  return "";
}

::std::optional<AtomicOrdering> symbolizeAtomicOrdering(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<AtomicOrdering>>(str)
      .Case("not_atomic", AtomicOrdering::not_atomic)
      .Case("unordered", AtomicOrdering::unordered)
      .Case("monotonic", AtomicOrdering::monotonic)
      .Case("acquire", AtomicOrdering::acquire)
      .Case("release", AtomicOrdering::release)
      .Case("acq_rel", AtomicOrdering::acq_rel)
      .Case("seq_cst", AtomicOrdering::seq_cst)
      .Default(::std::nullopt);
}
::std::optional<AtomicOrdering> symbolizeAtomicOrdering(uint32_t value) {
  switch (value) {
  case 0: return AtomicOrdering::not_atomic;
  case 1: return AtomicOrdering::unordered;
  case 2: return AtomicOrdering::monotonic;
  case 3: return AtomicOrdering::acquire;
  case 4: return AtomicOrdering::release;
  case 5: return AtomicOrdering::acq_rel;
  case 6: return AtomicOrdering::seq_cst;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::ptr
namespace mlir::ptr {

::llvm::StringRef stringifyPtrAddFlags(PtrAddFlags val) {
  switch (val) {
    case PtrAddFlags::none: return "none";
    case PtrAddFlags::nusw: return "nusw";
    case PtrAddFlags::nuw: return "nuw";
    case PtrAddFlags::inbounds: return "inbounds";
  }
  return "";
}

::std::optional<PtrAddFlags> symbolizePtrAddFlags(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<PtrAddFlags>>(str)
      .Case("none", PtrAddFlags::none)
      .Case("nusw", PtrAddFlags::nusw)
      .Case("nuw", PtrAddFlags::nuw)
      .Case("inbounds", PtrAddFlags::inbounds)
      .Default(::std::nullopt);
}
::std::optional<PtrAddFlags> symbolizePtrAddFlags(uint32_t value) {
  switch (value) {
  case 0: return PtrAddFlags::none;
  case 1: return PtrAddFlags::nusw;
  case 2: return PtrAddFlags::nuw;
  case 3: return PtrAddFlags::inbounds;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::ptr
namespace mlir::ptr {

std::string stringifyPtrDiffFlags(PtrDiffFlags symbol) {
  auto val = static_cast<uint8_t>(symbol);
  assert(3u == (3u | val) && "invalid bits set in bit enum");
  // Special case for all bits unset.
  if (val == 0) return "none";

  ::llvm::SmallVector<::llvm::StringRef, 2> strs;

  if (1u == (1u & val))
    strs.push_back("nuw");

  if (2u == (2u & val))
    strs.push_back("nsw");
  return ::llvm::join(strs, "|");
}

::std::optional<PtrDiffFlags> symbolizePtrDiffFlags(::llvm::StringRef str) {
  // Special case for all bits unset.
  if (str == "none") return PtrDiffFlags::none;

  ::llvm::SmallVector<::llvm::StringRef, 2> symbols;
  str.split(symbols, "|");

  uint8_t val = 0;
  for (auto symbol : symbols) {
    auto bit = llvm::StringSwitch<::std::optional<uint8_t>>(symbol.trim())
      .Case("nuw", 1)
      .Case("nsw", 2)
      .Default(::std::nullopt);
    if (bit) { val |= *bit; } else { return ::std::nullopt; }
  }
  return static_cast<PtrDiffFlags>(val);
}

::std::optional<PtrDiffFlags> symbolizePtrDiffFlags(uint8_t value) {
  // Special case for all bits unset.
  if (value == 0) return PtrDiffFlags::none;

  if (value & ~static_cast<uint8_t>(3u)) return std::nullopt;
  return static_cast<PtrDiffFlags>(value);
}

} // namespace mlir::ptr
