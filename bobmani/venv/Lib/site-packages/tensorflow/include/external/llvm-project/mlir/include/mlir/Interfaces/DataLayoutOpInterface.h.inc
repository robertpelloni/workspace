/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// Interface for operations that can have a data layout specification attached.
/// 
///     The `DataLayout` object, which can be used for data layout queries, can be
///     constructed for such operations. The absence of a data layout specification
///     must be handled without failing.
/// 
///     Concrete operations must implement the hook returning the data layout
///     specification. They may optionally override the methods used in data layout
///     queries, default implementations of which provide predefined answers for
///     built-in types and dispatch to the type interface for all other types. These
///     methods must be idempotent, that is return the same result on repeated
///     queries with the same parameters. They are declared static and therefore
///     have no access to the operation or its attributes. Instead, they receive a
///     list of data layout entries relevant to the request. The entries are known
///     to have passed the spec and entry verifier.
class DataLayoutOpInterface;

} // namespace mlir
namespace mlir {

/// Interface for operations that can have a data layout specification attached.
/// 
///     The `DataLayout` object, which can be used for data layout queries, can be
///     constructed for such operations. The absence of a data layout specification
///     must be handled without failing.
/// 
///     Concrete operations must implement the hook returning the data layout
///     specification. They may optionally override the methods used in data layout
///     queries, default implementations of which provide predefined answers for
///     built-in types and dispatch to the type interface for all other types. These
///     methods must be idempotent, that is return the same result on repeated
///     queries with the same parameters. They are declared static and therefore
///     have no access to the operation or its attributes. Instead, they receive a
///     list of data layout entries relevant to the request. The entries are known
///     to have passed the spec and entry verifier.
namespace detail {
struct DataLayoutOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::DataLayoutSpecInterface (*getDataLayoutSpec)(const Concept *impl, ::mlir::Operation *);
    ::mlir::TargetSystemSpecInterface (*getTargetSystemSpec)(const Concept *impl, ::mlir::Operation *);
    ::llvm::TypeSize (*getTypeSize)(::mlir::Type, const ::mlir::DataLayout &, ::mlir::DataLayoutEntryListRef);
    ::llvm::TypeSize (*getTypeSizeInBits)(::mlir::Type, const ::mlir::DataLayout &, ::mlir::DataLayoutEntryListRef);
    uint64_t (*getTypeABIAlignment)(::mlir::Type, const ::mlir::DataLayout &, ::mlir::DataLayoutEntryListRef);
    uint64_t (*getTypePreferredAlignment)(::mlir::Type, const ::mlir::DataLayout &, ::mlir::DataLayoutEntryListRef);
    std::optional<uint64_t> (*getIndexBitwidth)(::mlir::Type, const ::mlir::DataLayout &, ::mlir::DataLayoutEntryListRef);
    ::mlir::Attribute (*getEndianness)(::mlir::DataLayoutEntryInterface);
    ::mlir::Attribute (*getDefaultMemorySpace)(::mlir::DataLayoutEntryInterface);
    ::mlir::Attribute (*getAllocaMemorySpace)(::mlir::DataLayoutEntryInterface);
    ::mlir::Attribute (*getManglingMode)(::mlir::DataLayoutEntryInterface);
    ::mlir::Attribute (*getProgramMemorySpace)(::mlir::DataLayoutEntryInterface);
    ::mlir::Attribute (*getGlobalMemorySpace)(::mlir::DataLayoutEntryInterface);
    uint64_t (*getStackAlignment)(::mlir::DataLayoutEntryInterface);
    Attribute (*getFunctionPointerAlignment)(::mlir::DataLayoutEntryInterface);
    Attribute (*getLegalIntWidths)(::mlir::DataLayoutEntryInterface);
    std::optional<Attribute> (*getDevicePropertyValue)(::mlir::DataLayoutEntryInterface);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::DataLayoutOpInterface;
    Model() : Concept{getDataLayoutSpec, getTargetSystemSpec, getTypeSize, getTypeSizeInBits, getTypeABIAlignment, getTypePreferredAlignment, getIndexBitwidth, getEndianness, getDefaultMemorySpace, getAllocaMemorySpace, getManglingMode, getProgramMemorySpace, getGlobalMemorySpace, getStackAlignment, getFunctionPointerAlignment, getLegalIntWidths, getDevicePropertyValue} {}

