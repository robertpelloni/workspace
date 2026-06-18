/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// This method checks if it's valid to load a value from the memory space
/// with a specific type, alignment, and atomic ordering.
/// If `emitError` is non-null then the method is allowed to emit errors.
/// Furthermore, if `emitError` is non-null and the result is `false` an
/// error must have been emitted.
bool mlir::ptr::MemorySpaceAttrInterface::isValidLoad(::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const {
      return getImpl()->isValidLoad(getImpl(), *this, type, ordering, alignment, dataLayout, emitError);
  }

/// This method checks if it's valid to store a value in the memory space
/// with a specific type, alignment, and atomic ordering.
/// If `emitError` is non-null then the method is allowed to emit errors.
/// Furthermore, if `emitError` is non-null and the result is `false` an
/// error must have been emitted.
bool mlir::ptr::MemorySpaceAttrInterface::isValidStore(::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const {
      return getImpl()->isValidStore(getImpl(), *this, type, ordering, alignment, dataLayout, emitError);
  }

/// This method checks if it's valid to perform an atomic operation in the
/// memory space with a specific type, alignment, and atomic ordering.
/// If `emitError` is non-null then the method is allowed to emit errors.
/// Furthermore, if `emitError` is non-null and the result is `false` an
/// error must have been emitted.
bool mlir::ptr::MemorySpaceAttrInterface::isValidAtomicOp(::mlir::ptr::AtomicBinOp op, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const {
      return getImpl()->isValidAtomicOp(getImpl(), *this, op, type, ordering, alignment, dataLayout, emitError);
  }

/// This method checks if it's valid to perform an atomic exchange operation
/// in the memory space with a specific type, alignment, and atomic
/// orderings.
/// If `emitError` is non-null then the method is allowed to emit errors.
/// Furthermore, if `emitError` is non-null and the result is `false` an
/// error must have been emitted.
bool mlir::ptr::MemorySpaceAttrInterface::isValidAtomicXchg(::mlir::Type type, ::mlir::ptr::AtomicOrdering successOrdering, ::mlir::ptr::AtomicOrdering failureOrdering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const {
      return getImpl()->isValidAtomicXchg(getImpl(), *this, type, successOrdering, failureOrdering, alignment, dataLayout, emitError);
  }

/// This method checks if it's valid to perform an `addrspacecast` op
/// in the memory space.
/// If `emitError` is non-null then the method is allowed to emit errors.
/// Furthermore, if `emitError` is non-null and the result is `false` an
/// error must have been emitted.
bool mlir::ptr::MemorySpaceAttrInterface::isValidAddrSpaceCast(::mlir::Type tgt, ::mlir::Type src, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const {
      return getImpl()->isValidAddrSpaceCast(getImpl(), *this, tgt, src, emitError);
  }

/// This method checks if it's valid to perform a `ptrtoint` or `inttoptr`
/// op in the memory space.
/// The first type is expected to be integer-like, while the second must be
/// a ptr-like type.
/// If `emitError` is non-null then the method is allowed to emit errors.
/// Furthermore, if `emitError` is non-null and the result is `false` an
/// error must have been emitted.
bool mlir::ptr::MemorySpaceAttrInterface::isValidPtrIntCast(::mlir::Type intLikeTy, ::mlir::Type ptrLikeTy, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const {
      return getImpl()->isValidPtrIntCast(getImpl(), *this, intLikeTy, ptrLikeTy, emitError);
  }
