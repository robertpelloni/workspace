/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// Attribute interface exposing querying-mechanism for key-value associations.
/// 
///     The central feature of DLTI attributes is to allow looking up values at
///     keys. This interface represent the core functionality to do so - as such
///     most DLTI attributes should be implementing this interface.
/// 
///     Note that as the `query` method returns an attribute, this attribute can
///     be recursively queried when it also implements this interface.
class DLTIQueryInterface;

} // namespace mlir
namespace mlir {

/// Attribute interface describing an entry in a data layout specification.
/// 
///     A data layout specification entry is a key-value pair. Its key is either a
///     type, when the entry is related to a type or a class of types, or an
///     identifier, when it is not. `DataLayoutEntryKey` is an alias allowing one
///     to use both key types. Its value is an arbitrary attribute that is
///     interpreted either by the type for type keys or by the dialect containing
///     the identifier for identifier keys. The interface provides a hook that
///     can be used by specific implementations to delegate the verification of
///     attribute fitness for a particular key to the relevant type or dialect.
class DataLayoutEntryInterface;

} // namespace mlir
namespace mlir {

/// Attribute interface describing a data layout specification.
/// 
///     A data layout specification is seen as a sequence of entries, each of which
///     is an attribute implementing the data layout entry interface. It assumes
///     a contiguous underlying storage for entries. The interface provides a hook
///     for implementations to verify the well-formedness of the specification,
///     with a default implementation that verifies the absence of entries with
///     duplicate keys and the well-formedness of each individual entry before
///     dispatching to the type or dialect the entry is associated with.
/// 
///     Data layout specifications may need to be combined in case they appear on
///     nested operations subject to layout, or to ensure the validity of layout
///     modification. Concrete specification attributes must implement the
///     corresponding hook.
class DataLayoutSpecInterface;

} // namespace mlir
namespace mlir {

/// Attribute interface describing a target device description specification.
/// 
///     A target device description specification is a list of device properties (key)
///     and their values for a specific device. The device is identified using "device_id"
///     (as a key and ui32 value) and "device_type" key which must have a string value.
///     Both "device_id" and "device_type" are mandatory keys. As an example, L1 cache
///     size could be a device property, and its value would be a device specific size.
/// 
///     A target device description specification is attached to a module as a module level
///     attribute.
class TargetDeviceSpecInterface;

} // namespace mlir
namespace mlir {

/// Attribute interface describing a target system description specification.
/// 
///     A target system description specification is a list of target device
///     specifications, with one device specification for a device in the system. As
///     such, a target system description specification allows specifying a heterogenous
///     system, with devices of different types (e.g., CPU, GPU, etc.)
/// 
///     The only requirement on a valid target system description specification is that
///     the "device_id" in every target device description specification needs to be
///     unique. This is because, ultimately, this "device_id" is used by the user to
///     query a value of a device property.
class TargetSystemSpecInterface;

} // namespace mlir
namespace mlir {

/// Attribute interface exposing querying-mechanism for key-value associations.
/// 
///     The central feature of DLTI attributes is to allow looking up values at
///     keys. This interface represent the core functionality to do so - as such
///     most DLTI attributes should be implementing this interface.
/// 
///     Note that as the `query` method returns an attribute, this attribute can
///     be recursively queried when it also implements this interface.
namespace detail {
struct DLTIQueryInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::FailureOr<::mlir::Attribute> (*query)(const Concept *impl, ::mlir::Attribute , ::mlir::DataLayoutEntryKey);
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::DLTIQueryInterface;
    Model() : Concept{query} {}

    static inline ::mlir::FailureOr<::mlir::Attribute> query(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::DataLayoutEntryKey key);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::DLTIQueryInterface;
    FallbackModel() : Concept{query} {}

    static inline ::mlir::FailureOr<::mlir::Attribute> query(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::DataLayoutEntryKey key);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct DLTIQueryInterfaceTrait;

} // namespace detail
class DLTIQueryInterface : public ::mlir::AttributeInterface<DLTIQueryInterface, detail::DLTIQueryInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<DLTIQueryInterface, detail::DLTIQueryInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::DLTIQueryInterfaceTrait<ConcreteAttr> {};

