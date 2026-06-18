/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ShapeOps.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::shape {

/// Types and operations for shape dialect
/// This dialect contains operations for shape inference.
/// 
///     Note: Unless explicitly stated, all functions that return a shape and take
///     shapes as input, return the invalid shape if one of its operands is an
///     invalid shape. This avoids flagging multiple errors for one verification
///     failure. The dialect itself does not specify how errors should be combined
///     (there are multiple different options, from always choosing first operand,
///     concatting etc. on how to combine them).
class ShapeDialect : public ::mlir::Dialect {
  explicit ShapeDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~ShapeDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("shape");
  }

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;

  /// Materialize a single constant operation from a given attribute value with
  /// the desired resultant type.
  ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                         ::mlir::Attribute value,
                                         ::mlir::Type type,
                                         ::mlir::Location loc) override;

    /// Provides a hook for verifying dialect attributes attached to the given
    /// op.
    ::llvm::LogicalResult verifyOperationAttribute(
        ::mlir::Operation *op, ::mlir::NamedAttribute attribute) override;
};

} // namespace mlir::shape
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shape::ShapeDialect)
