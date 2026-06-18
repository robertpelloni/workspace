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
namespace mlir::mhlo {

/// XLA precision for an operand. Has backend specific meaning.
class PrecisionAttr;
/// Specifies the desired schedule for the custom-call.
class CustomCallScheduleAttr;
/// Kind of domain metatdata attached to an HLO domain.
class DomainKindAttr;
/// XLA fast fourier transform type.
class FftTypeAttr;
/// Which comparison operation to perform.
class ComparisonDirectionAttr;
/// Which comparison type to use.
class ComparisonTypeAttr;
/// Dequantization mode. Only MIN_COMBINED is supported.
class DequantizeModeAttr;
/// Transpose options
class TransposeAttr;
/// XLA PRNG distribution to be used.
class RngDistributionAttr;
/// fusion kind
class FusionKindAttr;
/// XLA PRNG algorithm to be used.
class RngAlgorithmAttr;
/// XLA result accuracy mode.
class ResultAccuracyModeAttr;
/// Attribute that models the dimension information for scatter
class ScatterDimensionNumbersAttr;
/// Attribute that models the dimension information for gather
class GatherDimensionNumbersAttr;
/// Attribute that models the algorithm constraints to use for computing dot.
class DotAlgorithmAttr;
/// Attribute that models the dimension information for dot.
class DotDimensionNumbersAttr;
/// Structure of dimension information for conv op
class ConvDimensionNumbersAttr;
/// Attribute that models the alias relationship of output and operand of a CustomCall op
/// This attribute captures the alias relationship of the output to one of the
///     operands for a CustomCall op, denoted by `operand_index`. The
///     `output_tuple_indices` and `operand_tuple_indices` are used to index into
///     output and operand types. These indices lists are empty if the corresponding
///     types are not tuple types, and can be arbitrarily long in case of
///     arbitrarily nested tuple types.
/// 
///     See https://www.tensorflow.org/xla/aliasing.
/// 
///     Example when used as array with in mhlo.custom-call:
/// 
///     ```mlir
///     %0 = "mhlo.custom_call"(%arg0, %arg1) {
///       // other attributes
///       output_operand_alias = [
///         #mhlo.output_operand_alias<output_tuple_indices = [0],
///                                    operand_index = 0,
///                                    operand_tuple_indices = [1]>
///       ]
///     } : (tuple<tensor<1x1xf32>, tensor<2x3xf32>>, tensor<5x5xf32>) -> tuple<tensor<2x3xf32>>
/// 
///     The output and the 0th operand are both tuples. The aliasing shows the
///     relationship between the 0th element in output tuple with the 1st element in
///     the 0th operand. And both of them are of the same type: tensor<2x3xf32>.
///     ```
class OutputOperandAliasAttr;
/// Attribute that models the alias relationship of entry function argument
/// This attribute captures the alias relationship of an MHLO main function
///     argument to one of the results, denoted by `resultIndex`. The
///     `argTupleIndices` and `resultTupleIndices` are used to index into nested
///     tuples in operand and result respectively. If `isMustAlias` is true then the
///     operand-result pair must alias.
/// 
///     This is meant to be used as an attribute on a function argument in MHLO.
///     For example, in the following code it expresses that `%arg1` may alias 0-th
///     result.
/// 
///     ```mlir
///     func @main(%arg0: tensor<2xf32>, %arg1: tensor<3xf32> {mhlo.result_alias =
///         mhlo.result_alias<result_index = [2], ...>}
///       ) -> tensor<2xf32>, tensor<3xf32> {
///       // function body ...
///     }
///     ```
class ArgResultAliasAttr;
/// two 64-bit integers 'handle' and 'type'
class ChannelHandleAttr;
/// Argument that is prefetched from another program
/// This attribute captures an argument that is prefetched from another program.
///     For a given `CrossProgramPrefetchAttr`, `parameter` tells us which argument
///     of the `main` function of the module is prefetched, and `indices` is a shape
///     index telling us what subshape of that argument is prefetched.
/// 
///     A shape has a subshape iff it is a tuple. In that case, the subshape of
///     the tuple by `indices` is the shape achieved after indexing by each
///     element of `indices` in turn. For example, the [1,0] subshape of
///     `tuple<tuple<token, token>, tuple<tensor<i32>, token>>` is `tensor<i32>`.
/// 
///     An empty value for `indices` means the whole shape is prefetched.
/// 
///     For example,
/// 
///     ```mlir
///     module attributes { mhlo.cross_program_prefetch = [ #mhlo.cross_program_prefetch< parameter = 0, indices = [0]> ]} {
///       func.func @copy(%arg0 : tuple<tensor<2x3xi32>, tensor<i32>>) -> tuple<tensor<2x3xi32>, tensor<i32>> {
///         %0 = "mhlo.copy"(%arg0) {is_cross_program_prefetch}
///         return %0 : tuple<tensor<2x3xi32>, tensor<i32>>
///       }
///       func.func @main(%arg0 : tuple<tensor<2x3xi32>, tensor<i32>>) -> tuple<tensor<2x3xi32>, tensor<i32>> {
///         %1 = "mhlo.async_start"(%arg0) {called_computation=@copy}
///         %2 = "mhlo.async_done"(%1) {called_computation=@copy}
///         return %2 : tuple<tensor<2x3xi32>, tensor<i32>>
///       }
///     }
///     ```
/// 
///     The `parameter = 0` tells us that the async copy of the `0`th parameter is
///     a `cross_program_prefetch`, while the `index` of `[0]` tells us that the
///     `0`th element of the tuple is prefetched while the other element of the
///     tuple is not.
class CrossProgramPrefetchAttr;
/// Attribute that extends tensor type with MHLO type properties.
/// This attribute is used to extend MLIR tensor type with MHLO tensor specific
///     properties. These properties aren't modeled in the MLIR type. This
///     attribute is set in the `encoding` field of the tensor type.
/// 
///     See `HLO_BoundedAttrInterface` for documentation for `bounds`.
class TypeExtensionsAttr;
/// Attribute that models the dimension information for ragged dot.
class RaggedDotDimensionNumbersAttr;
/// The requested accuracy for unary ops.
class ResultAccuracyAttr;
namespace detail {

struct PrecisionAttrStorage;

} // namespace detail
class PrecisionAttr : public ::mlir::Attribute::AttrBase<PrecisionAttr, ::mlir::Attribute, detail::PrecisionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.precision";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static PrecisionAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::Precision value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"precision"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::Precision getValue() const;
};
namespace detail {

struct CustomCallScheduleAttrStorage;

} // namespace detail
class CustomCallScheduleAttr : public ::mlir::Attribute::AttrBase<CustomCallScheduleAttr, ::mlir::Attribute, detail::CustomCallScheduleAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.custom_call_schedule";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static CustomCallScheduleAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::CustomCallSchedule value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"custom_call_schedule"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::CustomCallSchedule getValue() const;
};
namespace detail {

struct DomainKindAttrStorage;

} // namespace detail
class DomainKindAttr : public ::mlir::Attribute::AttrBase<DomainKindAttr, ::mlir::Attribute, detail::DomainKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.kind";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static DomainKindAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::DomainKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::DomainKind getValue() const;
};
namespace detail {

struct FftTypeAttrStorage;

} // namespace detail
class FftTypeAttr : public ::mlir::Attribute::AttrBase<FftTypeAttr, ::mlir::Attribute, detail::FftTypeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.fft_type";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static FftTypeAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::FftType value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"fft_type"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::FftType getValue() const;
};
namespace detail {

struct ComparisonDirectionAttrStorage;

} // namespace detail
class ComparisonDirectionAttr : public ::mlir::Attribute::AttrBase<ComparisonDirectionAttr, ::mlir::Attribute, detail::ComparisonDirectionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.comparison_direction";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static ComparisonDirectionAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::ComparisonDirection value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"comparison_direction"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::ComparisonDirection getValue() const;
};
namespace detail {

struct ComparisonTypeAttrStorage;

} // namespace detail
class ComparisonTypeAttr : public ::mlir::Attribute::AttrBase<ComparisonTypeAttr, ::mlir::Attribute, detail::ComparisonTypeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.comparison_type";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static ComparisonTypeAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::ComparisonType value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"comparison_type"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::ComparisonType getValue() const;
};
namespace detail {

struct DequantizeModeAttrStorage;

} // namespace detail
class DequantizeModeAttr : public ::mlir::Attribute::AttrBase<DequantizeModeAttr, ::mlir::Attribute, detail::DequantizeModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.dequantize_mode";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static DequantizeModeAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::DequantizeMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dequantize_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::DequantizeMode getValue() const;
};
namespace detail {

struct TransposeAttrStorage;

} // namespace detail
class TransposeAttr : public ::mlir::Attribute::AttrBase<TransposeAttr, ::mlir::Attribute, detail::TransposeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.transpose";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static TransposeAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::Transpose value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"transpose"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::Transpose getValue() const;
};
namespace detail {

struct RngDistributionAttrStorage;

} // namespace detail
class RngDistributionAttr : public ::mlir::Attribute::AttrBase<RngDistributionAttr, ::mlir::Attribute, detail::RngDistributionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.rng_distribution";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static RngDistributionAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::RngDistribution value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"rng_distribution"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::RngDistribution getValue() const;
};
namespace detail {

struct FusionKindAttrStorage;

} // namespace detail
class FusionKindAttr : public ::mlir::Attribute::AttrBase<FusionKindAttr, ::mlir::Attribute, detail::FusionKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.fusion_kind";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static FusionKindAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::FusionKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"fusion_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::FusionKind getValue() const;
};
namespace detail {

struct RngAlgorithmAttrStorage;

} // namespace detail
class RngAlgorithmAttr : public ::mlir::Attribute::AttrBase<RngAlgorithmAttr, ::mlir::Attribute, detail::RngAlgorithmAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.rng_algorithm";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static RngAlgorithmAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::RngAlgorithm value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"rng_algorithm"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::RngAlgorithm getValue() const;
};
namespace detail {

struct ResultAccuracyModeAttrStorage;

} // namespace detail
class ResultAccuracyModeAttr : public ::mlir::Attribute::AttrBase<ResultAccuracyModeAttr, ::mlir::Attribute, detail::ResultAccuracyModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.result_accuracy_mode";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static ResultAccuracyModeAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::ResultAccuracyMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"result_accuracy_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::ResultAccuracyMode getValue() const;
};
namespace detail {

struct ScatterDimensionNumbersAttrStorage;

} // namespace detail
class ScatterDimensionNumbersAttr : public ::mlir::Attribute::AttrBase<ScatterDimensionNumbersAttr, ::mlir::Attribute, detail::ScatterDimensionNumbersAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.scatter";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static ScatterDimensionNumbersAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> updateWindowDims, ::llvm::ArrayRef<int64_t> insertedWindowDims, ::llvm::ArrayRef<int64_t> inputBatchingDims, ::llvm::ArrayRef<int64_t> scatterIndicesBatchingDims, ::llvm::ArrayRef<int64_t> scatterDimsToOperandDims, int64_t indexVectorDim);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"scatter"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<int64_t> getUpdateWindowDims() const;
  ::llvm::ArrayRef<int64_t> getInsertedWindowDims() const;
  ::llvm::ArrayRef<int64_t> getInputBatchingDims() const;
  ::llvm::ArrayRef<int64_t> getScatterIndicesBatchingDims() const;
  ::llvm::ArrayRef<int64_t> getScatterDimsToOperandDims() const;
  int64_t getIndexVectorDim() const;
};
namespace detail {

struct GatherDimensionNumbersAttrStorage;

} // namespace detail
class GatherDimensionNumbersAttr : public ::mlir::Attribute::AttrBase<GatherDimensionNumbersAttr, ::mlir::Attribute, detail::GatherDimensionNumbersAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.gather";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static GatherDimensionNumbersAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> offsetDims, ::llvm::ArrayRef<int64_t> collapsedSliceDims, ::llvm::ArrayRef<int64_t> operandBatchingDims, ::llvm::ArrayRef<int64_t> startIndicesBatchingDims, ::llvm::ArrayRef<int64_t> startIndexMap, int64_t indexVectorDim);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"gather"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<int64_t> getOffsetDims() const;
  ::llvm::ArrayRef<int64_t> getCollapsedSliceDims() const;
  ::llvm::ArrayRef<int64_t> getOperandBatchingDims() const;
  ::llvm::ArrayRef<int64_t> getStartIndicesBatchingDims() const;
  ::llvm::ArrayRef<int64_t> getStartIndexMap() const;
  int64_t getIndexVectorDim() const;
};
namespace detail {

struct DotAlgorithmAttrStorage;

} // namespace detail
class DotAlgorithmAttr : public ::mlir::Attribute::AttrBase<DotAlgorithmAttr, ::mlir::Attribute, detail::DotAlgorithmAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.dot_algorithm";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  using Base::getChecked;
  static DotAlgorithmAttr get(::mlir::MLIRContext *context, Type lhsPrecisionType, Type rhsPrecisionType, Type accumulationType, int64_t lhsComponentCount, int64_t rhsComponentCount, int64_t numPrimitiveOperations, bool allowImpreciseAccumulation);
  static DotAlgorithmAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, Type lhsPrecisionType, Type rhsPrecisionType, Type accumulationType, int64_t lhsComponentCount, int64_t rhsComponentCount, int64_t numPrimitiveOperations, bool allowImpreciseAccumulation);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type lhsPrecisionType, Type rhsPrecisionType, Type accumulationType, int64_t lhsComponentCount, int64_t rhsComponentCount, int64_t numPrimitiveOperations, bool allowImpreciseAccumulation);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type lhsPrecisionType, Type rhsPrecisionType, Type accumulationType, int64_t lhsComponentCount, int64_t rhsComponentCount, int64_t numPrimitiveOperations, bool allowImpreciseAccumulation);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dot_algorithm"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  Type getLhsPrecisionType() const;
  Type getRhsPrecisionType() const;
  Type getAccumulationType() const;
  int64_t getLhsComponentCount() const;
  int64_t getRhsComponentCount() const;
  int64_t getNumPrimitiveOperations() const;
  bool getAllowImpreciseAccumulation() const;
};
namespace detail {

struct DotDimensionNumbersAttrStorage;

} // namespace detail
class DotDimensionNumbersAttr : public ::mlir::Attribute::AttrBase<DotDimensionNumbersAttr, ::mlir::Attribute, detail::DotDimensionNumbersAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.dot";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static DotDimensionNumbersAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> lhsBatchingDimensions, ::llvm::ArrayRef<int64_t> rhsBatchingDimensions, ::llvm::ArrayRef<int64_t> lhsContractingDimensions, ::llvm::ArrayRef<int64_t> rhsContractingDimensions);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dot"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<int64_t> getLhsBatchingDimensions() const;
  ::llvm::ArrayRef<int64_t> getRhsBatchingDimensions() const;
  ::llvm::ArrayRef<int64_t> getLhsContractingDimensions() const;
  ::llvm::ArrayRef<int64_t> getRhsContractingDimensions() const;
};
namespace detail {

struct ConvDimensionNumbersAttrStorage;

} // namespace detail
class ConvDimensionNumbersAttr : public ::mlir::Attribute::AttrBase<ConvDimensionNumbersAttr, ::mlir::Attribute, detail::ConvDimensionNumbersAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.conv";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static ConvDimensionNumbersAttr get(::mlir::MLIRContext *context, int64_t inputBatchDimension, int64_t inputFeatureDimension, ::llvm::ArrayRef<int64_t> inputSpatialDimensions, int64_t kernelInputFeatureDimension, int64_t kernelOutputFeatureDimension, ::llvm::ArrayRef<int64_t> kernelSpatialDimensions, int64_t outputBatchDimension, int64_t outputFeatureDimension, ::llvm::ArrayRef<int64_t> outputSpatialDimensions);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"conv"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  int64_t getInputBatchDimension() const;
  int64_t getInputFeatureDimension() const;
  ::llvm::ArrayRef<int64_t> getInputSpatialDimensions() const;
  int64_t getKernelInputFeatureDimension() const;
  int64_t getKernelOutputFeatureDimension() const;
  ::llvm::ArrayRef<int64_t> getKernelSpatialDimensions() const;
  int64_t getOutputBatchDimension() const;
  int64_t getOutputFeatureDimension() const;
  ::llvm::ArrayRef<int64_t> getOutputSpatialDimensions() const;
};
namespace detail {

struct OutputOperandAliasAttrStorage;

} // namespace detail
class OutputOperandAliasAttr : public ::mlir::Attribute::AttrBase<OutputOperandAliasAttr, ::mlir::Attribute, detail::OutputOperandAliasAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.output_operand_alias";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static OutputOperandAliasAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> outputTupleIndices, int64_t operandIndex, ::llvm::ArrayRef<int64_t> operandTupleIndices);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"output_operand_alias"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<int64_t> getOutputTupleIndices() const;
  int64_t getOperandIndex() const;
  ::llvm::ArrayRef<int64_t> getOperandTupleIndices() const;
};
namespace detail {

struct ArgResultAliasAttrStorage;

} // namespace detail
class ArgResultAliasAttr : public ::mlir::Attribute::AttrBase<ArgResultAliasAttr, ::mlir::Attribute, detail::ArgResultAliasAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.result_alias";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static ArgResultAliasAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> argTupleIndices, int64_t resultIndex, ::llvm::ArrayRef<int64_t> resultTupleIndices, bool isMustAlias);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"result_alias"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<int64_t> getArgTupleIndices() const;
  int64_t getResultIndex() const;
  ::llvm::ArrayRef<int64_t> getResultTupleIndices() const;
  bool getIsMustAlias() const;
};
namespace detail {

struct ChannelHandleAttrStorage;

} // namespace detail
class ChannelHandleAttr : public ::mlir::Attribute::AttrBase<ChannelHandleAttr, ::mlir::Attribute, detail::ChannelHandleAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.channel_handle";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static ChannelHandleAttr get(::mlir::MLIRContext *context, int64_t handle, int64_t type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"channel_handle"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  int64_t getHandle() const;
  int64_t getType() const;
};
namespace detail {

struct CrossProgramPrefetchAttrStorage;

} // namespace detail
class CrossProgramPrefetchAttr : public ::mlir::Attribute::AttrBase<CrossProgramPrefetchAttr, ::mlir::Attribute, detail::CrossProgramPrefetchAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.cross_program_prefetch";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static CrossProgramPrefetchAttr get(::mlir::MLIRContext *context, int64_t parameter, ::llvm::ArrayRef<int64_t> indices, std::optional<int64_t> offset);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cross_program_prefetch"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  int64_t getParameter() const;
  ::llvm::ArrayRef<int64_t> getIndices() const;
  std::optional<int64_t> getOffset() const;
};
namespace detail {

struct TypeExtensionsAttrStorage;

} // namespace detail
class TypeExtensionsAttr : public ::mlir::Attribute::AttrBase<TypeExtensionsAttr, ::mlir::Attribute, detail::TypeExtensionsAttrStorage, ::mlir::VerifiableTensorEncoding::Trait, ::mlir::hlo::BoundedAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.type_extensions";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  static TypeExtensionsAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> bounds);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"type_extensions"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<int64_t> getBounds() const;
  ::llvm::LogicalResult verifyEncoding(::mlir::ArrayRef<int64_t> shape, ::mlir::Type elementType, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
};
namespace detail {

struct RaggedDotDimensionNumbersAttrStorage;

} // namespace detail
class RaggedDotDimensionNumbersAttr : public ::mlir::Attribute::AttrBase<RaggedDotDimensionNumbersAttr, ::mlir::Attribute, detail::RaggedDotDimensionNumbersAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.ragged_dot";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  using Base::getChecked;
  static RaggedDotDimensionNumbersAttr get(::mlir::MLIRContext *context, ::mlir::mhlo::DotDimensionNumbersAttr dotDimensionNumbers, ::llvm::ArrayRef<int64_t> lhsRaggedDimensions, ::llvm::ArrayRef<int64_t> rhsGroupDimensions);
  static RaggedDotDimensionNumbersAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::mhlo::DotDimensionNumbersAttr dotDimensionNumbers, ::llvm::ArrayRef<int64_t> lhsRaggedDimensions, ::llvm::ArrayRef<int64_t> rhsGroupDimensions);
  static ::llvm::LogicalResult verifyInvariantsImpl(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::mhlo::DotDimensionNumbersAttr dotDimensionNumbers, ::llvm::ArrayRef<int64_t> lhsRaggedDimensions, ::llvm::ArrayRef<int64_t> rhsGroupDimensions);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::mhlo::DotDimensionNumbersAttr dotDimensionNumbers, ::llvm::ArrayRef<int64_t> lhsRaggedDimensions, ::llvm::ArrayRef<int64_t> rhsGroupDimensions);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ragged_dot"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::mhlo::DotDimensionNumbersAttr getDotDimensionNumbers() const;
  ::llvm::ArrayRef<int64_t> getLhsRaggedDimensions() const;
  ::llvm::ArrayRef<int64_t> getRhsGroupDimensions() const;
};
namespace detail {

struct ResultAccuracyAttrStorage;

} // namespace detail
class ResultAccuracyAttr : public ::mlir::Attribute::AttrBase<ResultAccuracyAttr, ::mlir::Attribute, detail::ResultAccuracyAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "mhlo.result_accuracy";
  static constexpr ::llvm::StringLiteral dialectName = "mhlo";
  using Base::getChecked;
  static ResultAccuracyAttr get(::mlir::MLIRContext *context, APFloat atol, APFloat rtol, int64_t ulps, ::mlir::mhlo::ResultAccuracyModeAttr mode);
  static ResultAccuracyAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, APFloat atol, APFloat rtol, int64_t ulps, ::mlir::mhlo::ResultAccuracyModeAttr mode);
  static ::llvm::LogicalResult verifyInvariantsImpl(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, APFloat atol, APFloat rtol, int64_t ulps, ::mlir::mhlo::ResultAccuracyModeAttr mode);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, APFloat atol, APFloat rtol, int64_t ulps, ::mlir::mhlo::ResultAccuracyModeAttr mode);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, APFloat atol, APFloat rtol, int64_t ulps, ::mlir::mhlo::ResultAccuracyModeAttr mode);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"result_accuracy"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  APFloat getAtol() const;
  APFloat getRtol() const;
  int64_t getUlps() const;
  ::mlir::mhlo::ResultAccuracyModeAttr getMode() const;
};

} // namespace mlir::mhlo
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::PrecisionAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::CustomCallScheduleAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::DomainKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::FftTypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::ComparisonDirectionAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::ComparisonTypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::DequantizeModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::TransposeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::RngDistributionAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::FusionKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::RngAlgorithmAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::ResultAccuracyModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::ScatterDimensionNumbersAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::GatherDimensionNumbersAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::DotAlgorithmAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::DotDimensionNumbersAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::ConvDimensionNumbersAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::OutputOperandAliasAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::ArgResultAliasAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::ChannelHandleAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::CrossProgramPrefetchAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::TypeExtensionsAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::RaggedDotDimensionNumbersAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::mhlo::ResultAccuracyAttr)

#endif // GET_ATTRDEF_CLASSES

