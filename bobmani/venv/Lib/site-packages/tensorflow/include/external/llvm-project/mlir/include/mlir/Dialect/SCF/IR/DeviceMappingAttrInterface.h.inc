/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// Attribute interface describing how to map a region to a processing unit.
/// 
///     It is intended to be a generic mechanism for binding regions to execution
///     units of an actual or virtual device. Each device first expresses its own
///     mappings, and those mappings must implement this interface. These mappings
///     can be used by the device-specific code generators and the desired regions
///     can be connected to the given processing unit.
/// 
///     Currently, `scf.forall` uses this interface to express the mapping
///     of the loops it contains to the GPU's parallelism units such as threads and
///     thread blocks.
class DeviceMappingAttrInterface;

} // namespace mlir
namespace mlir {

/// Attribute interface describing how to filter the processing units that a
///     region is mapped to.
/// 
///     For instance, consider the following example mask which specifies processing
///     units 2, 4 and 5 are active:
///     ```
///               8       4       0
///       mask  : 0 0 0 1 1 0 1 0 0
///     ```
///     The logical ID for an active processing unit is defined as its position
///     relative to the other active processing units. In this example, we have:
///     ```
///       Processing Unit    LogicalID
///               0             N/A
///               1             N/A
///               2              0
///               3             N/A
///               4              1
///               5              2
///               6             N/A
///               7             N/A
///     ```
class DeviceMaskingAttrInterface;

} // namespace mlir
namespace mlir {

/// Attribute interface describing how to map a region to a processing unit.
/// 
///     It is intended to be a generic mechanism for binding regions to execution
///     units of an actual or virtual device. Each device first expresses its own
///     mappings, and those mappings must implement this interface. These mappings
///     can be used by the device-specific code generators and the desired regions
///     can be connected to the given processing unit.
/// 
///     Currently, `scf.forall` uses this interface to express the mapping
///     of the loops it contains to the GPU's parallelism units such as threads and
///     thread blocks.
namespace detail {
struct DeviceMappingAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    int64_t (*getMappingId)(const Concept *impl, ::mlir::Attribute );
    bool (*isLinearMapping)(const Concept *impl, ::mlir::Attribute );
    int64_t (*getRelativeIndex)(const Concept *impl, ::mlir::Attribute );
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::DeviceMappingAttrInterface;
    Model() : Concept{getMappingId, isLinearMapping, getRelativeIndex} {}

