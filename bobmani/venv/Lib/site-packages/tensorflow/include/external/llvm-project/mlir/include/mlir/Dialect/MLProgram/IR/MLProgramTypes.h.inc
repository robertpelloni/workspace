/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace mlir::ml_program {

/// Token for establishing execution ordering in a graph
class TokenType;
class TokenType : public ::mlir::Type::TypeBase<TokenType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "ml_program.token";
  static constexpr ::llvm::StringLiteral dialectName = "ml_program";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"token"};
  }

};

} // namespace mlir::ml_program
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ml_program::TokenType)

#endif // GET_TYPEDEF_CLASSES

