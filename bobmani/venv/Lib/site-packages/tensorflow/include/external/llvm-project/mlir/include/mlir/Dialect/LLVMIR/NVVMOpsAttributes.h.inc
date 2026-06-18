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
namespace mlir::NVVM {

/// NVVM Cache Eviction Priority
/// Enum cases:
/// * evict_normal (`EvictNormal`)
/// * evict_first (`EvictFirst`)
/// * evict_last (`EvictLast`)
/// * evict_unchanged (`EvictUnchanged`)
/// * no_allocate (`NoAllocate`)
class CacheEvictionPriorityAttr;
/// NVVM Memory Space
/// Enum cases:
/// * generic (`Generic`)
/// * global (`Global`)
/// * shared (`Shared`)
/// * constant (`Constant`)
/// * local (`Local`)
/// * tensor (`Tensor`)
/// * shared_cluster (`SharedCluster`)
class NVVMMemorySpaceAttr;
/// NVVM Memory Scope kind
class MemScopeKindAttr;
/// Shared memory space
class SharedSpaceAttr;
/// NVVM Memory Ordering kind
class MemOrderKindAttr;
/// NVVM redux kind
class ReduxKindAttr;
/// NVVM barrier reduction operation
class BarrierReductionAttr;
/// Proxy kind
/// ProxyKind attribute represents a memory proxy which is an abstract label
///     applied to a method of memory access. When two memory operations use distinct
///     methods of memory access, they are said to be different proxies.
class ProxyKindAttr;
/// NVVM set max register action
class SetMaxRegisterActionAttr;
/// NVVM shuffle kind
class ShflKindAttr;
/// NVVM vote sync kind
class VoteSyncKindAttr;
/// NVVM permute mode
class PermuteModeAttr;
/// NVVM load cache modifier kind
/// Enum attribute of the different kinds of cache operators for load instructions.
/// 
///     [For more information, see PTX ISA](https://docs.nvidia.com/cuda/parallel-thread-execution/#id62)
class LoadCacheModifierKindAttr;
/// NVVM FPRoundingMode kind
class FPRoundingModeAttr;
/// NVVM SaturationMode kind
class SaturationModeAttr;
/// MMA binary operations
class MMAB1OpAttr;
/// MMA overflow options
class MMAIntOverflowAttr;
/// MMA operation kind
class MMAKindAttr;
/// Attribute for MMA operation shape.
class MMAShapeAttr;
/// NVVM MMA layout
class MMALayoutAttr;
/// NVVM MMA types
class MMATypesAttr;
/// NVVM MMA frag type
class MMAFragAttr;
/// Matrix shape for ldmatrix and stmatrix
class LdStMatrixShapeAttr;
/// Element type for ldmatrix and stmatrix
class LdStMatrixEltTypeAttr;
/// MMA Scale Vector Sizes
class ScaleVecSizeAttr;
/// MMA Block Scale Format
class BlockScaleFormatAttr;
/// Block Scale Kind
/// The MMABlockScaleKind attribute describes the allowed set of types for matrix A and B in the *.mma.{sp}.block_scale Op. The following are supported types for each kind:
/// 
///     ```
///     +--------------+-------------------------------------------+
///     | Matrix Kind  |      supported types for A / B            |
///     +--------------+-------------------------------------------+
///     | mxf8f6f4     | e4m3, e5m2, e2m3, e3m2, e2m1              |
///     | mxf4         | e2m1                                      |
///     | mxf4nvf4     | e2m1                                      |
///     +--------------+-------------------------------------------+
///     ```
class MMABlockScaleKindAttr;
/// List of Load-Modes supported for TMA Tensor Ops
/// TMA Tensor Ops support the following modes, when copying data from
///     global memory to shared memory (i.e. load):
/// 
///     Tile Mode: It's the default mode. The source multi-dimensional tensor
///     layout is preserved at the destination.
///     [For more information, see PTX ISA](https://docs.nvidia.com/cuda/parallel-thread-execution/#tensor-tiled-mode)
/// 
///     Im2col Mode: This mode is used when `im2colOffsets` operands are present.
///     The elements in the Bounding Box of the source tensor are rearranged into
///     columns at the destination. In this mode, the tensor has to be at least
///     3-dimensional. The number of `im2colOffsets` is `dims - 2` where `dims`
///     is the dimension of the tensor.
///     [For more information, see PTX ISA](https://docs.nvidia.com/cuda/parallel-thread-execution/#tensor-im2col-mode)
/// 
///     Im2col_W Mode: This mode is similar to Im2Col mode with the restriction that
///     elements are accessed across the W dimension only. The number of `im2colOffsets`
///     are always two, referred as `wHalo` and `wOffset`.
///     [For more information, see PTX ISA](https://docs.nvidia.com/cuda/parallel-thread-execution/#tensor-im2col-w-w128-modes)
/// 
///     Im2col_W_128 Mode: This mode is similar to Im2Col_W mode with the number of
///     elements accessed across the W dimension is always 128 only.
///     [For more information, see PTX ISA](https://docs.nvidia.com/cuda/parallel-thread-execution/#tensor-im2col-w-w128-modes)
/// 
///     Tile_Gather4 Mode: This mode is similar to Tile mode but works only on 2D tensor.
///     In gather4 mode, four rows in the source 2D tensor are combined to form a single
///     2D tensor at the destination. This mode requires five co-ordinates. The first one
///     represents the column-index followed by four row indices.
///     [For more information, see PTX ISA](https://docs.nvidia.com/cuda/parallel-thread-execution/#tensor-tiled-scatter4-gather4-modes)
class TMALoadModeAttr;
/// NVVM TMA Store Mode
class TMAStoreModeAttr;
/// NVVM CTA group kind
class CTAGroupKindAttr;
/// NVVM Prefetch Cache Level
/// Enum cases:
/// * L1 (`L1`)
/// * L2 (`L2`)
class PrefetchCacheLevelAttr;
/// NVVM TMA redux kind
class TMAReduxKindAttr;
/// WGMMA overflow options
class WGMMAScaleInAttr;
/// WGMMA input predicate
class WGMMAScaleOutAttr;
/// NVVM WGMMA types
class WGMMATypesAttr;
/// Action kind for grid dependency control
/// Enum cases:
/// * wait (`wait`)
/// * launch_dependents (`launch_dependents`)
class GridDepActionKindAttr;
/// NVVM match sync kind
class MatchSyncKindAttr;
/// NVVM Tcgen05 fence kind
class Tcgen05FenceKindAttr;
/// NVVM Tcgen05 wait kind
class Tcgen05WaitKindAttr;
/// tcgen05 cp shapes
class Tcgen05CpShapeAttr;
/// tcgen05 cp multicast
class Tcgen05CpMulticastAttr;
/// tcgen05 cp source format
class Tcgen05CpSrcFormatAttr;
/// allowed 32-bit signless integer cases: 0, 1, 2, 3, 4
class Tcgen05LdStShapeAttr;
/// NVVM DotAccumulateType
class DotAccumulateTypeAttr;
/// NVVM ClusterLaunchControlQueryType
/// Enum cases:
/// * is_canceled (`IS_CANCELED`)
/// * get_first_cta_id_x (`GET_FIRST_CTA_ID_X`)
/// * get_first_cta_id_y (`GET_FIRST_CTA_ID_Y`)
/// * get_first_cta_id_z (`GET_FIRST_CTA_ID_Z`)
class ClusterLaunchControlQueryTypeAttr;
/// tcgen05 MMA Supported Types
/// The Tcgen05MMAKind attribute describes the allowed set of types for matrix A and B in the tcgen05.mma.{sp} Op. The following are supported types for each kind:
/// 
///     ```
///     +-------------+--------------------------------------------+
///     | Matrix Kind |      supported types for A / B             |
///     +-------------+--------------------------------------------+
///     | f16         | f16, bf16                                  |
///     | tf32        | tf32                                       |
///     | f8f6f4      | e4m3, e5m2, e2m3, e3m2, e2m1               |
///     | i8          | unsigned 8b, signed 8b                     |
///     +-------------+--------------------------------------------+
///     ```
class Tcgen05MMAKindAttr;
/// tcgen05.mma Collector Buffer Operation
/// Tcgen05MMACollectorOp attribute specifies the collector buffer operations.
///     The following are the supported operations:
///       * discard : Release buffer after use (default)
///       * lastuse : Mark buffer for last use
///       * fill    : Fill buffer
///       * use     : Use buffer without modification
class Tcgen05MMACollectorOpAttr;
/// tcgen05.mma block scale attribute
class Tcgen05MMABlockScaleAttr;
/// tcgen05 MMA Collector Buffer B Attribute
class Tcgen05MMACollectorBBufferAttr;
/// NVVM Tensormap Field Kind
/// Enum cases:
/// * global_address (`GLOBAL_ADDRESS`)
/// * rank (`RANK`)
/// * box_dim (`BOX_DIM`)
/// * global_dim (`GLOBAL_DIM`)
/// * global_stride (`GLOBAL_STRIDE`)
/// * element_stride (`ELEMENT_STRIDE`)
/// * elemtype (`ELEMTYPE`)
/// * interleave_layout (`INTERLEAVE_LAYOUT`)
/// * swizzle_mode (`SWIZZLE_MODE`)
/// * swizzle_atomicity (`SWIZZLE_ATOMICITY`)
/// * fill_mode (`FILL_MODE`)
class TensormapFieldAttr;
/// NVVM Tensormap Elemtype
/// Enum cases:
/// * u8 (`U8`)
/// * u16 (`U16`)
/// * u32 (`U32`)
/// * s32 (`S32`)
/// * u64 (`U64`)
/// * s64 (`S64`)
/// * f16 (`F16`)
/// * f32 (`F32`)
/// * f32.ftz (`F32_FTZ`)
/// * f64 (`F64`)
/// * bf16 (`BF16`)
/// * tf32 (`TF32`)
/// * tf32.ftz (`TF32_FTZ`)
/// * b4x16 (`B4x16`)
/// * b4x16_p64 (`B4x16P64`)
/// * b6x16_p32 (`B6x16P32`)
class TensormapElemtypeAttr;
/// NVVM Tensormap Interleave Layout
/// Enum cases:
/// * no_interleave (`NO_INTERLEAVE`)
/// * b16 (`B16`)
/// * b32 (`B32`)
class TensormapInterleaveLayoutAttr;
/// NVVM Tensormap Swizzle Mode
/// Enum cases:
/// * no_swizzling (`NO_SWIZZLING`)
/// * b32 (`B32`)
/// * b64 (`B64`)
/// * b128 (`B128`)
/// * b96 (`B96`)
class TensormapSwizzleModeAttr;
/// NVVM Tensormap Swizzle Atomicity
/// Enum cases:
/// * b16 (`B16`)
/// * b32 (`B32`)
/// * b32_flip_b8 (`B32_FLIP_8B`)
/// * b64 (`B64`)
class TensormapSwizzleAtomicityAttr;
/// NVVM Tensormap Fill Mode
/// Enum cases:
/// * zero (`ZERO`)
/// * oob_nan (`OOB_NAN`)
class TensormapFillModeAttr;
/// GPU target attribute for controlling compilation of NVIDIA targets. All
///     parameters decay into default values if not present.
/// 
///     Examples:
/// 
///     1. Target with default values.
///     ```
///       gpu.module @mymodule [#nvvm.target] attributes {...} {
///         ...
///       }
///     ```
/// 
///     2. Target with `sm_90` chip and fast math.
///     ```
///       gpu.module @mymodule [#nvvm.target<chip = "sm_90", flags = {fast}>] {
///         ...
///       }
///     ```
class NVVMTargetAttr;
namespace detail {

struct CacheEvictionPriorityAttrStorage;

} // namespace detail
class CacheEvictionPriorityAttr : public ::mlir::Attribute::AttrBase<CacheEvictionPriorityAttr, ::mlir::Attribute, detail::CacheEvictionPriorityAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.cache_eviction_priority";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static CacheEvictionPriorityAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::CacheEvictionPriority value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cache_eviction_priority"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::CacheEvictionPriority getValue() const;
};
namespace detail {

struct NVVMMemorySpaceAttrStorage;

} // namespace detail
class NVVMMemorySpaceAttr : public ::mlir::Attribute::AttrBase<NVVMMemorySpaceAttr, ::mlir::Attribute, detail::NVVMMemorySpaceAttrStorage, ::mlir::LLVM::LLVMAddrSpaceAttrInterface::Trait, ::mlir::ptr::MemorySpaceAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.memory_space";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static NVVMMemorySpaceAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::NVVMMemorySpace value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"memory_space"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::NVVMMemorySpace getValue() const;
  unsigned getAddressSpace() const;
  bool isValidLoad(::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout *dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  bool isValidStore(::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout *dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  bool isValidAtomicOp(::mlir::ptr::AtomicBinOp op, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout *dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  bool isValidAtomicXchg(::mlir::Type type, ::mlir::ptr::AtomicOrdering successOrdering, ::mlir::ptr::AtomicOrdering failureOrdering, std::optional<int64_t> alignment, const ::mlir::DataLayout *dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  bool isValidAddrSpaceCast(::mlir::Type tgt, ::mlir::Type src, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  bool isValidPtrIntCast(::mlir::Type intLikeTy, ::mlir::Type ptrLikeTy, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
};
namespace detail {

struct MemScopeKindAttrStorage;

} // namespace detail
class MemScopeKindAttr : public ::mlir::Attribute::AttrBase<MemScopeKindAttr, ::mlir::Attribute, detail::MemScopeKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.mem_scope";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MemScopeKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::MemScopeKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mem_scope"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::MemScopeKind getValue() const;
};
namespace detail {

struct SharedSpaceAttrStorage;

} // namespace detail
class SharedSpaceAttr : public ::mlir::Attribute::AttrBase<SharedSpaceAttr, ::mlir::Attribute, detail::SharedSpaceAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.shared_space";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static SharedSpaceAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::SharedSpace value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"shared_space"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::SharedSpace getValue() const;
};
namespace detail {

struct MemOrderKindAttrStorage;

} // namespace detail
class MemOrderKindAttr : public ::mlir::Attribute::AttrBase<MemOrderKindAttr, ::mlir::Attribute, detail::MemOrderKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.mem_order";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MemOrderKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::MemOrderKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mem_order"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::MemOrderKind getValue() const;
};
namespace detail {

struct ReduxKindAttrStorage;

} // namespace detail
class ReduxKindAttr : public ::mlir::Attribute::AttrBase<ReduxKindAttr, ::mlir::Attribute, detail::ReduxKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.redux_kind";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static ReduxKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::ReduxKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"redux_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::ReduxKind getValue() const;
};
namespace detail {

struct BarrierReductionAttrStorage;

} // namespace detail
class BarrierReductionAttr : public ::mlir::Attribute::AttrBase<BarrierReductionAttr, ::mlir::Attribute, detail::BarrierReductionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.reduction";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static BarrierReductionAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::BarrierReduction value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"reduction"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::BarrierReduction getValue() const;
};
namespace detail {

struct ProxyKindAttrStorage;

} // namespace detail
class ProxyKindAttr : public ::mlir::Attribute::AttrBase<ProxyKindAttr, ::mlir::Attribute, detail::ProxyKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.proxy_kind";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static ProxyKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::ProxyKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"proxy_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::ProxyKind getValue() const;
};
namespace detail {

struct SetMaxRegisterActionAttrStorage;

} // namespace detail
class SetMaxRegisterActionAttr : public ::mlir::Attribute::AttrBase<SetMaxRegisterActionAttr, ::mlir::Attribute, detail::SetMaxRegisterActionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.action";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static SetMaxRegisterActionAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::SetMaxRegisterAction value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"action"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::SetMaxRegisterAction getValue() const;
};
namespace detail {

struct ShflKindAttrStorage;

} // namespace detail
class ShflKindAttr : public ::mlir::Attribute::AttrBase<ShflKindAttr, ::mlir::Attribute, detail::ShflKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.shfl_kind";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static ShflKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::ShflKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"shfl_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::ShflKind getValue() const;
};
namespace detail {

struct VoteSyncKindAttrStorage;

} // namespace detail
class VoteSyncKindAttr : public ::mlir::Attribute::AttrBase<VoteSyncKindAttr, ::mlir::Attribute, detail::VoteSyncKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.vote_sync_kind";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static VoteSyncKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::VoteSyncKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"vote_sync_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::VoteSyncKind getValue() const;
};
namespace detail {

struct PermuteModeAttrStorage;

} // namespace detail
class PermuteModeAttr : public ::mlir::Attribute::AttrBase<PermuteModeAttr, ::mlir::Attribute, detail::PermuteModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.permute_mode";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static PermuteModeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::PermuteMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"permute_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::PermuteMode getValue() const;
};
namespace detail {

struct LoadCacheModifierKindAttrStorage;

} // namespace detail
class LoadCacheModifierKindAttr : public ::mlir::Attribute::AttrBase<LoadCacheModifierKindAttr, ::mlir::Attribute, detail::LoadCacheModifierKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.load_cache_modifier";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static LoadCacheModifierKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::LoadCacheModifierKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"load_cache_modifier"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::LoadCacheModifierKind getValue() const;
};
namespace detail {

struct FPRoundingModeAttrStorage;

} // namespace detail
class FPRoundingModeAttr : public ::mlir::Attribute::AttrBase<FPRoundingModeAttr, ::mlir::Attribute, detail::FPRoundingModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.fp_rnd_mode";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static FPRoundingModeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::FPRoundingMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"fp_rnd_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::FPRoundingMode getValue() const;
};
namespace detail {

struct SaturationModeAttrStorage;

} // namespace detail
class SaturationModeAttr : public ::mlir::Attribute::AttrBase<SaturationModeAttr, ::mlir::Attribute, detail::SaturationModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.sat_mode";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static SaturationModeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::SaturationMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sat_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::SaturationMode getValue() const;
};
namespace detail {

struct MMAB1OpAttrStorage;

} // namespace detail
class MMAB1OpAttr : public ::mlir::Attribute::AttrBase<MMAB1OpAttr, ::mlir::Attribute, detail::MMAB1OpAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.mma_b1op";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MMAB1OpAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::MMAB1Op value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mma_b1op"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::MMAB1Op getValue() const;
};
namespace detail {

struct MMAIntOverflowAttrStorage;

} // namespace detail
class MMAIntOverflowAttr : public ::mlir::Attribute::AttrBase<MMAIntOverflowAttr, ::mlir::Attribute, detail::MMAIntOverflowAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.mma_int_overflow";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MMAIntOverflowAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::MMAIntOverflow value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mma_int_overflow"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::MMAIntOverflow getValue() const;
};
namespace detail {

struct MMAKindAttrStorage;

} // namespace detail
class MMAKindAttr : public ::mlir::Attribute::AttrBase<MMAKindAttr, ::mlir::Attribute, detail::MMAKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.mma_kind";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MMAKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::MMAKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mma_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::MMAKind getValue() const;
};
namespace detail {

struct MMAShapeAttrStorage;

} // namespace detail
class MMAShapeAttr : public ::mlir::Attribute::AttrBase<MMAShapeAttr, ::mlir::Attribute, detail::MMAShapeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.shape";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MMAShapeAttr get(::mlir::MLIRContext *context, int m, int n, int k);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"shape"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  int getM() const;
  int getN() const;
  int getK() const;
};
namespace detail {

struct MMALayoutAttrStorage;

} // namespace detail
class MMALayoutAttr : public ::mlir::Attribute::AttrBase<MMALayoutAttr, ::mlir::Attribute, detail::MMALayoutAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.mma_layout";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MMALayoutAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::MMALayout value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mma_layout"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::MMALayout getValue() const;
};
namespace detail {

struct MMATypesAttrStorage;

} // namespace detail
class MMATypesAttr : public ::mlir::Attribute::AttrBase<MMATypesAttr, ::mlir::Attribute, detail::MMATypesAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.mma_type";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MMATypesAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::MMATypes value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mma_type"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::MMATypes getValue() const;
};
namespace detail {

struct MMAFragAttrStorage;

} // namespace detail
class MMAFragAttr : public ::mlir::Attribute::AttrBase<MMAFragAttr, ::mlir::Attribute, detail::MMAFragAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.mma_frag";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MMAFragAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::MMAFrag value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mma_frag"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::MMAFrag getValue() const;
};
namespace detail {

struct LdStMatrixShapeAttrStorage;

} // namespace detail
class LdStMatrixShapeAttr : public ::mlir::Attribute::AttrBase<LdStMatrixShapeAttr, ::mlir::Attribute, detail::LdStMatrixShapeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.ld_st_matrix_shape";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static LdStMatrixShapeAttr get(::mlir::MLIRContext *context, int m, int n);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ld_st_matrix_shape"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  int getM() const;
  int getN() const;
};
namespace detail {

struct LdStMatrixEltTypeAttrStorage;

} // namespace detail
class LdStMatrixEltTypeAttr : public ::mlir::Attribute::AttrBase<LdStMatrixEltTypeAttr, ::mlir::Attribute, detail::LdStMatrixEltTypeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.ld_st_matrix_elt_type";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static LdStMatrixEltTypeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::LdStMatrixEltType value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ld_st_matrix_elt_type"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::LdStMatrixEltType getValue() const;
};
namespace detail {

struct ScaleVecSizeAttrStorage;

} // namespace detail
class ScaleVecSizeAttr : public ::mlir::Attribute::AttrBase<ScaleVecSizeAttr, ::mlir::Attribute, detail::ScaleVecSizeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.scale_vec_size";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static ScaleVecSizeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::ScaleVecSize value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"scale_vec_size"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::ScaleVecSize getValue() const;
};
namespace detail {

struct BlockScaleFormatAttrStorage;

} // namespace detail
class BlockScaleFormatAttr : public ::mlir::Attribute::AttrBase<BlockScaleFormatAttr, ::mlir::Attribute, detail::BlockScaleFormatAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.block_scale_format";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static BlockScaleFormatAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::BlockScaleFormat value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"block_scale_format"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::BlockScaleFormat getValue() const;
};
namespace detail {

struct MMABlockScaleKindAttrStorage;

} // namespace detail
class MMABlockScaleKindAttr : public ::mlir::Attribute::AttrBase<MMABlockScaleKindAttr, ::mlir::Attribute, detail::MMABlockScaleKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.block_scale_kind";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MMABlockScaleKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::MMABlockScaleKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"block_scale_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::MMABlockScaleKind getValue() const;
};
namespace detail {

struct TMALoadModeAttrStorage;

} // namespace detail
class TMALoadModeAttr : public ::mlir::Attribute::AttrBase<TMALoadModeAttr, ::mlir::Attribute, detail::TMALoadModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tma_load_mode";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static TMALoadModeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::TMALoadMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tma_load_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::TMALoadMode getValue() const;
};
namespace detail {

struct TMAStoreModeAttrStorage;

} // namespace detail
class TMAStoreModeAttr : public ::mlir::Attribute::AttrBase<TMAStoreModeAttr, ::mlir::Attribute, detail::TMAStoreModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tma_store_mode";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static TMAStoreModeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::TMAStoreMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tma_store_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::TMAStoreMode getValue() const;
};
namespace detail {

struct CTAGroupKindAttrStorage;

} // namespace detail
class CTAGroupKindAttr : public ::mlir::Attribute::AttrBase<CTAGroupKindAttr, ::mlir::Attribute, detail::CTAGroupKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.cta_group";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static CTAGroupKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::CTAGroupKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cta_group"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::CTAGroupKind getValue() const;
};
namespace detail {

struct PrefetchCacheLevelAttrStorage;

} // namespace detail
class PrefetchCacheLevelAttr : public ::mlir::Attribute::AttrBase<PrefetchCacheLevelAttr, ::mlir::Attribute, detail::PrefetchCacheLevelAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.prefetch_cache_level";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static PrefetchCacheLevelAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::PrefetchCacheLevel value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"prefetch_cache_level"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::PrefetchCacheLevel getValue() const;
};
namespace detail {

struct TMAReduxKindAttrStorage;

} // namespace detail
class TMAReduxKindAttr : public ::mlir::Attribute::AttrBase<TMAReduxKindAttr, ::mlir::Attribute, detail::TMAReduxKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tma_redux_kind";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static TMAReduxKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::TMAReduxKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tma_redux_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::TMAReduxKind getValue() const;
};
namespace detail {

struct WGMMAScaleInAttrStorage;

} // namespace detail
class WGMMAScaleInAttr : public ::mlir::Attribute::AttrBase<WGMMAScaleInAttr, ::mlir::Attribute, detail::WGMMAScaleInAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.wgmma_scale_in";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static WGMMAScaleInAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::WGMMAScaleIn value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"wgmma_scale_in"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::WGMMAScaleIn getValue() const;
};
namespace detail {

struct WGMMAScaleOutAttrStorage;

} // namespace detail
class WGMMAScaleOutAttr : public ::mlir::Attribute::AttrBase<WGMMAScaleOutAttr, ::mlir::Attribute, detail::WGMMAScaleOutAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.wgmma_scale_out";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static WGMMAScaleOutAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::WGMMAScaleOut value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"wgmma_scale_out"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::WGMMAScaleOut getValue() const;
};
namespace detail {

struct WGMMATypesAttrStorage;

} // namespace detail
class WGMMATypesAttr : public ::mlir::Attribute::AttrBase<WGMMATypesAttr, ::mlir::Attribute, detail::WGMMATypesAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.wgmma_type";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static WGMMATypesAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::WGMMATypes value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"wgmma_type"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::WGMMATypes getValue() const;
};
namespace detail {

struct GridDepActionKindAttrStorage;

} // namespace detail
class GridDepActionKindAttr : public ::mlir::Attribute::AttrBase<GridDepActionKindAttr, ::mlir::Attribute, detail::GridDepActionKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.grid_dep_action";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static GridDepActionKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::GridDepActionKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"grid_dep_action"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::GridDepActionKind getValue() const;
};
namespace detail {

struct MatchSyncKindAttrStorage;

} // namespace detail
class MatchSyncKindAttr : public ::mlir::Attribute::AttrBase<MatchSyncKindAttr, ::mlir::Attribute, detail::MatchSyncKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.match_sync_kind";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static MatchSyncKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::MatchSyncKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"match_sync_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::MatchSyncKind getValue() const;
};
namespace detail {

struct Tcgen05FenceKindAttrStorage;

} // namespace detail
class Tcgen05FenceKindAttr : public ::mlir::Attribute::AttrBase<Tcgen05FenceKindAttr, ::mlir::Attribute, detail::Tcgen05FenceKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tcgen05_fence";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static Tcgen05FenceKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::Tcgen05FenceKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tcgen05_fence"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::Tcgen05FenceKind getValue() const;
};
namespace detail {

struct Tcgen05WaitKindAttrStorage;

} // namespace detail
class Tcgen05WaitKindAttr : public ::mlir::Attribute::AttrBase<Tcgen05WaitKindAttr, ::mlir::Attribute, detail::Tcgen05WaitKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tcgen05_wait";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static Tcgen05WaitKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::Tcgen05WaitKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tcgen05_wait"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::Tcgen05WaitKind getValue() const;
};
namespace detail {

struct Tcgen05CpShapeAttrStorage;

} // namespace detail
class Tcgen05CpShapeAttr : public ::mlir::Attribute::AttrBase<Tcgen05CpShapeAttr, ::mlir::Attribute, detail::Tcgen05CpShapeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tcgen05_cp_shape";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static Tcgen05CpShapeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::Tcgen05CpShape value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tcgen05_cp_shape"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::Tcgen05CpShape getValue() const;
};
namespace detail {

struct Tcgen05CpMulticastAttrStorage;

} // namespace detail
class Tcgen05CpMulticastAttr : public ::mlir::Attribute::AttrBase<Tcgen05CpMulticastAttr, ::mlir::Attribute, detail::Tcgen05CpMulticastAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tcgen05_cp_multicast";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static Tcgen05CpMulticastAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::Tcgen05CpMulticast value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tcgen05_cp_multicast"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::Tcgen05CpMulticast getValue() const;
};
namespace detail {

struct Tcgen05CpSrcFormatAttrStorage;

} // namespace detail
class Tcgen05CpSrcFormatAttr : public ::mlir::Attribute::AttrBase<Tcgen05CpSrcFormatAttr, ::mlir::Attribute, detail::Tcgen05CpSrcFormatAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tcgen05_cp_src_fmt";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static Tcgen05CpSrcFormatAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::Tcgen05CpSrcFormat value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tcgen05_cp_src_fmt"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::Tcgen05CpSrcFormat getValue() const;
};
namespace detail {

struct Tcgen05LdStShapeAttrStorage;

} // namespace detail
class Tcgen05LdStShapeAttr : public ::mlir::Attribute::AttrBase<Tcgen05LdStShapeAttr, ::mlir::Attribute, detail::Tcgen05LdStShapeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tcgen05_ldst_shape";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static Tcgen05LdStShapeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::Tcgen05LdStShape value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tcgen05_ldst_shape"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::Tcgen05LdStShape getValue() const;
};
namespace detail {

struct DotAccumulateTypeAttrStorage;

} // namespace detail
class DotAccumulateTypeAttr : public ::mlir::Attribute::AttrBase<DotAccumulateTypeAttr, ::mlir::Attribute, detail::DotAccumulateTypeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.dot_accumulate_type";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static DotAccumulateTypeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::DotAccumulateType value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dot_accumulate_type"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::DotAccumulateType getValue() const;
};
namespace detail {

struct ClusterLaunchControlQueryTypeAttrStorage;

} // namespace detail
class ClusterLaunchControlQueryTypeAttr : public ::mlir::Attribute::AttrBase<ClusterLaunchControlQueryTypeAttr, ::mlir::Attribute, detail::ClusterLaunchControlQueryTypeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.cluster_launch_control_query_type";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static ClusterLaunchControlQueryTypeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::ClusterLaunchControlQueryType value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cluster_launch_control_query_type"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::ClusterLaunchControlQueryType getValue() const;
};
namespace detail {

struct Tcgen05MMAKindAttrStorage;

} // namespace detail
class Tcgen05MMAKindAttr : public ::mlir::Attribute::AttrBase<Tcgen05MMAKindAttr, ::mlir::Attribute, detail::Tcgen05MMAKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tcgen05_mma_kind";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static Tcgen05MMAKindAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::Tcgen05MMAKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tcgen05_mma_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::Tcgen05MMAKind getValue() const;
};
namespace detail {

struct Tcgen05MMACollectorOpAttrStorage;

} // namespace detail
class Tcgen05MMACollectorOpAttr : public ::mlir::Attribute::AttrBase<Tcgen05MMACollectorOpAttr, ::mlir::Attribute, detail::Tcgen05MMACollectorOpAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tcgen05_mma_collectorop";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static Tcgen05MMACollectorOpAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::Tcgen05MMACollectorOp value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tcgen05_mma_collectorop"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::Tcgen05MMACollectorOp getValue() const;
};
namespace detail {

struct Tcgen05MMABlockScaleAttrStorage;

} // namespace detail
class Tcgen05MMABlockScaleAttr : public ::mlir::Attribute::AttrBase<Tcgen05MMABlockScaleAttr, ::mlir::Attribute, detail::Tcgen05MMABlockScaleAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tcgen05_mma_block_scale";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static Tcgen05MMABlockScaleAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::Tcgen05MMABlockScale value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tcgen05_mma_block_scale"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::Tcgen05MMABlockScale getValue() const;
};
namespace detail {

struct Tcgen05MMACollectorBBufferAttrStorage;

} // namespace detail
class Tcgen05MMACollectorBBufferAttr : public ::mlir::Attribute::AttrBase<Tcgen05MMACollectorBBufferAttr, ::mlir::Attribute, detail::Tcgen05MMACollectorBBufferAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tcgen05_mma_collectorb";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static Tcgen05MMACollectorBBufferAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::Tcgen05MMACollectorBBuffer value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tcgen05_mma_collectorb"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::Tcgen05MMACollectorBBuffer getValue() const;
};
namespace detail {

struct TensormapFieldAttrStorage;

} // namespace detail
class TensormapFieldAttr : public ::mlir::Attribute::AttrBase<TensormapFieldAttr, ::mlir::Attribute, detail::TensormapFieldAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tensormap_field";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static TensormapFieldAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::TensormapField value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tensormap_field"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::TensormapField getValue() const;
};
namespace detail {

struct TensormapElemtypeAttrStorage;

} // namespace detail
class TensormapElemtypeAttr : public ::mlir::Attribute::AttrBase<TensormapElemtypeAttr, ::mlir::Attribute, detail::TensormapElemtypeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tensormap_elemtype";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static TensormapElemtypeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::TensormapElemtype value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tensormap_elemtype"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::TensormapElemtype getValue() const;
};
namespace detail {

struct TensormapInterleaveLayoutAttrStorage;

} // namespace detail
class TensormapInterleaveLayoutAttr : public ::mlir::Attribute::AttrBase<TensormapInterleaveLayoutAttr, ::mlir::Attribute, detail::TensormapInterleaveLayoutAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tensormap_interleave_layout";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static TensormapInterleaveLayoutAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::TensormapInterleaveLayout value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tensormap_interleave_layout"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::TensormapInterleaveLayout getValue() const;
};
namespace detail {

struct TensormapSwizzleModeAttrStorage;

} // namespace detail
class TensormapSwizzleModeAttr : public ::mlir::Attribute::AttrBase<TensormapSwizzleModeAttr, ::mlir::Attribute, detail::TensormapSwizzleModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tensormap_swizzle_mode";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static TensormapSwizzleModeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::TensormapSwizzleMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tensormap_swizzle_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::TensormapSwizzleMode getValue() const;
};
namespace detail {

struct TensormapSwizzleAtomicityAttrStorage;

} // namespace detail
class TensormapSwizzleAtomicityAttr : public ::mlir::Attribute::AttrBase<TensormapSwizzleAtomicityAttr, ::mlir::Attribute, detail::TensormapSwizzleAtomicityAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tensormap_swizzle_atomicity";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static TensormapSwizzleAtomicityAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::TensormapSwizzleAtomicity value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tensormap_swizzle_atomicity"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::TensormapSwizzleAtomicity getValue() const;
};
namespace detail {

struct TensormapFillModeAttrStorage;

} // namespace detail
class TensormapFillModeAttr : public ::mlir::Attribute::AttrBase<TensormapFillModeAttr, ::mlir::Attribute, detail::TensormapFillModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvvm.tensormap_fill_mode";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  static TensormapFillModeAttr get(::mlir::MLIRContext *context, ::mlir::NVVM::TensormapFillMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tensormap_fill_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::NVVM::TensormapFillMode getValue() const;
};
namespace detail {

struct NVVMTargetAttrStorage;

} // namespace detail
class NVVMTargetAttr : public ::mlir::Attribute::AttrBase<NVVMTargetAttr, ::mlir::Attribute, detail::NVVMTargetAttrStorage, ::mlir::gpu::TargetAttrVerifyInterface::Trait> {
public:
  using Base::Base;
  bool hasFlag(StringRef flag) const;
  bool hasFastMath() const;
  bool hasFtz() const;
  bool hasCmdOptions() const;
  std::optional<mlir::NamedAttribute> getCmdOptions() const;
  LogicalResult verifyTarget(Operation *gpuModule);
  static constexpr ::llvm::StringLiteral name = "nvvm.target";
  static constexpr ::llvm::StringLiteral dialectName = "nvvm";
  using Base::getChecked;
  static NVVMTargetAttr get(::mlir::MLIRContext *context, int optLevel = 2, StringRef triple = "nvptx64-nvidia-cuda", StringRef chip = "sm_50", StringRef features = "+ptx60", DictionaryAttr targetFlags = nullptr, ArrayAttr linkFiles = nullptr, bool verifyTarget = true);
  static NVVMTargetAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, int optLevel = 2, StringRef triple = "nvptx64-nvidia-cuda", StringRef chip = "sm_50", StringRef features = "+ptx60", DictionaryAttr targetFlags = nullptr, ArrayAttr linkFiles = nullptr, bool verifyTarget = true);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int O, ::llvm::StringRef triple, ::llvm::StringRef chip, ::llvm::StringRef features, DictionaryAttr flags, ArrayAttr link, bool verifyTarget);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int O, ::llvm::StringRef triple, ::llvm::StringRef chip, ::llvm::StringRef features, DictionaryAttr flags, ArrayAttr link, bool verifyTarget);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"target"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  int getO() const;
  ::llvm::StringRef getTriple() const;
  ::llvm::StringRef getChip() const;
  ::llvm::StringRef getFeatures() const;
  DictionaryAttr getFlags() const;
  ArrayAttr getLink() const;
  bool getVerifyTarget() const;
  ::mlir::LogicalResult verifyTarget(::mlir::Operation *module) const;
};

} // namespace mlir::NVVM
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::CacheEvictionPriorityAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::NVVMMemorySpaceAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MemScopeKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::SharedSpaceAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MemOrderKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::ReduxKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::BarrierReductionAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::ProxyKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::SetMaxRegisterActionAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::ShflKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::VoteSyncKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::PermuteModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::LoadCacheModifierKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::FPRoundingModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::SaturationModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MMAB1OpAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MMAIntOverflowAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MMAKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MMAShapeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MMALayoutAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MMATypesAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MMAFragAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::LdStMatrixShapeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::LdStMatrixEltTypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::ScaleVecSizeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::BlockScaleFormatAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MMABlockScaleKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::TMALoadModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::TMAStoreModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::CTAGroupKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::PrefetchCacheLevelAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::TMAReduxKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::WGMMAScaleInAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::WGMMAScaleOutAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::WGMMATypesAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::GridDepActionKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::MatchSyncKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::Tcgen05FenceKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::Tcgen05WaitKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::Tcgen05CpShapeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::Tcgen05CpMulticastAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::Tcgen05CpSrcFormatAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::Tcgen05LdStShapeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::DotAccumulateTypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::ClusterLaunchControlQueryTypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::Tcgen05MMAKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::Tcgen05MMACollectorOpAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::Tcgen05MMABlockScaleAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::Tcgen05MMACollectorBBufferAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::TensormapFieldAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::TensormapElemtypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::TensormapInterleaveLayoutAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::TensormapSwizzleModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::TensormapSwizzleAtomicityAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::TensormapFillModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NVVM::NVVMTargetAttr)

#endif // GET_ATTRDEF_CLASSES

