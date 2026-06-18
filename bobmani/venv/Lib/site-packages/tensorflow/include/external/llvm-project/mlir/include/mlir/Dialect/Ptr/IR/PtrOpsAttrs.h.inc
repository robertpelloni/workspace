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
namespace mlir::ptr {

/// Address attribute
/// The `address` attribute represents a raw memory address, expressed in bytes.
/// 
///     Example:
/// 
///     ```mlir
///       #ptr.address<0x1000> : !ptr.ptr<#ptr.generic_space>
///     ```
class AddressAttr;
/// Generic memory space
/// The `generic_space` attribute defines a memory space attribute with the
///     following properties:
///     - Load and store operations are always valid, regardless of the type.
///     - Atomic operations are always valid, regardless of the type.
///     - Cast operations to `generic_space` are always valid.
/// 
///     Example:
/// 
///     ```mlir
///       #ptr.generic_space : !ptr.ptr<#ptr.generic_space>
///     ```
class GenericSpaceAttr;
/// Null pointer attribute
/// The `null` attribute represents a null pointer.
/// 
///     Example:
/// 
///     ```mlir
///       #ptr.null
///     ```
class NullAttr;
/// ptr data layout spec
/// Defines the data layout spec for a pointer type. This attribute has 4
///     fields:
///      - [Required] size: size of the pointer in bits.
///      - [Required] abi: ABI-required alignment for the pointer in bits.
///      - [Required] preferred: preferred alignment for the pointer in bits.
///      - [Optional] index: bitwidth that should be used when performing index
///      computations for the type. Setting the field to `kOptionalSpecValue`, means
///      the field is optional.
/// 
///     Furthermore, the attribute will verify that all present values are divisible
///     by 8 (number of bits in a byte), and that `preferred` > `abi`.
/// 
///     Example:
///     ```mlir
///     // Spec for a 64 bit ptr, with a required alignment of 64 bits, but with
///     // a preferred alignment of 128 bits and an index bitwidth of 64 bits.
///     #ptr.spec<size = 64, abi = 64, preferred = 128, index = 64>
///     ```
class SpecAttr;
namespace detail {

struct AddressAttrStorage;

} // namespace detail
class AddressAttr : public ::mlir::Attribute::AttrBase<AddressAttr, ::mlir::Attribute, detail::AddressAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "ptr.address";
  static constexpr ::llvm::StringLiteral dialectName = "ptr";
  static AddressAttr get(::mlir::MLIRContext *context, PtrType type, ::llvm::APInt value);
  static AddressAttr get(PtrType type, const llvm::APInt &value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"address"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  PtrType getType() const;
  ::llvm::APInt getValue() const;
};
class GenericSpaceAttr : public ::mlir::Attribute::AttrBase<GenericSpaceAttr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::ptr::MemorySpaceAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "ptr.generic_space";
  static constexpr ::llvm::StringLiteral dialectName = "ptr";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"generic_space"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  bool isValidLoad(::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout *dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  bool isValidStore(::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout *dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  bool isValidAtomicOp(::mlir::ptr::AtomicBinOp op, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout *dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  bool isValidAtomicXchg(::mlir::Type type, ::mlir::ptr::AtomicOrdering successOrdering, ::mlir::ptr::AtomicOrdering failureOrdering, std::optional<int64_t> alignment, const ::mlir::DataLayout *dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  bool isValidAddrSpaceCast(::mlir::Type tgt, ::mlir::Type src, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  bool isValidPtrIntCast(::mlir::Type intLikeTy, ::mlir::Type ptrLikeTy, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
};
namespace detail {

struct NullAttrStorage;

} // namespace detail
class NullAttr : public ::mlir::Attribute::AttrBase<NullAttr, ::mlir::Attribute, detail::NullAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "ptr.null";
  static constexpr ::llvm::StringLiteral dialectName = "ptr";
  static NullAttr get(::mlir::MLIRContext *context, PtrType type);
  static NullAttr get(PtrType type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"null"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  PtrType getType() const;
};
namespace detail {

struct SpecAttrStorage;

} // namespace detail
class SpecAttr : public ::mlir::Attribute::AttrBase<SpecAttr, ::mlir::Attribute, detail::SpecAttrStorage> {
public:
  using Base::Base;
  /// Constant for specifying a spec entry is optional.
  static constexpr uint32_t kOptionalSpecValue = std::numeric_limits<uint32_t>::max();
  static constexpr ::llvm::StringLiteral name = "ptr.spec";
  static constexpr ::llvm::StringLiteral dialectName = "ptr";
  using Base::getChecked;
  static SpecAttr get(::mlir::MLIRContext *context, uint32_t size, uint32_t abi, uint32_t preferred, uint32_t index = kOptionalSpecValue);
  static SpecAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, uint32_t size, uint32_t abi, uint32_t preferred, uint32_t index = kOptionalSpecValue);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, uint32_t size, uint32_t abi, uint32_t preferred, uint32_t index);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, uint32_t size, uint32_t abi, uint32_t preferred, uint32_t index);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"spec"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  uint32_t getSize() const;
  uint32_t getAbi() const;
  uint32_t getPreferred() const;
  uint32_t getIndex() const;
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::AddressAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::GenericSpaceAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::NullAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::SpecAttr)

#endif // GET_ATTRDEF_CLASSES