  /// Returns the attribute associated with the key.
  ::mlir::FailureOr<::mlir::Attribute> query(::mlir::DataLayoutEntryKey key) const;
};

} // namespace mlir
namespace mlir {

/// Attribute interface describing an entry in a data layout specification.
/// 
///     A data layout specification entry is a key-value pair. Its key is either a
///     type, when the entry is related to a type or a class of types, or an
///     identifier, when it is not. `DataLayoutEntryKey` is an alias allowing one
///     to use both key types. Its value is an arbitrary attribute that is
///     interpreted either by the type for type keys or by the dialect containing
///     the identifier for identifier keys. The interface provides a hook that
///     can be used by specific implementations to delegate the verification of
///     attribute fitness for a particular key to the relevant type or dialect.
namespace detail {
struct DataLayoutEntryInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::DataLayoutEntryKey (*getKey)(const Concept *impl, ::mlir::Attribute );
    ::mlir::Attribute (*getValue)(const Concept *impl, ::mlir::Attribute );
    ::llvm::LogicalResult (*verifyEntry)(const Concept *impl, ::mlir::Attribute , ::mlir::Location);
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::DataLayoutEntryInterface;
    Model() : Concept{getKey, getValue, verifyEntry} {}

    static inline ::mlir::DataLayoutEntryKey getKey(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline ::mlir::Attribute getValue(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline ::llvm::LogicalResult verifyEntry(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::DataLayoutEntryInterface;
    FallbackModel() : Concept{getKey, getValue, verifyEntry} {}

    static inline ::mlir::DataLayoutEntryKey getKey(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline ::mlir::Attribute getValue(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline ::llvm::LogicalResult verifyEntry(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
    ::llvm::LogicalResult verifyEntry(::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) const;
  };
};
template <typename ConcreteAttr>
struct DataLayoutEntryInterfaceTrait;

} // namespace detail
class DataLayoutEntryInterface : public ::mlir::AttributeInterface<DataLayoutEntryInterface, detail::DataLayoutEntryInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<DataLayoutEntryInterface, detail::DataLayoutEntryInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::DataLayoutEntryInterfaceTrait<ConcreteAttr> {};

  /// Returns the key of the this layout entry.
  ::mlir::DataLayoutEntryKey getKey() const;

  /// Returns the value of this layout entry.
  ::mlir::Attribute getValue() const;

  /// Checks that the entry is well-formed, reports errors at the provided location.
  ::llvm::LogicalResult verifyEntry(::mlir::Location loc) const;

    /// Returns `true` if the key of this entry is a type.
    bool isTypeEntry() {
      return llvm::isa<::mlir::Type>(getKey());
    }
};

} // namespace mlir
namespace mlir {

/// Attribute interface describing a data layout specification.
/// 
///     A data layout specification is seen as a sequence of entries, each of which
///     is an attribute implementing the data layout entry interface. It assumes
///     a contiguous underlying storage for entries. The interface provides a hook
///     for implementations to verify the well-formedness of the specification,
///     with a default implementation that verifies the absence of entries with
///     duplicate keys and the well-formedness of each individual entry before
///     dispatching to the type or dialect the entry is associated with.
/// 
///     Data layout specifications may need to be combined in case they appear on
///     nested operations subject to layout, or to ensure the validity of layout
///     modification. Concrete specification attributes must implement the
///     corresponding hook.
namespace detail {
struct DataLayoutSpecInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::DataLayoutSpecInterface (*combineWith)(const Concept *impl, ::mlir::Attribute , ::llvm::ArrayRef<::mlir::DataLayoutSpecInterface>);
    ::mlir::DataLayoutEntryListRef (*getEntries)(const Concept *impl, ::mlir::Attribute );
    ::mlir::StringAttr (*getEndiannessIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::MLIRContext *);
    ::mlir::StringAttr (*getDefaultMemorySpaceIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::MLIRContext *);
    ::mlir::StringAttr (*getAllocaMemorySpaceIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::MLIRContext *);
    ::mlir::StringAttr (*getProgramMemorySpaceIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::MLIRContext *);
    ::mlir::StringAttr (*getGlobalMemorySpaceIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::MLIRContext *);
    ::mlir::StringAttr (*getManglingModeIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::MLIRContext *);
    ::mlir::StringAttr (*getStackAlignmentIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::MLIRContext *);
    ::mlir::StringAttr (*getFunctionPointerAlignmentIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::MLIRContext *);
    ::mlir::StringAttr (*getLegalIntWidthsIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::MLIRContext *);
    ::mlir::DataLayoutEntryList (*getSpecForType)(const Concept *impl, ::mlir::Attribute , ::mlir::TypeID);
    ::mlir::DataLayoutEntryInterface (*getSpecForIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::StringAttr);
    ::llvm::LogicalResult (*verifySpec)(const Concept *impl, ::mlir::Attribute , ::mlir::Location);
    /// The base classes of this interface.
    const ::mlir::DLTIQueryInterface::Concept *implDLTIQueryInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implDLTIQueryInterface = interfaceMap.lookup<::mlir::DLTIQueryInterface>();
      assert(implDLTIQueryInterface && "`::mlir::DataLayoutSpecInterface` expected its base interface `::mlir::DLTIQueryInterface` to be registered");
    }
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::DataLayoutSpecInterface;
    Model() : Concept{combineWith, getEntries, getEndiannessIdentifier, getDefaultMemorySpaceIdentifier, getAllocaMemorySpaceIdentifier, getProgramMemorySpaceIdentifier, getGlobalMemorySpaceIdentifier, getManglingModeIdentifier, getStackAlignmentIdentifier, getFunctionPointerAlignmentIdentifier, getLegalIntWidthsIdentifier, getSpecForType, getSpecForIdentifier, verifySpec} {}

    static inline ::mlir::DataLayoutSpecInterface combineWith(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::llvm::ArrayRef<::mlir::DataLayoutSpecInterface> specs);
    static inline ::mlir::DataLayoutEntryListRef getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline ::mlir::StringAttr getEndiannessIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getDefaultMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getAllocaMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getProgramMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getGlobalMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getManglingModeIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getStackAlignmentIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getFunctionPointerAlignmentIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getLegalIntWidthsIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::DataLayoutEntryList getSpecForType(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::TypeID type);
    static inline ::mlir::DataLayoutEntryInterface getSpecForIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier);
    static inline ::llvm::LogicalResult verifySpec(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::DataLayoutSpecInterface;
    FallbackModel() : Concept{combineWith, getEntries, getEndiannessIdentifier, getDefaultMemorySpaceIdentifier, getAllocaMemorySpaceIdentifier, getProgramMemorySpaceIdentifier, getGlobalMemorySpaceIdentifier, getManglingModeIdentifier, getStackAlignmentIdentifier, getFunctionPointerAlignmentIdentifier, getLegalIntWidthsIdentifier, getSpecForType, getSpecForIdentifier, verifySpec} {}

    static inline ::mlir::DataLayoutSpecInterface combineWith(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::llvm::ArrayRef<::mlir::DataLayoutSpecInterface> specs);
    static inline ::mlir::DataLayoutEntryListRef getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline ::mlir::StringAttr getEndiannessIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getDefaultMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getAllocaMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getProgramMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getGlobalMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getManglingModeIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getStackAlignmentIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getFunctionPointerAlignmentIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::StringAttr getLegalIntWidthsIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context);
    static inline ::mlir::DataLayoutEntryList getSpecForType(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::TypeID type);
    static inline ::mlir::DataLayoutEntryInterface getSpecForIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier);
    static inline ::llvm::LogicalResult verifySpec(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
    ::mlir::DataLayoutEntryList getSpecForType(::mlir::Attribute tablegen_opaque_val, ::mlir::TypeID type) const;
    ::mlir::DataLayoutEntryInterface getSpecForIdentifier(::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier) const;
    ::llvm::LogicalResult verifySpec(::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) const;
  };
};
template <typename ConcreteAttr>
struct DataLayoutSpecInterfaceTrait;

} // namespace detail
class DataLayoutSpecInterface : public ::mlir::AttributeInterface<DataLayoutSpecInterface, detail::DataLayoutSpecInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<DataLayoutSpecInterface, detail::DataLayoutSpecInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::DataLayoutSpecInterfaceTrait<ConcreteAttr> {};

  /// Combines the current layout with the given list of layouts, provided from the outermost (oldest) to the innermost (newest). Returns null on failure.
  ::mlir::DataLayoutSpecInterface combineWith(::llvm::ArrayRef<::mlir::DataLayoutSpecInterface> specs) const;

  /// Returns the list of layout entries.
  ::mlir::DataLayoutEntryListRef getEntries() const;

  /// Returns the endianness identifier.
  ::mlir::StringAttr getEndiannessIdentifier(::mlir::MLIRContext * context) const;

  /// Returns the default memory space identifier.
  ::mlir::StringAttr getDefaultMemorySpaceIdentifier(::mlir::MLIRContext * context) const;

  /// Returns the alloca memory space identifier.
  ::mlir::StringAttr getAllocaMemorySpaceIdentifier(::mlir::MLIRContext * context) const;

  /// Returns the program memory space identifier.
  ::mlir::StringAttr getProgramMemorySpaceIdentifier(::mlir::MLIRContext * context) const;

  /// Returns the global memory space identifier.
  ::mlir::StringAttr getGlobalMemorySpaceIdentifier(::mlir::MLIRContext * context) const;

  /// Returns the mangling mode identifier.
  ::mlir::StringAttr getManglingModeIdentifier(::mlir::MLIRContext * context) const;

  /// Returns the stack alignment identifier.
  ::mlir::StringAttr getStackAlignmentIdentifier(::mlir::MLIRContext * context) const;

  /// Returns the function pointer alignment identifier.
  ::mlir::StringAttr getFunctionPointerAlignmentIdentifier(::mlir::MLIRContext * context) const;

  /// Returns the legal int widths identifier.
  ::mlir::StringAttr getLegalIntWidthsIdentifier(::mlir::MLIRContext * context) const;

  /// Returns a copy of the entries related to a specific type class regardles of type parameters.
  ::mlir::DataLayoutEntryList getSpecForType(::mlir::TypeID type) const;

  /// Returns the entry related to the given identifier, if present.
  ::mlir::DataLayoutEntryInterface getSpecForIdentifier(::mlir::StringAttr identifier) const;

  /// Verifies the validity of the specification and reports any errors at the given location.
  ::llvm::LogicalResult verifySpec(::mlir::Location loc) const;

    /// Returns a copy of the entries related to the type specified as template
    /// parameter.
    template <typename Ty>
    DataLayoutEntryList getSpecForType() {
      return getSpecForType(TypeID::get<Ty>());
    }

    /// Helper for default implementation of `DLTIQueryInterface`'s `query`.
    inline ::mlir::FailureOr<::mlir::Attribute>
    queryHelper(::mlir::DataLayoutEntryKey key) const {
      for (DataLayoutEntryInterface entry : getEntries())
        if (entry.getKey() == key)
            return entry.getValue();
      return ::mlir::failure();
    }

    /// Populates the given maps with lists of entries grouped by the type or
    /// identifier they are associated with. Users are not expected to call this
    /// method directly.
    void bucketEntriesByType(
        ::llvm::MapVector<::mlir::TypeID, ::mlir::DataLayoutEntryList> &types,
        ::llvm::MapVector<::mlir::StringAttr,
                          ::mlir::DataLayoutEntryInterface> &ids);
  //===----------------------------------------------------------------===//
  // Inherited from ::mlir::DLTIQueryInterface
  //===----------------------------------------------------------------===//

  operator ::mlir::DLTIQueryInterface () const {
    if (!*this) return nullptr;
    return ::mlir::DLTIQueryInterface(*this, getImpl()->implDLTIQueryInterface);
  }


  /// Returns the attribute associated with the key.
  ::mlir::FailureOr<::mlir::Attribute> query(::mlir::DataLayoutEntryKey key) const;
};

} // namespace mlir
namespace mlir {

/// Attribute interface describing a target device description specification.
/// 
///     A target device description specification is a list of device properties (key)
///     and their values for a specific device. The device is identified using "device_id"
///     (as a key and ui32 value) and "device_type" key which must have a string value.
///     Both "device_id" and "device_type" are mandatory keys. As an example, L1 cache
///     size could be a device property, and its value would be a device specific size.
/// 
///     A target device description specification is attached to a module as a module level
///     attribute.
namespace detail {
struct TargetDeviceSpecInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::DataLayoutEntryListRef (*getEntries)(const Concept *impl, ::mlir::Attribute );
    ::mlir::DataLayoutEntryInterface (*getSpecForIdentifier)(const Concept *impl, ::mlir::Attribute , ::mlir::StringAttr);
    ::llvm::LogicalResult (*verifyEntry)(const Concept *impl, ::mlir::Attribute , ::mlir::Location);
    /// The base classes of this interface.
    const ::mlir::DLTIQueryInterface::Concept *implDLTIQueryInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implDLTIQueryInterface = interfaceMap.lookup<::mlir::DLTIQueryInterface>();
      assert(implDLTIQueryInterface && "`::mlir::TargetDeviceSpecInterface` expected its base interface `::mlir::DLTIQueryInterface` to be registered");
    }
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::TargetDeviceSpecInterface;
    Model() : Concept{getEntries, getSpecForIdentifier, verifyEntry} {}

