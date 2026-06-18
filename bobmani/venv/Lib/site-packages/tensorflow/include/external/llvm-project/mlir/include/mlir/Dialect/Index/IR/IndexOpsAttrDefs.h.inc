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
namespace mlir::index {

/// index comparison predicate kind
class IndexCmpPredicateAttr;
namespace detail {

struct IndexCmpPredicateAttrStorage;

} // namespace detail
class IndexCmpPredicateAttr : public ::mlir::Attribute::AttrBase<IndexCmpPredicateAttr, ::mlir::Attribute, detail::IndexCmpPredicateAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "index.cmp_predicate";
  static constexpr ::llvm::StringLiteral dialectName = "index";
  static IndexCmpPredicateAttr get(::mlir::MLIRContext *context, ::mlir::index::IndexCmpPredicate value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cmp_predicate"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::index::IndexCmpPredicate getValue() const;
};

} // namespace mlir::index
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::index::IndexCmpPredicateAttr)

#endif // GET_ATTRDEF_CLASSES

