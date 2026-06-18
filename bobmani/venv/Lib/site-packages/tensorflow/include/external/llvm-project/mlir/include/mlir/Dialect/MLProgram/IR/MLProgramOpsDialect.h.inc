/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: MLProgramOps.td                                                      *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::ml_program {

/// The MLProgram dialect contains structural operations and types for
///     defining a compiled Machine-Learning program, as created from common
///     ML frameworks, such as TensorFlow, PyTorch, JAX, etc. It does not itself
///     define computation ops common to such frameworks but establishes a common
///     programming model for establishing modules, functions, globals and
///     memory model components appropriate for such an abstract level of detail.
/// 
///     This dialect is under active development, and while stability is an
///     eventual goal, it is not guaranteed at this juncture. Given the early state,
///     it is recommended to inquire further prior to using this dialect.
class MLProgramDialect : public ::mlir::Dialect {
  explicit MLProgramDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~MLProgramDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("ml_program");
  }

  /// Parse an attribute registered to this dialect.
  ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                   ::mlir::Type type) const override;

  /// Print an attribute registered to this dialect.
  void printAttribute(::mlir::Attribute attr,
                      ::mlir::DialectAsmPrinter &os) const override;

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;
};

} // namespace mlir::ml_program
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ml_program::MLProgramDialect)
