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
namespace mlir::transform {

/// Used to refer to a specific param-operand (via its index) from within an
///     attribute on a transform operation.
class ParamOperandAttr;
namespace detail {

struct ParamOperandAttrStorage;

} // namespace detail
class ParamOperandAttr : public ::mlir::Attribute::AttrBase<ParamOperandAttr, ::mlir::Attribute, detail::ParamOperandAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "transform.param_operand";
  static constexpr ::llvm::StringLiteral dialectName = "transform";
  static ParamOperandAttr get(::mlir::MLIRContext *context, IntegerAttr index);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"param_operand"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  IntegerAttr getIndex() const;
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ParamOperandAttr)

#endif // GET_ATTRDEF_CLASSES