    static inline ::mlir::DataLayoutSpecInterface getDataLayoutSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::TargetSystemSpecInterface getTargetSystemSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::TypeSize getTypeSize(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline ::llvm::TypeSize getTypeSizeInBits(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline uint64_t getTypeABIAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline uint64_t getTypePreferredAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline std::optional<uint64_t> getIndexBitwidth(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline ::mlir::Attribute getEndianness(::mlir::DataLayoutEntryInterface entry);
    static inline ::mlir::Attribute getDefaultMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static inline ::mlir::Attribute getAllocaMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static inline ::mlir::Attribute getManglingMode(::mlir::DataLayoutEntryInterface entry);
    static inline ::mlir::Attribute getProgramMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static inline ::mlir::Attribute getGlobalMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static inline uint64_t getStackAlignment(::mlir::DataLayoutEntryInterface entry);
    static inline Attribute getFunctionPointerAlignment(::mlir::DataLayoutEntryInterface entry);
    static inline Attribute getLegalIntWidths(::mlir::DataLayoutEntryInterface entry);
    static inline std::optional<Attribute> getDevicePropertyValue(::mlir::DataLayoutEntryInterface entry);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::DataLayoutOpInterface;
    FallbackModel() : Concept{getDataLayoutSpec, getTargetSystemSpec, getTypeSize, getTypeSizeInBits, getTypeABIAlignment, getTypePreferredAlignment, getIndexBitwidth, getEndianness, getDefaultMemorySpace, getAllocaMemorySpace, getManglingMode, getProgramMemorySpace, getGlobalMemorySpace, getStackAlignment, getFunctionPointerAlignment, getLegalIntWidths, getDevicePropertyValue} {}

    static inline ::mlir::DataLayoutSpecInterface getDataLayoutSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::TargetSystemSpecInterface getTargetSystemSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::TypeSize getTypeSize(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline ::llvm::TypeSize getTypeSizeInBits(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline uint64_t getTypeABIAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline uint64_t getTypePreferredAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline std::optional<uint64_t> getIndexBitwidth(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline ::mlir::Attribute getEndianness(::mlir::DataLayoutEntryInterface entry);
    static inline ::mlir::Attribute getDefaultMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static inline ::mlir::Attribute getAllocaMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static inline ::mlir::Attribute getManglingMode(::mlir::DataLayoutEntryInterface entry);
    static inline ::mlir::Attribute getProgramMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static inline ::mlir::Attribute getGlobalMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static inline uint64_t getStackAlignment(::mlir::DataLayoutEntryInterface entry);
    static inline Attribute getFunctionPointerAlignment(::mlir::DataLayoutEntryInterface entry);
    static inline Attribute getLegalIntWidths(::mlir::DataLayoutEntryInterface entry);
    static inline std::optional<Attribute> getDevicePropertyValue(::mlir::DataLayoutEntryInterface entry);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    static ::llvm::TypeSize getTypeSize(::mlir::Type type, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params);
    static ::llvm::TypeSize getTypeSizeInBits(::mlir::Type type, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params);
    static uint64_t getTypeABIAlignment(::mlir::Type type, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params);
    static uint64_t getTypePreferredAlignment(::mlir::Type type, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params);
    static std::optional<uint64_t> getIndexBitwidth(::mlir::Type type, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params);
    static ::mlir::Attribute getEndianness(::mlir::DataLayoutEntryInterface entry);
    static ::mlir::Attribute getDefaultMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static ::mlir::Attribute getAllocaMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static ::mlir::Attribute getManglingMode(::mlir::DataLayoutEntryInterface entry);
    static ::mlir::Attribute getProgramMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static ::mlir::Attribute getGlobalMemorySpace(::mlir::DataLayoutEntryInterface entry);
    static uint64_t getStackAlignment(::mlir::DataLayoutEntryInterface entry);
    static Attribute getFunctionPointerAlignment(::mlir::DataLayoutEntryInterface entry);
    static Attribute getLegalIntWidths(::mlir::DataLayoutEntryInterface entry);
    static std::optional<Attribute> getDevicePropertyValue(::mlir::DataLayoutEntryInterface entry);
  };
};
template <typename ConcreteOp>
struct DataLayoutOpInterfaceTrait;

} // namespace detail
class DataLayoutOpInterface : public ::mlir::OpInterface<DataLayoutOpInterface, detail::DataLayoutOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<DataLayoutOpInterface, detail::DataLayoutOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::DataLayoutOpInterfaceTrait<ConcreteOp> {};

  /// Returns the data layout specification for this op, or null if it does not exist.
  ::mlir::DataLayoutSpecInterface getDataLayoutSpec();

  /// Returns the target system desc specification for this op, or null if it does not exist.
  ::mlir::TargetSystemSpecInterface getTargetSystemSpec();

  /// Returns the size of the given type computed using the relevant entries. The data layout object can be used for recursive queries.
  ::llvm::TypeSize getTypeSize(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);

  /// Returns the size of the given type in bits computed using the relevant entries. The data layout object can be used for recursive queries.
  ::llvm::TypeSize getTypeSizeInBits(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);

  /// Returns the alignment required by the ABI for the given type computed using the relevant entries. The data layout object can be used for recursive queries.
  uint64_t getTypeABIAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);

  /// Returns the alignment preferred by the given type computed using the relevant entries. The data layoutobject can be used for recursive queries.
  uint64_t getTypePreferredAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);

  /// Returns the bitwidth that should be used when performing index computations for the type computed using the relevant entries. The data layout object can be used for recursive queries.
  std::optional<uint64_t> getIndexBitwidth(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);

  /// Returns the endianness used by the ABI computed using the relevant entries. The data layout object can be used for recursive queries.
  ::mlir::Attribute getEndianness(::mlir::DataLayoutEntryInterface entry);

  /// Returns the memory space used by the ABI computed using the relevant entries. The data layout object can be used for recursive queries.
  ::mlir::Attribute getDefaultMemorySpace(::mlir::DataLayoutEntryInterface entry);

  /// Returns the memory space used by the ABI computed using the relevant entries. The data layout object can be used for recursive queries.
  ::mlir::Attribute getAllocaMemorySpace(::mlir::DataLayoutEntryInterface entry);

  /// Returns the mangling mode computed using the relevant entries. The data layout object can be used for recursive queries.
  ::mlir::Attribute getManglingMode(::mlir::DataLayoutEntryInterface entry);

  /// Returns the memory space used by the ABI computed using the relevant entries. The data layout object can be used for recursive queries.
  ::mlir::Attribute getProgramMemorySpace(::mlir::DataLayoutEntryInterface entry);

  /// Returns the memory space used by the ABI computed using the relevant entries. The data layout object can be used for recursive queries.
  ::mlir::Attribute getGlobalMemorySpace(::mlir::DataLayoutEntryInterface entry);

  /// Returns the natural stack alignment in bits computed using the relevant entries. The data layout object can be used for recursive queries.
  uint64_t getStackAlignment(::mlir::DataLayoutEntryInterface entry);

  /// Returns the function pointer alignment in bits computed using the relevant entries. The data layout object can be used for recursive queries.
  Attribute getFunctionPointerAlignment(::mlir::DataLayoutEntryInterface entry);

  /// Returns the legal int widths, each width in bits computed using the relevant entries. The data layout object can be used for recursive queries.
  Attribute getLegalIntWidths(::mlir::DataLayoutEntryInterface entry);

  /// Returns the value of the property, if the property is defined. Otherwise, it returns std::nullopt.
  std::optional<Attribute> getDevicePropertyValue(::mlir::DataLayoutEntryInterface entry);
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteOp>
  struct DataLayoutOpInterfaceTrait : public ::mlir::OpInterface<DataLayoutOpInterface, detail::DataLayoutOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns the size of the given type computed using the relevant entries. The data layout object can be used for recursive queries.
    static ::llvm::TypeSize getTypeSize(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
      ::llvm::TypeSize bits = ConcreteOp::getTypeSizeInBits(type, dataLayout, params);
        return ::mlir::detail::divideCeil(bits, 8u);
    }

    /// Returns the size of the given type in bits computed using the relevant entries. The data layout object can be used for recursive queries.
    static ::llvm::TypeSize getTypeSizeInBits(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
      return ::mlir::detail::getDefaultTypeSizeInBits(type, dataLayout,
                                                        params);
    }

    /// Returns the alignment required by the ABI for the given type computed using the relevant entries. The data layout object can be used for recursive queries.
    static uint64_t getTypeABIAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
      return ::mlir::detail::getDefaultABIAlignment(type, dataLayout, params);
    }

