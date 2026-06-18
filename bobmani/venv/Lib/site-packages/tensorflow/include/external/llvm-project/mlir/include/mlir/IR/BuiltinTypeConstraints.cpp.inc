
bool isValidVectorTypeElementType(::mlir::Type type) {
return ((::llvm::isa<::mlir::VectorElementTypeInterface>(type)));
}
