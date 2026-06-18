/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace mlir::tf_type {

/// This type models a control dependency between two TensorFlow nodes.
class ControlType;
/// This type models an opaque tensor: the shape and dtypes are unknown. This is
///     particularly useful in generic functions.
class OpaqueTensorType;
class ControlType : public ::mlir::Type::TypeBase<ControlType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "tf_type.control";
  static constexpr ::llvm::StringLiteral dialectName = "tf_type";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"control"};
  }

};
class OpaqueTensorType : public ::mlir::Type::TypeBase<OpaqueTensorType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "tf_type.tensor";
  static constexpr ::llvm::StringLiteral dialectName = "tf_type";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tensor"};
  }

};

} // namespace mlir::tf_type
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_type::ControlType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_type::OpaqueTensorType)

#endif // GET_TYPEDEF_CLASSES

