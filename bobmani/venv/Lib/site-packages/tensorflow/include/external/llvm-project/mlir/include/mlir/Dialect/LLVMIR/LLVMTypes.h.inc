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
namespace mlir::LLVM {

/// LLVM array type
/// The `!llvm.array` type represents a fixed-size array of element types.
///     It is an aggregate type representing consecutive elements in memory,
///     parameterized by the number of elements and the element type.
/// 
///     Example:
/// 
///     ```mlir
///     !llvm.array<4 x i32>
///     ```
class LLVMArrayType;
/// LLVM function type
/// The `!llvm.func` is a function type. It consists of a single return type
///     (unlike MLIR which can have multiple), a list of parameter types and can
///     optionally be variadic.
/// 
///     Example:
/// 
///     ```mlir
///     !llvm.func<i32 (i32)>
///     ```
class LLVMFunctionType;
/// LLVM struct type
/// LLVM dialect structure type representing a collection of different-typed
///     elements manipulated together. Struct types can optionally be packed, meaning
///     that their elements immediately follow each other in memory without
///     accounting for potential alignment.
/// 
///     Structure types can be identified (named) or literal. Literal structures
///     are uniquely represented by the list of types they contain and packedness.
///     Literal structure types are immutable after construction.
/// 
///     Identified structures are uniquely represented by their name, a string. They
///     have a mutable component, consisting of the list of types they contain,
///     the packedness and the opacity bits. Identified structs can be created
///     without providing the lists of element types, making them suitable to
///     represent recursive, i.e. self-referring, structures. Identified structs
///     without body are considered opaque. For such structs, one can set the body.
///     Identified structs can be created as intentionally-opaque, implying that the
///     caller does not intend to ever set the body (e.g. forward-declarations of
///     structs from another module) and wants to disallow further modification of
///     the body. For intentionally-opaque structs or non-opaque structs with the
///     body, one is not allowed to set another body (however, one can set exactly
///     the same body).
/// 
///     Note that the packedness of the struct takes place in uniquing of literal
///     structs, but does not in uniquing of identified structs.
class LLVMStructType;
/// LLVM pointer type
/// The `!llvm.ptr` type is an LLVM pointer type. This type typically represents
///     a reference to an object in memory. Pointers are optionally parameterized
///     by the address space.
/// 
///     Example:
/// 
///     ```mlir
///     !llvm.ptr
///     ```
class LLVMPointerType;
/// LLVM target-specific extension type
/// LLVM dialect target extension type, which are generally unintrospectable
///     from target-independent optimizations.
/// 
///     Target extension types have a string name, and optionally have type and/or
///     integer parameters. The exact meaning of any parameters is dependent on the
///     target.
class LLVMTargetExtType;
/// LLVM x86_amx type.
/// The x86_amx type represents a value held in an AMX tile register on an x86
///     machine. Can only be used in AMX intrinsics calls.
class LLVMX86AMXType;
/// 128 bit FP type with IBM double-double semantics
/// A 128 bit floating-point type with IBM double-double semantics.
///     See S_PPCDoubleDouble in APFloat.h for details.
class LLVMPPCFP128Type;
namespace detail {

struct LLVMArrayTypeStorage;

} // namespace detail
class LLVMArrayType : public ::mlir::Type::TypeBase<LLVMArrayType, ::mlir::Type, detail::LLVMArrayTypeStorage, ::mlir::DataLayoutTypeInterface::Trait, ::mlir::DestructurableTypeInterface::Trait> {
public:
  using Base::Base;
  /// Checks if the given type can be used inside an array type.
  static bool isValidElementType(Type type);
  static constexpr ::llvm::StringLiteral name = "llvm.array";
  static constexpr ::llvm::StringLiteral dialectName = "llvm";
  using Base::getChecked;
  using ::mlir::DataLayoutTypeInterface::Trait<LLVMArrayType>::getIndexBitwidth;
  using ::mlir::DataLayoutTypeInterface::Trait<LLVMArrayType>::areCompatible;
  using ::mlir::DataLayoutTypeInterface::Trait<LLVMArrayType>::verifyEntries;
  static LLVMArrayType get(::mlir::MLIRContext *context, Type elementType, uint64_t numElements);
  static LLVMArrayType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, Type elementType, uint64_t numElements);
  static LLVMArrayType get(Type elementType, uint64_t numElements);
  static LLVMArrayType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, uint64_t numElements);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, uint64_t numElements);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, uint64_t numElements);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"array"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  Type getElementType() const;
  uint64_t getNumElements() const;
  ::llvm::TypeSize getTypeSize(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  ::llvm::TypeSize getTypeSizeInBits(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  uint64_t getABIAlignment(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  uint64_t getPreferredAlignment(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  ::std::optional<::llvm::DenseMap<::mlir::Attribute, ::mlir::Type>> getSubelementIndexMap() const;
  ::mlir::Type getTypeAtIndex(::mlir::Attribute index) const;
};
namespace detail {

struct LLVMFunctionTypeStorage;

} // namespace detail
class LLVMFunctionType : public ::mlir::Type::TypeBase<LLVMFunctionType, ::mlir::Type, detail::LLVMFunctionTypeStorage> {
public:
  using Base::Base;
  /// Checks if the given type can be used an argument in a function type.
  static bool isValidArgumentType(Type type);

  /// Checks if the given type can be used as a result in a function type.
  static bool isValidResultType(Type type);

  /// Returns whether the function is variadic.
  bool isVarArg() const { return getVarArg(); }

  /// Returns a clone of this function type with the given argument
  /// and result types. Returns null if the resulting function type would
  /// not verify.
  LLVMFunctionType clone(TypeRange inputs, TypeRange results) const;

  /// Returns the result type of the function as an ArrayRef, enabling better
  /// integration with generic MLIR utilities.
  ArrayRef<Type> getReturnTypes() const;

  /// Returns the number of arguments to the function.
  unsigned getNumParams() const { return getParams().size(); }

  /// Returns `i`-th argument of the function. Asserts on out-of-bounds.
  Type getParamType(unsigned i) { return getParams()[i]; }
  static constexpr ::llvm::StringLiteral name = "llvm.func";
  static constexpr ::llvm::StringLiteral dialectName = "llvm";
  using Base::getChecked;
  static LLVMFunctionType get(::mlir::MLIRContext *context, Type returnType, ::llvm::ArrayRef<Type> params, bool varArg);
  static LLVMFunctionType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, Type returnType, ::llvm::ArrayRef<Type> params, bool varArg);
  static LLVMFunctionType get(Type result, ArrayRef<Type> arguments, bool isVarArg = false);
  static LLVMFunctionType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type result, ArrayRef<Type> arguments, bool isVarArg = false);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type returnType, ::llvm::ArrayRef<Type> params, bool varArg);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type returnType, ::llvm::ArrayRef<Type> params, bool varArg);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"func"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  Type getReturnType() const;
  ::llvm::ArrayRef<Type> getParams() const;
  bool getVarArg() const;
};
class LLVMStructType : public ::mlir::Type::TypeBase<LLVMStructType, ::mlir::Type, detail::LLVMStructTypeStorage, ::mlir::TypeTrait::IsMutable, ::mlir::DataLayoutTypeInterface::Trait, ::mlir::DestructurableTypeInterface::Trait> {
public:
  using Base::Base;
  /// Checks if the given type can be contained in a structure type.
  static bool isValidElementType(Type type);

