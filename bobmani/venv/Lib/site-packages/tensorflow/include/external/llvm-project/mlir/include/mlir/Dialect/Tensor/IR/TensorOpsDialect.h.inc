/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: TensorOps.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::tensor {

/// The `tensor` dialect is intended to hold core tensor creation and
///     manipulation ops, which are not strongly associated with any particular
///     other dialect or domain abstraction. The aim for ops in this dialect is
///     that they make sense for any tensor element type. When this is not the
///     case, the op is left to live in other dialects. Examples of element types
///     that could be supported by the `tensor` dialect include:
/// 
///     - representing large, dense aggregations of primitive types, suitable for
///       high-performance numerical computing.
///     - representing shapes in the `shape` dialect, which consist of small 1D
///       tensors of `index` data type.
///     - representing aggregations of strings or “variant” types.
///     - representing large, sparse aggregations of primitive types, suitable for
///       high-performance numerical computing.
/// 
///     Because of this broad element type support and because of the existence of
///     more dedicated dialects, such as the `sparse_tensor` and `linalg` dialects,
///     we prefer for now to keep the `tensor` dialect as small as possible. The
///     expectation is that at some point in the future, the `tensor` dialect’s
///     scope may be broadened through a careful discussion of the tradeoffs.
/// 
///     On the `tensor` type itself, note that it is actually a builtin type (it
///     lives in the builtin dialect), and does not live in this dialect.
///     Furthermore, a `tensor` is an immutable object. For example, this means
///     that a copy will always be made of the `tensor` object when it is passed to
///     the `dest` operand used by some ops in this dialect. As an optimization,
///     an implementation can eliminate these copies during lowering when they
///     are redundant and perform in-place mutation, see the [Destination-Passing
///     Style](
///     https://mlir.llvm.org/docs/Bufferization/#destination-passing-style)
///     documentation for more information.
class TensorDialect : public ::mlir::Dialect {
  explicit TensorDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~TensorDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("tensor");
  }

  /// Register canonicalization patterns.
  void getCanonicalizationPatterns(
      ::mlir::RewritePatternSet &results) const override;

  /// Materialize a single constant operation from a given attribute value with
  /// the desired resultant type.
  ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                         ::mlir::Attribute value,
                                         ::mlir::Type type,
                                         ::mlir::Location loc) override;
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::TensorDialect)