    static inline ::mlir::DataLayoutEntryListRef getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline ::mlir::DataLayoutEntryInterface getSpecForIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier);
    static inline ::llvm::LogicalResult verifyEntry(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::TargetDeviceSpecInterface;
    FallbackModel() : Concept{getEntries, getSpecForIdentifier, verifyEntry} {}

    static inline ::mlir::DataLayoutEntryListRef getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline ::mlir::DataLayoutEntryInterface getSpecForIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier);
    static inline ::llvm::LogicalResult verifyEntry(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
    ::mlir::DataLayoutEntryInterface getSpecForIdentifier(::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier) const;
    ::llvm::LogicalResult verifyEntry(::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) const;
  };
};
template <typename ConcreteAttr>
struct TargetDeviceSpecInterfaceTrait;

} // namespace detail
class TargetDeviceSpecInterface : public ::mlir::AttributeInterface<TargetDeviceSpecInterface, detail::TargetDeviceSpecInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<TargetDeviceSpecInterface, detail::TargetDeviceSpecInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::TargetDeviceSpecInterfaceTrait<ConcreteAttr> {};

  /// Returns the list of layout entries.
  ::mlir::DataLayoutEntryListRef getEntries() const;

  /// Returns the entry related to the given identifier, if present.
  ::mlir::DataLayoutEntryInterface getSpecForIdentifier(::mlir::StringAttr identifier) const;

  /// Checks that the entry is well-formed, reports errors at the provided location.
  ::llvm::LogicalResult verifyEntry(::mlir::Location loc) const;

    /// Helper for default implementation of `DLTIQueryInterface`'s `query`.
    ::mlir::FailureOr<::mlir::Attribute>
    queryHelper(::mlir::DataLayoutEntryKey key) const {
      if (auto strKey = ::llvm::dyn_cast<StringAttr>(key))
        if (DataLayoutEntryInterface spec = getSpecForIdentifier(strKey))
          return spec.getValue();
      return ::mlir::failure();
    }
  //===----------------------------------------------------------------===//
  // Inherited from ::mlir::DLTIQueryInterface
  //===----------------------------------------------------------------===//

  operator ::mlir::DLTIQueryInterface () const {
    if (!*this) return nullptr;
    return ::mlir::DLTIQueryInterface(*this, getImpl()->implDLTIQueryInterface);
  }


  /// Returns the attribute associated with the key.
  ::mlir::FailureOr<::mlir::Attribute> query(::mlir::DataLayoutEntryKey key) const;
};

} // namespace mlir
namespace mlir {

/// Attribute interface describing a target system description specification.
/// 
///     A target system description specification is a list of target device
///     specifications, with one device specification for a device in the system. As
///     such, a target system description specification allows specifying a heterogenous
///     system, with devices of different types (e.g., CPU, GPU, etc.)
/// 
///     The only requirement on a valid target system description specification is that
///     the "device_id" in every target device description specification needs to be
///     unique. This is because, ultimately, this "device_id" is used by the user to
///     query a value of a device property.
namespace detail {
struct TargetSystemSpecInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::ArrayRef<DataLayoutEntryInterface> (*getEntries)(const Concept *impl, ::mlir::Attribute );
    std::optional<::mlir::TargetDeviceSpecInterface> (*getDeviceSpecForDeviceID)(const Concept *impl, ::mlir::Attribute , StringAttr);
    ::llvm::LogicalResult (*verifySpec)(const Concept *impl, ::mlir::Attribute , ::mlir::Location);
    /// The base classes of this interface.
    const ::mlir::DLTIQueryInterface::Concept *implDLTIQueryInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implDLTIQueryInterface = interfaceMap.lookup<::mlir::DLTIQueryInterface>();
      assert(implDLTIQueryInterface && "`::mlir::TargetSystemSpecInterface` expected its base interface `::mlir::DLTIQueryInterface` to be registered");
    }
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::TargetSystemSpecInterface;
    Model() : Concept{getEntries, getDeviceSpecForDeviceID, verifySpec} {}

