/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace mlir::ROCDL {

/// ROCDL target attribute for controlling compilation of AMDGPU targets. All
///     parameters decay into default values if not present.
/// 
///     Examples:
/// 
///     1. Target with default values.
///     ```
///       gpu.module @mymodule [#rocdl.target] attributes {...} {
///         ...
///       }
///     ```
/// 
///     2. Target with `gfx90a` chip and fast math.
///     ```
///       gpu.module @mymodule [#rocdl.target<chip = "gfx90a", flags = {fast, no_wave64}>] {
///         ...
///       }
///     ```
class ROCDLTargetAttr;
namespace detail {

struct ROCDLTargetAttrStorage;

} // namespace detail
class ROCDLTargetAttr : public ::mlir::Attribute::AttrBase<ROCDLTargetAttr, ::mlir::Attribute, detail::ROCDLTargetAttrStorage> {
public:
  using Base::Base;
  bool hasFlag(StringRef flag) const;
  bool hasWave64() const;
  bool hasFastMath() const;
  bool hasDaz() const;
  bool hasFiniteOnly() const;
  bool hasUnsafeMath() const;
  bool hasCorrectSqrt() const;
  static constexpr ::llvm::StringLiteral name = "rocdl.target";
  static constexpr ::llvm::StringLiteral dialectName = "rocdl";
  using Base::getChecked;
  static ROCDLTargetAttr get(::mlir::MLIRContext *context, int optLevel = 2, StringRef triple = "amdgcn-amd-amdhsa", StringRef chip = "gfx900", StringRef features = "", StringRef abiVersion = "600", DictionaryAttr targetFlags = nullptr, ArrayAttr linkFiles = nullptr);
  static ROCDLTargetAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, int optLevel = 2, StringRef triple = "amdgcn-amd-amdhsa", StringRef chip = "gfx900", StringRef features = "", StringRef abiVersion = "600", DictionaryAttr targetFlags = nullptr, ArrayAttr linkFiles = nullptr);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int O, ::llvm::StringRef triple, ::llvm::StringRef chip, ::llvm::StringRef features, ::llvm::StringRef abi, DictionaryAttr flags, ArrayAttr link);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int O, ::llvm::StringRef triple, ::llvm::StringRef chip, ::llvm::StringRef features, ::llvm::StringRef abi, DictionaryAttr flags, ArrayAttr link);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"target"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  int getO() const;
  ::llvm::StringRef getTriple() const;
  ::llvm::StringRef getChip() const;
  ::llvm::StringRef getFeatures() const;
  ::llvm::StringRef getAbi() const;
  DictionaryAttr getFlags() const;
  ArrayAttr getLink() const;
};

} // namespace mlir::ROCDL
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ROCDL::ROCDLTargetAttr)

#endif // GET_ATTRDEF_CLASSES

