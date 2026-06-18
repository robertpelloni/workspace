/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ArithBase.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::arith {

/// The arith dialect is intended to hold basic integer and floating point
///     mathematical operations. This includes unary, binary, and ternary arithmetic
///     ops, bitwise and shift ops, cast ops, and compare ops. Operations in this
///     dialect also accept vectors and tensors of integers or floats. The dialect
///     assumes integers are represented by bitvectors with a two's complement
///     representation. Unless otherwise stated, the operations within this dialect
///     propagate poison values, i.e., if any of its inputs are poison, then the
///     output is poison. Unless otherwise stated, operations applied to `vector`
///     and `tensor` values propagates poison elementwise.
class ArithDialect : public ::mlir::Dialect {
  explicit ArithDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~ArithDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("arith");
  }

  /// Parse an attribute registered to this dialect.
  ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                   ::mlir::Type type) const override;

  /// Print an attribute registered to this dialect.
  void printAttribute(::mlir::Attribute attr,
                      ::mlir::DialectAsmPrinter &os) const override;

  /// Materialize a single constant operation from a given attribute value with
  /// the desired resultant type.
  ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                         ::mlir::Attribute value,
                                         ::mlir::Type type,
                                         ::mlir::Location loc) override;
};

} // namespace mlir::arith
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::arith::ArithDialect)
