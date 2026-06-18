/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::omp {

/// OpenMP operations that define entry block arguments as part of the
///     representation of its clauses.
class BlockArgOpenMPOpInterface;

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations whose region will be outlined will implement this
///     interface.
class OutlineableOpenMPOpInterface;

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations which own a list of omp::MapInfoOp's implement this interface
///     to allow generic access to deal with map operands to more easily manipulate
///     this class of operations.
class MapClauseOwningOpInterface;

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations that wrap a single loop nest. They must only contain a
///     single region with a single block in which there's a single operation and a
///     terminator. That nested operation must be another loop wrapper or an
///     `omp.loop_nest`.
/// 
///     Operation-specific verifiers should make the following checks in their
///     verifier, additionally to what the interface itself checks:
///       - If `getNestedWrapper() != nullptr`, is the type of the nested wrapper
///       allowed in that context? This check might require looking at the parent as
///       well.
///       - If the operation is a `ComposableOpInterface`, check that it is
///       consistent with the potential existence of a `LoopWrapperInterface` parent
///       and whether `getNestedWrapper() != nullptr`.
class LoopWrapperInterface;

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations that can represent a single leaf of a composite OpenMP
///     construct.
class ComposableOpInterface;

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations that support declare target have this interface.
///     For example, FuncOp's and llvm.GlobalOp/fir.GlobalOp's. This
///     interface allows simple manipulation and introspection of the
///     declare target attribute that can be applied to these operations.
class DeclareTargetInterface;

} // namespace mlir::omp
namespace mlir::omp {

/// Operations that represent a module for offloading (host or device)
///     should have this interface.
class OffloadModuleInterface;

} // namespace mlir::omp
namespace mlir::omp {

/// Methods that are common for OpenMP loop transformation operations.
class LoopTransformationInterface;

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations that define entry block arguments as part of the
///     representation of its clauses.
namespace detail {
struct BlockArgOpenMPOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::OperandRange (*getHasDeviceAddrVars)(const Concept *impl, ::mlir::Operation *);
    ::mlir::OperandRange (*getHostEvalVars)(const Concept *impl, ::mlir::Operation *);
    ::mlir::OperandRange (*getInReductionVars)(const Concept *impl, ::mlir::Operation *);
    ::mlir::OperandRange (*getMapVars)(const Concept *impl, ::mlir::Operation *);
    ::mlir::OperandRange (*getPrivateVars)(const Concept *impl, ::mlir::Operation *);
    ::mlir::OperandRange (*getReductionVars)(const Concept *impl, ::mlir::Operation *);
    ::mlir::OperandRange (*getTaskReductionVars)(const Concept *impl, ::mlir::Operation *);
    ::mlir::OperandRange (*getUseDeviceAddrVars)(const Concept *impl, ::mlir::Operation *);
    ::mlir::OperandRange (*getUseDevicePtrVars)(const Concept *impl, ::mlir::Operation *);
    unsigned (*numHasDeviceAddrBlockArgs)(const Concept *impl, ::mlir::Operation *);
    unsigned (*numHostEvalBlockArgs)(const Concept *impl, ::mlir::Operation *);
    unsigned (*numInReductionBlockArgs)(const Concept *impl, ::mlir::Operation *);
    unsigned (*numMapBlockArgs)(const Concept *impl, ::mlir::Operation *);
    unsigned (*numPrivateBlockArgs)(const Concept *impl, ::mlir::Operation *);
    unsigned (*numReductionBlockArgs)(const Concept *impl, ::mlir::Operation *);
    unsigned (*numTaskReductionBlockArgs)(const Concept *impl, ::mlir::Operation *);
    unsigned (*numUseDeviceAddrBlockArgs)(const Concept *impl, ::mlir::Operation *);
    unsigned (*numUseDevicePtrBlockArgs)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getHasDeviceAddrBlockArgsStart)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getHostEvalBlockArgsStart)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getInReductionBlockArgsStart)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getMapBlockArgsStart)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getPrivateBlockArgsStart)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getReductionBlockArgsStart)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getTaskReductionBlockArgsStart)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getUseDeviceAddrBlockArgsStart)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getUseDevicePtrBlockArgsStart)(const Concept *impl, ::mlir::Operation *);
    ::llvm::MutableArrayRef<::mlir::BlockArgument> (*getHasDeviceAddrBlockArgs)(const Concept *impl, ::mlir::Operation *);
    ::llvm::MutableArrayRef<::mlir::BlockArgument> (*getHostEvalBlockArgs)(const Concept *impl, ::mlir::Operation *);
    ::llvm::MutableArrayRef<::mlir::BlockArgument> (*getInReductionBlockArgs)(const Concept *impl, ::mlir::Operation *);
    ::llvm::MutableArrayRef<::mlir::BlockArgument> (*getMapBlockArgs)(const Concept *impl, ::mlir::Operation *);
    ::llvm::MutableArrayRef<::mlir::BlockArgument> (*getPrivateBlockArgs)(const Concept *impl, ::mlir::Operation *);
    ::llvm::MutableArrayRef<::mlir::BlockArgument> (*getReductionBlockArgs)(const Concept *impl, ::mlir::Operation *);
    ::llvm::MutableArrayRef<::mlir::BlockArgument> (*getTaskReductionBlockArgs)(const Concept *impl, ::mlir::Operation *);
    ::llvm::MutableArrayRef<::mlir::BlockArgument> (*getUseDeviceAddrBlockArgs)(const Concept *impl, ::mlir::Operation *);
    ::llvm::MutableArrayRef<::mlir::BlockArgument> (*getUseDevicePtrBlockArgs)(const Concept *impl, ::mlir::Operation *);
    unsigned (*numClauseBlockArgs)(const Concept *impl, ::mlir::Operation *);
    void (*getBlockArgsPairs)(const Concept *impl, ::mlir::Operation *, ::llvm::SmallVectorImpl<std::pair<::mlir::Value, ::mlir::BlockArgument>> &);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::omp::BlockArgOpenMPOpInterface;
    Model() : Concept{getHasDeviceAddrVars, getHostEvalVars, getInReductionVars, getMapVars, getPrivateVars, getReductionVars, getTaskReductionVars, getUseDeviceAddrVars, getUseDevicePtrVars, numHasDeviceAddrBlockArgs, numHostEvalBlockArgs, numInReductionBlockArgs, numMapBlockArgs, numPrivateBlockArgs, numReductionBlockArgs, numTaskReductionBlockArgs, numUseDeviceAddrBlockArgs, numUseDevicePtrBlockArgs, getHasDeviceAddrBlockArgsStart, getHostEvalBlockArgsStart, getInReductionBlockArgsStart, getMapBlockArgsStart, getPrivateBlockArgsStart, getReductionBlockArgsStart, getTaskReductionBlockArgsStart, getUseDeviceAddrBlockArgsStart, getUseDevicePtrBlockArgsStart, getHasDeviceAddrBlockArgs, getHostEvalBlockArgs, getInReductionBlockArgs, getMapBlockArgs, getPrivateBlockArgs, getReductionBlockArgs, getTaskReductionBlockArgs, getUseDeviceAddrBlockArgs, getUseDevicePtrBlockArgs, numClauseBlockArgs, getBlockArgsPairs} {}

    static inline ::mlir::OperandRange getHasDeviceAddrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getHostEvalVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getInReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getMapVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getPrivateVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getTaskReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getUseDeviceAddrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getUseDevicePtrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numHasDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numHostEvalBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numInReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numMapBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numPrivateBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numTaskReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numUseDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numUseDevicePtrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getHasDeviceAddrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getHostEvalBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getInReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getMapBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getPrivateBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getTaskReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getUseDeviceAddrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getUseDevicePtrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getHasDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getHostEvalBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getInReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getMapBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getPrivateBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getTaskReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getUseDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getUseDevicePtrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numClauseBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void getBlockArgsPairs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::SmallVectorImpl<std::pair<::mlir::Value, ::mlir::BlockArgument>> & pairs);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::omp::BlockArgOpenMPOpInterface;
    FallbackModel() : Concept{getHasDeviceAddrVars, getHostEvalVars, getInReductionVars, getMapVars, getPrivateVars, getReductionVars, getTaskReductionVars, getUseDeviceAddrVars, getUseDevicePtrVars, numHasDeviceAddrBlockArgs, numHostEvalBlockArgs, numInReductionBlockArgs, numMapBlockArgs, numPrivateBlockArgs, numReductionBlockArgs, numTaskReductionBlockArgs, numUseDeviceAddrBlockArgs, numUseDevicePtrBlockArgs, getHasDeviceAddrBlockArgsStart, getHostEvalBlockArgsStart, getInReductionBlockArgsStart, getMapBlockArgsStart, getPrivateBlockArgsStart, getReductionBlockArgsStart, getTaskReductionBlockArgsStart, getUseDeviceAddrBlockArgsStart, getUseDevicePtrBlockArgsStart, getHasDeviceAddrBlockArgs, getHostEvalBlockArgs, getInReductionBlockArgs, getMapBlockArgs, getPrivateBlockArgs, getReductionBlockArgs, getTaskReductionBlockArgs, getUseDeviceAddrBlockArgs, getUseDevicePtrBlockArgs, numClauseBlockArgs, getBlockArgsPairs} {}

    static inline ::mlir::OperandRange getHasDeviceAddrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getHostEvalVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getInReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getMapVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getPrivateVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getTaskReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getUseDeviceAddrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::OperandRange getUseDevicePtrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numHasDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numHostEvalBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numInReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numMapBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numPrivateBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numTaskReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numUseDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numUseDevicePtrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getHasDeviceAddrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getHostEvalBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getInReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getMapBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getPrivateBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getTaskReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getUseDeviceAddrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getUseDevicePtrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getHasDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getHostEvalBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getInReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getMapBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getPrivateBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getTaskReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getUseDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::MutableArrayRef<::mlir::BlockArgument> getUseDevicePtrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned numClauseBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void getBlockArgsPairs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::SmallVectorImpl<std::pair<::mlir::Value, ::mlir::BlockArgument>> & pairs);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::mlir::OperandRange getHasDeviceAddrVars(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::OperandRange getHostEvalVars(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::OperandRange getInReductionVars(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::OperandRange getMapVars(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::OperandRange getPrivateVars(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::OperandRange getReductionVars(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::OperandRange getTaskReductionVars(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::OperandRange getUseDeviceAddrVars(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::OperandRange getUseDevicePtrVars(::mlir::Operation *tablegen_opaque_val) const;
    unsigned numHasDeviceAddrBlockArgs(::mlir::Operation *tablegen_opaque_val) const;
    unsigned numHostEvalBlockArgs(::mlir::Operation *tablegen_opaque_val) const;
    unsigned numInReductionBlockArgs(::mlir::Operation *tablegen_opaque_val) const;
    unsigned numMapBlockArgs(::mlir::Operation *tablegen_opaque_val) const;
    unsigned numPrivateBlockArgs(::mlir::Operation *tablegen_opaque_val) const;
    unsigned numReductionBlockArgs(::mlir::Operation *tablegen_opaque_val) const;
    unsigned numTaskReductionBlockArgs(::mlir::Operation *tablegen_opaque_val) const;
    unsigned numUseDeviceAddrBlockArgs(::mlir::Operation *tablegen_opaque_val) const;
    unsigned numUseDevicePtrBlockArgs(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct BlockArgOpenMPOpInterfaceTrait;

} // namespace detail
class BlockArgOpenMPOpInterface : public ::mlir::OpInterface<BlockArgOpenMPOpInterface, detail::BlockArgOpenMPOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<BlockArgOpenMPOpInterface, detail::BlockArgOpenMPOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::BlockArgOpenMPOpInterfaceTrait<ConcreteOp> {};

  /// Get operation operands associated to `has_device_addr`.
  ::mlir::OperandRange getHasDeviceAddrVars();

  /// Get operation operands associated to `host_eval`.
  ::mlir::OperandRange getHostEvalVars();

  /// Get operation operands associated to `in_reduction`.
  ::mlir::OperandRange getInReductionVars();

  /// Get operation operands associated to `map`.
  ::mlir::OperandRange getMapVars();

  /// Get operation operands associated to `private`.
  ::mlir::OperandRange getPrivateVars();

  /// Get operation operands associated to `reduction`.
  ::mlir::OperandRange getReductionVars();

  /// Get operation operands associated to `task_reduction`.
  ::mlir::OperandRange getTaskReductionVars();

  /// Get operation operands associated to `use_device_addr`.
  ::mlir::OperandRange getUseDeviceAddrVars();

  /// Get operation operands associated to `use_device_ptr`.
  ::mlir::OperandRange getUseDevicePtrVars();

  /// Get number of block arguments defined by `has_device_addr`.
  unsigned numHasDeviceAddrBlockArgs();

  /// Get number of block arguments defined by `host_eval`.
  unsigned numHostEvalBlockArgs();

  /// Get number of block arguments defined by `in_reduction`.
  unsigned numInReductionBlockArgs();

  /// Get number of block arguments defined by `map`.
  unsigned numMapBlockArgs();

  /// Get number of block arguments defined by `private`.
  unsigned numPrivateBlockArgs();

  /// Get number of block arguments defined by `reduction`.
  unsigned numReductionBlockArgs();

  /// Get number of block arguments defined by `task_reduction`.
  unsigned numTaskReductionBlockArgs();

  /// Get number of block arguments defined by `use_device_addr`.
  unsigned numUseDeviceAddrBlockArgs();

  /// Get number of block arguments defined by `use_device_ptr`.
  unsigned numUseDevicePtrBlockArgs();

  /// Get start index of block arguments defined by `has_device_addr`.
  unsigned getHasDeviceAddrBlockArgsStart();

  /// Get start index of block arguments defined by `host_eval`.
  unsigned getHostEvalBlockArgsStart();

  /// Get start index of block arguments defined by `in_reduction`.
  unsigned getInReductionBlockArgsStart();

  /// Get start index of block arguments defined by `map`.
  unsigned getMapBlockArgsStart();

  /// Get start index of block arguments defined by `private`.
  unsigned getPrivateBlockArgsStart();

  /// Get start index of block arguments defined by `reduction`.
  unsigned getReductionBlockArgsStart();

  /// Get start index of block arguments defined by `task_reduction`.
  unsigned getTaskReductionBlockArgsStart();

  /// Get start index of block arguments defined by `use_device_addr`.
  unsigned getUseDeviceAddrBlockArgsStart();

  /// Get start index of block arguments defined by `use_device_ptr`.
  unsigned getUseDevicePtrBlockArgsStart();

  /// Get block arguments defined by `has_device_addr`.
  ::llvm::MutableArrayRef<::mlir::BlockArgument> getHasDeviceAddrBlockArgs();

  /// Get block arguments defined by `host_eval`.
  ::llvm::MutableArrayRef<::mlir::BlockArgument> getHostEvalBlockArgs();

  /// Get block arguments defined by `in_reduction`.
  ::llvm::MutableArrayRef<::mlir::BlockArgument> getInReductionBlockArgs();

  /// Get block arguments defined by `map`.
  ::llvm::MutableArrayRef<::mlir::BlockArgument> getMapBlockArgs();

  /// Get block arguments defined by `private`.
  ::llvm::MutableArrayRef<::mlir::BlockArgument> getPrivateBlockArgs();

  /// Get block arguments defined by `reduction`.
  ::llvm::MutableArrayRef<::mlir::BlockArgument> getReductionBlockArgs();

  /// Get block arguments defined by `task_reduction`.
  ::llvm::MutableArrayRef<::mlir::BlockArgument> getTaskReductionBlockArgs();

  /// Get block arguments defined by `use_device_addr`.
  ::llvm::MutableArrayRef<::mlir::BlockArgument> getUseDeviceAddrBlockArgs();

  /// Get block arguments defined by `use_device_ptr`.
  ::llvm::MutableArrayRef<::mlir::BlockArgument> getUseDevicePtrBlockArgs();

  /// Get the total number of clause-defined entry block arguments
  unsigned numClauseBlockArgs();

  /// Populate a vector of pairs representing the matching between operands and entry block arguments.
  void getBlockArgsPairs(::llvm::SmallVectorImpl<std::pair<::mlir::Value, ::mlir::BlockArgument>> & pairs);
};

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations whose region will be outlined will implement this
///     interface.
namespace detail {
struct OutlineableOpenMPOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::Block*(*getAllocaBlock)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::omp::OutlineableOpenMPOpInterface;
    Model() : Concept{getAllocaBlock} {}

    static inline ::mlir::Block*getAllocaBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::omp::OutlineableOpenMPOpInterface;
    FallbackModel() : Concept{getAllocaBlock} {}

    static inline ::mlir::Block*getAllocaBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct OutlineableOpenMPOpInterfaceTrait;

} // namespace detail
class OutlineableOpenMPOpInterface : public ::mlir::OpInterface<OutlineableOpenMPOpInterface, detail::OutlineableOpenMPOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<OutlineableOpenMPOpInterface, detail::OutlineableOpenMPOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::OutlineableOpenMPOpInterfaceTrait<ConcreteOp> {};

  /// Get alloca block
  ::mlir::Block*getAllocaBlock();
};

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations which own a list of omp::MapInfoOp's implement this interface
///     to allow generic access to deal with map operands to more easily manipulate
///     this class of operations.
namespace detail {
struct MapClauseOwningOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::OperandRange (*getMapVars)(const Concept *impl, ::mlir::Operation *);
    ::mlir::MutableOperandRange (*getMapVarsMutable)(const Concept *impl, ::mlir::Operation *);
    int64_t (*getOperandIndexForMap)(const Concept *impl, ::mlir::Operation *, ::mlir::Value);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::omp::MapClauseOwningOpInterface;
    Model() : Concept{getMapVars, getMapVarsMutable, getOperandIndexForMap} {}

    static inline ::mlir::OperandRange getMapVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::MutableOperandRange getMapVarsMutable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline int64_t getOperandIndexForMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Value map);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::omp::MapClauseOwningOpInterface;
    FallbackModel() : Concept{getMapVars, getMapVarsMutable, getOperandIndexForMap} {}

    static inline ::mlir::OperandRange getMapVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::MutableOperandRange getMapVarsMutable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline int64_t getOperandIndexForMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Value map);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct MapClauseOwningOpInterfaceTrait;

} // namespace detail
class MapClauseOwningOpInterface : public ::mlir::OpInterface<MapClauseOwningOpInterface, detail::MapClauseOwningOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<MapClauseOwningOpInterface, detail::MapClauseOwningOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::MapClauseOwningOpInterfaceTrait<ConcreteOp> {};

  /// Get map operands
  ::mlir::OperandRange getMapVars();

  /// Get mutable map operands
  ::mlir::MutableOperandRange getMapVarsMutable();

  /// Get operand index for a map clause
  int64_t getOperandIndexForMap(::mlir::Value map);
};

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations that wrap a single loop nest. They must only contain a
///     single region with a single block in which there's a single operation and a
///     terminator. That nested operation must be another loop wrapper or an
///     `omp.loop_nest`.
/// 
///     Operation-specific verifiers should make the following checks in their
///     verifier, additionally to what the interface itself checks:
///       - If `getNestedWrapper() != nullptr`, is the type of the nested wrapper
///       allowed in that context? This check might require looking at the parent as
///       well.
///       - If the operation is a `ComposableOpInterface`, check that it is
///       consistent with the potential existence of a `LoopWrapperInterface` parent
///       and whether `getNestedWrapper() != nullptr`.
namespace detail {
struct LoopWrapperInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::omp::LoopWrapperInterface (*getNestedWrapper)(const Concept *impl, ::mlir::Operation *);
    ::mlir::Operation *(*getWrappedLoop)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::omp::LoopWrapperInterface;
    Model() : Concept{getNestedWrapper, getWrappedLoop} {}

    static inline ::mlir::omp::LoopWrapperInterface getNestedWrapper(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Operation *getWrappedLoop(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::omp::LoopWrapperInterface;
    FallbackModel() : Concept{getNestedWrapper, getWrappedLoop} {}

    static inline ::mlir::omp::LoopWrapperInterface getNestedWrapper(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Operation *getWrappedLoop(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::mlir::omp::LoopWrapperInterface getNestedWrapper(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::Operation *getWrappedLoop(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct LoopWrapperInterfaceTrait;

} // namespace detail
class LoopWrapperInterface : public ::mlir::OpInterface<LoopWrapperInterface, detail::LoopWrapperInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<LoopWrapperInterface, detail::LoopWrapperInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::LoopWrapperInterfaceTrait<ConcreteOp> {};

  /// If there is another loop wrapper immediately nested inside, return that
  /// operation. Assumes this operation is a valid loop wrapper.
  ::mlir::omp::LoopWrapperInterface getNestedWrapper();

  /// Return the loop nest nested directly or indirectly inside of this loop
  /// wrapper. Assumes this operation is a valid loop wrapper.
  ::mlir::Operation *getWrappedLoop();

    /// Interface verifier implementation.
    llvm::LogicalResult verifyImpl();
};

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations that can represent a single leaf of a composite OpenMP
///     construct.
namespace detail {
struct ComposableOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*isComposite)(const Concept *impl, ::mlir::Operation *);
    void (*setComposite)(const Concept *impl, ::mlir::Operation *, bool);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::omp::ComposableOpInterface;
    Model() : Concept{isComposite, setComposite} {}

    static inline bool isComposite(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setComposite(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::omp::ComposableOpInterface;
    FallbackModel() : Concept{isComposite, setComposite} {}

    static inline bool isComposite(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setComposite(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    bool isComposite(::mlir::Operation *tablegen_opaque_val) const;
    void setComposite(::mlir::Operation *tablegen_opaque_val, bool val) const;
  };
};
template <typename ConcreteOp>
struct ComposableOpInterfaceTrait;

} // namespace detail
class ComposableOpInterface : public ::mlir::OpInterface<ComposableOpInterface, detail::ComposableOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ComposableOpInterface, detail::ComposableOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ComposableOpInterfaceTrait<ConcreteOp> {};

  /// Check whether the operation is representing a leaf of a composite OpenMP
  /// construct.
  bool isComposite();

  /// Mark the operation as part of an OpenMP composite construct.
  void setComposite(bool val);
};

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP operations that support declare target have this interface.
///     For example, FuncOp's and llvm.GlobalOp/fir.GlobalOp's. This
///     interface allows simple manipulation and introspection of the
///     declare target attribute that can be applied to these operations.
namespace detail {
struct DeclareTargetInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    void (*setDeclareTarget)(const Concept *impl, ::mlir::Operation *, mlir::omp::DeclareTargetDeviceType, mlir::omp::DeclareTargetCaptureClause, bool);
    bool (*isDeclareTarget)(const Concept *impl, ::mlir::Operation *);
    mlir::omp::DeclareTargetDeviceType (*getDeclareTargetDeviceType)(const Concept *impl, ::mlir::Operation *);
    mlir::omp::DeclareTargetCaptureClause (*getDeclareTargetCaptureClause)(const Concept *impl, ::mlir::Operation *);
    bool (*getDeclareTargetAutomap)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::omp::DeclareTargetInterface;
    Model() : Concept{setDeclareTarget, isDeclareTarget, getDeclareTargetDeviceType, getDeclareTargetCaptureClause, getDeclareTargetAutomap} {}

    static inline void setDeclareTarget(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::omp::DeclareTargetDeviceType deviceType, mlir::omp::DeclareTargetCaptureClause captureClause, bool automap);
    static inline bool isDeclareTarget(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::omp::DeclareTargetDeviceType getDeclareTargetDeviceType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::omp::DeclareTargetCaptureClause getDeclareTargetCaptureClause(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool getDeclareTargetAutomap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::omp::DeclareTargetInterface;
    FallbackModel() : Concept{setDeclareTarget, isDeclareTarget, getDeclareTargetDeviceType, getDeclareTargetCaptureClause, getDeclareTargetAutomap} {}

    static inline void setDeclareTarget(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::omp::DeclareTargetDeviceType deviceType, mlir::omp::DeclareTargetCaptureClause captureClause, bool automap);
    static inline bool isDeclareTarget(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::omp::DeclareTargetDeviceType getDeclareTargetDeviceType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::omp::DeclareTargetCaptureClause getDeclareTargetCaptureClause(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool getDeclareTargetAutomap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    void setDeclareTarget(::mlir::Operation *tablegen_opaque_val, mlir::omp::DeclareTargetDeviceType deviceType, mlir::omp::DeclareTargetCaptureClause captureClause, bool automap) const;
    bool isDeclareTarget(::mlir::Operation *tablegen_opaque_val) const;
    mlir::omp::DeclareTargetDeviceType getDeclareTargetDeviceType(::mlir::Operation *tablegen_opaque_val) const;
    mlir::omp::DeclareTargetCaptureClause getDeclareTargetCaptureClause(::mlir::Operation *tablegen_opaque_val) const;
    bool getDeclareTargetAutomap(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct DeclareTargetInterfaceTrait;

} // namespace detail
class DeclareTargetInterface : public ::mlir::OpInterface<DeclareTargetInterface, detail::DeclareTargetInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<DeclareTargetInterface, detail::DeclareTargetInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::DeclareTargetInterfaceTrait<ConcreteOp> {};

  /// Set the declare target attribute on the current operation with the
  /// specified attribute arguments.
  void setDeclareTarget(mlir::omp::DeclareTargetDeviceType deviceType, mlir::omp::DeclareTargetCaptureClause captureClause, bool automap);

  /// Checks if the declare target attribute has been applied and exists on the
  /// current operation. Returns true if it exists on it, otherwise returns
  /// false.
  bool isDeclareTarget();

  /// Returns the DeclareTargetDeviceType segment of the DeclareTarget attribute if it
  /// exists on the current operation. Otherwise it returns null.
  mlir::omp::DeclareTargetDeviceType getDeclareTargetDeviceType();

  /// Returns the DeclareTargetCaptureClause segment of the DeclareTarget attribute if it
  /// exists on the current operation. Otherwise it returns null.
  mlir::omp::DeclareTargetCaptureClause getDeclareTargetCaptureClause();

  /// Return true if the DeclareTarget attribute has the AUTOMAP modifier.
  bool getDeclareTargetAutomap();
};

} // namespace mlir::omp
namespace mlir::omp {

/// Operations that represent a module for offloading (host or device)
///     should have this interface.
namespace detail {
struct OffloadModuleInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    void (*setIsTargetDevice)(const Concept *impl, ::mlir::Operation *, bool);
    bool (*getIsTargetDevice)(const Concept *impl, ::mlir::Operation *);
    void (*setIsGPU)(const Concept *impl, ::mlir::Operation *, bool);
    bool (*getIsGPU)(const Concept *impl, ::mlir::Operation *);
    mlir::omp::FlagsAttr (*getFlags)(const Concept *impl, ::mlir::Operation *);
    void (*setFlags)(const Concept *impl, ::mlir::Operation *, uint32_t, bool, bool, bool, bool, uint32_t, bool);
    void (*setHostIRFilePath)(const Concept *impl, ::mlir::Operation *, std::string);
    llvm::StringRef (*getHostIRFilePath)(const Concept *impl, ::mlir::Operation *);
    ::mlir::omp::ClauseRequires (*getRequires)(const Concept *impl, ::mlir::Operation *);
    void (*setRequires)(const Concept *impl, ::mlir::Operation *, ::mlir::omp::ClauseRequires);
    ::llvm::ArrayRef<::mlir::Attribute> (*getTargetTriples)(const Concept *impl, ::mlir::Operation *);
    void (*setTargetTriples)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<::std::string>);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::omp::OffloadModuleInterface;
    Model() : Concept{setIsTargetDevice, getIsTargetDevice, setIsGPU, getIsGPU, getFlags, setFlags, setHostIRFilePath, getHostIRFilePath, getRequires, setRequires, getTargetTriples, setTargetTriples} {}

    static inline void setIsTargetDevice(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool isTargetDevice);
    static inline bool getIsTargetDevice(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setIsGPU(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool isGPU);
    static inline bool getIsGPU(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::omp::FlagsAttr getFlags(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setFlags(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, uint32_t debugKind, bool assumeTeamsOversubscription, bool assumeThreadsOversubscription, bool assumeNoThreadState, bool assumeNoNestedParallelism, uint32_t openmpDeviceVersion, bool noGPULib);
    static inline void setHostIRFilePath(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, std::string hostIRFilePath);
    static inline llvm::StringRef getHostIRFilePath(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::omp::ClauseRequires getRequires(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setRequires(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::omp::ClauseRequires clauses);
    static inline ::llvm::ArrayRef<::mlir::Attribute> getTargetTriples(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setTargetTriples(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::std::string> targetTriples);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::omp::OffloadModuleInterface;
    FallbackModel() : Concept{setIsTargetDevice, getIsTargetDevice, setIsGPU, getIsGPU, getFlags, setFlags, setHostIRFilePath, getHostIRFilePath, getRequires, setRequires, getTargetTriples, setTargetTriples} {}

    static inline void setIsTargetDevice(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool isTargetDevice);
    static inline bool getIsTargetDevice(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setIsGPU(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool isGPU);
    static inline bool getIsGPU(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::omp::FlagsAttr getFlags(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setFlags(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, uint32_t debugKind, bool assumeTeamsOversubscription, bool assumeThreadsOversubscription, bool assumeNoThreadState, bool assumeNoNestedParallelism, uint32_t openmpDeviceVersion, bool noGPULib);
    static inline void setHostIRFilePath(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, std::string hostIRFilePath);
    static inline llvm::StringRef getHostIRFilePath(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::omp::ClauseRequires getRequires(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setRequires(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::omp::ClauseRequires clauses);
    static inline ::llvm::ArrayRef<::mlir::Attribute> getTargetTriples(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setTargetTriples(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::std::string> targetTriples);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    void setIsTargetDevice(::mlir::Operation *tablegen_opaque_val, bool isTargetDevice) const;
    bool getIsTargetDevice(::mlir::Operation *tablegen_opaque_val) const;
    void setIsGPU(::mlir::Operation *tablegen_opaque_val, bool isGPU) const;
    bool getIsGPU(::mlir::Operation *tablegen_opaque_val) const;
    mlir::omp::FlagsAttr getFlags(::mlir::Operation *tablegen_opaque_val) const;
    void setFlags(::mlir::Operation *tablegen_opaque_val, uint32_t debugKind, bool assumeTeamsOversubscription, bool assumeThreadsOversubscription, bool assumeNoThreadState, bool assumeNoNestedParallelism, uint32_t openmpDeviceVersion, bool noGPULib) const;
    void setHostIRFilePath(::mlir::Operation *tablegen_opaque_val, std::string hostIRFilePath) const;
    llvm::StringRef getHostIRFilePath(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::omp::ClauseRequires getRequires(::mlir::Operation *tablegen_opaque_val) const;
    void setRequires(::mlir::Operation *tablegen_opaque_val, ::mlir::omp::ClauseRequires clauses) const;
    ::llvm::ArrayRef<::mlir::Attribute> getTargetTriples(::mlir::Operation *tablegen_opaque_val) const;
    void setTargetTriples(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::std::string> targetTriples) const;
  };
};
template <typename ConcreteOp>
struct OffloadModuleInterfaceTrait;

} // namespace detail
class OffloadModuleInterface : public ::mlir::OpInterface<OffloadModuleInterface, detail::OffloadModuleInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<OffloadModuleInterface, detail::OffloadModuleInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::OffloadModuleInterfaceTrait<ConcreteOp> {};

  /// Set the attribute on the current module with the specified boolean
  /// argument.
  void setIsTargetDevice(bool isTargetDevice);

  /// Get the attribute on the current module if it exists and
  /// return its value, if it doesn't exist it returns false by default.
  bool getIsTargetDevice();

  /// Set the attribute on the current module with the specified boolean
  /// argument.
  void setIsGPU(bool isGPU);

  /// Get the attribute on the current module if it exists and
  /// return its value, if it doesn't exist it returns false by default.
  bool getIsGPU();

  /// Get the FlagsAttr attribute on the current module if it exists
  /// and return the attribute, if it doesn't exit it returns a nullptr
  mlir::omp::FlagsAttr getFlags();

  /// Apply an omp.FlagsAttr to a module with the specified values
  /// for the flags
  void setFlags(uint32_t debugKind, bool assumeTeamsOversubscription, bool assumeThreadsOversubscription, bool assumeNoThreadState, bool assumeNoNestedParallelism, uint32_t openmpDeviceVersion, bool noGPULib);

  /// Set a StringAttr on the current module containing the host IR file path. This
  /// file path is used in two-phase compilation during the device phase to generate
  /// device side LLVM IR when lowering MLIR.
  void setHostIRFilePath(std::string hostIRFilePath);

  /// Find the host-ir file path StringAttr from the current module if it exists and
  /// return its contained value, if it doesn't exist it returns an empty string. This
  /// file path is used in two-phase compilation during the device phase to generate
  /// device side LLVM IR when lowering MLIR.
  llvm::StringRef getHostIRFilePath();

  /// Get the omp.requires attribute on the operator if it's present and
  /// return its value. If it doesn't exist, return `ClauseRequires::none` by
  /// default.
  ::mlir::omp::ClauseRequires getRequires();

  /// Set the omp.requires attribute on the operator to the specified clauses.
  void setRequires(::mlir::omp::ClauseRequires clauses);

  /// Get the omp.target_triples attribute on the operator if it's present and
  /// return its value. If it doesn't exist, return an empty array by default.
  ::llvm::ArrayRef<::mlir::Attribute> getTargetTriples();

  /// Set the omp.target_triples attribute on the operation.
  void setTargetTriples(::llvm::ArrayRef<::std::string> targetTriples);
};

} // namespace mlir::omp
namespace mlir::omp {

/// Methods that are common for OpenMP loop transformation operations.
namespace detail {
struct LoopTransformationInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    std::pair<unsigned, unsigned> (*getApplyeesODSOperandIndexAndLength)(const Concept *impl, ::mlir::Operation *);
    std::pair<unsigned, unsigned> (*getGenerateesODSOperandIndexAndLength)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getNumApplyees)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getNumGeneratees)(const Concept *impl, ::mlir::Operation *);
    unsigned (*isApplyee)(const Concept *impl, ::mlir::Operation *, unsigned);
    unsigned (*isGeneratee)(const Concept *impl, ::mlir::Operation *, unsigned);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::omp::LoopTransformationInterface;
    Model() : Concept{getApplyeesODSOperandIndexAndLength, getGenerateesODSOperandIndexAndLength, getNumApplyees, getNumGeneratees, isApplyee, isGeneratee} {}

    static inline std::pair<unsigned, unsigned> getApplyeesODSOperandIndexAndLength(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline std::pair<unsigned, unsigned> getGenerateesODSOperandIndexAndLength(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getNumApplyees(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getNumGeneratees(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned isApplyee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned opnum);
    static inline unsigned isGeneratee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned opnum);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::omp::LoopTransformationInterface;
    FallbackModel() : Concept{getApplyeesODSOperandIndexAndLength, getGenerateesODSOperandIndexAndLength, getNumApplyees, getNumGeneratees, isApplyee, isGeneratee} {}

    static inline std::pair<unsigned, unsigned> getApplyeesODSOperandIndexAndLength(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline std::pair<unsigned, unsigned> getGenerateesODSOperandIndexAndLength(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getNumApplyees(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getNumGeneratees(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned isApplyee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned opnum);
    static inline unsigned isGeneratee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned opnum);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    unsigned getNumApplyees(::mlir::Operation *tablegen_opaque_val) const;
    unsigned getNumGeneratees(::mlir::Operation *tablegen_opaque_val) const;
    unsigned isApplyee(::mlir::Operation *tablegen_opaque_val, unsigned opnum) const;
    unsigned isGeneratee(::mlir::Operation *tablegen_opaque_val, unsigned opnum) const;
  };
};
template <typename ConcreteOp>
struct LoopTransformationInterfaceTrait;

} // namespace detail
class LoopTransformationInterface : public ::mlir::OpInterface<LoopTransformationInterface, detail::LoopTransformationInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<LoopTransformationInterface, detail::LoopTransformationInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::LoopTransformationInterfaceTrait<ConcreteOp> {};

  /// Get the indices for the arguments that represent CanonicalLoopInfo
  /// applyees, i.e. loops that are transformed/consumed by this operation.
  std::pair<unsigned, unsigned> getApplyeesODSOperandIndexAndLength();

  /// Get the indices for the arguments that represent CanonicalLoopInfo
  /// generatees, i.e. loops that are emitted by this operation.
  std::pair<unsigned, unsigned> getGenerateesODSOperandIndexAndLength();

  /// Return the number of applyees of this loop transformation.
  unsigned getNumApplyees();

  /// Return the number of generatees of this loop transformation.
  unsigned getNumGeneratees();

  /// Return whether the provided operand is an applyee of this operation.
  unsigned isApplyee(unsigned opnum);

  /// Return whether the provided operand is a generatee of this operation.
  unsigned isGeneratee(unsigned opnum);
};

} // namespace mlir::omp
namespace mlir::omp::detail {

  template <typename ConcreteOp>
  struct BlockArgOpenMPOpInterfaceTrait : public ::mlir::OpInterface<BlockArgOpenMPOpInterface, detail::BlockArgOpenMPOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Get operation operands associated to `has_device_addr`.
    ::mlir::OperandRange getHasDeviceAddrVars() {
      return {0, 0};
    }

    /// Get operation operands associated to `host_eval`.
    ::mlir::OperandRange getHostEvalVars() {
      return {0, 0};
    }

    /// Get operation operands associated to `in_reduction`.
    ::mlir::OperandRange getInReductionVars() {
      return {0, 0};
    }

    /// Get operation operands associated to `map`.
    ::mlir::OperandRange getMapVars() {
      return {0, 0};
    }

    /// Get operation operands associated to `private`.
    ::mlir::OperandRange getPrivateVars() {
      return {0, 0};
    }

    /// Get operation operands associated to `reduction`.
    ::mlir::OperandRange getReductionVars() {
      return {0, 0};
    }

    /// Get operation operands associated to `task_reduction`.
    ::mlir::OperandRange getTaskReductionVars() {
      return {0, 0};
    }

    /// Get operation operands associated to `use_device_addr`.
    ::mlir::OperandRange getUseDeviceAddrVars() {
      return {0, 0};
    }

    /// Get operation operands associated to `use_device_ptr`.
    ::mlir::OperandRange getUseDevicePtrVars() {
      return {0, 0};
    }

    /// Get number of block arguments defined by `has_device_addr`.
    unsigned numHasDeviceAddrBlockArgs() {
      return (*static_cast<ConcreteOp *>(this)).getHasDeviceAddrVars().size();
    }

    /// Get number of block arguments defined by `host_eval`.
    unsigned numHostEvalBlockArgs() {
      return (*static_cast<ConcreteOp *>(this)).getHostEvalVars().size();
    }

    /// Get number of block arguments defined by `in_reduction`.
    unsigned numInReductionBlockArgs() {
      return (*static_cast<ConcreteOp *>(this)).getInReductionVars().size();
    }

    /// Get number of block arguments defined by `map`.
    unsigned numMapBlockArgs() {
      return (*static_cast<ConcreteOp *>(this)).getMapVars().size();
    }

    /// Get number of block arguments defined by `private`.
    unsigned numPrivateBlockArgs() {
      return (*static_cast<ConcreteOp *>(this)).getPrivateVars().size();
    }

    /// Get number of block arguments defined by `reduction`.
    unsigned numReductionBlockArgs() {
      return (*static_cast<ConcreteOp *>(this)).getReductionVars().size();
    }

    /// Get number of block arguments defined by `task_reduction`.
    unsigned numTaskReductionBlockArgs() {
      return (*static_cast<ConcreteOp *>(this)).getTaskReductionVars().size();
    }

    /// Get number of block arguments defined by `use_device_addr`.
    unsigned numUseDeviceAddrBlockArgs() {
      return (*static_cast<ConcreteOp *>(this)).getUseDeviceAddrVars().size();
    }

    /// Get number of block arguments defined by `use_device_ptr`.
    unsigned numUseDevicePtrBlockArgs() {
      return (*static_cast<ConcreteOp *>(this)).getUseDevicePtrVars().size();
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(op);
    unsigned expectedArgs = iface.numClauseBlockArgs();
    if (op->getRegion(0).getNumArguments() < expectedArgs)
      return op->emitOpError() << "expected at least " << expectedArgs
                                 << " entry block argument(s)";
    return ::mlir::success();
    }
  };

} // namespace mlir::omp::detail
namespace mlir::omp::detail {

  template <typename ConcreteOp>
  struct OutlineableOpenMPOpInterfaceTrait : public ::mlir::OpInterface<OutlineableOpenMPOpInterface, detail::OutlineableOpenMPOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::omp::detail
namespace mlir::omp::detail {

  template <typename ConcreteOp>
  struct MapClauseOwningOpInterfaceTrait : public ::mlir::OpInterface<MapClauseOwningOpInterface, detail::MapClauseOwningOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::omp::detail
namespace mlir::omp::detail {

  template <typename ConcreteOp>
  struct LoopWrapperInterfaceTrait : public ::mlir::OpInterface<LoopWrapperInterface, detail::LoopWrapperInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// If there is another loop wrapper immediately nested inside, return that
    /// operation. Assumes this operation is a valid loop wrapper.
    ::mlir::omp::LoopWrapperInterface getNestedWrapper() {
      Operation *nested = &*(*static_cast<ConcreteOp *>(this))->getRegion(0).op_begin();
        return ::llvm::dyn_cast<LoopWrapperInterface>(nested);
    }

    /// Return the loop nest nested directly or indirectly inside of this loop
    /// wrapper. Assumes this operation is a valid loop wrapper.
    ::mlir::Operation *getWrappedLoop() {
      if (LoopWrapperInterface nested = (*static_cast<ConcreteOp *>(this)).getNestedWrapper())
          return nested.getWrappedLoop();
        return &*(*static_cast<ConcreteOp *>(this))->getRegion(0).op_begin();
    }
    static ::llvm::LogicalResult verifyRegionTrait(::mlir::Operation *op) {
      return ::llvm::cast<::mlir::omp::LoopWrapperInterface>(op).verifyImpl();
    }
  };

} // namespace mlir::omp::detail
namespace mlir::omp::detail {

  template <typename ConcreteOp>
  struct ComposableOpInterfaceTrait : public ::mlir::OpInterface<ComposableOpInterface, detail::ComposableOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Check whether the operation is representing a leaf of a composite OpenMP
    /// construct.
    bool isComposite() {
      return (*static_cast<ConcreteOp *>(this))->hasAttr("omp.composite");
    }

    /// Mark the operation as part of an OpenMP composite construct.
    void setComposite(bool val) {
      if (val)
          (*static_cast<ConcreteOp *>(this))->setDiscardableAttr("omp.composite", mlir::UnitAttr::get((*static_cast<ConcreteOp *>(this))->getContext()));
        else
          (*static_cast<ConcreteOp *>(this))->removeDiscardableAttr("omp.composite");
    }
  };

} // namespace mlir::omp::detail
namespace mlir::omp::detail {

  template <typename ConcreteOp>
  struct DeclareTargetInterfaceTrait : public ::mlir::OpInterface<DeclareTargetInterface, detail::DeclareTargetInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Set the declare target attribute on the current operation with the
    /// specified attribute arguments.
    void setDeclareTarget(mlir::omp::DeclareTargetDeviceType deviceType, mlir::omp::DeclareTargetCaptureClause captureClause, bool automap) {
      (*static_cast<ConcreteOp *>(this))->setAttr("omp.declare_target",
                  mlir::omp::DeclareTargetAttr::get(
                      (*static_cast<ConcreteOp *>(this))->getContext(),
                      mlir::omp::DeclareTargetDeviceTypeAttr::get(
                          (*static_cast<ConcreteOp *>(this))->getContext(), deviceType),
                      mlir::omp::DeclareTargetCaptureClauseAttr::get(
                          (*static_cast<ConcreteOp *>(this))->getContext(), captureClause),
                      mlir::BoolAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), automap)));
    }

    /// Checks if the declare target attribute has been applied and exists on the
    /// current operation. Returns true if it exists on it, otherwise returns
    /// false.
    bool isDeclareTarget() {
      return (*static_cast<ConcreteOp *>(this))->hasAttr("omp.declare_target");
    }

    /// Returns the DeclareTargetDeviceType segment of the DeclareTarget attribute if it
    /// exists on the current operation. Otherwise it returns null.
    mlir::omp::DeclareTargetDeviceType getDeclareTargetDeviceType() {
      if (mlir::Attribute dTar = (*static_cast<ConcreteOp *>(this))->getAttr("omp.declare_target"))
          if (auto dAttr = llvm::dyn_cast_or_null<mlir::omp::DeclareTargetAttr>(dTar))
            return dAttr.getDeviceType().getValue();
        return {};
    }

    /// Returns the DeclareTargetCaptureClause segment of the DeclareTarget attribute if it
    /// exists on the current operation. Otherwise it returns null.
    mlir::omp::DeclareTargetCaptureClause getDeclareTargetCaptureClause() {
      if (mlir::Attribute dTar = (*static_cast<ConcreteOp *>(this))->getAttr("omp.declare_target"))
          if (auto dAttr = llvm::dyn_cast_or_null<mlir::omp::DeclareTargetAttr>(dTar))
            return dAttr.getCaptureClause().getValue();
        return {};
    }

    /// Return true if the DeclareTarget attribute has the AUTOMAP modifier.
    bool getDeclareTargetAutomap() {
      if (mlir::Attribute dTar = (*static_cast<ConcreteOp *>(this))->getAttr("omp.declare_target"))
          if (auto dAttr = llvm::dyn_cast_or_null<mlir::omp::DeclareTargetAttr>(dTar))
            if (auto autoVal = dAttr.getAutomap())
              return autoVal.getValue();
         return false;
    }
  };

} // namespace mlir::omp::detail
namespace mlir::omp::detail {

  template <typename ConcreteOp>
  struct OffloadModuleInterfaceTrait : public ::mlir::OpInterface<OffloadModuleInterface, detail::OffloadModuleInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Set the attribute on the current module with the specified boolean
    /// argument.
    void setIsTargetDevice(bool isTargetDevice) {
      (*static_cast<ConcreteOp *>(this))->setAttr(
          mlir::StringAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), llvm::Twine{"omp.is_target_device"}),
            mlir::BoolAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), isTargetDevice));
    }

    /// Get the attribute on the current module if it exists and
    /// return its value, if it doesn't exist it returns false by default.
    bool getIsTargetDevice() {
      if (Attribute isTargetDevice = (*static_cast<ConcreteOp *>(this))->getAttr("omp.is_target_device"))
          if (::llvm::isa<mlir::BoolAttr>(isTargetDevice))
           return ::llvm::dyn_cast<BoolAttr>(isTargetDevice).getValue();
        return false;
    }

    /// Set the attribute on the current module with the specified boolean
    /// argument.
    void setIsGPU(bool isGPU) {
      (*static_cast<ConcreteOp *>(this))->setAttr(
          mlir::StringAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), "omp.is_gpu"),
            mlir::BoolAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), isGPU));
    }

    /// Get the attribute on the current module if it exists and
    /// return its value, if it doesn't exist it returns false by default.
    bool getIsGPU() {
      if (Attribute isTargetCGAttr = (*static_cast<ConcreteOp *>(this))->getAttr("omp.is_gpu"))
          if (auto isTargetCGVal = ::llvm::dyn_cast<BoolAttr>(isTargetCGAttr))
           return isTargetCGVal.getValue();
        return false;
    }

    /// Get the FlagsAttr attribute on the current module if it exists
    /// and return the attribute, if it doesn't exit it returns a nullptr
    mlir::omp::FlagsAttr getFlags() {
      if (Attribute flags = (*static_cast<ConcreteOp *>(this))->getAttr("omp.flags"))
          return ::llvm::dyn_cast_or_null<mlir::omp::FlagsAttr>(flags);
        return nullptr;
    }

    /// Apply an omp.FlagsAttr to a module with the specified values
    /// for the flags
    void setFlags(uint32_t debugKind, bool assumeTeamsOversubscription, bool assumeThreadsOversubscription, bool assumeNoThreadState, bool assumeNoNestedParallelism, uint32_t openmpDeviceVersion, bool noGPULib) {
      (*static_cast<ConcreteOp *>(this))->setAttr(("omp." + mlir::omp::FlagsAttr::getMnemonic()).str(),
                  mlir::omp::FlagsAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), debugKind,
                      assumeTeamsOversubscription, assumeThreadsOversubscription,
                      assumeNoThreadState, assumeNoNestedParallelism, noGPULib, openmpDeviceVersion));
    }

    /// Set a StringAttr on the current module containing the host IR file path. This
    /// file path is used in two-phase compilation during the device phase to generate
    /// device side LLVM IR when lowering MLIR.
    void setHostIRFilePath(std::string hostIRFilePath) {
      (*static_cast<ConcreteOp *>(this))->setAttr(
          mlir::StringAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), llvm::Twine{"omp.host_ir_filepath"}),
            mlir::StringAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), hostIRFilePath));
    }

    /// Find the host-ir file path StringAttr from the current module if it exists and
    /// return its contained value, if it doesn't exist it returns an empty string. This
    /// file path is used in two-phase compilation during the device phase to generate
    /// device side LLVM IR when lowering MLIR.
    llvm::StringRef getHostIRFilePath() {
      if (Attribute filepath = (*static_cast<ConcreteOp *>(this))->getAttr("omp.host_ir_filepath"))
          if (::llvm::isa<mlir::StringAttr>(filepath))
            return ::llvm::dyn_cast<mlir::StringAttr>(filepath).getValue();
        return {};
    }

    /// Get the omp.requires attribute on the operator if it's present and
    /// return its value. If it doesn't exist, return `ClauseRequires::none` by
    /// default.
    ::mlir::omp::ClauseRequires getRequires() {
      if (Attribute requiresAttr = (*static_cast<ConcreteOp *>(this))->getAttr("omp.requires"))
          if (auto requiresVal = ::llvm::dyn_cast<mlir::omp::ClauseRequiresAttr>(requiresAttr))
            return requiresVal.getValue();
        return mlir::omp::ClauseRequires::none;
    }

    /// Set the omp.requires attribute on the operator to the specified clauses.
    void setRequires(::mlir::omp::ClauseRequires clauses) {
      (*static_cast<ConcreteOp *>(this))->setAttr(mlir::StringAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), "omp.requires"),
          mlir::omp::ClauseRequiresAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), clauses));
    }

    /// Get the omp.target_triples attribute on the operator if it's present and
    /// return its value. If it doesn't exist, return an empty array by default.
    ::llvm::ArrayRef<::mlir::Attribute> getTargetTriples() {
      if (Attribute triplesAttr = (*static_cast<ConcreteOp *>(this))->getAttr("omp.target_triples"))
          if (auto triples = ::llvm::dyn_cast<::mlir::ArrayAttr>(triplesAttr))
            return triples.getValue();
        return {};
    }

    /// Set the omp.target_triples attribute on the operation.
    void setTargetTriples(::llvm::ArrayRef<::std::string> targetTriples) {
      auto names = ::llvm::to_vector(::llvm::map_range(
            targetTriples, [&](::std::string str) -> ::mlir::Attribute {
              return mlir::StringAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), str);
            }));
        (*static_cast<ConcreteOp *>(this))->setAttr(
            ::mlir::StringAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), "omp.target_triples"),
            ::mlir::ArrayAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), names));
    }
  };

} // namespace mlir::omp::detail
namespace mlir::omp::detail {

