/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: PtrDialect.td                                                        *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::ptr {

/// Pointer dialect
/// The pointer dialect provides types and operations for representing and
///     interacting with pointer values in MLIR, such as loading and storing values
///     from/to memory addresses.
/// 
///     The dialect's main type is an opaque pointer (`ptr`) that can be
///     parameterized by a memory space. This type represents a handle to an object
///     in memory, or target-dependent values like `nullptr`. Further, the dialect
///     assumes that the minimum addressable unit by a pointer is a byte. However,
///     the dialect does not make assumptions about the size of a byte, which is
///     considered a target-specific property.
class PtrDialect : public ::mlir::Dialect {
  explicit PtrDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~PtrDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("ptr");
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

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::PtrDialect)
