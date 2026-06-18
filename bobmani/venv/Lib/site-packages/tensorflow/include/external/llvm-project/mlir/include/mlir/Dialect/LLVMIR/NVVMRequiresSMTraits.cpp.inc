/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get the SM version required by the op from the trait
const mlir::NVVM::NVVMCheckSMVersion mlir::NVVM::RequiresSMInterface::getRequiredMinSMVersion() {
      return getImpl()->getRequiredMinSMVersion(getImpl(), getOperation());
  }
