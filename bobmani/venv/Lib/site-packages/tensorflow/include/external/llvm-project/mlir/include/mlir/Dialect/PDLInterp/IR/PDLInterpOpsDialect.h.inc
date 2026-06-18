/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: PDLInterpOps.td                                                      *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::pdl_interp {

/// Interpreted pattern execution dialect
/// The PDL Interpreter dialect provides a lower level abstraction compared to
///     the PDL dialect, and is targeted towards low level optimization and
///     interpreter code generation. The dialect operations encapsulates
///     low-level pattern match and rewrite "primitives", such as navigating the
///     IR (Operation::getOperand), creating new operations (OpBuilder::create),
///     etc. Many of the operations within this dialect also fuse branching control
///     flow with some form of a predicate comparison operation. This type of fusion
///     reduces the amount of work that an interpreter must do when executing.
class PDLInterpDialect : public ::mlir::Dialect {
  explicit PDLInterpDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~PDLInterpDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("pdl_interp");
  }

    /// Returns the name of the function containing the matcher code. This
    /// function is called by the interpreter when matching an operation.
    static StringRef getMatcherFunctionName() { return "matcher"; }

    /// Returns the name of the module containing the rewrite functions. These
    /// functions are invoked by distinct patterns within the matcher function
    /// to rewrite the IR after a successful match.
    static StringRef getRewriterModuleName() { return "rewriters"; }
  };

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::PDLInterpDialect)
