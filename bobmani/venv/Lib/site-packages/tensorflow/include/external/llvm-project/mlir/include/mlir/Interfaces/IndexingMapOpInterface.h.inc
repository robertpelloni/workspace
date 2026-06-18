/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// Interface for operations that connect an iteration domain to operands via
///     affine maps. Provides methods to access indexing maps between iteration
///     domain and operand index spaces.
class IndexingMapOpInterface;

} // namespace mlir
namespace mlir {

/// Interface for operations that connect an iteration domain to operands via
///     affine maps. Provides methods to access indexing maps between iteration
///     domain and operand index spaces.
namespace detail {
struct IndexingMapOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ArrayAttr (*getIndexingMaps)(const Concept *impl, ::mlir::Operation *);
    SmallVector<AffineMap> (*getIndexingMapsArray)(const Concept *impl, ::mlir::Operation *);
    AffineMap (*getMatchingIndexingMap)(const Concept *impl, ::mlir::Operation *, OpOperand*);
    AffineMap (*getLoopsToShapesMap)(const Concept *impl, ::mlir::Operation *);
    AffineMap (*getShapesToLoopsMap)(const Concept *impl, ::mlir::Operation *);
    SmallVector<int64_t> (*getStaticOperandShape)(const Concept *impl, ::mlir::Operation *, OpOperand*);
    SmallVector<int64_t> (*getStaticLoopRanges)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::IndexingMapOpInterface;
    Model() : Concept{getIndexingMaps, getIndexingMapsArray, getMatchingIndexingMap, getLoopsToShapesMap, getShapesToLoopsMap, getStaticOperandShape, getStaticLoopRanges} {}

