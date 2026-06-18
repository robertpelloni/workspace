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
namespace mlir::shard {

/// Reduction of an iterator/grid dimension.
class ReductionKindAttr;
class GridAxesArrayAttr;
namespace detail {

struct ReductionKindAttrStorage;

} // namespace detail
class ReductionKindAttr : public ::mlir::Attribute::AttrBase<ReductionKindAttr, ::mlir::Attribute, detail::ReductionKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "shard.partial";
  static constexpr ::llvm::StringLiteral dialectName = "shard";
  static ReductionKindAttr get(::mlir::MLIRContext *context, ::mlir::shard::ReductionKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"partial"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::shard::ReductionKind getValue() const;
};
namespace detail {

struct GridAxesArrayAttrStorage;

} // namespace detail
class GridAxesArrayAttr : public ::mlir::Attribute::AttrBase<GridAxesArrayAttr, ::mlir::Attribute, detail::GridAxesArrayAttrStorage> {
public:
  using Base::Base;
  size_t size() const { return getAxes().size(); }
  auto begin() const { return getAxes().begin(); }
  auto end() const { return getAxes().end(); }
  static constexpr ::llvm::StringLiteral name = "shard.axisarray";
  static constexpr ::llvm::StringLiteral dialectName = "shard";
  static GridAxesArrayAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<GridAxesAttr> axes);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"axisarray"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<GridAxesAttr> getAxes() const;
};

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ReductionKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::GridAxesArrayAttr)

#endif // GET_ATTRDEF_CLASSES