    /// Returns the alignment preferred by the given type computed using the relevant entries. The data layoutobject can be used for recursive queries.
    static uint64_t getTypePreferredAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
      return ::mlir::detail::getDefaultPreferredAlignment(type, dataLayout,
                                                            params);
    }

    /// Returns the bitwidth that should be used when performing index computations for the type computed using the relevant entries. The data layout object can be used for recursive queries.
    static std::optional<uint64_t> getIndexBitwidth(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
      return ::mlir::detail::getDefaultIndexBitwidth(type, dataLayout,
                                                       params);
    }

    /// Returns the endianness used by the ABI computed using the relevant entries. The data layout object can be used for recursive queries.
    static ::mlir::Attribute getEndianness(::mlir::DataLayoutEntryInterface entry) {
      return ::mlir::detail::getDefaultEndianness(entry);
    }

    /// Returns the memory space used by the ABI computed using the relevant entries. The data layout object can be used for recursive queries.
    static ::mlir::Attribute getDefaultMemorySpace(::mlir::DataLayoutEntryInterface entry) {
      return ::mlir::detail::getDefaultMemorySpace(entry);
    }

    /// Returns the memory space used by the ABI computed using the relevant entries. The data layout object can be used for recursive queries.
    static ::mlir::Attribute getAllocaMemorySpace(::mlir::DataLayoutEntryInterface entry) {
      return ::mlir::detail::getDefaultAllocaMemorySpace(entry);
    }

