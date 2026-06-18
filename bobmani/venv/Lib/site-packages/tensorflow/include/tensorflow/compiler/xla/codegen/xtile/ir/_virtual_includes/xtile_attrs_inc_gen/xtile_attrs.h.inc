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
namespace xla::xtile {

/// Contains auxillary information about how a program is tiled.
class TilingInfoAttr;
class LayoutAttr;
namespace detail {

struct TilingInfoAttrStorage;

} // namespace detail
class TilingInfoAttr : public ::mlir::Attribute::AttrBase<TilingInfoAttr, ::mlir::Attribute, detail::TilingInfoAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "xtile.tiling_info";
  static constexpr ::llvm::StringLiteral dialectName = "xtile";
  static TilingInfoAttr get(::mlir::MLIRContext *context, int32_t tile_count, int32_t tiles_per_workgroup);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tiling_info"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  int32_t getTileCount() const;
  int32_t getTilesPerWorkgroup() const;
};
namespace detail {

struct LayoutAttrStorage;

} // namespace detail
class LayoutAttr : public ::mlir::Attribute::AttrBase<LayoutAttr, ::mlir::Attribute, detail::LayoutAttrStorage, ::mlir::MemRefLayoutAttrInterface::Trait> {
public:
  using Base::Base;
  mlir::LogicalResult verifyLayout(
      mlir::ArrayRef<int64_t> shape, mlir::function_ref<mlir::InFlightDiagnostic()> emit_error) const;
  mlir::LogicalResult getStridesAndOffset(
      mlir::ArrayRef<int64_t> shape, mlir::SmallVectorImpl<int64_t>& strides, int64_t& offset) const;
  static constexpr ::llvm::StringLiteral name = "xtile.layout";
  static constexpr ::llvm::StringLiteral dialectName = "xtile";
  using ::mlir::MemRefLayoutAttrInterface::Trait<LayoutAttr>::isIdentity;
  using ::mlir::MemRefLayoutAttrInterface::Trait<LayoutAttr>::verifyLayout;
  using ::mlir::MemRefLayoutAttrInterface::Trait<LayoutAttr>::getStridesAndOffset;
  static LayoutAttr get(::mlir::MLIRContext *context, ::mlir::DenseI64ArrayAttr minor_to_major);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"layout"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::DenseI64ArrayAttr getMinorToMajor() const;
  ::mlir::AffineMap getAffineMap() const;
};

} // namespace xla::xtile
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::xtile::TilingInfoAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::xtile::LayoutAttr)

#endif // GET_ATTRDEF_CLASSES

