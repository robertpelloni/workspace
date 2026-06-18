/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ControlFlowOps.td                                                    *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::cf {

/// This dialect contains low-level, i.e. non-region based, control flow
///     constructs. These constructs generally represent control flow directly
///     on SSA blocks of a control flow graph.
class ControlFlowDialect : public ::mlir::Dialect {
  explicit ControlFlowDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~ControlFlowDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("cf");
  }
};

} // namespace mlir::cf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::cf::ControlFlowDialect)
