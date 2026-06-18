/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get whether this attr describes a recursive self reference.
bool mlir::LLVM::DIRecursiveTypeAttrInterface::getIsRecSelf() const {
      return getImpl()->getIsRecSelf(getImpl(), *this);
  }

/// Get the recursive ID used for matching "rec-decl" with "rec-self".
/// If this attr instance is not recursive, return a null attribute.
DistinctAttr mlir::LLVM::DIRecursiveTypeAttrInterface::getRecId() const {
      return getImpl()->getRecId(getImpl(), *this);
  }

/// Get a copy of this type attr but with the recursive ID set to `recId`.
DIRecursiveTypeAttrInterface mlir::LLVM::DIRecursiveTypeAttrInterface::withRecId(DistinctAttr recId) const {
      return getImpl()->withRecId(getImpl(), *this, recId);
  }

/// Build a rec-self instance using the provided `recId`.
DIRecursiveTypeAttrInterface mlir::LLVM::DIRecursiveTypeAttrInterface::getRecSelf(DistinctAttr recId) const {
      return getImpl()->getRecSelf(recId);
  }

/// Returns the address space as an unsigned integer.
unsigned mlir::LLVM::LLVMAddrSpaceAttrInterface::getAddressSpace() const {
      return getImpl()->getAddressSpace(getImpl(), *this);
  }

/// Returns the target triple identifier.
StringAttr mlir::LLVM::TargetAttrInterface::getTriple() const {
      return getImpl()->getTriple(getImpl(), *this);
  }

/// Returns the target chip (i.e. "cpu") identifier.
StringAttr mlir::LLVM::TargetAttrInterface::getChip() const {
      return getImpl()->getChip(getImpl(), *this);
  }

/// Returns the target features as a TargetFeaturesAttr.
Attribute mlir::LLVM::TargetAttrInterface::getFeatures() const {
      return getImpl()->getFeatures(getImpl(), *this);
  }

/// Returns the attribute associated with the key.
::mlir::FailureOr<::mlir::Attribute> mlir::LLVM::TargetAttrInterface::query(::mlir::DataLayoutEntryKey key) const {
      return getImpl()->implDLTIQueryInterface->query(getImpl()->implDLTIQueryInterface, *this, key);
  }
