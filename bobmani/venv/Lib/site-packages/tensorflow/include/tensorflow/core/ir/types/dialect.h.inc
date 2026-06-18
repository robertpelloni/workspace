/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: dialect.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::tf_type {

/// This dialect defines TensorFlow Types.
/// This dialect is only provide types and attributes used by various dialects
///     in TensorFlow, but does not include any operation.
///     It is separated from the other dialect for modularity and binary-size
///     control.
class TFTypeDialect : public ::mlir::Dialect {
  explicit TFTypeDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~TFTypeDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("tf_type");
  }

  /// Parse an attribute registered to this dialect.
  ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                   ::mlir::Type type) const override;

  /// Print an attribute registered to this dialect.
  void printAttribute(::mlir::Attribute attr,
                      ::mlir::DialectAsmPrinter &os) const override;

     ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const;
     void printType(::mlir::Type type, ::mlir::DialectAsmPrinter &printer) const;
  };

} // namespace mlir::tf_type
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_type::TFTypeDialect)
