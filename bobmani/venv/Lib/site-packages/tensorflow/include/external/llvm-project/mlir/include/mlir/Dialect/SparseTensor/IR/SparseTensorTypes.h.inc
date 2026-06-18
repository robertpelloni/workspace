/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace mlir::sparse_tensor {

/// Structured metadata for sparse tensor low-level storage scheme
/// Values with storage_specifier types represent aggregated storage scheme
///     metadata for the given sparse tensor encoding.  It currently holds
///     a set of values for level-sizes, coordinate arrays, position arrays,
///     and value array.  Note that the type is not yet stable and subject to
///     change in the near future.
/// 
///     Examples:
/// 
///     ```mlir
///     // A storage specifier that can be used to store storage scheme metadata from CSR matrix.
///     !storage_specifier<#CSR>
///     ```
class StorageSpecifierType;
/// A sparse iteration space that represents an abstract N-D (sparse) iteration space
///     extracted from a sparse tensor, i.e., a set of (crd_0, crd_1, ..., crd_N) for
///     every stored element (usually nonzeros) in a sparse tensor between the specified
///     [$loLvl, $hiLvl) levels.
/// 
///     Examples:
/// 
///     ```mlir
///     // An iteration space extracted from a CSR tensor between levels [0, 2).
///     !iter_space<#CSR, lvls = 0 to 2>
///     ```
class IterSpaceType;
/// An iterator that points to the current element in the corresponding iteration space.
/// 
///     Examples:
/// 
///     ```mlir
///     // An iterator that iterates over a iteration space of type `!iter_space<#CSR, lvls = 0 to 2>`
///     !iterator<#CSR, lvls = 0 to 2>
///     ```
class IteratorType;
namespace detail {

struct StorageSpecifierTypeStorage;

} // namespace detail
class StorageSpecifierType : public ::mlir::Type::TypeBase<StorageSpecifierType, ::mlir::Type, detail::StorageSpecifierTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sparse_tensor.storage_specifier";
  static constexpr ::llvm::StringLiteral dialectName = "sparse_tensor";
  using Base::getChecked;
  static StorageSpecifierType get(::mlir::MLIRContext *context, SparseTensorEncodingAttr encoding);
  static StorageSpecifierType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, SparseTensorEncodingAttr encoding);
  static StorageSpecifierType get(SparseTensorEncodingAttr encoding);
  static StorageSpecifierType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, SparseTensorEncodingAttr encoding);
  static StorageSpecifierType get(Type type);
  static StorageSpecifierType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type type);
  static StorageSpecifierType get(Value tensor);
  static StorageSpecifierType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Value tensor);
  static ::llvm::LogicalResult verifyInvariantsImpl(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoding);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoding);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"storage_specifier"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::sparse_tensor::SparseTensorEncodingAttr getEncoding() const;
};
namespace detail {

struct IterSpaceTypeStorage;

} // namespace detail
class IterSpaceType : public ::mlir::Type::TypeBase<IterSpaceType, ::mlir::Type, detail::IterSpaceTypeStorage> {
public:
  using Base::Base;
  /// The the dimension of the iteration space.
  unsigned getSpaceDim() const {
    return getHiLvl() - getLoLvl();
  }

  /// Get the level types for the iteration space.
  ArrayRef<LevelType> getLvlTypes() const {
    return getEncoding().getLvlTypes().slice(getLoLvl(), getSpaceDim());
  }

  /// Whether the iteration space is unique (i.e., no duplicated coordinate).
  bool isUnique() {
    return !getLvlTypes().back().isa<LevelPropNonDefault::Nonunique>();
  }

  /// Get the corresponding iterator type.
  ::mlir::sparse_tensor::IteratorType getIteratorType() const;
  static constexpr ::llvm::StringLiteral name = "sparse_tensor.iter_space";
  static constexpr ::llvm::StringLiteral dialectName = "sparse_tensor";
  using Base::getChecked;
  static IterSpaceType get(::mlir::MLIRContext *context, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoding, Level loLvl, Level hiLvl);
  static IterSpaceType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoding, Level loLvl, Level hiLvl);
  static ::llvm::LogicalResult verifyInvariantsImpl(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoding, Level loLvl, Level hiLvl);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoding, Level loLvl, Level hiLvl);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"iter_space"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::sparse_tensor::SparseTensorEncodingAttr getEncoding() const;
  Level getLoLvl() const;
  Level getHiLvl() const;
};
namespace detail {

struct IteratorTypeStorage;

} // namespace detail
class IteratorType : public ::mlir::Type::TypeBase<IteratorType, ::mlir::Type, detail::IteratorTypeStorage> {
public:
  using Base::Base;
  /// Get the corresponding iteration space type.
  ::mlir::sparse_tensor::IterSpaceType getIterSpaceType() const;

  unsigned getSpaceDim() const { return getIterSpaceType().getSpaceDim(); }
  ArrayRef<LevelType> getLvlTypes() const { return getIterSpaceType().getLvlTypes(); }
  bool isUnique() { return getIterSpaceType().isUnique(); }
  static constexpr ::llvm::StringLiteral name = "sparse_tensor.iterator";
  static constexpr ::llvm::StringLiteral dialectName = "sparse_tensor";
  using Base::getChecked;
  static IteratorType get(::mlir::MLIRContext *context, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoding, Level loLvl, Level hiLvl);
  static IteratorType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoding, Level loLvl, Level hiLvl);
  static ::llvm::LogicalResult verifyInvariantsImpl(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoding, Level loLvl, Level hiLvl);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoding, Level loLvl, Level hiLvl);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"iterator"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::sparse_tensor::SparseTensorEncodingAttr getEncoding() const;
  Level getLoLvl() const;
  Level getHiLvl() const;
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::StorageSpecifierType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::IterSpaceType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::IteratorType)

#endif // GET_TYPEDEF_CLASSES

