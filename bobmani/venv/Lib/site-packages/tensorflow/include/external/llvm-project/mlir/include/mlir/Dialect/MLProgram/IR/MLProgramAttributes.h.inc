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
namespace mlir::ml_program {

/// Value used for a global signalling external resolution
/// When used as the value for a GlobalOp, this indicates that the actual
///   value should be resolved externally in an implementation defined manner.
///   The `sym_name` of the global is the key for locating the value.
/// 
///   Examples:
/// 
///   ```mlir
///   extern : tensor<4xi32>
///   ```
class ExternAttr;
namespace detail {

struct ExternAttrStorage;

} // namespace detail
class ExternAttr : public ::mlir::Attribute::AttrBase<ExternAttr, ::mlir::Attribute, detail::ExternAttrStorage, ::mlir::TypedAttr::Trait, ::mlir::OpAsmAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "ml_program.extern";
  static constexpr ::llvm::StringLiteral dialectName = "ml_program";
  static ExternAttr get(::mlir::MLIRContext *context, ::mlir::Type type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"extern"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getType() const;
  ::mlir::OpAsmAliasResult getAlias(::llvm::raw_ostream &os) const;
};

} // namespace mlir::ml_program
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ml_program::ExternAttr)

#endif // GET_ATTRDEF_CLASSES

