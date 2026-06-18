/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get a name to use when generating an alias for this attribute.
::mlir::OpAsmAliasResult mlir::OpAsmAttrInterface::getAlias(::llvm::raw_ostream& os) const {
      return getImpl()->getAlias(getImpl(), *this, os);
  }
