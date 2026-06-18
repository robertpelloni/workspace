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
namespace mlir::omp {

/// Type for representing omp map clause bounds information
class MapBoundsType;
/// Type for representing a reference to a canonical loop
/// A variable of type CanonicalLoopInfo refers to an OpenMP-compatible
///     canonical loop in the same function. Values of this type are not
///     available at runtime and therefore cannot be used by the program itself,
///     i.e. an opaque type. It is similar to the transform dialect's
///     `!transform.interface` type, but instead of implementing an interface
///     for each transformation, the OpenMP dialect itself defines possible
///     operations on this type.
/// 
///     A value of type CanonicalLoopInfoType (in the following: CLI) value can be
/// 
///     1. created by omp.new_cli.
///     2. passed to omp.canonical_loop to associate the loop to that CLI. A CLI
///        can only be associated once.
///     3. passed to an omp loop transformation operation that modifies the loop
///        associated with the CLI. The CLI is the "applyee" and the operation is
///        the consumer. A CLI can only be consumed once.
///     4. passed to an omp loop transformation operation to associate the cli with
///        a result of that transformation. The CLI is the "generatee" and the
///        operation is the generator.
/// 
///     A CLI cannot
/// 
///     1. be returned from a function.
///     2. be passed to operations that are not specifically designed to take a
///        CanonicalLoopInfoType, including AnyType.
/// 
///     A CLI directly corresponds to an object of
///     OpenMPIRBuilder's CanonicalLoopInfo struct when lowering to LLVM-IR.
class CanonicalLoopInfoType;
class MapBoundsType : public ::mlir::Type::TypeBase<MapBoundsType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "omp.map_bounds_ty";
  static constexpr ::llvm::StringLiteral dialectName = "omp";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"map_bounds_ty"};
  }

};
class CanonicalLoopInfoType : public ::mlir::Type::TypeBase<CanonicalLoopInfoType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "omp.cli";
  static constexpr ::llvm::StringLiteral dialectName = "omp";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cli"};
  }

};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::MapBoundsType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::CanonicalLoopInfoType)

#endif // GET_TYPEDEF_CLASSES

