/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: PDLOps.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::pdl {

/// High level pattern definition dialect
/// PDL presents a high level abstraction for the rewrite pattern infrastructure
///     available in MLIR. This abstraction allows for representing patterns
///     transforming MLIR, as MLIR. This allows for applying all of the benefits
///     that the general MLIR infrastructure provides, to the infrastructure itself.
///     This means that pattern matching can be more easily verified for
///     correctness, targeted by frontends, and optimized.
/// 
///     PDL abstracts over various different aspects of patterns and core MLIR data
///     structures. Patterns are specified via a `pdl.pattern` operation. These
///     operations contain a region body for the "matcher" code, and terminate with
///     a `pdl.rewrite` that either dispatches to an external rewriter or contains
///     a region for the rewrite specified via `pdl`. The types of values in `pdl`
///     are handle types to MLIR C++ types, with `!pdl.attribute`, `!pdl.operation`,
///     `!pdl.value`, and `!pdl.type` directly mapping to `mlir::Attribute`,
///     `mlir::Operation*`, `mlir::Value`, and `mlir::Type` respectively.
/// 
///     An example pattern is shown below:
/// 
///     ```mlir
///     // pdl.pattern contains metadata similarly to a `RewritePattern`.
///     pdl.pattern : benefit(1) {
///       // External input operand values are specified via `pdl.operand` operations.
///       // Result types are constrainted via `pdl.type` operations.
/// 
///       %resultType = pdl.type
///       %inputOperand = pdl.operand
///       %root = pdl.operation "foo.op"(%inputOperand) -> %resultType
///       pdl.rewrite %root {
///         pdl.replace %root with (%inputOperand)
///       }
///     }
///     ```
/// 
///     The above pattern simply replaces an operation with its first operand. Note
///     how the input operation is specified structurally, similarly to how it would
///     look in memory. This is a simple example and pdl provides support for many
///     other features such as applying external constraints or external generator
///     methods. These features and more are detailed below.
class PDLDialect : public ::mlir::Dialect {
  explicit PDLDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~PDLDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("pdl");
  }

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;

    void registerTypes();
  };

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::PDLDialect)