  /// Gets or creates an identified struct with the given name in the provided
  /// context. Note that unlike llvm::StructType::create, this function will
  /// _NOT_ rename a struct in case a struct with the same name already exists
  /// in the context. Instead, it will just return the existing struct,
  /// similarly to the rest of MLIR type ::get methods.
  static LLVMStructType getIdentified(MLIRContext *context, StringRef name);
  static LLVMStructType
  getIdentifiedChecked(function_ref<InFlightDiagnostic()> emitError,
                       MLIRContext *context, StringRef name);

  /// Gets a new identified struct with the given body. The body _cannot_ be
  /// changed later. If a struct with the given name already exists, renames
  /// the struct by appending a `.` followed by a number to the name. Renaming
  /// happens even if the existing struct has the same body.
  static LLVMStructType getNewIdentified(MLIRContext *context, StringRef name,
                                         ArrayRef<Type> elements,
                                         bool isPacked = false);

  /// Gets or creates a literal struct with the given body in the provided
  /// context.
  static LLVMStructType getLiteral(MLIRContext *context, ArrayRef<Type> types,
                                   bool isPacked = false);

  static LLVMStructType
  getLiteralChecked(function_ref<InFlightDiagnostic()> emitError,
                    MLIRContext *context, ArrayRef<Type> types,
                    bool isPacked = false);

  /// Gets or creates an intentionally-opaque identified struct. Such a struct
  /// cannot have its body set.
  /// Note that unlike llvm::StructType::create, this function will _NOT_
  /// rename a struct in case a struct with the same name
  /// already exists in the context. Instead, it will just return the existing
  /// struct, similarly to the rest of MLIR type ::get methods.
  static LLVMStructType getOpaque(StringRef name, MLIRContext *context);

  static LLVMStructType
  getOpaqueChecked(function_ref<InFlightDiagnostic()> emitError,
                   MLIRContext *context, StringRef name);

  /// Set the body of an identified struct. Returns failure if the body could
  /// not be set, e.g. if the struct already has a body or if it was marked as
  /// intentionally opaque. This might happen in a multi-threaded context when a
  /// different thread modified the struct after it was created. Most callers
  /// are likely to assert this always succeeds, but it is possible to implement
  /// a local renaming scheme based on the result of this call.
  LogicalResult setBody(ArrayRef<Type> types, bool isPacked);