  template <typename ConcreteOp>
  struct LoopTransformationInterfaceTrait : public ::mlir::OpInterface<LoopTransformationInterface, detail::LoopTransformationInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Return the number of applyees of this loop transformation.
    unsigned getNumApplyees() {
      return (*static_cast<ConcreteOp *>(this)).getApplyeesODSOperandIndexAndLength().second;
    }

    /// Return the number of generatees of this loop transformation.
    unsigned getNumGeneratees() {
      return (*static_cast<ConcreteOp *>(this)).getGenerateesODSOperandIndexAndLength().second;
    }

    /// Return whether the provided operand is an applyee of this operation.
    unsigned isApplyee(unsigned opnum) {
      auto applyeeArgs = (*static_cast<ConcreteOp *>(this)).getApplyeesODSOperandIndexAndLength();
        return (applyeeArgs.first <= opnum && opnum < applyeeArgs.first + applyeeArgs.second) ;
    }

    /// Return whether the provided operand is a generatee of this operation.
    unsigned isGeneratee(unsigned opnum) {
      auto generateeArgs = (*static_cast<ConcreteOp *>(this)).getGenerateesODSOperandIndexAndLength();
        return (generateeArgs.first <= opnum && opnum < generateeArgs.first + generateeArgs.second) ;
    }
  };

} // namespace mlir::omp::detail
namespace mlir::omp {

template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getHasDeviceAddrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getHasDeviceAddrVars();
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getHostEvalVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getHostEvalVars();
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInReductionVars();
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getMapVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getMapVars();
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPrivateVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPrivateVars();
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getReductionVars();
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTaskReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getTaskReductionVars();
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getUseDeviceAddrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getUseDeviceAddrVars();
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getUseDevicePtrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getUseDevicePtrVars();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::numHasDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numHasDeviceAddrBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::numHostEvalBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numHostEvalBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::numInReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numInReductionBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::numMapBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numMapBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::numPrivateBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numPrivateBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::numReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numReductionBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::numTaskReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numTaskReductionBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::numUseDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numUseDeviceAddrBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::numUseDevicePtrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numUseDevicePtrBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getHasDeviceAddrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return 0;
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getHostEvalBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return iface.getHasDeviceAddrBlockArgsStart() + iface.numHasDeviceAddrBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return iface.getHostEvalBlockArgsStart() + iface.numHostEvalBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getMapBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return iface.getInReductionBlockArgsStart() + iface.numInReductionBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPrivateBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return iface.getMapBlockArgsStart() + iface.numMapBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return iface.getPrivateBlockArgsStart() + iface.numPrivateBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTaskReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return iface.getReductionBlockArgsStart() + iface.numReductionBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getUseDeviceAddrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return iface.getTaskReductionBlockArgsStart() + iface.numTaskReductionBlockArgs();
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getUseDevicePtrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return iface.getUseDeviceAddrBlockArgsStart() + iface.numUseDeviceAddrBlockArgs();
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getHasDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).getArguments().slice(
    iface.getHasDeviceAddrBlockArgsStart(), iface.numHasDeviceAddrBlockArgs());
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getHostEvalBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).getArguments().slice(
    iface.getHostEvalBlockArgsStart(), iface.numHostEvalBlockArgs());
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).getArguments().slice(
    iface.getInReductionBlockArgsStart(), iface.numInReductionBlockArgs());
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getMapBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).getArguments().slice(
    iface.getMapBlockArgsStart(), iface.numMapBlockArgs());
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPrivateBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).getArguments().slice(
    iface.getPrivateBlockArgsStart(), iface.numPrivateBlockArgs());
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).getArguments().slice(
    iface.getReductionBlockArgsStart(), iface.numReductionBlockArgs());
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTaskReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).getArguments().slice(
    iface.getTaskReductionBlockArgsStart(), iface.numTaskReductionBlockArgs());
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getUseDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).getArguments().slice(
    iface.getUseDeviceAddrBlockArgsStart(), iface.numUseDeviceAddrBlockArgs());
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getUseDevicePtrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
      return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).getArguments().slice(
    iface.getUseDevicePtrBlockArgsStart(), iface.numUseDevicePtrBlockArgs());
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::numClauseBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numHasDeviceAddrBlockArgs() + (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numHostEvalBlockArgs() + (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numInReductionBlockArgs() + (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numMapBlockArgs() + (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numPrivateBlockArgs() + (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numReductionBlockArgs() + (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numTaskReductionBlockArgs() + (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numUseDeviceAddrBlockArgs() + (llvm::cast<ConcreteOp>(tablegen_opaque_val)).numUseDevicePtrBlockArgs();
}
template<typename ConcreteOp>
void detail::BlockArgOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getBlockArgsPairs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::SmallVectorImpl<std::pair<::mlir::Value, ::mlir::BlockArgument>> & pairs) {
  auto iface = ::llvm::cast<BlockArgOpenMPOpInterface>(*(llvm::cast<ConcreteOp>(tablegen_opaque_val)));
          pairs.reserve(pairs.size() + iface.numClauseBlockArgs());
        
        if (iface.numHasDeviceAddrBlockArgs() > 0) {
          for (auto [var, arg] : ::llvm::zip_equal(iface.getHasDeviceAddrVars(),iface.getHasDeviceAddrBlockArgs()))
            pairs.emplace_back(var, arg);
        } 

        if (iface.numHostEvalBlockArgs() > 0) {
          for (auto [var, arg] : ::llvm::zip_equal(iface.getHostEvalVars(),iface.getHostEvalBlockArgs()))
            pairs.emplace_back(var, arg);
        } 

        if (iface.numInReductionBlockArgs() > 0) {
          for (auto [var, arg] : ::llvm::zip_equal(iface.getInReductionVars(),iface.getInReductionBlockArgs()))
            pairs.emplace_back(var, arg);
        } 

        if (iface.numMapBlockArgs() > 0) {
          for (auto [var, arg] : ::llvm::zip_equal(iface.getMapVars(),iface.getMapBlockArgs()))
            pairs.emplace_back(var, arg);
        } 

        if (iface.numPrivateBlockArgs() > 0) {
          for (auto [var, arg] : ::llvm::zip_equal(iface.getPrivateVars(),iface.getPrivateBlockArgs()))
            pairs.emplace_back(var, arg);
        } 

        if (iface.numReductionBlockArgs() > 0) {
          for (auto [var, arg] : ::llvm::zip_equal(iface.getReductionVars(),iface.getReductionBlockArgs()))
            pairs.emplace_back(var, arg);
        } 

        if (iface.numTaskReductionBlockArgs() > 0) {
          for (auto [var, arg] : ::llvm::zip_equal(iface.getTaskReductionVars(),iface.getTaskReductionBlockArgs()))
            pairs.emplace_back(var, arg);
        } 

        if (iface.numUseDeviceAddrBlockArgs() > 0) {
          for (auto [var, arg] : ::llvm::zip_equal(iface.getUseDeviceAddrVars(),iface.getUseDeviceAddrBlockArgs()))
            pairs.emplace_back(var, arg);
        } 

        if (iface.numUseDevicePtrBlockArgs() > 0) {
          for (auto [var, arg] : ::llvm::zip_equal(iface.getUseDevicePtrVars(),iface.getUseDevicePtrBlockArgs()))
            pairs.emplace_back(var, arg);
        }
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getHasDeviceAddrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getHasDeviceAddrVars(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getHostEvalVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getHostEvalVars(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInReductionVars(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getMapVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getMapVars(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPrivateVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPrivateVars(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getReductionVars(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTaskReductionVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getTaskReductionVars(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getUseDeviceAddrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getUseDeviceAddrVars(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getUseDevicePtrVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getUseDevicePtrVars(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::numHasDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->numHasDeviceAddrBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::numHostEvalBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->numHostEvalBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::numInReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->numInReductionBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::numMapBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->numMapBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::numPrivateBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->numPrivateBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::numReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->numReductionBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::numTaskReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->numTaskReductionBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::numUseDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->numUseDeviceAddrBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::numUseDevicePtrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->numUseDevicePtrBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getHasDeviceAddrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getHasDeviceAddrBlockArgsStart(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getHostEvalBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getHostEvalBlockArgsStart(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInReductionBlockArgsStart(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getMapBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getMapBlockArgsStart(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPrivateBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPrivateBlockArgsStart(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getReductionBlockArgsStart(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTaskReductionBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getTaskReductionBlockArgsStart(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getUseDeviceAddrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getUseDeviceAddrBlockArgsStart(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getUseDevicePtrBlockArgsStart(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getUseDevicePtrBlockArgsStart(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getHasDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getHasDeviceAddrBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getHostEvalBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getHostEvalBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInReductionBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getMapBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getMapBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPrivateBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPrivateBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getReductionBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTaskReductionBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getTaskReductionBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getUseDeviceAddrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getUseDeviceAddrBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::MutableArrayRef<::mlir::BlockArgument> detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getUseDevicePtrBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getUseDevicePtrBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::numClauseBlockArgs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->numClauseBlockArgs(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::BlockArgOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getBlockArgsPairs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::SmallVectorImpl<std::pair<::mlir::Value, ::mlir::BlockArgument>> & pairs) {
  return static_cast<const ConcreteOp *>(impl)->getBlockArgsPairs(tablegen_opaque_val, pairs);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getHasDeviceAddrVars(::mlir::Operation *tablegen_opaque_val) const {
return {0, 0};
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getHostEvalVars(::mlir::Operation *tablegen_opaque_val) const {
return {0, 0};
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInReductionVars(::mlir::Operation *tablegen_opaque_val) const {
return {0, 0};
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getMapVars(::mlir::Operation *tablegen_opaque_val) const {
return {0, 0};
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPrivateVars(::mlir::Operation *tablegen_opaque_val) const {
return {0, 0};
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getReductionVars(::mlir::Operation *tablegen_opaque_val) const {
return {0, 0};
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getTaskReductionVars(::mlir::Operation *tablegen_opaque_val) const {
return {0, 0};
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getUseDeviceAddrVars(::mlir::Operation *tablegen_opaque_val) const {
return {0, 0};
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::OperandRange detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getUseDevicePtrVars(::mlir::Operation *tablegen_opaque_val) const {
return {0, 0};
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::numHasDeviceAddrBlockArgs(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getHasDeviceAddrVars().size();
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::numHostEvalBlockArgs(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getHostEvalVars().size();
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::numInReductionBlockArgs(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInReductionVars().size();
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::numMapBlockArgs(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getMapVars().size();
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::numPrivateBlockArgs(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPrivateVars().size();
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::numReductionBlockArgs(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getReductionVars().size();
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::numTaskReductionBlockArgs(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getTaskReductionVars().size();
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::numUseDeviceAddrBlockArgs(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getUseDeviceAddrVars().size();
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::BlockArgOpenMPOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::numUseDevicePtrBlockArgs(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getUseDevicePtrVars().size();
}

} // namespace mlir::omp
namespace mlir::omp {

template<typename ConcreteOp>
::mlir::Block*detail::OutlineableOpenMPOpInterfaceInterfaceTraits::Model<ConcreteOp>::getAllocaBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  // For taskloop: put the allocas inside of the wrapped loop. Loop wrappers
      // are expected to contain only the wrapped loop (or another loop wrapper)
      if (LoopWrapperInterface loopWrapper =
              mlir::dyn_cast<LoopWrapperInterface>((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getOperation()))
        return &loopWrapper.getWrappedLoop()->getRegion(0).front();
      return &(llvm::cast<ConcreteOp>(tablegen_opaque_val)).getRegion().front();
}
template<typename ConcreteOp>
::mlir::Block*detail::OutlineableOpenMPOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getAllocaBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getAllocaBlock(tablegen_opaque_val);
}

} // namespace mlir::omp
namespace mlir::omp {

template<typename ConcreteOp>
::mlir::OperandRange detail::MapClauseOwningOpInterfaceInterfaceTraits::Model<ConcreteOp>::getMapVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getMapVars();
}
template<typename ConcreteOp>
::mlir::MutableOperandRange detail::MapClauseOwningOpInterfaceInterfaceTraits::Model<ConcreteOp>::getMapVarsMutable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getMapVarsMutable();
}
template<typename ConcreteOp>
int64_t detail::MapClauseOwningOpInterfaceInterfaceTraits::Model<ConcreteOp>::getOperandIndexForMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Value map) {
  return std::distance((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getMapVars().begin(),
                              llvm::find((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getMapVars(), map));
}
template<typename ConcreteOp>
::mlir::OperandRange detail::MapClauseOwningOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getMapVars(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getMapVars(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::MutableOperandRange detail::MapClauseOwningOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getMapVarsMutable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getMapVarsMutable(tablegen_opaque_val);
}
template<typename ConcreteOp>
int64_t detail::MapClauseOwningOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getOperandIndexForMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Value map) {
  return static_cast<const ConcreteOp *>(impl)->getOperandIndexForMap(tablegen_opaque_val, map);
}

} // namespace mlir::omp
namespace mlir::omp {

template<typename ConcreteOp>
::mlir::omp::LoopWrapperInterface detail::LoopWrapperInterfaceInterfaceTraits::Model<ConcreteOp>::getNestedWrapper(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNestedWrapper();
}
template<typename ConcreteOp>
::mlir::Operation *detail::LoopWrapperInterfaceInterfaceTraits::Model<ConcreteOp>::getWrappedLoop(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getWrappedLoop();
}
template<typename ConcreteOp>
::mlir::omp::LoopWrapperInterface detail::LoopWrapperInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getNestedWrapper(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNestedWrapper(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::Operation *detail::LoopWrapperInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getWrappedLoop(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getWrappedLoop(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::omp::LoopWrapperInterface detail::LoopWrapperInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getNestedWrapper(::mlir::Operation *tablegen_opaque_val) const {
Operation *nested = &*(llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).op_begin();
        return ::llvm::dyn_cast<LoopWrapperInterface>(nested);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Operation *detail::LoopWrapperInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getWrappedLoop(::mlir::Operation *tablegen_opaque_val) const {
if (LoopWrapperInterface nested = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNestedWrapper())
          return nested.getWrappedLoop();
        return &*(llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0).op_begin();
}

} // namespace mlir::omp
namespace mlir::omp {

template<typename ConcreteOp>
bool detail::ComposableOpInterfaceInterfaceTraits::Model<ConcreteOp>::isComposite(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isComposite();
}
template<typename ConcreteOp>
void detail::ComposableOpInterfaceInterfaceTraits::Model<ConcreteOp>::setComposite(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setComposite(val);
}
template<typename ConcreteOp>
bool detail::ComposableOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isComposite(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->isComposite(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::ComposableOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setComposite(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool val) {
  return static_cast<const ConcreteOp *>(impl)->setComposite(tablegen_opaque_val, val);
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::ComposableOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::isComposite(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->hasAttr("omp.composite");
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::ComposableOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setComposite(::mlir::Operation *tablegen_opaque_val, bool val) const {
if (val)
          (llvm::cast<ConcreteOp>(tablegen_opaque_val))->setDiscardableAttr("omp.composite", mlir::UnitAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext()));
        else
          (llvm::cast<ConcreteOp>(tablegen_opaque_val))->removeDiscardableAttr("omp.composite");
}

} // namespace mlir::omp
namespace mlir::omp {

template<typename ConcreteOp>
void detail::DeclareTargetInterfaceInterfaceTraits::Model<ConcreteOp>::setDeclareTarget(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::omp::DeclareTargetDeviceType deviceType, mlir::omp::DeclareTargetCaptureClause captureClause, bool automap) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setDeclareTarget(deviceType, captureClause, automap);
}
template<typename ConcreteOp>
bool detail::DeclareTargetInterfaceInterfaceTraits::Model<ConcreteOp>::isDeclareTarget(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isDeclareTarget();
}
template<typename ConcreteOp>
mlir::omp::DeclareTargetDeviceType detail::DeclareTargetInterfaceInterfaceTraits::Model<ConcreteOp>::getDeclareTargetDeviceType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDeclareTargetDeviceType();
}
template<typename ConcreteOp>
mlir::omp::DeclareTargetCaptureClause detail::DeclareTargetInterfaceInterfaceTraits::Model<ConcreteOp>::getDeclareTargetCaptureClause(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDeclareTargetCaptureClause();
}
template<typename ConcreteOp>
bool detail::DeclareTargetInterfaceInterfaceTraits::Model<ConcreteOp>::getDeclareTargetAutomap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDeclareTargetAutomap();
}
template<typename ConcreteOp>
void detail::DeclareTargetInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setDeclareTarget(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::omp::DeclareTargetDeviceType deviceType, mlir::omp::DeclareTargetCaptureClause captureClause, bool automap) {
  return static_cast<const ConcreteOp *>(impl)->setDeclareTarget(tablegen_opaque_val, deviceType, captureClause, automap);
}
template<typename ConcreteOp>
bool detail::DeclareTargetInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isDeclareTarget(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->isDeclareTarget(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::omp::DeclareTargetDeviceType detail::DeclareTargetInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getDeclareTargetDeviceType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDeclareTargetDeviceType(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::omp::DeclareTargetCaptureClause detail::DeclareTargetInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getDeclareTargetCaptureClause(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDeclareTargetCaptureClause(tablegen_opaque_val);
}
template<typename ConcreteOp>
bool detail::DeclareTargetInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getDeclareTargetAutomap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDeclareTargetAutomap(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::DeclareTargetInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setDeclareTarget(::mlir::Operation *tablegen_opaque_val, mlir::omp::DeclareTargetDeviceType deviceType, mlir::omp::DeclareTargetCaptureClause captureClause, bool automap) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val))->setAttr("omp.declare_target",
                  mlir::omp::DeclareTargetAttr::get(
                      (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(),
                      mlir::omp::DeclareTargetDeviceTypeAttr::get(
                          (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), deviceType),
                      mlir::omp::DeclareTargetCaptureClauseAttr::get(
                          (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), captureClause),
                      mlir::BoolAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), automap)));
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::DeclareTargetInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::isDeclareTarget(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->hasAttr("omp.declare_target");
}
template<typename ConcreteModel, typename ConcreteOp>
mlir::omp::DeclareTargetDeviceType detail::DeclareTargetInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDeclareTargetDeviceType(::mlir::Operation *tablegen_opaque_val) const {
if (mlir::Attribute dTar = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getAttr("omp.declare_target"))
          if (auto dAttr = llvm::dyn_cast_or_null<mlir::omp::DeclareTargetAttr>(dTar))
            return dAttr.getDeviceType().getValue();
        return {};
}
template<typename ConcreteModel, typename ConcreteOp>
mlir::omp::DeclareTargetCaptureClause detail::DeclareTargetInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDeclareTargetCaptureClause(::mlir::Operation *tablegen_opaque_val) const {
if (mlir::Attribute dTar = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getAttr("omp.declare_target"))
          if (auto dAttr = llvm::dyn_cast_or_null<mlir::omp::DeclareTargetAttr>(dTar))
            return dAttr.getCaptureClause().getValue();
        return {};
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::DeclareTargetInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDeclareTargetAutomap(::mlir::Operation *tablegen_opaque_val) const {
if (mlir::Attribute dTar = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getAttr("omp.declare_target"))
          if (auto dAttr = llvm::dyn_cast_or_null<mlir::omp::DeclareTargetAttr>(dTar))
            if (auto autoVal = dAttr.getAutomap())
              return autoVal.getValue();
         return false;
}

} // namespace mlir::omp
namespace mlir::omp {

template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::setIsTargetDevice(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool isTargetDevice) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setIsTargetDevice(isTargetDevice);
}
template<typename ConcreteOp>
bool detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::getIsTargetDevice(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getIsTargetDevice();
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::setIsGPU(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool isGPU) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setIsGPU(isGPU);
}
template<typename ConcreteOp>
bool detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::getIsGPU(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getIsGPU();
}
template<typename ConcreteOp>
mlir::omp::FlagsAttr detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::getFlags(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getFlags();
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::setFlags(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, uint32_t debugKind, bool assumeTeamsOversubscription, bool assumeThreadsOversubscription, bool assumeNoThreadState, bool assumeNoNestedParallelism, uint32_t openmpDeviceVersion, bool noGPULib) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setFlags(debugKind, assumeTeamsOversubscription, assumeThreadsOversubscription, assumeNoThreadState, assumeNoNestedParallelism, openmpDeviceVersion, noGPULib);
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::setHostIRFilePath(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, std::string hostIRFilePath) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setHostIRFilePath(hostIRFilePath);
}
template<typename ConcreteOp>
llvm::StringRef detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::getHostIRFilePath(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getHostIRFilePath();
}
template<typename ConcreteOp>
::mlir::omp::ClauseRequires detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::getRequires(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getRequires();
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::setRequires(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::omp::ClauseRequires clauses) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setRequires(clauses);
}
template<typename ConcreteOp>
::llvm::ArrayRef<::mlir::Attribute> detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::getTargetTriples(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getTargetTriples();
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::Model<ConcreteOp>::setTargetTriples(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::std::string> targetTriples) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setTargetTriples(targetTriples);
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setIsTargetDevice(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool isTargetDevice) {
  return static_cast<const ConcreteOp *>(impl)->setIsTargetDevice(tablegen_opaque_val, isTargetDevice);
}
template<typename ConcreteOp>
bool detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getIsTargetDevice(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getIsTargetDevice(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setIsGPU(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, bool isGPU) {
  return static_cast<const ConcreteOp *>(impl)->setIsGPU(tablegen_opaque_val, isGPU);
}
template<typename ConcreteOp>
bool detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getIsGPU(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getIsGPU(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::omp::FlagsAttr detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getFlags(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getFlags(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setFlags(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, uint32_t debugKind, bool assumeTeamsOversubscription, bool assumeThreadsOversubscription, bool assumeNoThreadState, bool assumeNoNestedParallelism, uint32_t openmpDeviceVersion, bool noGPULib) {
  return static_cast<const ConcreteOp *>(impl)->setFlags(tablegen_opaque_val, debugKind, assumeTeamsOversubscription, assumeThreadsOversubscription, assumeNoThreadState, assumeNoNestedParallelism, openmpDeviceVersion, noGPULib);
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setHostIRFilePath(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, std::string hostIRFilePath) {
  return static_cast<const ConcreteOp *>(impl)->setHostIRFilePath(tablegen_opaque_val, hostIRFilePath);
}
template<typename ConcreteOp>
llvm::StringRef detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getHostIRFilePath(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getHostIRFilePath(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::omp::ClauseRequires detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getRequires(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getRequires(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setRequires(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::omp::ClauseRequires clauses) {
  return static_cast<const ConcreteOp *>(impl)->setRequires(tablegen_opaque_val, clauses);
}
template<typename ConcreteOp>
::llvm::ArrayRef<::mlir::Attribute> detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTargetTriples(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getTargetTriples(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setTargetTriples(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::std::string> targetTriples) {
  return static_cast<const ConcreteOp *>(impl)->setTargetTriples(tablegen_opaque_val, targetTriples);
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setIsTargetDevice(::mlir::Operation *tablegen_opaque_val, bool isTargetDevice) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val))->setAttr(
          mlir::StringAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), llvm::Twine{"omp.is_target_device"}),
            mlir::BoolAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), isTargetDevice));
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getIsTargetDevice(::mlir::Operation *tablegen_opaque_val) const {
if (Attribute isTargetDevice = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getAttr("omp.is_target_device"))
          if (::llvm::isa<mlir::BoolAttr>(isTargetDevice))
           return ::llvm::dyn_cast<BoolAttr>(isTargetDevice).getValue();
        return false;
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setIsGPU(::mlir::Operation *tablegen_opaque_val, bool isGPU) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val))->setAttr(
          mlir::StringAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), "omp.is_gpu"),
            mlir::BoolAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), isGPU));
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getIsGPU(::mlir::Operation *tablegen_opaque_val) const {
if (Attribute isTargetCGAttr = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getAttr("omp.is_gpu"))
          if (auto isTargetCGVal = ::llvm::dyn_cast<BoolAttr>(isTargetCGAttr))
           return isTargetCGVal.getValue();
        return false;
}
template<typename ConcreteModel, typename ConcreteOp>
mlir::omp::FlagsAttr detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getFlags(::mlir::Operation *tablegen_opaque_val) const {
if (Attribute flags = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getAttr("omp.flags"))
          return ::llvm::dyn_cast_or_null<mlir::omp::FlagsAttr>(flags);
        return nullptr;
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setFlags(::mlir::Operation *tablegen_opaque_val, uint32_t debugKind, bool assumeTeamsOversubscription, bool assumeThreadsOversubscription, bool assumeNoThreadState, bool assumeNoNestedParallelism, uint32_t openmpDeviceVersion, bool noGPULib) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val))->setAttr(("omp." + mlir::omp::FlagsAttr::getMnemonic()).str(),
                  mlir::omp::FlagsAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), debugKind,
                      assumeTeamsOversubscription, assumeThreadsOversubscription,
                      assumeNoThreadState, assumeNoNestedParallelism, noGPULib, openmpDeviceVersion));
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setHostIRFilePath(::mlir::Operation *tablegen_opaque_val, std::string hostIRFilePath) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val))->setAttr(
          mlir::StringAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), llvm::Twine{"omp.host_ir_filepath"}),
            mlir::StringAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), hostIRFilePath));
}
template<typename ConcreteModel, typename ConcreteOp>
llvm::StringRef detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getHostIRFilePath(::mlir::Operation *tablegen_opaque_val) const {
if (Attribute filepath = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getAttr("omp.host_ir_filepath"))
          if (::llvm::isa<mlir::StringAttr>(filepath))
            return ::llvm::dyn_cast<mlir::StringAttr>(filepath).getValue();
        return {};
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::omp::ClauseRequires detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getRequires(::mlir::Operation *tablegen_opaque_val) const {
if (Attribute requiresAttr = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getAttr("omp.requires"))
          if (auto requiresVal = ::llvm::dyn_cast<mlir::omp::ClauseRequiresAttr>(requiresAttr))
            return requiresVal.getValue();
        return mlir::omp::ClauseRequires::none;
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setRequires(::mlir::Operation *tablegen_opaque_val, ::mlir::omp::ClauseRequires clauses) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val))->setAttr(mlir::StringAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), "omp.requires"),
          mlir::omp::ClauseRequiresAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), clauses));
}
template<typename ConcreteModel, typename ConcreteOp>
::llvm::ArrayRef<::mlir::Attribute> detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getTargetTriples(::mlir::Operation *tablegen_opaque_val) const {
if (Attribute triplesAttr = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getAttr("omp.target_triples"))
          if (auto triples = ::llvm::dyn_cast<::mlir::ArrayAttr>(triplesAttr))
            return triples.getValue();
        return {};
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::OffloadModuleInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setTargetTriples(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::std::string> targetTriples) const {
auto names = ::llvm::to_vector(::llvm::map_range(
            targetTriples, [&](::std::string str) -> ::mlir::Attribute {
              return mlir::StringAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), str);
            }));
        (llvm::cast<ConcreteOp>(tablegen_opaque_val))->setAttr(
            ::mlir::StringAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), "omp.target_triples"),
            ::mlir::ArrayAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(), names));
}

} // namespace mlir::omp
namespace mlir::omp {

template<typename ConcreteOp>
std::pair<unsigned, unsigned> detail::LoopTransformationInterfaceInterfaceTraits::Model<ConcreteOp>::getApplyeesODSOperandIndexAndLength(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getApplyeesODSOperandIndexAndLength();
}
template<typename ConcreteOp>
std::pair<unsigned, unsigned> detail::LoopTransformationInterfaceInterfaceTraits::Model<ConcreteOp>::getGenerateesODSOperandIndexAndLength(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getGenerateesODSOperandIndexAndLength();
}
template<typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::Model<ConcreteOp>::getNumApplyees(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNumApplyees();
}
template<typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::Model<ConcreteOp>::getNumGeneratees(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNumGeneratees();
}
template<typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::Model<ConcreteOp>::isApplyee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned opnum) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isApplyee(opnum);
}
template<typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::Model<ConcreteOp>::isGeneratee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned opnum) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isGeneratee(opnum);
}
template<typename ConcreteOp>
std::pair<unsigned, unsigned> detail::LoopTransformationInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getApplyeesODSOperandIndexAndLength(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getApplyeesODSOperandIndexAndLength(tablegen_opaque_val);
}
template<typename ConcreteOp>
std::pair<unsigned, unsigned> detail::LoopTransformationInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getGenerateesODSOperandIndexAndLength(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getGenerateesODSOperandIndexAndLength(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getNumApplyees(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNumApplyees(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getNumGeneratees(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNumGeneratees(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isApplyee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned opnum) {
  return static_cast<const ConcreteOp *>(impl)->isApplyee(tablegen_opaque_val, opnum);
}
template<typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isGeneratee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned opnum) {
  return static_cast<const ConcreteOp *>(impl)->isGeneratee(tablegen_opaque_val, opnum);
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getNumApplyees(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getApplyeesODSOperandIndexAndLength().second;
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getNumGeneratees(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getGenerateesODSOperandIndexAndLength().second;
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::isApplyee(::mlir::Operation *tablegen_opaque_val, unsigned opnum) const {
auto applyeeArgs = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getApplyeesODSOperandIndexAndLength();
        return (applyeeArgs.first <= opnum && opnum < applyeeArgs.first + applyeeArgs.second) ;
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::LoopTransformationInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::isGeneratee(::mlir::Operation *tablegen_opaque_val, unsigned opnum) const {
auto generateeArgs = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getGenerateesODSOperandIndexAndLength();
        return (generateeArgs.first <= opnum && opnum < generateeArgs.first + generateeArgs.second) ;
}

} // namespace mlir::omp
