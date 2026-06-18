/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: MathBase.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::math {

/// The math dialect is intended to hold mathematical operations on integer and
///     floating types beyond simple arithmetics. Each operation works on scalar, vector
///     or tensor type. On vector and tensor type operations apply elementwise unless
///     explicitly specified otherwise. As an example, the floating point absolute value
///     can be expressed as:
/// 
///     ```mlir
///     // Scalar absolute value.
///     %a = math.absf %b : f64
/// 
///     // Vector elementwise absolute value.
///     %f = math.absf %g : vector<4xf32>
/// 
///     // Tensor elementwise absolute value.
///     %x = math.absf %y : tensor<4x?xf8>
///     ```
class MathDialect : public ::mlir::Dialect {
  explicit MathDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~MathDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("math");
  }

  /// Materialize a single constant operation from a given attribute value with
  /// the desired resultant type.
  ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                         ::mlir::Attribute value,
                                         ::mlir::Type type,
                                         ::mlir::Location loc) override;
};

} // namespace mlir::math
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::math::MathDialect)
