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
namespace mlir::shard {

/// sharding definition
class ShardingType;
class ShardingType : public ::mlir::Type::TypeBase<ShardingType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "shard.sharding";
  static constexpr ::llvm::StringLiteral dialectName = "shard";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sharding"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
};

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ShardingType)

#endif // GET_TYPEDEF_CLASSES

