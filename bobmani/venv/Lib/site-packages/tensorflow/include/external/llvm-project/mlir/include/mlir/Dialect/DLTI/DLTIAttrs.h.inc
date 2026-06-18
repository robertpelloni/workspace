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
namespace mlir {

/// An attribute to represent an entry of a data layout specification.
/// A data layout entry attribute is a key-value pair where the key is a type or
///     an identifier and the value is another attribute. These entries form a data
///     layout specification.
class DataLayoutEntryAttr;
/// An attribute to represent a data layout specification.
/// A data layout specification is a list of entries that specify (partial) data
///     layout information. It is expected to be attached to operations that serve
///     as scopes for data layout requests.
class DataLayoutSpecAttr;
/// A mapping of DLTI-information by way of key-value pairs
/// A Data Layout and Target Information map is a list of entries effectively
///     encoding a dictionary, mapping DLTI-related keys to DLTI-related values.
/// 
///     This attribute's main purpose is to facilate querying IR for arbitrary
///     key-value associations that encode DLTI. Facility functions exist to perform
///     recursive lookups on nested DLTI-map/query interface-implementing
///     attributes.
/// 
///     Consider the following flat encoding of a single-key dictionary
///     ```
///     #dlti.map<"CPU::cache::L1::size_in_bytes" = 65536 : i32>>
///     ```
///     versus nested maps, which make it possible to obtain sub-dictionaries of
///     related information (with the following example making use of other
///     attributes that also implement the `DLTIQueryInterface`):
///     ```
///     #dlti.target_system_spec<"CPU" =
///       #dlti.target_device_spec<"cache" =
///         #dlti.map<"L1" = #dlti.map<"size_in_bytes" = 65536 : i32>,
///                   "L1d" = #dlti.map<"size_in_bytes" = 32768 : i32> >>>
///     ```
/// 
///     With the flat encoding, the implied structure of the key is ignored, that is
///     the only successful query (as expressed in the Transform Dialect) is:
///     `transform.dlti.query ["CPU::cache::L1::size_in_bytes"] at %op`,
///     where `%op` is a handle to an operation which associates the flat-encoding
///     `#dlti.map` attribute.
/// 
///     For querying nested dictionaries, the relevant keys need to be separately
///     provided. That is, if `%op` is an handle to an op which has the nesting
///     `#dlti.target_system_spec`-attribute from above attached, then
///     `transform.dlti.query ["CPU","cache","L1","size_in_bytes"] at %op` gives
///     back the first leaf value contained. To access the other leaf, we need to do
///     `transform.dlti.query ["CPU","cache","L1d","size_in_bytes"] at %op`.
class MapAttr;
/// An attribute to represent target system specification.
/// A system specification describes the overall system containing
///     multiple devices, with each device having a unique ID (string)
///     and its corresponding TargetDeviceSpec object.
/// 
///     Example:
///     ```
///     dlti.target_system_spec =
///      #dlti.target_system_spec<
///       "CPU" = #dlti.target_device_spec<
///         "L1_cache_size_in_bytes" = 4096: ui32>,
///       "GPU" = #dlti.target_device_spec<
///         "max_vector_op_width" = 64 : ui32>,
///       "XPU" = #dlti.target_device_spec<
///         "max_vector_op_width" = 4096 : ui32>>
///     ```
/// 
///     The verifier checks that keys are strings and pointed to values implement
///     DLTI's TargetDeviceSpecInterface.
class TargetSystemSpecAttr;
/// An attribute to represent target device specification.
/// Each device specification describes a single device and its
///     hardware properties. Each device specification can contain any number
///     of optional hardware properties (e.g., max_vector_op_width below).
/// 
///     Example:
///     ```
///     #dlti.target_device_spec<"max_vector_op_width" = 64 : ui32>
///     ```
class TargetDeviceSpecAttr;
/// An attribute to represent function pointer alignment.
/// Function pointer alignment specifies the minimum alignment of function
///     pointers, it's a multiple of `alignment`. This alignment can also depend
///     on the target function, indicated by `function_dependent`.
///     Example:
///     ```
///     #dlti.dl_entry<"dlti.function_pointer_alignment",
///                #dlti.function_pointer_alignment<64, function_dependent = false>>
///     ```
class FunctionPointerAlignmentAttr;
class DataLayoutEntryAttr : public ::mlir::Attribute::AttrBase<DataLayoutEntryAttr, ::mlir::Attribute, detail::DataLayoutEntryAttrStorage, ::mlir::DataLayoutEntryInterface::Trait> {
public:
  using Base::Base;
  /// Returns the entry with the given key and value.
  static DataLayoutEntryAttr get(StringAttr key, Attribute value);
  static DataLayoutEntryAttr get(MLIRContext *context, Type key, Attribute value);
  static DataLayoutEntryAttr get(Type key, Attribute value);
  static constexpr ::llvm::StringLiteral name = "dlti.dl_entry";
  static constexpr ::llvm::StringLiteral dialectName = "dlti";
  static DataLayoutEntryAttr get(::mlir::MLIRContext *context, DataLayoutEntryKey key, Attribute value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dl_entry"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  DataLayoutEntryKey getKey() const;
  Attribute getValue() const;
};
namespace detail {

struct DataLayoutSpecAttrStorage;

} // namespace detail
class DataLayoutSpecAttr : public ::mlir::Attribute::AttrBase<DataLayoutSpecAttr, ::mlir::Attribute, detail::DataLayoutSpecAttrStorage, ::mlir::DLTIQueryInterface::Trait, ::mlir::DataLayoutSpecInterface::Trait> {
public:
  using Base::Base;
  /// Combines this specification with `specs`, enclosing specifications listed
  /// from outermost to innermost. This overwrites the older entries with the
  /// same key as the newer entries if the entries are compatible. Returns null
  /// if the specifications are not compatible.
  DataLayoutSpecAttr combineWith(ArrayRef<DataLayoutSpecInterface> specs) const;