    static inline ArrayAttr getIndexingMaps(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<AffineMap> getIndexingMapsArray(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline AffineMap getMatchingIndexingMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, OpOperand* opOperand);
    static inline AffineMap getLoopsToShapesMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline AffineMap getShapesToLoopsMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<int64_t> getStaticOperandShape(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, OpOperand* opOperand);
    static inline SmallVector<int64_t> getStaticLoopRanges(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::IndexingMapOpInterface;
    FallbackModel() : Concept{getIndexingMaps, getIndexingMapsArray, getMatchingIndexingMap, getLoopsToShapesMap, getShapesToLoopsMap, getStaticOperandShape, getStaticLoopRanges} {}

    static inline ArrayAttr getIndexingMaps(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<AffineMap> getIndexingMapsArray(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline AffineMap getMatchingIndexingMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, OpOperand* opOperand);
    static inline AffineMap getLoopsToShapesMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline AffineMap getShapesToLoopsMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<int64_t> getStaticOperandShape(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, OpOperand* opOperand);
    static inline SmallVector<int64_t> getStaticLoopRanges(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    SmallVector<AffineMap> getIndexingMapsArray(::mlir::Operation *tablegen_opaque_val) const;
    AffineMap getMatchingIndexingMap(::mlir::Operation *tablegen_opaque_val, OpOperand*opOperand) const;
    AffineMap getLoopsToShapesMap(::mlir::Operation *tablegen_opaque_val) const;
    AffineMap getShapesToLoopsMap(::mlir::Operation *tablegen_opaque_val) const;
    SmallVector<int64_t> getStaticOperandShape(::mlir::Operation *tablegen_opaque_val, OpOperand*opOperand) const;
    SmallVector<int64_t> getStaticLoopRanges(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct IndexingMapOpInterfaceTrait;

} // namespace detail
class IndexingMapOpInterface : public ::mlir::OpInterface<IndexingMapOpInterface, detail::IndexingMapOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<IndexingMapOpInterface, detail::IndexingMapOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::IndexingMapOpInterfaceTrait<ConcreteOp> {};

  /// Return the indexing maps attribute within the current operation.
  ArrayAttr getIndexingMaps();

  /// Return the indexing maps within the current operation.
  SmallVector<AffineMap> getIndexingMapsArray();

  /// Return the input or output indexing map for `opOperand`.
  AffineMap getMatchingIndexingMap(OpOperand* opOperand);

  /// Hook to provide a custom AffineMap used to compute all the operand
  /// subshapes given loop bounds. This is used to answer the question: "given
  /// an iteration space over the codomain, what are the subshapes of the
  /// operands involved in the computation".
  /// The default behavior is to just concatenate all the indexing maps.
  /// A custom AffineMap allows providing a map that can be used to
  /// compute subshapes even in cases where the concatenation of indexing maps
  /// (i.e. the data traversal order) is not a simple permutation of the loop
  /// traversal order. It is then possible to define ops with skewed data
  /// traversal order for which we can still easily compute hyperrectangular
  /// loop bounds and subviews.
  AffineMap getLoopsToShapesMap();

  /// Hook to provide a custom AffineMap used to construct the
  /// hyperrectangular loop iteration space given all the operand subshapes.
  /// This is used to answer the question:
  /// "Given a list of operand ranges, what is the subportion of the iteration
  /// space involved in the computation".
  /// This is the inverse problem of `getLoopsToShapesMap`.
  /// Return the empty AffineMap when such an AffineMap cannot be constructed.
  /// The default behavior is based on a very simple inference procedure that
  /// only works with permutation affine maps.
  /// A more advanced Tensor-Comprehension like inference is possible but has
  /// proven to be ambiguous in unfavorable case.
  /// A safer and more robust alternative is to allow each op to define
  /// its own AffineMap.
  AffineMap getShapesToLoopsMap();

  /// Returns the static shape of the underlying operand (note this is
  /// op-specific behavior).
  /// Returns ShapedType::kDynamic for non-statically-known loop ranges.
  SmallVector<int64_t> getStaticOperandShape(OpOperand* opOperand);

  /// Returns loop ranges by composing `getShapesToLoopsMap()` with the
  /// flattened list of operand shapes.
  /// Returns ShapedType::kDynamic for non-statically-known loop ranges.
  SmallVector<int64_t> getStaticLoopRanges();

    // Verifier implementation for IndexingMapOpInterface.
    // This must be called manually as part of other verifiers so that the
    // verification order, and meaningful error messages, are not preempted.
    LogicalResult verifyImpl();
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteOp>
  struct IndexingMapOpInterfaceTrait : public ::mlir::OpInterface<IndexingMapOpInterface, detail::IndexingMapOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Return the indexing maps within the current operation.
    SmallVector<AffineMap> getIndexingMapsArray() {
      auto range = (*static_cast<ConcreteOp *>(this)).getIndexingMaps()
          .template getAsValueRange<AffineMapAttr>();
        return {range.begin(), range.end()};
    }

    /// Return the input or output indexing map for `opOperand`.
    AffineMap getMatchingIndexingMap(OpOperand* opOperand) {
      assert(opOperand->getOwner() == this->getOperation());
        auto indexingMaps =
          (*static_cast<ConcreteOp *>(this)).getIndexingMaps().template getAsValueRange<AffineMapAttr>();
        return *(indexingMaps.begin() + opOperand->getOperandNumber());
    }

    /// Hook to provide a custom AffineMap used to compute all the operand
    /// subshapes given loop bounds. This is used to answer the question: "given
    /// an iteration space over the codomain, what are the subshapes of the
    /// operands involved in the computation".
    /// The default behavior is to just concatenate all the indexing maps.
    /// A custom AffineMap allows providing a map that can be used to
    /// compute subshapes even in cases where the concatenation of indexing maps
    /// (i.e. the data traversal order) is not a simple permutation of the loop
    /// traversal order. It is then possible to define ops with skewed data
    /// traversal order for which we can still easily compute hyperrectangular
    /// loop bounds and subviews.
    AffineMap getLoopsToShapesMap() {
      auto maps =  (*static_cast<ConcreteOp *>(this)).getIndexingMapsArray();
        return concatAffineMaps(maps, (*static_cast<ConcreteOp *>(this)).getContext());
    }

    /// Hook to provide a custom AffineMap used to construct the
    /// hyperrectangular loop iteration space given all the operand subshapes.
    /// This is used to answer the question:
    /// "Given a list of operand ranges, what is the subportion of the iteration
    /// space involved in the computation".
    /// This is the inverse problem of `getLoopsToShapesMap`.
    /// Return the empty AffineMap when such an AffineMap cannot be constructed.
    /// The default behavior is based on a very simple inference procedure that
    /// only works with permutation affine maps.
    /// A more advanced Tensor-Comprehension like inference is possible but has
    /// proven to be ambiguous in unfavorable case.
    /// A safer and more robust alternative is to allow each op to define
    /// its own AffineMap.
    AffineMap getShapesToLoopsMap() {
      return inversePermutation((*static_cast<ConcreteOp *>(this)).getLoopsToShapesMap());
    }

    /// Returns the static shape of the underlying operand (note this is
    /// op-specific behavior).
    /// Returns ShapedType::kDynamic for non-statically-known loop ranges.
    SmallVector<int64_t> getStaticOperandShape(OpOperand* opOperand) {
      SmallVector<int64_t> res;
        llvm::append_range(res, (*static_cast<ConcreteOp *>(this)).getShape(opOperand));
        return res;
    }

    /// Returns loop ranges by composing `getShapesToLoopsMap()` with the
    /// flattened list of operand shapes.
    /// Returns ShapedType::kDynamic for non-statically-known loop ranges.
    SmallVector<int64_t> getStaticLoopRanges() {
      SmallVector<int64_t> allShapesSizes;
        for (OpOperand &opOperand : this->getOperation()->getOpOperands())
          llvm::append_range(allShapesSizes, (*static_cast<ConcreteOp *>(this)).getShape(&opOperand));
        AffineMap invertedMap = (*static_cast<ConcreteOp *>(this)).getShapesToLoopsMap();
        assert(invertedMap && "expected a valid op");
        return invertedMap.compose(allShapesSizes);
    }
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteOp>
ArrayAttr detail::IndexingMapOpInterfaceInterfaceTraits::Model<ConcreteOp>::getIndexingMaps(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getIndexingMaps();
}
template<typename ConcreteOp>
SmallVector<AffineMap> detail::IndexingMapOpInterfaceInterfaceTraits::Model<ConcreteOp>::getIndexingMapsArray(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getIndexingMapsArray();
}
template<typename ConcreteOp>
AffineMap detail::IndexingMapOpInterfaceInterfaceTraits::Model<ConcreteOp>::getMatchingIndexingMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, OpOperand* opOperand) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getMatchingIndexingMap(opOperand);
}
template<typename ConcreteOp>
AffineMap detail::IndexingMapOpInterfaceInterfaceTraits::Model<ConcreteOp>::getLoopsToShapesMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLoopsToShapesMap();
}
template<typename ConcreteOp>
AffineMap detail::IndexingMapOpInterfaceInterfaceTraits::Model<ConcreteOp>::getShapesToLoopsMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getShapesToLoopsMap();
}
template<typename ConcreteOp>
SmallVector<int64_t> detail::IndexingMapOpInterfaceInterfaceTraits::Model<ConcreteOp>::getStaticOperandShape(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, OpOperand* opOperand) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getStaticOperandShape(opOperand);
}
template<typename ConcreteOp>
SmallVector<int64_t> detail::IndexingMapOpInterfaceInterfaceTraits::Model<ConcreteOp>::getStaticLoopRanges(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getStaticLoopRanges();
}
template<typename ConcreteOp>
ArrayAttr detail::IndexingMapOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getIndexingMaps(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getIndexingMaps(tablegen_opaque_val);
}
template<typename ConcreteOp>
SmallVector<AffineMap> detail::IndexingMapOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getIndexingMapsArray(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getIndexingMapsArray(tablegen_opaque_val);
}
template<typename ConcreteOp>
AffineMap detail::IndexingMapOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getMatchingIndexingMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, OpOperand* opOperand) {
  return static_cast<const ConcreteOp *>(impl)->getMatchingIndexingMap(tablegen_opaque_val, opOperand);
}
template<typename ConcreteOp>
AffineMap detail::IndexingMapOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getLoopsToShapesMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLoopsToShapesMap(tablegen_opaque_val);
}
template<typename ConcreteOp>
AffineMap detail::IndexingMapOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getShapesToLoopsMap(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getShapesToLoopsMap(tablegen_opaque_val);
}
template<typename ConcreteOp>
SmallVector<int64_t> detail::IndexingMapOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getStaticOperandShape(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, OpOperand* opOperand) {
  return static_cast<const ConcreteOp *>(impl)->getStaticOperandShape(tablegen_opaque_val, opOperand);
}
template<typename ConcreteOp>
SmallVector<int64_t> detail::IndexingMapOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getStaticLoopRanges(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getStaticLoopRanges(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
SmallVector<AffineMap> detail::IndexingMapOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getIndexingMapsArray(::mlir::Operation *tablegen_opaque_val) const {
auto range = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getIndexingMaps()
          .template getAsValueRange<AffineMapAttr>();
        return {range.begin(), range.end()};
}
template<typename ConcreteModel, typename ConcreteOp>
AffineMap detail::IndexingMapOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getMatchingIndexingMap(::mlir::Operation *tablegen_opaque_val, OpOperand*opOperand) const {
assert(opOperand->getOwner() == this->getOperation());
        auto indexingMaps =
          (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getIndexingMaps().template getAsValueRange<AffineMapAttr>();
        return *(indexingMaps.begin() + opOperand->getOperandNumber());
}
template<typename ConcreteModel, typename ConcreteOp>
AffineMap detail::IndexingMapOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getLoopsToShapesMap(::mlir::Operation *tablegen_opaque_val) const {
auto maps =  (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getIndexingMapsArray();
        return concatAffineMaps(maps, (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getContext());
}
template<typename ConcreteModel, typename ConcreteOp>
AffineMap detail::IndexingMapOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getShapesToLoopsMap(::mlir::Operation *tablegen_opaque_val) const {
return inversePermutation((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLoopsToShapesMap());
}
template<typename ConcreteModel, typename ConcreteOp>
SmallVector<int64_t> detail::IndexingMapOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getStaticOperandShape(::mlir::Operation *tablegen_opaque_val, OpOperand*opOperand) const {
SmallVector<int64_t> res;
        llvm::append_range(res, (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getShape(opOperand));
        return res;
}
template<typename ConcreteModel, typename ConcreteOp>
SmallVector<int64_t> detail::IndexingMapOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getStaticLoopRanges(::mlir::Operation *tablegen_opaque_val) const {
SmallVector<int64_t> allShapesSizes;
        for (OpOperand &opOperand : this->getOperation()->getOpOperands())
          llvm::append_range(allShapesSizes, (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getShape(&opOperand));
        AffineMap invertedMap = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getShapesToLoopsMap();
        assert(invertedMap && "expected a valid op");
        return invertedMap.compose(allShapesSizes);
}

} // namespace mlir
