/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: AMX.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::amx {

/// The Intel Advanced Matrix Extensions (AMX) provide a tile matrix
///     multiply unit (TMUL), a tile control register (TILECFG), and eight
///     tile registers TMM0 through TMM7 (TILEDATA).
/// 
///     This `AMX` dialect provides a bridge between MLIR concepts such as
///     vectors and memrefs and the lower level LLVM IR support of AMX.
/// 
///     Note that since configuration changes (implicit at dialect level) are
///     costly, it is highly recommended to use the AMX dialect on same-shaped
///     vectors, at least within a single method.
/// 
///     For details, see the Intel documentation:
///     https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html
class AMXDialect : public ::mlir::Dialect {
  explicit AMXDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~AMXDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("amx");
  }

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;
};

} // namespace mlir::amx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::amx::AMXDialect)
