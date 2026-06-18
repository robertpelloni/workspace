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
namespace mlir::ptr {

/// pointer type
/// The `ptr` type is an opaque pointer type. This type typically represents a
///     handle to an object in memory or target-dependent values like `nullptr`.
///     Pointers are parameterized by a memory space.
/// 
///     Syntax:
/// 
///     ```mlir
///     pointer ::= `ptr` (`<` memory-space `>`)?
///     memory-space ::= attribute-value
///     ```
class PtrType;
/// Pointer metadata type
/// The `ptr_metadata` type represents an opaque-view of the metadata associated
///     with a `ptr-like` object type.
/// 
///     Note: It's a verification error to construct a `ptr_metadata` type using a
///     `ptr-like` type with no metadata.
/// 
///     Example:
/// 
///     ```mlir
///     // The metadata associated with a `memref` type.
///     !ptr.ptr_metadata<memref<f32>>
///     ```
class PtrMetadataType;
namespace detail {

struct PtrTypeStorage;

} // namespace detail
class PtrType : public ::mlir::Type::TypeBase<PtrType, ::mlir::Type, detail::PtrTypeStorage, ::mlir::MemRefElementTypeInterface::Trait, ::mlir::PtrLikeTypeInterface::Trait, ::mlir::VectorElementTypeInterface::Trait, ::mlir::DataLayoutTypeInterface::Trait> {
public:
  using Base::Base;
  // `PtrLikeTypeInterface` interface methods.
  /// Returns `Type()` as this pointer type is opaque.
  Type getElementType() const {
    return Type();
  }
  /// Clones the pointer with specified memory space or returns failure
  /// if an `elementType` was specified or if the memory space doesn't
  /// implement `MemorySpaceAttrInterface`.
  FailureOr<PtrLikeTypeInterface> clonePtrWith(Attribute memorySpace,
    std::optional<Type> elementType) const {
    if (elementType)
      return failure();
    if (auto ms = dyn_cast<MemorySpaceAttrInterface>(memorySpace))
      return cast<PtrLikeTypeInterface>(get(ms));
    return failure();
  }
  /// `!ptr.ptr` types are seen as ptr-like objects with no metadata.
  bool hasPtrMetadata() const {
    return false;
  }
  static constexpr ::llvm::StringLiteral name = "ptr.ptr";
  static constexpr ::llvm::StringLiteral dialectName = "ptr";
  using ::mlir::DataLayoutTypeInterface::Trait<PtrType>::getTypeSize;
  static PtrType get(::mlir::MLIRContext *context, MemorySpaceAttrInterface memorySpace);
  static PtrType get(MemorySpaceAttrInterface memorySpace);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ptr"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  MemorySpaceAttrInterface getMemorySpace() const;
  ::llvm::TypeSize getTypeSizeInBits(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  uint64_t getABIAlignment(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  uint64_t getPreferredAlignment(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  std::optional<uint64_t> getIndexBitwidth(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  bool areCompatible(::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap&identified) const;
  ::llvm::LogicalResult verifyEntries(::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc) const;
};
namespace detail {

struct PtrMetadataTypeStorage;

} // namespace detail
class PtrMetadataType : public ::mlir::Type::TypeBase<PtrMetadataType, ::mlir::Type, detail::PtrMetadataTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "ptr.ptr_metadata";
  static constexpr ::llvm::StringLiteral dialectName = "ptr";
  using Base::getChecked;
  static PtrMetadataType get(::mlir::MLIRContext *context, PtrLikeTypeInterface type);
  static PtrMetadataType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, PtrLikeTypeInterface type);
  static PtrMetadataType get(PtrLikeTypeInterface ptrLike);
  static PtrMetadataType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, PtrLikeTypeInterface ptrLike);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, PtrLikeTypeInterface type);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, PtrLikeTypeInterface type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ptr_metadata"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  PtrLikeTypeInterface getType() const;
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::PtrType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::PtrMetadataType)

#endif // GET_TYPEDEF_CLASSES