  /// Checks if a struct is packed.
  bool isPacked() const;

  /// Checks if a struct is identified.
  bool isIdentified() const;

  /// Checks if a struct is opaque.
  bool isOpaque() const;

  /// Checks if a struct is initialized.
  bool isInitialized();

  /// Verifies that the type about to be constructed is well-formed.
  static LogicalResult
  verifyInvariants(function_ref<InFlightDiagnostic()> emitError, StringRef,
                   bool);
  static LogicalResult
  verifyInvariants(function_ref<InFlightDiagnostic()> emitError,
                   ArrayRef<Type> types, bool);
  using Base::verifyInvariants;
  static constexpr ::llvm::StringLiteral name = "llvm.struct";
  static constexpr ::llvm::StringLiteral dialectName = "llvm";
  using ::mlir::DataLayoutTypeInterface::Trait<LLVMStructType>::getTypeSize;
  using ::mlir::DataLayoutTypeInterface::Trait<LLVMStructType>::getIndexBitwidth;
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"struct"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::StringRef getName() const;
  ::llvm::ArrayRef<mlir::Type> getBody() const;
  ::llvm::TypeSize getTypeSizeInBits(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  uint64_t getABIAlignment(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  uint64_t getPreferredAlignment(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  bool areCompatible(::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap&identified) const;
  ::llvm::LogicalResult verifyEntries(::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc) const;
  ::std::optional<::llvm::DenseMap<::mlir::Attribute, ::mlir::Type>> getSubelementIndexMap() const;
  ::mlir::Type getTypeAtIndex(::mlir::Attribute index) const;
};
namespace detail {

struct LLVMPointerTypeStorage;

} // namespace detail
class LLVMPointerType : public ::mlir::Type::TypeBase<LLVMPointerType, ::mlir::Type, detail::LLVMPointerTypeStorage, ::mlir::DataLayoutTypeInterface::Trait, ::mlir::VectorElementTypeInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "llvm.ptr";
  static constexpr ::llvm::StringLiteral dialectName = "llvm";
  using ::mlir::DataLayoutTypeInterface::Trait<LLVMPointerType>::getTypeSize;
  static LLVMPointerType get(::mlir::MLIRContext *context, unsigned addressSpace = 0);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ptr"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getAddressSpace() const;
  ::llvm::TypeSize getTypeSizeInBits(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  uint64_t getABIAlignment(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  uint64_t getPreferredAlignment(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  std::optional<uint64_t> getIndexBitwidth(const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
  bool areCompatible(::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap&identified) const;
  ::llvm::LogicalResult verifyEntries(::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc) const;
};
namespace detail {

struct LLVMTargetExtTypeStorage;

} // namespace detail
class LLVMTargetExtType : public ::mlir::Type::TypeBase<LLVMTargetExtType, ::mlir::Type, detail::LLVMTargetExtTypeStorage> {
public:
  using Base::Base;
  enum Property {
    /// zeroinitializer is valid for this target extension type.
    HasZeroInit = 1U << 0,
    /// This type may be used as the value type of a global variable.
    CanBeGlobal = 1U << 1,
  };

  bool hasProperty(Property Prop) const;
  bool supportsMemOps() const;
  static constexpr ::llvm::StringLiteral name = "llvm.target";
  static constexpr ::llvm::StringLiteral dialectName = "llvm";
  static LLVMTargetExtType get(::mlir::MLIRContext *context, ::llvm::StringRef extTypeName, ::llvm::ArrayRef<Type> typeParams, ::llvm::ArrayRef<unsigned int> intParams);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"target"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::StringRef getExtTypeName() const;
  ::llvm::ArrayRef<Type> getTypeParams() const;
  ::llvm::ArrayRef<unsigned int> getIntParams() const;
};
class LLVMX86AMXType : public ::mlir::Type::TypeBase<LLVMX86AMXType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "llvm.x86_amx";
  static constexpr ::llvm::StringLiteral dialectName = "llvm";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"x86_amx"};
  }

};
class LLVMPPCFP128Type : public ::mlir::Type::TypeBase<LLVMPPCFP128Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "llvm.ppc_fp128";
  static constexpr ::llvm::StringLiteral dialectName = "llvm";
  using ::mlir::FloatType::Trait<LLVMPPCFP128Type>::scaleElementBitwidth;
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ppc_fp128"};
  }

  const ::llvm::fltSemantics &getFloatSemantics() const;
};

} // namespace mlir::LLVM
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::LLVM::LLVMArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::LLVM::LLVMFunctionType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::LLVM::LLVMStructType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::LLVM::LLVMPointerType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::LLVM::LLVMTargetExtType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::LLVM::LLVMX86AMXType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::LLVM::LLVMPPCFP128Type)

#endif // GET_TYPEDEF_CLASSES

