/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ShardOps.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::shard::ShardDialect)
namespace mlir::shard {


ShardDialect::ShardDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<ShardDialect>())
    
     {
  getContext()->loadDialect<arith::ArithDialect>();
  initialize();
}

ShardDialect::~ShardDialect() = default;


} // namespace mlir::shard
