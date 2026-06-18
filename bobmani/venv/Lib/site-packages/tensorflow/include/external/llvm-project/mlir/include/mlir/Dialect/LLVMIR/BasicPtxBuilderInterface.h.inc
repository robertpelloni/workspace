/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::NVVM {

/// This interface is used to generate inline assembly with PTX for basic 
///     operations. It's utilized in the `convert-nvvm-to-llvm pass` to lower 
///     NVVM Ops that implement this interface to PTX (parallel thread execution) 
///     using inline assembly Ops. Interface methods play a crucial role in this 
///     lowering process.
/// 
///     Here's an example of an Op with the `BasicPtxBuilderOpInterface`:    
///     ```tablegen
///       def NVVM_SpecialOp : NVVM_Op<"special.op",
///           [DeclareOpInterfaceMethods<BasicPtxBuilderOpInterface>]>,  
///         Results<(outs LLVM_Type:$res)>,
///         Arguments<(ins LLVM_i64ptr_any:$op1, I32:$op2)> {
///         ...
///         let extraClassDefinition = [{
///           std::string $cppClass::getPtx() { 
///             return std::string("special.op %0, %1, %2;"); 
///           }
///      } ];
///     ```
/// 
///     In the above NVVM Op example:
///     ```mlir
///       %0 = nvvm.special.op %1, %2 : !llvm.ptr, i32 -> i32
///     ```
/// 
///     The `convert-nvvm-to-llvm` pass generates the inline assembly like below. 
///     The order of arguments is retained, and the read and write modifiers are 
///     set based on the input and result types:
///     ```mlir
///       %0 = llvm.inline_asm 
///                 has_side_effects 
///                 asm_dialect = 
///                 att "special.op %0, %1, %2;", "=r,l,r" %arg0, %arg1 
///                 : (!llvm.ptr, i32) -> i32
///     ```
class BasicPtxBuilderInterface;

} // namespace mlir::NVVM
namespace mlir::NVVM {

/// This interface is used to generate inline assembly with PTX for basic 
///     operations. It's utilized in the `convert-nvvm-to-llvm pass` to lower 
///     NVVM Ops that implement this interface to PTX (parallel thread execution) 
///     using inline assembly Ops. Interface methods play a crucial role in this 
///     lowering process.
/// 
///     Here's an example of an Op with the `BasicPtxBuilderOpInterface`:    
///     ```tablegen
///       def NVVM_SpecialOp : NVVM_Op<"special.op",
///           [DeclareOpInterfaceMethods<BasicPtxBuilderOpInterface>]>,  
///         Results<(outs LLVM_Type:$res)>,
///         Arguments<(ins LLVM_i64ptr_any:$op1, I32:$op2)> {
///         ...
///         let extraClassDefinition = [{
///           std::string $cppClass::getPtx() { 
///             return std::string("special.op %0, %1, %2;"); 
///           }
///      } ];
///     ```
/// 
///     In the above NVVM Op example:
///     ```mlir
///       %0 = nvvm.special.op %1, %2 : !llvm.ptr, i32 -> i32
///     ```
/// 
///     The `convert-nvvm-to-llvm` pass generates the inline assembly like below. 
///     The order of arguments is retained, and the read and write modifiers are 
///     set based on the input and result types:
///     ```mlir
///       %0 = llvm.inline_asm 
///                 has_side_effects 
///                 asm_dialect = 
///                 att "special.op %0, %1, %2;", "=r,l,r" %arg0, %arg1 
///                 : (!llvm.ptr, i32) -> i32
///     ```
namespace detail {
struct BasicPtxBuilderInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    std::optional<::mlir::Value> (*getPredicate)(const Concept *impl, ::mlir::Operation *);
    std::string (*getPtx)(const Concept *impl, ::mlir::Operation *);
    bool (*hasIntrinsic)(const Concept *impl, ::mlir::Operation *);
    bool (*hasSideEffect)(const Concept *impl, ::mlir::Operation *);
    ::mlir::Value (*makeConstantI32)(const Concept *impl, ::mlir::Operation *, ::mlir::RewriterBase &, int);
    bool (*getAsmValues)(const Concept *impl, ::mlir::Operation *, ::mlir::RewriterBase &, llvm::SmallVectorImpl<std::pair<mlir::Value, mlir::NVVM::PTXRegisterMod>>&);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::NVVM::BasicPtxBuilderInterface;
    Model() : Concept{getPredicate, getPtx, hasIntrinsic, hasSideEffect, makeConstantI32, getAsmValues} {}