    /// Returns the mangling mode computed using the relevant entries. The data layout object can be used for recursive queries.
    static ::mlir::Attribute getManglingMode(::mlir::DataLayoutEntryInterface entry) {
      return ::mlir::detail::getDefaultManglingMode(entry);
    }

    /// Returns the memory space used by the ABI computed using the relevant entries. The data layout object can be used for recursive queries.
    static ::mlir::Attribute getProgramMemorySpace(::mlir::DataLayoutEntryInterface entry) {
      return ::mlir::detail::getDefaultProgramMemorySpace(entry);
    }

    /// Returns the memory space used by the ABI computed using the relevant entries. The data layout object can be used for recursive queries.
    static ::mlir::Attribute getGlobalMemorySpace(::mlir::DataLayoutEntryInterface entry) {
      return ::mlir::detail::getDefaultGlobalMemorySpace(entry);
    }

    /// Returns the natural stack alignment in bits computed using the relevant entries. The data layout object can be used for recursive queries.
    static uint64_t getStackAlignment(::mlir::DataLayoutEntryInterface entry) {
      return ::mlir::detail::getDefaultStackAlignment(entry);
    }

    /// Returns the function pointer alignment in bits computed using the relevant entries. The data layout object can be used for recursive queries.
    static Attribute getFunctionPointerAlignment(::mlir::DataLayoutEntryInterface entry) {
      return ::mlir::detail::getDefaultFunctionPointerAlignment(entry);
    }