    static inline int64_t getMappingId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline bool isLinearMapping(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline int64_t getRelativeIndex(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::DeviceMappingAttrInterface;
    FallbackModel() : Concept{getMappingId, isLinearMapping, getRelativeIndex} {}

    static inline int64_t getMappingId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline bool isLinearMapping(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline int64_t getRelativeIndex(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct DeviceMappingAttrInterfaceTrait;

} // namespace detail
class DeviceMappingAttrInterface : public ::mlir::AttributeInterface<DeviceMappingAttrInterface, detail::DeviceMappingAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<DeviceMappingAttrInterface, detail::DeviceMappingAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::DeviceMappingAttrInterfaceTrait<ConcreteAttr> {};

  /// Return mapping as an integer from the attribute.
  int64_t getMappingId() const;

  /// Return true if the attribute specifies a linear mapping
  bool isLinearMapping() const;

  /// Return the [0..n) relative index of the attribute depending on its group.
  /// This can be used to index into a contiguous array.
  int64_t getRelativeIndex() const;
};

} // namespace mlir
namespace mlir {

/// Attribute interface describing how to filter the processing units that a
///     region is mapped to.
/// 
///     For instance, consider the following example mask which specifies processing
///     units 2, 4 and 5 are active:
///     ```
///               8       4       0
///       mask  : 0 0 0 1 1 0 1 0 0
///     ```
///     The logical ID for an active processing unit is defined as its position
///     relative to the other active processing units. In this example, we have:
///     ```
///       Processing Unit    LogicalID
///               0             N/A
///               1             N/A
///               2              0
///               3             N/A
///               4              1
///               5              2
///               6             N/A
///               7             N/A
///     ```
namespace detail {
struct DeviceMaskingAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    Value (*createLogicalLinearMappingId)(const Concept *impl, ::mlir::Attribute , OpBuilder&, Value);
    Value (*createIsActiveIdPredicate)(const Concept *impl, ::mlir::Attribute , OpBuilder&, Value);
    int64_t (*getMaxNumPhysicalIds)(const Concept *impl, ::mlir::Attribute );
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::DeviceMaskingAttrInterface;
    Model() : Concept{createLogicalLinearMappingId, createIsActiveIdPredicate, getMaxNumPhysicalIds} {}

    static inline Value createLogicalLinearMappingId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, OpBuilder& builder, Value physicalLinearMappingId);
    static inline Value createIsActiveIdPredicate(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, OpBuilder& builder, Value physicalLinearMappingId);
    static inline int64_t getMaxNumPhysicalIds(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::DeviceMaskingAttrInterface;
    FallbackModel() : Concept{createLogicalLinearMappingId, createIsActiveIdPredicate, getMaxNumPhysicalIds} {}

    static inline Value createLogicalLinearMappingId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, OpBuilder& builder, Value physicalLinearMappingId);
    static inline Value createIsActiveIdPredicate(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, OpBuilder& builder, Value physicalLinearMappingId);
    static inline int64_t getMaxNumPhysicalIds(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct DeviceMaskingAttrInterfaceTrait;

} // namespace detail
class DeviceMaskingAttrInterface : public ::mlir::AttributeInterface<DeviceMaskingAttrInterface, detail::DeviceMaskingAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<DeviceMaskingAttrInterface, detail::DeviceMaskingAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::DeviceMaskingAttrInterfaceTrait<ConcreteAttr> {};

  /// Create the logical active id for a given physical id.
  /// Expects a physicalLinearMappingId of I64Type.
  Value createLogicalLinearMappingId(OpBuilder& builder, Value physicalLinearMappingId) const;

  /// Return the dynamic condition determining whether a given physical id is
  /// active under the mask.
  /// Expects a physicalLinearMappingId of I64Type.
  Value createIsActiveIdPredicate(OpBuilder& builder, Value physicalLinearMappingId) const;

  /// Return the maximal number of pysical ids supported.
  /// This is to account for temporary implementation limitations (e.g. i64)
  /// and fail gracefully with actionnable error messages.
  int64_t getMaxNumPhysicalIds() const;
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteAttr>
  struct DeviceMappingAttrInterfaceTrait : public ::mlir::AttributeInterface<DeviceMappingAttrInterface, detail::DeviceMappingAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteAttr>
  struct DeviceMaskingAttrInterfaceTrait : public ::mlir::AttributeInterface<DeviceMaskingAttrInterface, detail::DeviceMaskingAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteAttr>
int64_t detail::DeviceMappingAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getMappingId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getMappingId();
}
template<typename ConcreteAttr>
bool detail::DeviceMappingAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::isLinearMapping(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).isLinearMapping();
}
template<typename ConcreteAttr>
int64_t detail::DeviceMappingAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getRelativeIndex(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getRelativeIndex();
}
template<typename ConcreteAttr>
int64_t detail::DeviceMappingAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getMappingId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getMappingId(tablegen_opaque_val);
}
template<typename ConcreteAttr>
bool detail::DeviceMappingAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::isLinearMapping(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->isLinearMapping(tablegen_opaque_val);
}
template<typename ConcreteAttr>
int64_t detail::DeviceMappingAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getRelativeIndex(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getRelativeIndex(tablegen_opaque_val);
}

} // namespace mlir
namespace mlir {

template<typename ConcreteAttr>
Value detail::DeviceMaskingAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::createLogicalLinearMappingId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, OpBuilder& builder, Value physicalLinearMappingId) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).createLogicalLinearMappingId(builder, physicalLinearMappingId);
}
template<typename ConcreteAttr>
Value detail::DeviceMaskingAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::createIsActiveIdPredicate(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, OpBuilder& builder, Value physicalLinearMappingId) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).createIsActiveIdPredicate(builder, physicalLinearMappingId);
}
template<typename ConcreteAttr>
int64_t detail::DeviceMaskingAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getMaxNumPhysicalIds(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getMaxNumPhysicalIds();
}
template<typename ConcreteAttr>
Value detail::DeviceMaskingAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::createLogicalLinearMappingId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, OpBuilder& builder, Value physicalLinearMappingId) {
  return static_cast<const ConcreteAttr *>(impl)->createLogicalLinearMappingId(tablegen_opaque_val, builder, physicalLinearMappingId);
}
template<typename ConcreteAttr>
Value detail::DeviceMaskingAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::createIsActiveIdPredicate(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, OpBuilder& builder, Value physicalLinearMappingId) {
  return static_cast<const ConcreteAttr *>(impl)->createIsActiveIdPredicate(tablegen_opaque_val, builder, physicalLinearMappingId);
}
template<typename ConcreteAttr>
int64_t detail::DeviceMaskingAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getMaxNumPhysicalIds(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getMaxNumPhysicalIds(tablegen_opaque_val);
}

} // namespace mlir
