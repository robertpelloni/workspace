/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// Allows operations to participate in strided metadata analysis by providing
///     methods that allow them to specify bounds on offsets, sizes, and strides
///     of their result(s) given bounds on their input(s) if known.
class InferStridedMetadataOpInterface;

} // namespace mlir
namespace mlir {

/// Allows operations to participate in strided metadata analysis by providing
///     methods that allow them to specify bounds on offsets, sizes, and strides
///     of their result(s) given bounds on their input(s) if known.
namespace detail {
struct InferStridedMetadataOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    void (*inferStridedMetadataRanges)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<::mlir::StridedMetadataRange>, ::mlir::GetIntRangeFn, ::mlir::SetStridedMetadataRangeFn, int32_t);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::InferStridedMetadataOpInterface;
    Model() : Concept{inferStridedMetadataRanges} {}

    static inline void inferStridedMetadataRanges(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::StridedMetadataRange> operands, ::mlir::GetIntRangeFn getIntRange, ::mlir::SetStridedMetadataRangeFn setMetadata, int32_t indexBitwidth);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::InferStridedMetadataOpInterface;
    FallbackModel() : Concept{inferStridedMetadataRanges} {}

    static inline void inferStridedMetadataRanges(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::StridedMetadataRange> operands, ::mlir::GetIntRangeFn getIntRange, ::mlir::SetStridedMetadataRangeFn setMetadata, int32_t indexBitwidth);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct InferStridedMetadataOpInterfaceTrait;

} // namespace detail
class InferStridedMetadataOpInterface : public ::mlir::OpInterface<InferStridedMetadataOpInterface, detail::InferStridedMetadataOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<InferStridedMetadataOpInterface, detail::InferStridedMetadataOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::InferStridedMetadataOpInterfaceTrait<ConcreteOp> {};

  /// Infer the strided metadata bounds on the results of this op given
  /// the bounds on its operands.
  /// For each result value or block argument of interest, the method should
  /// call `setMetadata` with that `Value` as an argument.
  /// The `operands` parameter contains the strided metadata ranges for all the
  /// operands of the operation in order.
  /// The `getIntRange` callback is provided for obtaining the int-range
  /// analysis result for a given value.
  void inferStridedMetadataRanges(::llvm::ArrayRef<::mlir::StridedMetadataRange> operands, ::mlir::GetIntRangeFn getIntRange, ::mlir::SetStridedMetadataRangeFn setMetadata, int32_t indexBitwidth);
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteOp>
  struct InferStridedMetadataOpInterfaceTrait : public ::mlir::OpInterface<InferStridedMetadataOpInterface, detail::InferStridedMetadataOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteOp>
void detail::InferStridedMetadataOpInterfaceInterfaceTraits::Model<ConcreteOp>::inferStridedMetadataRanges(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::StridedMetadataRange> operands, ::mlir::GetIntRangeFn getIntRange, ::mlir::SetStridedMetadataRangeFn setMetadata, int32_t indexBitwidth) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).inferStridedMetadataRanges(operands, getIntRange, setMetadata, indexBitwidth);
}
template<typename ConcreteOp>
void detail::InferStridedMetadataOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::inferStridedMetadataRanges(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::StridedMetadataRange> operands, ::mlir::GetIntRangeFn getIntRange, ::mlir::SetStridedMetadataRangeFn setMetadata, int32_t indexBitwidth) {
  return static_cast<const ConcreteOp *>(impl)->inferStridedMetadataRanges(tablegen_opaque_val, operands, getIntRange, setMetadata, indexBitwidth);
}

} // namespace mlir