    /// Returns the legal int widths, each width in bits computed using the relevant entries. The data layout object can be used for recursive queries.
    static Attribute getLegalIntWidths(::mlir::DataLayoutEntryInterface entry) {
      return ::mlir::detail::getDefaultLegalIntWidths(entry);
    }

    /// Returns the value of the property, if the property is defined. Otherwise, it returns std::nullopt.
    static std::optional<Attribute> getDevicePropertyValue(::mlir::DataLayoutEntryInterface entry) {
      return ::mlir::detail::getDevicePropertyValue(entry);
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return ::mlir::detail::verifyDataLayoutOp(op);
    }
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteOp>
::mlir::DataLayoutSpecInterface detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getDataLayoutSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDataLayoutSpec();
}
template<typename ConcreteOp>
::mlir::TargetSystemSpecInterface detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTargetSystemSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getTargetSystemSpec();
}
template<typename ConcreteOp>
::llvm::TypeSize detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTypeSize(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return ConcreteOp::getTypeSize(type, dataLayout, params);
}
template<typename ConcreteOp>
::llvm::TypeSize detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTypeSizeInBits(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return ConcreteOp::getTypeSizeInBits(type, dataLayout, params);
}
template<typename ConcreteOp>
uint64_t detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTypeABIAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return ConcreteOp::getTypeABIAlignment(type, dataLayout, params);
}
template<typename ConcreteOp>
uint64_t detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTypePreferredAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return ConcreteOp::getTypePreferredAlignment(type, dataLayout, params);
}
template<typename ConcreteOp>
std::optional<uint64_t> detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getIndexBitwidth(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return ConcreteOp::getIndexBitwidth(type, dataLayout, params);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getEndianness(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getEndianness(entry);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getDefaultMemorySpace(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getDefaultMemorySpace(entry);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getAllocaMemorySpace(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getAllocaMemorySpace(entry);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getManglingMode(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getManglingMode(entry);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getProgramMemorySpace(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getProgramMemorySpace(entry);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getGlobalMemorySpace(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getGlobalMemorySpace(entry);
}
template<typename ConcreteOp>
uint64_t detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getStackAlignment(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getStackAlignment(entry);
}
template<typename ConcreteOp>
Attribute detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getFunctionPointerAlignment(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getFunctionPointerAlignment(entry);
}
template<typename ConcreteOp>
Attribute detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getLegalIntWidths(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getLegalIntWidths(entry);
}
template<typename ConcreteOp>
std::optional<Attribute> detail::DataLayoutOpInterfaceInterfaceTraits::Model<ConcreteOp>::getDevicePropertyValue(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getDevicePropertyValue(entry);
}
template<typename ConcreteOp>
::mlir::DataLayoutSpecInterface detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getDataLayoutSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDataLayoutSpec(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::TargetSystemSpecInterface detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTargetSystemSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getTargetSystemSpec(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::TypeSize detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTypeSize(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return ConcreteOp::getTypeSize(type, dataLayout, params);
}
template<typename ConcreteOp>
::llvm::TypeSize detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTypeSizeInBits(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return ConcreteOp::getTypeSizeInBits(type, dataLayout, params);
}
template<typename ConcreteOp>
uint64_t detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTypeABIAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return ConcreteOp::getTypeABIAlignment(type, dataLayout, params);
}
template<typename ConcreteOp>
uint64_t detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTypePreferredAlignment(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return ConcreteOp::getTypePreferredAlignment(type, dataLayout, params);
}
template<typename ConcreteOp>
std::optional<uint64_t> detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getIndexBitwidth(::mlir::Type type, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return ConcreteOp::getIndexBitwidth(type, dataLayout, params);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getEndianness(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getEndianness(entry);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getDefaultMemorySpace(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getDefaultMemorySpace(entry);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getAllocaMemorySpace(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getAllocaMemorySpace(entry);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getManglingMode(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getManglingMode(entry);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getProgramMemorySpace(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getProgramMemorySpace(entry);
}
template<typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getGlobalMemorySpace(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getGlobalMemorySpace(entry);
}
template<typename ConcreteOp>
uint64_t detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getStackAlignment(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getStackAlignment(entry);
}
template<typename ConcreteOp>
Attribute detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getFunctionPointerAlignment(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getFunctionPointerAlignment(entry);
}
template<typename ConcreteOp>
Attribute detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getLegalIntWidths(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getLegalIntWidths(entry);
}
template<typename ConcreteOp>
std::optional<Attribute> detail::DataLayoutOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getDevicePropertyValue(::mlir::DataLayoutEntryInterface entry) {
  return ConcreteOp::getDevicePropertyValue(entry);
}
template<typename ConcreteModel, typename ConcreteOp>
::llvm::TypeSize detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getTypeSize(::mlir::Type type, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) {
::llvm::TypeSize bits = ConcreteOp::getTypeSizeInBits(type, dataLayout, params);
        return ::mlir::detail::divideCeil(bits, 8u);
}
template<typename ConcreteModel, typename ConcreteOp>
::llvm::TypeSize detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getTypeSizeInBits(::mlir::Type type, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) {
return ::mlir::detail::getDefaultTypeSizeInBits(type, dataLayout,
                                                        params);
}
template<typename ConcreteModel, typename ConcreteOp>
uint64_t detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getTypeABIAlignment(::mlir::Type type, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) {
return ::mlir::detail::getDefaultABIAlignment(type, dataLayout, params);
}
template<typename ConcreteModel, typename ConcreteOp>
uint64_t detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getTypePreferredAlignment(::mlir::Type type, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) {
return ::mlir::detail::getDefaultPreferredAlignment(type, dataLayout,
                                                            params);
}
template<typename ConcreteModel, typename ConcreteOp>
std::optional<uint64_t> detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getIndexBitwidth(::mlir::Type type, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) {
return ::mlir::detail::getDefaultIndexBitwidth(type, dataLayout,
                                                       params);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getEndianness(::mlir::DataLayoutEntryInterface entry) {
return ::mlir::detail::getDefaultEndianness(entry);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDefaultMemorySpace(::mlir::DataLayoutEntryInterface entry) {
return ::mlir::detail::getDefaultMemorySpace(entry);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getAllocaMemorySpace(::mlir::DataLayoutEntryInterface entry) {
return ::mlir::detail::getDefaultAllocaMemorySpace(entry);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getManglingMode(::mlir::DataLayoutEntryInterface entry) {
return ::mlir::detail::getDefaultManglingMode(entry);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getProgramMemorySpace(::mlir::DataLayoutEntryInterface entry) {
return ::mlir::detail::getDefaultProgramMemorySpace(entry);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Attribute detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getGlobalMemorySpace(::mlir::DataLayoutEntryInterface entry) {
return ::mlir::detail::getDefaultGlobalMemorySpace(entry);
}
template<typename ConcreteModel, typename ConcreteOp>
uint64_t detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getStackAlignment(::mlir::DataLayoutEntryInterface entry) {
return ::mlir::detail::getDefaultStackAlignment(entry);
}
template<typename ConcreteModel, typename ConcreteOp>
Attribute detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getFunctionPointerAlignment(::mlir::DataLayoutEntryInterface entry) {
return ::mlir::detail::getDefaultFunctionPointerAlignment(entry);
}
template<typename ConcreteModel, typename ConcreteOp>
Attribute detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getLegalIntWidths(::mlir::DataLayoutEntryInterface entry) {
return ::mlir::detail::getDefaultLegalIntWidths(entry);
}
template<typename ConcreteModel, typename ConcreteOp>
std::optional<Attribute> detail::DataLayoutOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDevicePropertyValue(::mlir::DataLayoutEntryInterface entry) {
return ::mlir::detail::getDevicePropertyValue(entry);
}

} // namespace mlir
