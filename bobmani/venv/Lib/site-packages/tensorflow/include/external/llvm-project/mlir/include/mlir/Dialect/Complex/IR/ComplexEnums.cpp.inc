/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ComplexAttributes.td                                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::complex {

std::string stringifyComplexRangeFlags(ComplexRangeFlags symbol) {
  auto val = static_cast<uint32_t>(symbol);
  assert(7u == (7u | val) && "invalid bits set in bit enum");
  ::llvm::SmallVector<::llvm::StringRef, 2> strs;

  if (1u == (1u & val))
    strs.push_back("improved");

  if (2u == (2u & val))
    strs.push_back("basic");

  if (4u == (4u & val))
    strs.push_back("none");
  return ::llvm::join(strs, "|");
}

::std::optional<ComplexRangeFlags> symbolizeComplexRangeFlags(::llvm::StringRef str) {
  ::llvm::SmallVector<::llvm::StringRef, 2> symbols;
  str.split(symbols, "|");

  uint32_t val = 0;
  for (auto symbol : symbols) {
    auto bit = llvm::StringSwitch<::std::optional<uint32_t>>(symbol.trim())
      .Case("improved", 1)
      .Case("basic", 2)
      .Case("none", 4)
      .Default(::std::nullopt);
    if (bit) { val |= *bit; } else { return ::std::nullopt; }
  }
  return static_cast<ComplexRangeFlags>(val);
}

::std::optional<ComplexRangeFlags> symbolizeComplexRangeFlags(uint32_t value) {
  if (value & ~static_cast<uint32_t>(7u)) return std::nullopt;
  return static_cast<ComplexRangeFlags>(value);
}
bool ComplexRangeFlagsAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && ((!(::llvm::cast<::mlir::IntegerAttr>(attr).getValue().getZExtValue() & (~(1u|2u|4u)))));
}
ComplexRangeFlagsAttr ComplexRangeFlagsAttr::get(::mlir::MLIRContext *context, ComplexRangeFlags val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<ComplexRangeFlagsAttr>(baseAttr);
}
ComplexRangeFlags ComplexRangeFlagsAttr::getValue() const {
  return static_cast<ComplexRangeFlags>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace mlir::complex
