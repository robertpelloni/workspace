/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace mlir::linalg {

/// allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23
class ElementwiseKindAttr;
/// allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
class UnaryFnAttr;
/// allowed 32-bit signless integer cases: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
class BinaryFnAttr;
/// allowed 32-bit signless integer cases: 0
class TernaryFnAttr;
/// allowed 32-bit signless integer cases: 0, 1
class TypeFnAttr;
/// Iterator type
class IteratorTypeAttr;
namespace detail {

struct ElementwiseKindAttrStorage;

} // namespace detail
class ElementwiseKindAttr : public ::mlir::Attribute::AttrBase<ElementwiseKindAttr, ::mlir::Attribute, detail::ElementwiseKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "linalg.elementwise_kind";
  static constexpr ::llvm::StringLiteral dialectName = "linalg";
  static ElementwiseKindAttr get(::mlir::MLIRContext *context, ::mlir::linalg::ElementwiseKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"elementwise_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::linalg::ElementwiseKind getValue() const;
};
namespace detail {

struct UnaryFnAttrStorage;

} // namespace detail
class UnaryFnAttr : public ::mlir::Attribute::AttrBase<UnaryFnAttr, ::mlir::Attribute, detail::UnaryFnAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "linalg.unary_fn";
  static constexpr ::llvm::StringLiteral dialectName = "linalg";
  static UnaryFnAttr get(::mlir::MLIRContext *context, ::mlir::linalg::UnaryFn value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"unary_fn"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::linalg::UnaryFn getValue() const;
};
namespace detail {

struct BinaryFnAttrStorage;

} // namespace detail
class BinaryFnAttr : public ::mlir::Attribute::AttrBase<BinaryFnAttr, ::mlir::Attribute, detail::BinaryFnAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "linalg.binary_fn";
  static constexpr ::llvm::StringLiteral dialectName = "linalg";
  static BinaryFnAttr get(::mlir::MLIRContext *context, ::mlir::linalg::BinaryFn value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"binary_fn"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::linalg::BinaryFn getValue() const;
};
namespace detail {

struct TernaryFnAttrStorage;

} // namespace detail
class TernaryFnAttr : public ::mlir::Attribute::AttrBase<TernaryFnAttr, ::mlir::Attribute, detail::TernaryFnAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "linalg.ternary_fn";
  static constexpr ::llvm::StringLiteral dialectName = "linalg";
  static TernaryFnAttr get(::mlir::MLIRContext *context, ::mlir::linalg::TernaryFn value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ternary_fn"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::linalg::TernaryFn getValue() const;
};
namespace detail {

struct TypeFnAttrStorage;

} // namespace detail
class TypeFnAttr : public ::mlir::Attribute::AttrBase<TypeFnAttr, ::mlir::Attribute, detail::TypeFnAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "linalg.type_fn";
  static constexpr ::llvm::StringLiteral dialectName = "linalg";
  static TypeFnAttr get(::mlir::MLIRContext *context, ::mlir::linalg::TypeFn value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"type_fn"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::linalg::TypeFn getValue() const;
};
namespace detail {

struct IteratorTypeAttrStorage;

} // namespace detail
class IteratorTypeAttr : public ::mlir::Attribute::AttrBase<IteratorTypeAttr, ::mlir::Attribute, detail::IteratorTypeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "linalg.iterator_type";
  static constexpr ::llvm::StringLiteral dialectName = "linalg";
  static IteratorTypeAttr get(::mlir::MLIRContext *context, ::mlir::utils::IteratorType value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"iterator_type"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::utils::IteratorType getValue() const;
};

} // namespace mlir::linalg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::ElementwiseKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::UnaryFnAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::BinaryFnAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::TernaryFnAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::TypeFnAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::IteratorTypeAttr)

#endif // GET_ATTRDEF_CLASSES