    static inline ::llvm::ArrayRef<DataLayoutEntryInterface> getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline std::optional<::mlir::TargetDeviceSpecInterface> getDeviceSpecForDeviceID(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, StringAttr deviceID);
    static inline ::llvm::LogicalResult verifySpec(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::TargetSystemSpecInterface;
    FallbackModel() : Concept{getEntries, getDeviceSpecForDeviceID, verifySpec} {}

    static inline ::llvm::ArrayRef<DataLayoutEntryInterface> getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline std::optional<::mlir::TargetDeviceSpecInterface> getDeviceSpecForDeviceID(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, StringAttr deviceID);
    static inline ::llvm::LogicalResult verifySpec(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
    ::llvm::LogicalResult verifySpec(::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) const;
  };
};
template <typename ConcreteAttr>
struct TargetSystemSpecInterfaceTrait;

} // namespace detail
class TargetSystemSpecInterface : public ::mlir::AttributeInterface<TargetSystemSpecInterface, detail::TargetSystemSpecInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<TargetSystemSpecInterface, detail::TargetSystemSpecInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::TargetSystemSpecInterfaceTrait<ConcreteAttr> {};

  /// Returns the list of layout entries.
  ::llvm::ArrayRef<DataLayoutEntryInterface> getEntries() const;

  /// Returns the device description spec for given device ID
  std::optional<::mlir::TargetDeviceSpecInterface> getDeviceSpecForDeviceID(StringAttr deviceID) const;

  /// Verifies the validity of the specification and reports any errors at the given location.
  ::llvm::LogicalResult verifySpec(::mlir::Location loc) const;

    using DeviceID = StringAttr;

    /// Helper for default implementation of `DLTIQueryInterface`'s `query`.
    ::mlir::FailureOr<::mlir::Attribute>
    queryHelper(::mlir::DataLayoutEntryKey key) const {
      if (auto strKey = ::llvm::dyn_cast<::mlir::StringAttr>(key))
        if (auto deviceSpec = getDeviceSpecForDeviceID(strKey))
          return *deviceSpec;
      return ::mlir::failure();
    }
  //===----------------------------------------------------------------===//
  // Inherited from ::mlir::DLTIQueryInterface
  //===----------------------------------------------------------------===//

  operator ::mlir::DLTIQueryInterface () const {
    if (!*this) return nullptr;
    return ::mlir::DLTIQueryInterface(*this, getImpl()->implDLTIQueryInterface);
  }


  /// Returns the attribute associated with the key.
  ::mlir::FailureOr<::mlir::Attribute> query(::mlir::DataLayoutEntryKey key) const;
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteAttr>
  struct DLTIQueryInterfaceTrait : public ::mlir::AttributeInterface<DLTIQueryInterface, detail::DLTIQueryInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteAttr>
  struct DataLayoutEntryInterfaceTrait : public ::mlir::AttributeInterface<DataLayoutEntryInterface, detail::DataLayoutEntryInterfaceInterfaceTraits>::Trait<ConcreteAttr> {

    /// Checks that the entry is well-formed, reports errors at the provided location.
    ::llvm::LogicalResult verifyEntry(::mlir::Location loc) const {
      return ::mlir::success();
    }
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteAttr>
  struct DataLayoutSpecInterfaceTrait : public ::mlir::AttributeInterface<DataLayoutSpecInterface, detail::DataLayoutSpecInterfaceInterfaceTraits>::Trait<ConcreteAttr> {

    /// Returns a copy of the entries related to a specific type class regardles of type parameters.
    ::mlir::DataLayoutEntryList getSpecForType(::mlir::TypeID type) const {
      return ::mlir::detail::filterEntriesForType((*static_cast<const ConcreteAttr *>(this)).getEntries(), type);
    }

    /// Returns the entry related to the given identifier, if present.
    ::mlir::DataLayoutEntryInterface getSpecForIdentifier(::mlir::StringAttr identifier) const {
      return ::mlir::detail::filterEntryForIdentifier((*static_cast<const ConcreteAttr *>(this)).getEntries(),
                                                        identifier);
    }

    /// Verifies the validity of the specification and reports any errors at the given location.
    ::llvm::LogicalResult verifySpec(::mlir::Location loc) const {
      return ::mlir::detail::verifyDataLayoutSpec((*static_cast<const ConcreteAttr *>(this)), loc);
    }
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteAttr>
  struct TargetDeviceSpecInterfaceTrait : public ::mlir::AttributeInterface<TargetDeviceSpecInterface, detail::TargetDeviceSpecInterfaceInterfaceTraits>::Trait<ConcreteAttr> {

    /// Returns the entry related to the given identifier, if present.
    ::mlir::DataLayoutEntryInterface getSpecForIdentifier(::mlir::StringAttr identifier) const {
      return ::mlir::detail::filterEntryForIdentifier((*static_cast<const ConcreteAttr *>(this)).getEntries(),
                                                        identifier);
    }

    /// Checks that the entry is well-formed, reports errors at the provided location.
    ::llvm::LogicalResult verifyEntry(::mlir::Location loc) const {
      return ::mlir::success();
    }
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteAttr>
  struct TargetSystemSpecInterfaceTrait : public ::mlir::AttributeInterface<TargetSystemSpecInterface, detail::TargetSystemSpecInterfaceInterfaceTraits>::Trait<ConcreteAttr> {

    /// Verifies the validity of the specification and reports any errors at the given location.
    ::llvm::LogicalResult verifySpec(::mlir::Location loc) const {
      return ::mlir::detail::verifyTargetSystemSpec((*static_cast<const ConcreteAttr *>(this)), loc);
    }
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteAttr>
::mlir::FailureOr<::mlir::Attribute> detail::DLTIQueryInterfaceInterfaceTraits::Model<ConcreteAttr>::query(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::DataLayoutEntryKey key) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).query(key);
}
template<typename ConcreteAttr>
::mlir::FailureOr<::mlir::Attribute> detail::DLTIQueryInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::query(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::DataLayoutEntryKey key) {
  return static_cast<const ConcreteAttr *>(impl)->query(tablegen_opaque_val, key);
}

} // namespace mlir
namespace mlir {

template<typename ConcreteAttr>
::mlir::DataLayoutEntryKey detail::DataLayoutEntryInterfaceInterfaceTraits::Model<ConcreteAttr>::getKey(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getKey();
}
template<typename ConcreteAttr>
::mlir::Attribute detail::DataLayoutEntryInterfaceInterfaceTraits::Model<ConcreteAttr>::getValue(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getValue();
}
template<typename ConcreteAttr>
::llvm::LogicalResult detail::DataLayoutEntryInterfaceInterfaceTraits::Model<ConcreteAttr>::verifyEntry(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).verifyEntry(loc);
}
template<typename ConcreteAttr>
::mlir::DataLayoutEntryKey detail::DataLayoutEntryInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getKey(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getKey(tablegen_opaque_val);
}
template<typename ConcreteAttr>
::mlir::Attribute detail::DataLayoutEntryInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getValue(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getValue(tablegen_opaque_val);
}
template<typename ConcreteAttr>
::llvm::LogicalResult detail::DataLayoutEntryInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::verifyEntry(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) {
  return static_cast<const ConcreteAttr *>(impl)->verifyEntry(tablegen_opaque_val, loc);
}
template<typename ConcreteModel, typename ConcreteAttr>
::llvm::LogicalResult detail::DataLayoutEntryInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteAttr>::verifyEntry(::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) const {
return ::mlir::success();
}

} // namespace mlir
namespace mlir {

template<typename ConcreteAttr>
::mlir::DataLayoutSpecInterface detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::combineWith(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::llvm::ArrayRef<::mlir::DataLayoutSpecInterface> specs) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).combineWith(specs);
}
template<typename ConcreteAttr>
::mlir::DataLayoutEntryListRef detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getEntries();
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getEndiannessIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getEndiannessIdentifier(context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getDefaultMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getDefaultMemorySpaceIdentifier(context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getAllocaMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getAllocaMemorySpaceIdentifier(context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getProgramMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getProgramMemorySpaceIdentifier(context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getGlobalMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getGlobalMemorySpaceIdentifier(context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getManglingModeIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getManglingModeIdentifier(context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getStackAlignmentIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getStackAlignmentIdentifier(context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getFunctionPointerAlignmentIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getFunctionPointerAlignmentIdentifier(context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getLegalIntWidthsIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getLegalIntWidthsIdentifier(context);
}
template<typename ConcreteAttr>
::mlir::DataLayoutEntryList detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getSpecForType(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::TypeID type) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getSpecForType(type);
}
template<typename ConcreteAttr>
::mlir::DataLayoutEntryInterface detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getSpecForIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getSpecForIdentifier(identifier);
}
template<typename ConcreteAttr>
::llvm::LogicalResult detail::DataLayoutSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::verifySpec(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).verifySpec(loc);
}
template<typename ConcreteAttr>
::mlir::DataLayoutSpecInterface detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::combineWith(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::llvm::ArrayRef<::mlir::DataLayoutSpecInterface> specs) {
  return static_cast<const ConcreteAttr *>(impl)->combineWith(tablegen_opaque_val, specs);
}
template<typename ConcreteAttr>
::mlir::DataLayoutEntryListRef detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getEntries(tablegen_opaque_val);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getEndiannessIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return static_cast<const ConcreteAttr *>(impl)->getEndiannessIdentifier(tablegen_opaque_val, context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getDefaultMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return static_cast<const ConcreteAttr *>(impl)->getDefaultMemorySpaceIdentifier(tablegen_opaque_val, context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getAllocaMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return static_cast<const ConcreteAttr *>(impl)->getAllocaMemorySpaceIdentifier(tablegen_opaque_val, context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getProgramMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return static_cast<const ConcreteAttr *>(impl)->getProgramMemorySpaceIdentifier(tablegen_opaque_val, context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getGlobalMemorySpaceIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return static_cast<const ConcreteAttr *>(impl)->getGlobalMemorySpaceIdentifier(tablegen_opaque_val, context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getManglingModeIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return static_cast<const ConcreteAttr *>(impl)->getManglingModeIdentifier(tablegen_opaque_val, context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getStackAlignmentIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return static_cast<const ConcreteAttr *>(impl)->getStackAlignmentIdentifier(tablegen_opaque_val, context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getFunctionPointerAlignmentIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return static_cast<const ConcreteAttr *>(impl)->getFunctionPointerAlignmentIdentifier(tablegen_opaque_val, context);
}
template<typename ConcreteAttr>
::mlir::StringAttr detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getLegalIntWidthsIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::MLIRContext * context) {
  return static_cast<const ConcreteAttr *>(impl)->getLegalIntWidthsIdentifier(tablegen_opaque_val, context);
}
template<typename ConcreteAttr>
::mlir::DataLayoutEntryList detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getSpecForType(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::TypeID type) {
  return static_cast<const ConcreteAttr *>(impl)->getSpecForType(tablegen_opaque_val, type);
}
template<typename ConcreteAttr>
::mlir::DataLayoutEntryInterface detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getSpecForIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier) {
  return static_cast<const ConcreteAttr *>(impl)->getSpecForIdentifier(tablegen_opaque_val, identifier);
}
template<typename ConcreteAttr>
::llvm::LogicalResult detail::DataLayoutSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::verifySpec(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) {
  return static_cast<const ConcreteAttr *>(impl)->verifySpec(tablegen_opaque_val, loc);
}
template<typename ConcreteModel, typename ConcreteAttr>
::mlir::DataLayoutEntryList detail::DataLayoutSpecInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteAttr>::getSpecForType(::mlir::Attribute tablegen_opaque_val, ::mlir::TypeID type) const {
return ::mlir::detail::filterEntriesForType((::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getEntries(), type);
}
template<typename ConcreteModel, typename ConcreteAttr>
::mlir::DataLayoutEntryInterface detail::DataLayoutSpecInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteAttr>::getSpecForIdentifier(::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier) const {
return ::mlir::detail::filterEntryForIdentifier((::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getEntries(),
                                                        identifier);
}
template<typename ConcreteModel, typename ConcreteAttr>
::llvm::LogicalResult detail::DataLayoutSpecInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteAttr>::verifySpec(::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) const {
return ::mlir::detail::verifyDataLayoutSpec((::llvm::cast<ConcreteAttr>(tablegen_opaque_val)), loc);
}

} // namespace mlir
namespace mlir {

template<typename ConcreteAttr>
::mlir::DataLayoutEntryListRef detail::TargetDeviceSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getEntries();
}
template<typename ConcreteAttr>
::mlir::DataLayoutEntryInterface detail::TargetDeviceSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getSpecForIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getSpecForIdentifier(identifier);
}
template<typename ConcreteAttr>
::llvm::LogicalResult detail::TargetDeviceSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::verifyEntry(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).verifyEntry(loc);
}
template<typename ConcreteAttr>
::mlir::DataLayoutEntryListRef detail::TargetDeviceSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getEntries(tablegen_opaque_val);
}
template<typename ConcreteAttr>
::mlir::DataLayoutEntryInterface detail::TargetDeviceSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getSpecForIdentifier(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier) {
  return static_cast<const ConcreteAttr *>(impl)->getSpecForIdentifier(tablegen_opaque_val, identifier);
}
template<typename ConcreteAttr>
::llvm::LogicalResult detail::TargetDeviceSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::verifyEntry(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) {
  return static_cast<const ConcreteAttr *>(impl)->verifyEntry(tablegen_opaque_val, loc);
}
template<typename ConcreteModel, typename ConcreteAttr>
::mlir::DataLayoutEntryInterface detail::TargetDeviceSpecInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteAttr>::getSpecForIdentifier(::mlir::Attribute tablegen_opaque_val, ::mlir::StringAttr identifier) const {
return ::mlir::detail::filterEntryForIdentifier((::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getEntries(),
                                                        identifier);
}
template<typename ConcreteModel, typename ConcreteAttr>
::llvm::LogicalResult detail::TargetDeviceSpecInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteAttr>::verifyEntry(::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) const {
return ::mlir::success();
}

} // namespace mlir
namespace mlir {

template<typename ConcreteAttr>
::llvm::ArrayRef<DataLayoutEntryInterface> detail::TargetSystemSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getEntries();
}
template<typename ConcreteAttr>
std::optional<::mlir::TargetDeviceSpecInterface> detail::TargetSystemSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::getDeviceSpecForDeviceID(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, StringAttr deviceID) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getDeviceSpecForDeviceID(deviceID);
}
template<typename ConcreteAttr>
::llvm::LogicalResult detail::TargetSystemSpecInterfaceInterfaceTraits::Model<ConcreteAttr>::verifySpec(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).verifySpec(loc);
}
template<typename ConcreteAttr>
::llvm::ArrayRef<DataLayoutEntryInterface> detail::TargetSystemSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getEntries(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getEntries(tablegen_opaque_val);
}
template<typename ConcreteAttr>
std::optional<::mlir::TargetDeviceSpecInterface> detail::TargetSystemSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getDeviceSpecForDeviceID(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, StringAttr deviceID) {
  return static_cast<const ConcreteAttr *>(impl)->getDeviceSpecForDeviceID(tablegen_opaque_val, deviceID);
}
template<typename ConcreteAttr>
::llvm::LogicalResult detail::TargetSystemSpecInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::verifySpec(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) {
  return static_cast<const ConcreteAttr *>(impl)->verifySpec(tablegen_opaque_val, loc);
}
template<typename ConcreteModel, typename ConcreteAttr>
::llvm::LogicalResult detail::TargetSystemSpecInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteAttr>::verifySpec(::mlir::Attribute tablegen_opaque_val, ::mlir::Location loc) const {
return ::mlir::detail::verifyTargetSystemSpec((::llvm::cast<ConcreteAttr>(tablegen_opaque_val)), loc);
}

} // namespace mlir
