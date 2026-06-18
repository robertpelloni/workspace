/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: GPUOps.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::gpu::GPUDialect)
namespace mlir::gpu {


GPUDialect::GPUDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<GPUDialect>())
    , knownBlockSizeAttrName(context), knownGridSizeAttrName(context), knownClusterSizeAttrName(context)
     {
  getContext()->loadDialect<arith::ArithDialect>();
  initialize();
}

GPUDialect::~GPUDialect() = default;


} // namespace mlir::gpu
