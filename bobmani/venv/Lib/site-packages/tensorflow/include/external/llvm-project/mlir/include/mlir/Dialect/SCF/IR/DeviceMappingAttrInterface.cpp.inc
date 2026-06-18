/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Return mapping as an integer from the attribute.
int64_t mlir::DeviceMappingAttrInterface::getMappingId() const {
      return getImpl()->getMappingId(getImpl(), *this);
  }

/// Return true if the attribute specifies a linear mapping
bool mlir::DeviceMappingAttrInterface::isLinearMapping() const {
      return getImpl()->isLinearMapping(getImpl(), *this);
  }

/// Return the [0..n) relative index of the attribute depending on its group.
/// This can be used to index into a contiguous array.
int64_t mlir::DeviceMappingAttrInterface::getRelativeIndex() const {
      return getImpl()->getRelativeIndex(getImpl(), *this);
  }

/// Create the logical active id for a given physical id.
/// Expects a physicalLinearMappingId of I64Type.
Value mlir::DeviceMaskingAttrInterface::createLogicalLinearMappingId(OpBuilder& builder, Value physicalLinearMappingId) const {
      return getImpl()->createLogicalLinearMappingId(getImpl(), *this, builder, physicalLinearMappingId);
  }

/// Return the dynamic condition determining whether a given physical id is
/// active under the mask.
/// Expects a physicalLinearMappingId of I64Type.
Value mlir::DeviceMaskingAttrInterface::createIsActiveIdPredicate(OpBuilder& builder, Value physicalLinearMappingId) const {
      return getImpl()->createIsActiveIdPredicate(getImpl(), *this, builder, physicalLinearMappingId);
  }

/// Return the maximal number of pysical ids supported.
/// This is to account for temporary implementation limitations (e.g. i64)
/// and fail gracefully with actionnable error messages.
int64_t mlir::DeviceMaskingAttrInterface::getMaxNumPhysicalIds() const {
      return getImpl()->getMaxNumPhysicalIds(getImpl(), *this);
  }
