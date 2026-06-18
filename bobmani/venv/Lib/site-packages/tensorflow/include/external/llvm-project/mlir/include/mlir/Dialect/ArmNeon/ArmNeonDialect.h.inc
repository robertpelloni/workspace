/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ArmNeon.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::arm_neon {


class ArmNeonDialect : public ::mlir::Dialect {
  explicit ArmNeonDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~ArmNeonDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("arm_neon");
  }
};

} // namespace mlir::arm_neon
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::arm_neon::ArmNeonDialect)
