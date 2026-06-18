/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ArmSVE.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::arm_sve {

/// Basic dialect to target Arm SVE architectures
/// This dialect contains the definitions necessary to target specific Arm SVE
///     scalable vector operations.
class ArmSVEDialect : public ::mlir::Dialect {
  explicit ArmSVEDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~ArmSVEDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("arm_sve");
  }
};

} // namespace mlir::arm_sve
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::arm_sve::ArmSVEDialect)
