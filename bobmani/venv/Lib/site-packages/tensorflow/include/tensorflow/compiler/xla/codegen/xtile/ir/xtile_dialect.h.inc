/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: xtile_dialect.td                                                     *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace xla::xtile {

/// This dialect contains ops required for lowering HLO to LLVM.
class XTileDialect : public ::mlir::Dialect {
  explicit XTileDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~XTileDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("xtile");
  }

  /// Parse an attribute registered to this dialect.
  ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                   ::mlir::Type type) const override;

  /// Print an attribute registered to this dialect.
  void printAttribute(::mlir::Attribute attr,
                      ::mlir::DialectAsmPrinter &os) const override;
};

} // namespace xla::xtile
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::xtile::XTileDialect)
