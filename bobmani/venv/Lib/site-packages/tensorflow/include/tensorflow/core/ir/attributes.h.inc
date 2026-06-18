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
namespace mlir::tfg {

/// Region attributes, argument and result attributes.
/// Region attributes on control-flow operations represent argument, result,
///     and general attributes on a region, analogous to function attributes. These
///     arise when converting control-flow operations from functional form to region
///     form; the control-flow functions' attributes are preserved as region
///     attributes. These may also be added by transformations that create region
///     control-flow operations.
/// 
///     The region attributes are required to have as many argument attributes as
///     there are data block arguments and result attributes as data results. If
///     operands or results are added or removed from the owning operation, the
///     region attributes, if present, must be updated.
class RegionAttr;
namespace detail {

struct RegionAttrStorage;

} // namespace detail
class RegionAttr : public ::mlir::Attribute::AttrBase<RegionAttr, ::mlir::Attribute, detail::RegionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "tfg.region_attrs";
  static constexpr ::llvm::StringLiteral dialectName = "tfg";
  static RegionAttr get(::mlir::MLIRContext *context, DictionaryAttr attrs, ArrayAttr arg_attrs, ArrayAttr res_attrs);
  static RegionAttr get(DictionaryAttr attrs, ArrayAttr arg_attrs, ArrayAttr res_attrs);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"region_attrs"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  DictionaryAttr getAttrs() const;
  ArrayAttr getArgAttrs() const;
  ArrayAttr getResAttrs() const;
};

} // namespace mlir::tfg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tfg::RegionAttr)

#endif // GET_ATTRDEF_CLASSES