  /// Returns the endiannes identifier.
  StringAttr getEndiannessIdentifier(MLIRContext *context) const;

  /// Returns the default memory space identifier.
  StringAttr getDefaultMemorySpaceIdentifier(MLIRContext *context) const;

  /// Returns the alloca memory space identifier.
  StringAttr getAllocaMemorySpaceIdentifier(MLIRContext *context) const;

  /// Returns the mangling mode identifier.
  StringAttr getManglingModeIdentifier(MLIRContext *context) const;

  /// Returns the program memory space identifier.
  StringAttr getProgramMemorySpaceIdentifier(MLIRContext *context) const;

  /// Returns the global memory space identifier.
  StringAttr getGlobalMemorySpaceIdentifier(MLIRContext *context) const;

  /// Returns the stack alignment identifier.
  StringAttr getStackAlignmentIdentifier(MLIRContext *context) const;

  /// Returns the function pointer alignment identifier.
  StringAttr getFunctionPointerAlignmentIdentifier(MLIRContext *context) const;

  /// Returns the legal int widths identifier.
  StringAttr getLegalIntWidthsIdentifier(MLIRContext *context) const;

  /// Returns the attribute associated with the key.
  FailureOr<Attribute> query(DataLayoutEntryKey key) {
    return ::llvm::cast<mlir::DataLayoutSpecInterface>(*this).queryHelper(key);
  }
  static constexpr ::llvm::StringLiteral name = "dlti.dl_spec";
  static constexpr ::llvm::StringLiteral dialectName = "dlti";
  using Base::getChecked;
  static DataLayoutSpecAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static DataLayoutSpecAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dl_spec"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<DataLayoutEntryInterface> getEntries() const;
};
namespace detail {

struct MapAttrStorage;

} // namespace detail
class MapAttr : public ::mlir::Attribute::AttrBase<MapAttr, ::mlir::Attribute, detail::MapAttrStorage, ::mlir::DLTIQueryInterface::Trait> {
public:
  using Base::Base;
  /// Returns the attribute associated with the key.
  FailureOr<Attribute> query(DataLayoutEntryKey key) {
    for (DataLayoutEntryInterface entry : getEntries())
      if (entry.getKey() == key)
          return entry.getValue();
    return ::mlir::failure();
  }
  static constexpr ::llvm::StringLiteral name = "dlti.map";
  static constexpr ::llvm::StringLiteral dialectName = "dlti";
  using Base::getChecked;
  static MapAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static MapAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"map"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<DataLayoutEntryInterface> getEntries() const;
};
namespace detail {

struct TargetSystemSpecAttrStorage;

} // namespace detail
class TargetSystemSpecAttr : public ::mlir::Attribute::AttrBase<TargetSystemSpecAttr, ::mlir::Attribute, detail::TargetSystemSpecAttrStorage, ::mlir::DLTIQueryInterface::Trait, ::mlir::TargetSystemSpecInterface::Trait> {
public:
  using Base::Base;
  /// Return the device specification that matches the given device ID
  std::optional<TargetDeviceSpecInterface>
  getDeviceSpecForDeviceID(
    TargetSystemSpecInterface::DeviceID deviceID);

