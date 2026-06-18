/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get a name to use when printing a value of this type.
void mlir::OpAsmTypeInterface::getAsmName(::mlir::OpAsmSetNameFn setNameFn) const {
      return getImpl()->getAsmName(getImpl(), *this, setNameFn);
  }

/// Get a name to use when generating an alias for this type.
::mlir::OpAsmAliasResult mlir::OpAsmTypeInterface::getAlias(::llvm::raw_ostream& os) const {
      return getImpl()->getAlias(getImpl(), *this, os);
  }
