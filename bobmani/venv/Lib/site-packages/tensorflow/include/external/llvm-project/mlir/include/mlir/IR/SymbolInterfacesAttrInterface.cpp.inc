/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Verify the symbol uses held by this attribute of this operation.
::llvm::LogicalResult mlir::SymbolUserAttrInterface::verifySymbolUses(::mlir::Operation * op, ::mlir::SymbolTableCollection & symbolTable) const {
      return getImpl()->verifySymbolUses(getImpl(), *this, op, symbolTable);
  }
