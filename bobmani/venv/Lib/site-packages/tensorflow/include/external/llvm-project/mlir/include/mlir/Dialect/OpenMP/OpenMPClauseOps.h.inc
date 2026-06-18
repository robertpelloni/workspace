namespace mlir::omp {

struct AlignClauseOps {
  ::mlir::IntegerAttr align;
};
struct AlignedClauseOps {
  ::llvm::SmallVector<::mlir::Value> alignedVars;
  ::llvm::SmallVector<::mlir::Attribute> alignments;
};
struct AllocateClauseOps {
  ::llvm::SmallVector<::mlir::Value> allocateVars;
  ::llvm::SmallVector<::mlir::Value> allocatorVars;
};
struct AllocatorClauseOps {
  ::mlir::Value allocator;
};
struct BareClauseOps {
  ::mlir::UnitAttr bare;
};
struct BindClauseOps {
  ::mlir::omp::ClauseBindKindAttr bindKind;
};
struct CancelDirectiveNameClauseOps {
  ::mlir::omp::ClauseCancellationConstructTypeAttr cancelDirective;
};
struct CollapseClauseOps {
  ::mlir::IntegerAttr collapseNumLoops;
};
struct CopyprivateClauseOps {
  ::llvm::SmallVector<::mlir::Value> copyprivateVars;
  ::llvm::SmallVector<::mlir::Attribute> copyprivateSyms;
};
struct CriticalNameClauseOps {
  ::mlir::StringAttr symName;
};
struct DependClauseOps {
  ::llvm::SmallVector<::mlir::Attribute> dependKinds;
  ::llvm::SmallVector<::mlir::Value> dependVars;
};
struct DetachClauseOps {
  ::mlir::Value eventHandle;
};
struct DeviceClauseOps {
  ::mlir::Value device;
};
struct DistScheduleClauseOps {
  ::mlir::UnitAttr distScheduleStatic;
  ::mlir::Value distScheduleChunkSize;
};
struct DoacrossClauseOps {
  ::mlir::omp::ClauseDependAttr doacrossDependType;
  ::mlir::IntegerAttr doacrossNumLoops;
  ::llvm::SmallVector<::mlir::Value> doacrossDependVars;
};
struct ExclusiveClauseOps {
  ::llvm::SmallVector<::mlir::Value> exclusiveVars;
};
struct FilterClauseOps {
  ::mlir::Value filteredThreadId;
};
struct FinalClauseOps {
  ::mlir::Value final;
};
struct GrainsizeClauseOps {
  ::mlir::omp::ClauseGrainsizeTypeAttr grainsizeMod;
  ::mlir::Value grainsize;
};
struct HasDeviceAddrClauseOps {
  ::llvm::SmallVector<::mlir::Value> hasDeviceAddrVars;
};
struct HintClauseOps {
  ::mlir::IntegerAttr hint;
};
struct HostEvalClauseOps {
  ::llvm::SmallVector<::mlir::Value> hostEvalVars;
};
struct IfClauseOps {
  ::mlir::Value ifExpr;
};
struct InReductionClauseOps {
  ::llvm::SmallVector<::mlir::Value> inReductionVars;
  ::llvm::SmallVector<bool> inReductionByref;
  ::llvm::SmallVector<::mlir::Attribute> inReductionSyms;
};
struct InbranchClauseOps {
  ::mlir::UnitAttr inbranch;
};
struct InclusiveClauseOps {
  ::llvm::SmallVector<::mlir::Value> inclusiveVars;
};
struct IsDevicePtrClauseOps {
  ::llvm::SmallVector<::mlir::Value> isDevicePtrVars;
};
struct LinearClauseOps {
  ::llvm::SmallVector<::mlir::Value> linearVars;
  ::llvm::SmallVector<::mlir::Value> linearStepVars;
  ::mlir::ArrayAttr linearVarTypes;
};
struct LoopRelatedClauseOps {
  ::llvm::SmallVector<::mlir::Value> loopLowerBounds;
  ::llvm::SmallVector<::mlir::Value> loopUpperBounds;
  ::llvm::SmallVector<::mlir::Value> loopSteps;
  ::mlir::UnitAttr loopInclusive;
};
struct MapClauseOps {
  ::llvm::SmallVector<::mlir::Value> mapVars;
};
struct MemoryOrderClauseOps {
  ::mlir::omp::ClauseMemoryOrderKindAttr memoryOrder;
};
struct MergeableClauseOps {
  ::mlir::UnitAttr mergeable;
};
struct NogroupClauseOps {
  ::mlir::UnitAttr nogroup;
};
struct NontemporalClauseOps {
  ::llvm::SmallVector<::mlir::Value> nontemporalVars;
};
struct NotinbranchClauseOps {
  ::mlir::UnitAttr notinbranch;
};
struct NowaitClauseOps {
  ::mlir::UnitAttr nowait;
};
struct NumTasksClauseOps {
  ::mlir::omp::ClauseNumTasksTypeAttr numTasksMod;
  ::mlir::Value numTasks;
};
struct NumTeamsClauseOps {
  ::mlir::Value numTeamsLower;
  ::llvm::SmallVector<::mlir::Value> numTeamsUpperVars;
};
struct NumThreadsClauseOps {
  ::llvm::SmallVector<::mlir::Value> numThreadsVars;
};
struct OrderClauseOps {
  ::mlir::omp::ClauseOrderKindAttr order;
  ::mlir::omp::OrderModifierAttr orderMod;
};
struct OrderedClauseOps {
  ::mlir::IntegerAttr ordered;
};
struct ParallelizationLevelClauseOps {
  ::mlir::UnitAttr parLevelSimd;
};
struct PriorityClauseOps {
  ::mlir::Value priority;
};
struct PrivateClauseOps {
  ::llvm::SmallVector<::mlir::Value> privateVars;
  ::llvm::SmallVector<::mlir::Attribute> privateSyms;
  ::mlir::UnitAttr privateNeedsBarrier;
};
struct ProcBindClauseOps {
  ::mlir::omp::ClauseProcBindKindAttr procBindKind;
};
struct ReductionClauseOps {
  ::mlir::omp::ReductionModifierAttr reductionMod;
  ::llvm::SmallVector<::mlir::Value> reductionVars;
  ::llvm::SmallVector<bool> reductionByref;
  ::llvm::SmallVector<::mlir::Attribute> reductionSyms;
};
struct SafelenClauseOps {
  ::mlir::IntegerAttr safelen;
};
struct ScheduleClauseOps {
  ::mlir::omp::ClauseScheduleKindAttr scheduleKind;
  ::mlir::Value scheduleChunk;
  ::mlir::omp::ScheduleModifierAttr scheduleMod;
  ::mlir::UnitAttr scheduleSimd;
};
struct SimdlenClauseOps {
  ::mlir::IntegerAttr simdlen;
};
struct SizesClauseOps {
  ::llvm::SmallVector<::mlir::Value> sizes;
};
struct TaskReductionClauseOps {
  ::llvm::SmallVector<::mlir::Value> taskReductionVars;
  ::llvm::SmallVector<bool> taskReductionByref;
  ::llvm::SmallVector<::mlir::Attribute> taskReductionSyms;
};
struct ThreadLimitClauseOps {
  ::llvm::SmallVector<::mlir::Value> threadLimitVars;
};
struct TileSizesClauseOps {
  ::llvm::SmallVector<int64_t> tileSizes;
};
struct UniformClauseOps {
  ::llvm::SmallVector<::mlir::Value> uniformVars;
};
struct UntiedClauseOps {
  ::mlir::UnitAttr untied;
};
struct UseDeviceAddrClauseOps {
  ::llvm::SmallVector<::mlir::Value> useDeviceAddrVars;
};
struct UseDevicePtrClauseOps {
  ::llvm::SmallVector<::mlir::Value> useDevicePtrVars;
};

namespace detail {
template <typename... Mixins>
struct Clauses : public Mixins... {};
} // namespace detail

using AllocateDirOperands = detail::Clauses<AlignClauseOps, AllocatorClauseOps>;

using AtomicCaptureOperands = detail::Clauses<HintClauseOps, MemoryOrderClauseOps>;

using AtomicReadOperands = detail::Clauses<HintClauseOps, MemoryOrderClauseOps>;

using AtomicUpdateOperands = detail::Clauses<HintClauseOps, MemoryOrderClauseOps>;

using AtomicWriteOperands = detail::Clauses<HintClauseOps, MemoryOrderClauseOps>;

using BarrierOperands = detail::Clauses<>;

using CancelOperands = detail::Clauses<CancelDirectiveNameClauseOps, IfClauseOps>;

using CancellationPointOperands = detail::Clauses<CancelDirectiveNameClauseOps>;

using CanonicalLoopOperands = detail::Clauses<>;

using CriticalDeclareOperands = detail::Clauses<CriticalNameClauseOps, HintClauseOps>;

using CriticalOperands = detail::Clauses<>;

using DeclareMapperInfoOperands = detail::Clauses<MapClauseOps>;

using DeclareMapperOperands = detail::Clauses<>;

using DeclareReductionOperands = detail::Clauses<>;

using DeclareSimdOperands = detail::Clauses<AlignedClauseOps, InbranchClauseOps, LinearClauseOps, NotinbranchClauseOps, SimdlenClauseOps, UniformClauseOps>;

using DistributeOperands = detail::Clauses<AllocateClauseOps, DistScheduleClauseOps, OrderClauseOps, PrivateClauseOps>;

using FlushOperands = detail::Clauses<>;

using LoopNestOperands = detail::Clauses<CollapseClauseOps, LoopRelatedClauseOps, TileSizesClauseOps>;

using LoopOperands = detail::Clauses<BindClauseOps, PrivateClauseOps, OrderClauseOps, ReductionClauseOps>;

using MapBoundsOperands = detail::Clauses<>;

using MapInfoOperands = detail::Clauses<>;

using MaskedOperands = detail::Clauses<FilterClauseOps>;

using MasterOperands = detail::Clauses<>;

using NewCliOperands = detail::Clauses<>;

using OrderedOperands = detail::Clauses<DoacrossClauseOps>;

using OrderedRegionOperands = detail::Clauses<ParallelizationLevelClauseOps>;

using ParallelOperands = detail::Clauses<AllocateClauseOps, IfClauseOps, NumThreadsClauseOps, PrivateClauseOps, ProcBindClauseOps, ReductionClauseOps>;

using PrivateClauseOperands = detail::Clauses<>;

using ScanOperands = detail::Clauses<InclusiveClauseOps, ExclusiveClauseOps>;

using SectionOperands = detail::Clauses<>;

using SectionsOperands = detail::Clauses<AllocateClauseOps, NowaitClauseOps, PrivateClauseOps, ReductionClauseOps>;

using SimdOperands = detail::Clauses<AlignedClauseOps, IfClauseOps, LinearClauseOps, NontemporalClauseOps, OrderClauseOps, PrivateClauseOps, ReductionClauseOps, SafelenClauseOps, SimdlenClauseOps>;

using SingleOperands = detail::Clauses<AllocateClauseOps, CopyprivateClauseOps, NowaitClauseOps, PrivateClauseOps>;

using TargetAllocMemOperands = detail::Clauses<>;

using TargetDataOperands = detail::Clauses<DeviceClauseOps, IfClauseOps, MapClauseOps, UseDeviceAddrClauseOps, UseDevicePtrClauseOps>;

using TargetEnterDataOperands = detail::Clauses<DependClauseOps, DeviceClauseOps, IfClauseOps, MapClauseOps, NowaitClauseOps>;

using TargetExitDataOperands = detail::Clauses<DependClauseOps, DeviceClauseOps, IfClauseOps, MapClauseOps, NowaitClauseOps>;

using TargetFreeMemOperands = detail::Clauses<>;

using TargetOperands = detail::Clauses<AllocateClauseOps, BareClauseOps, DependClauseOps, DeviceClauseOps, HasDeviceAddrClauseOps, HostEvalClauseOps, IfClauseOps, InReductionClauseOps, IsDevicePtrClauseOps, MapClauseOps, NowaitClauseOps, PrivateClauseOps, ThreadLimitClauseOps>;

using TargetUpdateOperands = detail::Clauses<DependClauseOps, DeviceClauseOps, IfClauseOps, MapClauseOps, NowaitClauseOps>;

using TaskOperands = detail::Clauses<AllocateClauseOps, DependClauseOps, FinalClauseOps, IfClauseOps, InReductionClauseOps, MergeableClauseOps, PriorityClauseOps, PrivateClauseOps, UntiedClauseOps, DetachClauseOps>;

using TaskgroupOperands = detail::Clauses<AllocateClauseOps, TaskReductionClauseOps>;

using TaskloopOperands = detail::Clauses<AllocateClauseOps, FinalClauseOps, GrainsizeClauseOps, IfClauseOps, InReductionClauseOps, MergeableClauseOps, NogroupClauseOps, NumTasksClauseOps, PriorityClauseOps, PrivateClauseOps, ReductionClauseOps, UntiedClauseOps>;

using TaskwaitOperands = detail::Clauses<DependClauseOps, NowaitClauseOps>;

using TaskyieldOperands = detail::Clauses<>;

using TeamsOperands = detail::Clauses<AllocateClauseOps, IfClauseOps, NumTeamsClauseOps, PrivateClauseOps, ReductionClauseOps, ThreadLimitClauseOps>;

using TerminatorOperands = detail::Clauses<>;

using ThreadprivateOperands = detail::Clauses<>;

using TileOperands = detail::Clauses<SizesClauseOps>;

using UnrollHeuristicOperands = detail::Clauses<>;

using WorkdistributeOperands = detail::Clauses<>;

using WorkshareLoopWrapperOperands = detail::Clauses<>;

using WorkshareOperands = detail::Clauses<NowaitClauseOps>;

using WsloopOperands = detail::Clauses<AllocateClauseOps, LinearClauseOps, NowaitClauseOps, OrderClauseOps, OrderedClauseOps, PrivateClauseOps, ReductionClauseOps, ScheduleClauseOps>;

using YieldOperands = detail::Clauses<>;

} // namespace mlir::omp
