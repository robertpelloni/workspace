/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: PDLInterpOps.td                                                      *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::PDLInterpDialect)
namespace mlir::pdl_interp {


PDLInterpDialect::PDLInterpDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<PDLInterpDialect>())
    
     {
  getContext()->loadDialect<pdl::PDLDialect>();
  initialize();
}

PDLInterpDialect::~PDLInterpDialect() = default;


} // namespace mlir::pdl_interp