  /// Returns the attribute associated with the key.
  FailureOr<Attribute> query(DataLayoutEntryKey key) const {
    return ::llvm::cast<mlir::TargetSystemSpecInterface>(*this).queryHelper(key);
  }
  static constexpr ::llvm::StringLiteral name = "dlti.target_system_spec";
  static constexpr ::llvm::StringLiteral dialectName = "dlti";
  using Base::getChecked;
  static TargetSystemSpecAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static TargetSystemSpecAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"target_system_spec"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<DataLayoutEntryInterface> getEntries() const;
};
namespace detail {

struct TargetDeviceSpecAttrStorage;

} // namespace detail
class TargetDeviceSpecAttr : public ::mlir::Attribute::AttrBase<TargetDeviceSpecAttr, ::mlir::Attribute, detail::TargetDeviceSpecAttrStorage, ::mlir::DLTIQueryInterface::Trait, ::mlir::TargetDeviceSpecInterface::Trait> {
public:
  using Base::Base;
  /// Returns the attribute associated with the key.
  FailureOr<Attribute> query(DataLayoutEntryKey key) const {
    return ::llvm::cast<mlir::TargetDeviceSpecInterface>(*this).queryHelper(key);
  }
  static constexpr ::llvm::StringLiteral name = "dlti.target_device_spec";
  static constexpr ::llvm::StringLiteral dialectName = "dlti";
  using Base::getChecked;
  static TargetDeviceSpecAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static TargetDeviceSpecAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<DataLayoutEntryInterface> entries);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"target_device_spec"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<DataLayoutEntryInterface> getEntries() const;
};
namespace detail {

struct FunctionPointerAlignmentAttrStorage;

} // namespace detail
class FunctionPointerAlignmentAttr : public ::mlir::Attribute::AttrBase<FunctionPointerAlignmentAttr, ::mlir::Attribute, detail::FunctionPointerAlignmentAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "dlti.function_pointer_alignment";
  static constexpr ::llvm::StringLiteral dialectName = "dlti";
  static FunctionPointerAlignmentAttr get(::mlir::MLIRContext *context, uint64_t alignment, bool function_dependent);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"function_pointer_alignment"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  uint64_t getAlignment() const;
  bool getFunctionDependent() const;
};

} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::DataLayoutEntryAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::DataLayoutSpecAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::MapAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TargetSystemSpecAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TargetDeviceSpecAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::FunctionPointerAlignmentAttr)

#endif // GET_ATTRDEF_CLASSES

