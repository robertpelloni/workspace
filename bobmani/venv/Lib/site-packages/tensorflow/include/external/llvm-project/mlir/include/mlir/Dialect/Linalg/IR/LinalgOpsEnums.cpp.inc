/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LinalgEnums.td                                                       *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::linalg {

::llvm::StringRef stringifyBinaryFn(BinaryFn val) {
  switch (val) {
    case BinaryFn::add: return "add";
    case BinaryFn::sub: return "sub";
    case BinaryFn::mul: return "mul";
    case BinaryFn::div: return "div";
    case BinaryFn::div_unsigned: return "div_unsigned";
    case BinaryFn::max_signed: return "max_signed";
    case BinaryFn::min_signed: return "min_signed";
    case BinaryFn::max_unsigned: return "max_unsigned";
    case BinaryFn::min_unsigned: return "min_unsigned";
    case BinaryFn::powf: return "powf";
  }
  return "";
}

::std::optional<BinaryFn> symbolizeBinaryFn(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<BinaryFn>>(str)
      .Case("add", BinaryFn::add)
      .Case("sub", BinaryFn::sub)
      .Case("mul", BinaryFn::mul)
      .Case("div", BinaryFn::div)
      .Case("div_unsigned", BinaryFn::div_unsigned)
      .Case("max_signed", BinaryFn::max_signed)
      .Case("min_signed", BinaryFn::min_signed)
      .Case("max_unsigned", BinaryFn::max_unsigned)
      .Case("min_unsigned", BinaryFn::min_unsigned)
      .Case("powf", BinaryFn::powf)
      .Default(::std::nullopt);
}
::std::optional<BinaryFn> symbolizeBinaryFn(uint32_t value) {
  switch (value) {
  case 0: return BinaryFn::add;
  case 1: return BinaryFn::sub;
  case 2: return BinaryFn::mul;
  case 3: return BinaryFn::div;
  case 4: return BinaryFn::div_unsigned;
  case 5: return BinaryFn::max_signed;
  case 6: return BinaryFn::min_signed;
  case 7: return BinaryFn::max_unsigned;
  case 8: return BinaryFn::min_unsigned;
  case 9: return BinaryFn::powf;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::linalg
namespace mlir::linalg {

::llvm::StringRef stringifyElementwiseArityGroup(ElementwiseArityGroup val) {
  switch (val) {
    case ElementwiseArityGroup::Unary: return "Unary";
    case ElementwiseArityGroup::Binary: return "Binary";
    case ElementwiseArityGroup::Ternary: return "Ternary";
  }
  return "";
}

::std::optional<ElementwiseArityGroup> symbolizeElementwiseArityGroup(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ElementwiseArityGroup>>(str)
      .Case("Unary", ElementwiseArityGroup::Unary)
      .Case("Binary", ElementwiseArityGroup::Binary)
      .Case("Ternary", ElementwiseArityGroup::Ternary)
      .Default(::std::nullopt);
}
::std::optional<ElementwiseArityGroup> symbolizeElementwiseArityGroup(uint32_t value) {
  switch (value) {
  case 1: return ElementwiseArityGroup::Unary;
  case 2: return ElementwiseArityGroup::Binary;
  case 3: return ElementwiseArityGroup::Ternary;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::linalg
namespace mlir::linalg {

::llvm::StringRef stringifyElementwiseCaseLimits(ElementwiseCaseLimits val) {
  switch (val) {
    case ElementwiseCaseLimits::LastUnary: return "LastUnary";
    case ElementwiseCaseLimits::LastBinary: return "LastBinary";
    case ElementwiseCaseLimits::LastTernary: return "LastTernary";
  }
  return "";
}

::std::optional<ElementwiseCaseLimits> symbolizeElementwiseCaseLimits(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ElementwiseCaseLimits>>(str)
      .Case("LastUnary", ElementwiseCaseLimits::LastUnary)
      .Case("LastBinary", ElementwiseCaseLimits::LastBinary)
      .Case("LastTernary", ElementwiseCaseLimits::LastTernary)
      .Default(::std::nullopt);
}
::std::optional<ElementwiseCaseLimits> symbolizeElementwiseCaseLimits(uint32_t value) {
  switch (value) {
  case 13: return ElementwiseCaseLimits::LastUnary;
  case 23: return ElementwiseCaseLimits::LastBinary;
  case 24: return ElementwiseCaseLimits::LastTernary;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::linalg
namespace mlir::linalg {

::llvm::StringRef stringifyElementwiseKind(ElementwiseKind val) {
  switch (val) {
    case ElementwiseKind::exp: return "exp";
    case ElementwiseKind::log: return "log";
    case ElementwiseKind::abs: return "abs";
    case ElementwiseKind::ceil: return "ceil";
    case ElementwiseKind::floor: return "floor";
    case ElementwiseKind::negf: return "negf";
    case ElementwiseKind::reciprocal: return "reciprocal";
    case ElementwiseKind::round: return "round";
    case ElementwiseKind::sqrt: return "sqrt";
    case ElementwiseKind::rsqrt: return "rsqrt";
    case ElementwiseKind::square: return "square";
    case ElementwiseKind::tanh: return "tanh";
    case ElementwiseKind::erf: return "erf";
    case ElementwiseKind::add: return "add";
    case ElementwiseKind::sub: return "sub";
    case ElementwiseKind::mul: return "mul";
    case ElementwiseKind::div: return "div";
    case ElementwiseKind::div_unsigned: return "div_unsigned";
    case ElementwiseKind::max_signed: return "max_signed";
    case ElementwiseKind::min_signed: return "min_signed";
    case ElementwiseKind::max_unsigned: return "max_unsigned";
    case ElementwiseKind::min_unsigned: return "min_unsigned";
    case ElementwiseKind::powf: return "powf";
    case ElementwiseKind::select: return "select";
  }
  return "";
}

::std::optional<ElementwiseKind> symbolizeElementwiseKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ElementwiseKind>>(str)
      .Case("exp", ElementwiseKind::exp)
      .Case("log", ElementwiseKind::log)
      .Case("abs", ElementwiseKind::abs)
      .Case("ceil", ElementwiseKind::ceil)
      .Case("floor", ElementwiseKind::floor)
      .Case("negf", ElementwiseKind::negf)
      .Case("reciprocal", ElementwiseKind::reciprocal)
      .Case("round", ElementwiseKind::round)
      .Case("sqrt", ElementwiseKind::sqrt)
      .Case("rsqrt", ElementwiseKind::rsqrt)
      .Case("square", ElementwiseKind::square)
      .Case("tanh", ElementwiseKind::tanh)
      .Case("erf", ElementwiseKind::erf)
      .Case("add", ElementwiseKind::add)
      .Case("sub", ElementwiseKind::sub)
      .Case("mul", ElementwiseKind::mul)
      .Case("div", ElementwiseKind::div)
      .Case("div_unsigned", ElementwiseKind::div_unsigned)
      .Case("max_signed", ElementwiseKind::max_signed)
      .Case("min_signed", ElementwiseKind::min_signed)
      .Case("max_unsigned", ElementwiseKind::max_unsigned)
      .Case("min_unsigned", ElementwiseKind::min_unsigned)
      .Case("powf", ElementwiseKind::powf)
      .Case("select", ElementwiseKind::select)
      .Default(::std::nullopt);
}
::std::optional<ElementwiseKind> symbolizeElementwiseKind(uint32_t value) {
  switch (value) {
  case 0: return ElementwiseKind::exp;
  case 1: return ElementwiseKind::log;
  case 2: return ElementwiseKind::abs;
  case 3: return ElementwiseKind::ceil;
  case 4: return ElementwiseKind::floor;
  case 5: return ElementwiseKind::negf;
  case 6: return ElementwiseKind::reciprocal;
  case 7: return ElementwiseKind::round;
  case 8: return ElementwiseKind::sqrt;
  case 9: return ElementwiseKind::rsqrt;
  case 10: return ElementwiseKind::square;
  case 11: return ElementwiseKind::tanh;
  case 12: return ElementwiseKind::erf;
  case 13: return ElementwiseKind::add;
  case 14: return ElementwiseKind::sub;
  case 15: return ElementwiseKind::mul;
  case 16: return ElementwiseKind::div;
  case 17: return ElementwiseKind::div_unsigned;
  case 18: return ElementwiseKind::max_signed;
  case 19: return ElementwiseKind::min_signed;
  case 20: return ElementwiseKind::max_unsigned;
  case 21: return ElementwiseKind::min_unsigned;
  case 22: return ElementwiseKind::powf;
  case 23: return ElementwiseKind::select;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::linalg
namespace mlir::linalg {

::llvm::StringRef stringifyTernaryFn(TernaryFn val) {
  switch (val) {
    case TernaryFn::select: return "select";
  }
  return "";
}

::std::optional<TernaryFn> symbolizeTernaryFn(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TernaryFn>>(str)
      .Case("select", TernaryFn::select)
      .Default(::std::nullopt);
}
::std::optional<TernaryFn> symbolizeTernaryFn(uint32_t value) {
  switch (value) {
  case 0: return TernaryFn::select;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::linalg
namespace mlir::linalg {

::llvm::StringRef stringifyTypeFn(TypeFn val) {
  switch (val) {
    case TypeFn::cast_signed: return "cast_signed";
    case TypeFn::cast_unsigned: return "cast_unsigned";
  }
  return "";
}

::std::optional<TypeFn> symbolizeTypeFn(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TypeFn>>(str)
      .Case("cast_signed", TypeFn::cast_signed)
      .Case("cast_unsigned", TypeFn::cast_unsigned)
      .Default(::std::nullopt);
}
::std::optional<TypeFn> symbolizeTypeFn(uint32_t value) {
  switch (value) {
  case 0: return TypeFn::cast_signed;
  case 1: return TypeFn::cast_unsigned;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::linalg
namespace mlir::linalg {

::llvm::StringRef stringifyUnaryFn(UnaryFn val) {
  switch (val) {
    case UnaryFn::exp: return "exp";
    case UnaryFn::log: return "log";
    case UnaryFn::abs: return "abs";
    case UnaryFn::ceil: return "ceil";
    case UnaryFn::floor: return "floor";
    case UnaryFn::negf: return "negf";
    case UnaryFn::reciprocal: return "reciprocal";
    case UnaryFn::round: return "round";
    case UnaryFn::sqrt: return "sqrt";
    case UnaryFn::rsqrt: return "rsqrt";
    case UnaryFn::square: return "square";
    case UnaryFn::tanh: return "tanh";
    case UnaryFn::erf: return "erf";
  }
  return "";
}

::std::optional<UnaryFn> symbolizeUnaryFn(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<UnaryFn>>(str)
      .Case("exp", UnaryFn::exp)
      .Case("log", UnaryFn::log)
      .Case("abs", UnaryFn::abs)
      .Case("ceil", UnaryFn::ceil)
      .Case("floor", UnaryFn::floor)
      .Case("negf", UnaryFn::negf)
      .Case("reciprocal", UnaryFn::reciprocal)
      .Case("round", UnaryFn::round)
      .Case("sqrt", UnaryFn::sqrt)
      .Case("rsqrt", UnaryFn::rsqrt)
      .Case("square", UnaryFn::square)
      .Case("tanh", UnaryFn::tanh)
      .Case("erf", UnaryFn::erf)
      .Default(::std::nullopt);
}
::std::optional<UnaryFn> symbolizeUnaryFn(uint32_t value) {
  switch (value) {
  case 0: return UnaryFn::exp;
  case 1: return UnaryFn::log;
  case 2: return UnaryFn::abs;
  case 3: return UnaryFn::ceil;
  case 4: return UnaryFn::floor;
  case 5: return UnaryFn::negf;
  case 6: return UnaryFn::reciprocal;
  case 7: return UnaryFn::round;
  case 8: return UnaryFn::sqrt;
  case 9: return UnaryFn::rsqrt;
  case 10: return UnaryFn::square;
  case 11: return UnaryFn::tanh;
  case 12: return UnaryFn::erf;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::linalg
namespace mlir::linalg {

::llvm::StringRef stringifyWinogradConv2DFmr(WinogradConv2DFmr val) {
  switch (val) {
    case WinogradConv2DFmr::F_2_3: return "F_2_3";
    case WinogradConv2DFmr::F_4_3: return "F_4_3";
    case WinogradConv2DFmr::F_2_5: return "F_2_5";
  }
  return "";
}

::std::optional<WinogradConv2DFmr> symbolizeWinogradConv2DFmr(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<WinogradConv2DFmr>>(str)
      .Case("F_2_3", WinogradConv2DFmr::F_2_3)
      .Case("F_4_3", WinogradConv2DFmr::F_4_3)
      .Case("F_2_5", WinogradConv2DFmr::F_2_5)
      .Default(::std::nullopt);
}
::std::optional<WinogradConv2DFmr> symbolizeWinogradConv2DFmr(uint32_t value) {
  switch (value) {
  case 0: return WinogradConv2DFmr::F_2_3;
  case 1: return WinogradConv2DFmr::F_4_3;
  case 2: return WinogradConv2DFmr::F_2_5;
  default: return ::std::nullopt;
  }
}

bool WinogradConv2DFmrAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
WinogradConv2DFmrAttr WinogradConv2DFmrAttr::get(::mlir::MLIRContext *context, WinogradConv2DFmr val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<WinogradConv2DFmrAttr>(baseAttr);
}
WinogradConv2DFmr WinogradConv2DFmrAttr::getValue() const {
  return static_cast<WinogradConv2DFmr>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace mlir::linalg
