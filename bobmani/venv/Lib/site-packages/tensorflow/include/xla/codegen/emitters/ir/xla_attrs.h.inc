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
namespace xla {

/// An Attribute representing an indexing map.
/// This attribute stores an indexing map. See
///     https://openxla.org/xla/indexing for more details.
class IndexingMapAttr;
/// XLA Backend kind (or type)
class BackendKindAttr;
class ExtraBackendOptionsAttr;
class CpuMemoryRegionNameAttr;
/// a dimension, either 'x', 'y', or 'z'
class WorkGroupDimensionAttr;
namespace detail {

struct IndexingMapAttrStorage;

} // namespace detail
class IndexingMapAttr : public ::mlir::Attribute::AttrBase<IndexingMapAttr, ::mlir::Attribute, detail::IndexingMapAttrStorage> {
public:
  using Base::Base;
  // Returns the indexing map constructed from IndexingMapAttr.
  xla::IndexingMap getIndexingMap() const;

  // Returns the number of indexing map results.
  int64_t getNumResults() const;
  static constexpr ::llvm::StringLiteral name = "xla.indexing_map";
  static constexpr ::llvm::StringLiteral dialectName = "xla";
  using Base::getChecked;
  static IndexingMapAttr get(::mlir::MLIRContext *context, ::mlir::AffineMap map, ::llvm::ArrayRef<::xla::IndexingMap::Variable> dim_vars, ::llvm::ArrayRef<::xla::IndexingMap::Variable> range_vars, ::llvm::ArrayRef<::std::pair<::mlir::AffineExpr, ::xla::Interval>> constraints);
  static IndexingMapAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::AffineMap map, ::llvm::ArrayRef<::xla::IndexingMap::Variable> dim_vars, ::llvm::ArrayRef<::xla::IndexingMap::Variable> range_vars, ::llvm::ArrayRef<::std::pair<::mlir::AffineExpr, ::xla::Interval>> constraints);
  static IndexingMapAttr get(::mlir::MLIRContext *context, const ::xla::IndexingMap&indexing_map);
  static IndexingMapAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, const ::xla::IndexingMap&indexing_map);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::AffineMap map, ::llvm::ArrayRef<::xla::IndexingMap::Variable> dim_vars, ::llvm::ArrayRef<::xla::IndexingMap::Variable> range_vars, ::llvm::ArrayRef<::std::pair<::mlir::AffineExpr, ::xla::Interval>> constraints);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::AffineMap map, ::llvm::ArrayRef<::xla::IndexingMap::Variable> dim_vars, ::llvm::ArrayRef<::xla::IndexingMap::Variable> range_vars, ::llvm::ArrayRef<::std::pair<::mlir::AffineExpr, ::xla::Interval>> constraints);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"indexing_map"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::AffineMap getMap() const;
  ::llvm::ArrayRef<::xla::IndexingMap::Variable> getDimVars() const;
  ::llvm::ArrayRef<::xla::IndexingMap::Variable> getRangeVars() const;
  ::llvm::ArrayRef<::std::pair<::mlir::AffineExpr, ::xla::Interval>> getConstraints() const;
};
namespace detail {

struct BackendKindAttrStorage;

} // namespace detail
class BackendKindAttr : public ::mlir::Attribute::AttrBase<BackendKindAttr, ::mlir::Attribute, detail::BackendKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "xla.backend_kind";
  static constexpr ::llvm::StringLiteral dialectName = "xla";
  static BackendKindAttr get(::mlir::MLIRContext *context, ::xla::BackendKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"backend_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::xla::BackendKind getValue() const;
};
namespace detail {

struct ExtraBackendOptionsAttrStorage;

} // namespace detail
class ExtraBackendOptionsAttr : public ::mlir::Attribute::AttrBase<ExtraBackendOptionsAttr, ::mlir::Attribute, detail::ExtraBackendOptionsAttrStorage> {
public:
  using Base::Base;
  auto begin() const { return getValue().begin(); }
  auto end() const { return getValue().end(); }
  bool empty() const { return getValue().empty(); }
  size_t size() const { return getValue().size(); }
  auto &front() const { return getValue().front(); }
  auto &back() const { return getValue().back(); }
  auto &operator[](size_t index) { return getValue()[index]; }
  operator ::llvm::ArrayRef<mlir::StringAttr>() const { return getValue(); }
  static constexpr ::llvm::StringLiteral name = "xla.extra_backend_options";
  static constexpr ::llvm::StringLiteral dialectName = "xla";
  static ExtraBackendOptionsAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<mlir::StringAttr> value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"extra_backend_options"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<mlir::StringAttr> getValue() const;
};
class CpuMemoryRegionNameAttr : public ::mlir::Attribute::AttrBase<CpuMemoryRegionNameAttr, mlir::StringAttr, ::mlir::AttributeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "xla.cpu_memory_region_name";
  static constexpr ::llvm::StringLiteral dialectName = "xla";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cpu_memory_region_name"};
  }

};
namespace detail {

struct WorkGroupDimensionAttrStorage;

} // namespace detail
class WorkGroupDimensionAttr : public ::mlir::Attribute::AttrBase<WorkGroupDimensionAttr, ::mlir::Attribute, detail::WorkGroupDimensionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "xla.dim";
  static constexpr ::llvm::StringLiteral dialectName = "xla";
  static WorkGroupDimensionAttr get(::mlir::MLIRContext *context, ::xla::WorkGroupDimension value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dim"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::xla::WorkGroupDimension getValue() const;
};

} // namespace xla
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::IndexingMapAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::BackendKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::ExtraBackendOptionsAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::CpuMemoryRegionNameAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::WorkGroupDimensionAttr)

#endif // GET_ATTRDEF_CLASSES

