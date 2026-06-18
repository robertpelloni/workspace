/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SCFOps.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::scf {

/// The `scf` (structured control flow) dialect contains operations that
///     represent control flow constructs such as `if` and `for`. Being
///     _structured_ means that the control flow has a structure unlike, for
///     example, `goto`s or `assert`s. Unstructured control flow operations are
///     located in the `cf` (control flow) dialect.
/// 
///     Originally, this dialect was developed as a common lowering stage for the
///     `affine` and `linalg` dialects. Both convert to SCF loops instead of
///     targeting branch-based CFGs directly. Typically, `scf` is lowered to `cf`
///     and then lowered to some final target like LLVM or SPIR-V.
class SCFDialect : public ::mlir::Dialect {
  explicit SCFDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~SCFDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("scf");
  }
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::SCFDialect)
