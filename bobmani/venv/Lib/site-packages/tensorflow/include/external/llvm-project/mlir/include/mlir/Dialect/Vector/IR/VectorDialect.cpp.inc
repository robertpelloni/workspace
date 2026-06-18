/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Vector.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::vector::VectorDialect)
namespace mlir::vector {


VectorDialect::VectorDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<VectorDialect>())
    
     {
  getContext()->loadDialect<arith::ArithDialect>();
  getContext()->loadDialect<ub::UBDialect>();
  initialize();
}

VectorDialect::~VectorDialect() = default;


} // namespace mlir::vector