    static inline std::optional<::mlir::Value> getPredicate(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline std::string getPtx(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool hasIntrinsic(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool hasSideEffect(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Value makeConstantI32(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase & rewriter, int val);
    static inline bool getAsmValues(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase & rewriter, llvm::SmallVectorImpl<std::pair<mlir::Value, mlir::NVVM::PTXRegisterMod>>& asmValues);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::NVVM::BasicPtxBuilderInterface;
    FallbackModel() : Concept{getPredicate, getPtx, hasIntrinsic, hasSideEffect, makeConstantI32, getAsmValues} {}

    static inline std::optional<::mlir::Value> getPredicate(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline std::string getPtx(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool hasIntrinsic(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool hasSideEffect(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Value makeConstantI32(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase & rewriter, int val);
    static inline bool getAsmValues(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase & rewriter, llvm::SmallVectorImpl<std::pair<mlir::Value, mlir::NVVM::PTXRegisterMod>>& asmValues);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    std::optional<::mlir::Value> getPredicate(::mlir::Operation *tablegen_opaque_val) const;
    bool hasIntrinsic(::mlir::Operation *tablegen_opaque_val) const;
    bool hasSideEffect(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::Value makeConstantI32(::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase &rewriter, int val) const;
    bool getAsmValues(::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase &rewriter, llvm::SmallVectorImpl<std::pair<mlir::Value, mlir::NVVM::PTXRegisterMod>>&asmValues) const;
  };
};
template <typename ConcreteOp>
struct BasicPtxBuilderInterfaceTrait;

} // namespace detail
class BasicPtxBuilderInterface : public ::mlir::OpInterface<BasicPtxBuilderInterface, detail::BasicPtxBuilderInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<BasicPtxBuilderInterface, detail::BasicPtxBuilderInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::BasicPtxBuilderInterfaceTrait<ConcreteOp> {};

  /// Optional function for setting a predicate, which 
  /// always returns a `PtxPredicate` value of type i1. If no predicate is 
  /// provided, the instruction is unguarded; otherwise, it's guarded by the 
  /// predicate value. The `PtxPredicate` value must always be the last argument. 
  /// The provided PTX code by `getPtx` should not include the predicate usage.
  /// The interface automatically handles predicate usage in the generated
  /// PTX code when necessary.
  std::optional<::mlir::Value> getPredicate();

  /// Returns PTX assembly with operand number.
  std::string getPtx();

  /// This function indicates whether the operation is supported by LLVM 
  /// intrinsics. It's particularly useful for operations that have 
  /// specific cases with LLVM intrinsic support.
  bool hasIntrinsic();

  /// Return whether the operation has memory side effects.
  bool hasSideEffect();

  /// Helper function to generate i32 constant value.
  ::mlir::Value makeConstantI32(::mlir::RewriterBase & rewriter, int val);

  /// This function supplies the necessary arguments for passing PTX code,
  /// following this order:
  ///  1) Adds results 
  ///  2) Adds operands 
  ///  3) Adds attributes
  ///  Returns true if the OP is going to do register mapping itself
  bool getAsmValues(::mlir::RewriterBase & rewriter, llvm::SmallVectorImpl<std::pair<mlir::Value, mlir::NVVM::PTXRegisterMod>>& asmValues);
};

} // namespace mlir::NVVM
namespace mlir::NVVM::detail {

  template <typename ConcreteOp>
  struct BasicPtxBuilderInterfaceTrait : public ::mlir::OpInterface<BasicPtxBuilderInterface, detail::BasicPtxBuilderInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Optional function for setting a predicate, which 
    /// always returns a `PtxPredicate` value of type i1. If no predicate is 
    /// provided, the instruction is unguarded; otherwise, it's guarded by the 
    /// predicate value. The `PtxPredicate` value must always be the last argument. 
    /// The provided PTX code by `getPtx` should not include the predicate usage.
    /// The interface automatically handles predicate usage in the generated
    /// PTX code when necessary.
    std::optional<::mlir::Value> getPredicate() {
      return {};
    }

    /// This function indicates whether the operation is supported by LLVM 
    /// intrinsics. It's particularly useful for operations that have 
    /// specific cases with LLVM intrinsic support.
    bool hasIntrinsic() {
      return false;
    }

    /// Return whether the operation has memory side effects.
    bool hasSideEffect() {
      return true;
    }

    /// Helper function to generate i32 constant value.
    ::mlir::Value makeConstantI32(::mlir::RewriterBase & rewriter, int val) {
      mlir::Operation* op = (*static_cast<ConcreteOp *>(this));
            return LLVM::ConstantOp::create(rewriter,
              op->getLoc(), rewriter.getIntegerType(32), val);
    }

    /// This function supplies the necessary arguments for passing PTX code,
    /// following this order:
    ///  1) Adds results 
    ///  2) Adds operands 
    ///  3) Adds attributes
    ///  Returns true if the OP is going to do register mapping itself
    bool getAsmValues(::mlir::RewriterBase & rewriter, llvm::SmallVectorImpl<std::pair<mlir::Value, mlir::NVVM::PTXRegisterMod>>& asmValues) {
      mlir::Operation* op = (*static_cast<ConcreteOp *>(this));
           
           // Step 1. Add results
            for (auto val : op->getResults()) 
              asmValues.push_back({val, mlir::NVVM::PTXRegisterMod::Write});

           // Step 2. Add operands
           for (auto val : op->getOperands()) 
            asmValues.push_back({val, mlir::NVVM::PTXRegisterMod::Read});
           
           // Step 3. Add attributes
           for (auto attr : op->getAttrs()) {
            if (auto intAttr = dyn_cast<mlir::IntegerAttr>(attr.getValue())) {
             ::mlir::Value val = makeConstantI32(rewriter, intAttr.getInt());
             asmValues.push_back({val, mlir::NVVM::PTXRegisterMod::Read});
             }
           }
           return false; // No manual mapping needed
    }
  };

} // namespace mlir::NVVM::detail
namespace mlir::NVVM {

template<typename ConcreteOp>
std::optional<::mlir::Value> detail::BasicPtxBuilderInterfaceInterfaceTraits::Model<ConcreteOp>::getPredicate(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPredicate();
}
template<typename ConcreteOp>
std::string detail::BasicPtxBuilderInterfaceInterfaceTraits::Model<ConcreteOp>::getPtx(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPtx();
}
template<typename ConcreteOp>
bool detail::BasicPtxBuilderInterfaceInterfaceTraits::Model<ConcreteOp>::hasIntrinsic(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).hasIntrinsic();
}
template<typename ConcreteOp>
bool detail::BasicPtxBuilderInterfaceInterfaceTraits::Model<ConcreteOp>::hasSideEffect(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).hasSideEffect();
}
template<typename ConcreteOp>
::mlir::Value detail::BasicPtxBuilderInterfaceInterfaceTraits::Model<ConcreteOp>::makeConstantI32(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase & rewriter, int val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).makeConstantI32(rewriter, val);
}
template<typename ConcreteOp>
bool detail::BasicPtxBuilderInterfaceInterfaceTraits::Model<ConcreteOp>::getAsmValues(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase & rewriter, llvm::SmallVectorImpl<std::pair<mlir::Value, mlir::NVVM::PTXRegisterMod>>& asmValues) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getAsmValues(rewriter, asmValues);
}
template<typename ConcreteOp>
std::optional<::mlir::Value> detail::BasicPtxBuilderInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPredicate(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPredicate(tablegen_opaque_val);
}
template<typename ConcreteOp>
std::string detail::BasicPtxBuilderInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPtx(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPtx(tablegen_opaque_val);
}
template<typename ConcreteOp>
bool detail::BasicPtxBuilderInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::hasIntrinsic(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->hasIntrinsic(tablegen_opaque_val);
}
template<typename ConcreteOp>
bool detail::BasicPtxBuilderInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::hasSideEffect(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->hasSideEffect(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::Value detail::BasicPtxBuilderInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::makeConstantI32(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase & rewriter, int val) {
  return static_cast<const ConcreteOp *>(impl)->makeConstantI32(tablegen_opaque_val, rewriter, val);
}
template<typename ConcreteOp>
bool detail::BasicPtxBuilderInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getAsmValues(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase & rewriter, llvm::SmallVectorImpl<std::pair<mlir::Value, mlir::NVVM::PTXRegisterMod>>& asmValues) {
  return static_cast<const ConcreteOp *>(impl)->getAsmValues(tablegen_opaque_val, rewriter, asmValues);
}
template<typename ConcreteModel, typename ConcreteOp>
std::optional<::mlir::Value> detail::BasicPtxBuilderInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPredicate(::mlir::Operation *tablegen_opaque_val) const {
return {};
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::BasicPtxBuilderInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::hasIntrinsic(::mlir::Operation *tablegen_opaque_val) const {
return false;
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::BasicPtxBuilderInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::hasSideEffect(::mlir::Operation *tablegen_opaque_val) const {
return true;
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Value detail::BasicPtxBuilderInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::makeConstantI32(::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase &rewriter, int val) const {
mlir::Operation* op = (llvm::cast<ConcreteOp>(tablegen_opaque_val));
            return LLVM::ConstantOp::create(rewriter,
              op->getLoc(), rewriter.getIntegerType(32), val);
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::BasicPtxBuilderInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getAsmValues(::mlir::Operation *tablegen_opaque_val, ::mlir::RewriterBase &rewriter, llvm::SmallVectorImpl<std::pair<mlir::Value, mlir::NVVM::PTXRegisterMod>>&asmValues) const {
mlir::Operation* op = (llvm::cast<ConcreteOp>(tablegen_opaque_val));
           
           // Step 1. Add results
            for (auto val : op->getResults()) 
              asmValues.push_back({val, mlir::NVVM::PTXRegisterMod::Write});

           // Step 2. Add operands
           for (auto val : op->getOperands()) 
            asmValues.push_back({val, mlir::NVVM::PTXRegisterMod::Read});
           
           // Step 3. Add attributes
           for (auto attr : op->getAttrs()) {
            if (auto intAttr = dyn_cast<mlir::IntegerAttr>(attr.getValue())) {
             ::mlir::Value val = makeConstantI32(rewriter, intAttr.getInt());
             asmValues.push_back({val, mlir::NVVM::PTXRegisterMod::Read});
             }
           }
           return false; // No manual mapping needed
}

} // namespace mlir::NVVM
