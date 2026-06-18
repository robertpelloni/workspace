/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: NVVMOps.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::NVVM {

::llvm::StringRef stringifyBarrierReduction(BarrierReduction val) {
  switch (val) {
    case BarrierReduction::POPC: return "popc";
    case BarrierReduction::AND: return "and";
    case BarrierReduction::OR: return "or";
  }
  return "";
}

::std::optional<BarrierReduction> symbolizeBarrierReduction(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<BarrierReduction>>(str)
      .Case("popc", BarrierReduction::POPC)
      .Case("and", BarrierReduction::AND)
      .Case("or", BarrierReduction::OR)
      .Default(::std::nullopt);
}
::std::optional<BarrierReduction> symbolizeBarrierReduction(uint32_t value) {
  switch (value) {
  case 0: return BarrierReduction::POPC;
  case 1: return BarrierReduction::AND;
  case 2: return BarrierReduction::OR;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyBlockScaleFormat(BlockScaleFormat val) {
  switch (val) {
    case BlockScaleFormat::UE8M0: return "ue8m0";
    case BlockScaleFormat::UE4M3: return "ue4m3";
  }
  return "";
}

::std::optional<BlockScaleFormat> symbolizeBlockScaleFormat(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<BlockScaleFormat>>(str)
      .Case("ue8m0", BlockScaleFormat::UE8M0)
      .Case("ue4m3", BlockScaleFormat::UE4M3)
      .Default(::std::nullopt);
}
::std::optional<BlockScaleFormat> symbolizeBlockScaleFormat(uint32_t value) {
  switch (value) {
  case 0: return BlockScaleFormat::UE8M0;
  case 1: return BlockScaleFormat::UE4M3;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyCTAGroupKind(CTAGroupKind val) {
  switch (val) {
    case CTAGroupKind::CTA_1: return "cta_1";
    case CTAGroupKind::CTA_2: return "cta_2";
  }
  return "";
}

::std::optional<CTAGroupKind> symbolizeCTAGroupKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<CTAGroupKind>>(str)
      .Case("cta_1", CTAGroupKind::CTA_1)
      .Case("cta_2", CTAGroupKind::CTA_2)
      .Default(::std::nullopt);
}
::std::optional<CTAGroupKind> symbolizeCTAGroupKind(uint32_t value) {
  switch (value) {
  case 0: return CTAGroupKind::CTA_1;
  case 1: return CTAGroupKind::CTA_2;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyCacheEvictionPriority(CacheEvictionPriority val) {
  switch (val) {
    case CacheEvictionPriority::EvictNormal: return "evict_normal";
    case CacheEvictionPriority::EvictFirst: return "evict_first";
    case CacheEvictionPriority::EvictLast: return "evict_last";
    case CacheEvictionPriority::EvictUnchanged: return "evict_unchanged";
    case CacheEvictionPriority::NoAllocate: return "no_allocate";
  }
  return "";
}

::std::optional<CacheEvictionPriority> symbolizeCacheEvictionPriority(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<CacheEvictionPriority>>(str)
      .Case("evict_normal", CacheEvictionPriority::EvictNormal)
      .Case("evict_first", CacheEvictionPriority::EvictFirst)
      .Case("evict_last", CacheEvictionPriority::EvictLast)
      .Case("evict_unchanged", CacheEvictionPriority::EvictUnchanged)
      .Case("no_allocate", CacheEvictionPriority::NoAllocate)
      .Default(::std::nullopt);
}
::std::optional<CacheEvictionPriority> symbolizeCacheEvictionPriority(uint32_t value) {
  switch (value) {
  case 0: return CacheEvictionPriority::EvictNormal;
  case 1: return CacheEvictionPriority::EvictFirst;
  case 2: return CacheEvictionPriority::EvictLast;
  case 3: return CacheEvictionPriority::EvictUnchanged;
  case 4: return CacheEvictionPriority::NoAllocate;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyClusterLaunchControlQueryType(ClusterLaunchControlQueryType val) {
  switch (val) {
    case ClusterLaunchControlQueryType::IS_CANCELED: return "is_canceled";
    case ClusterLaunchControlQueryType::GET_FIRST_CTA_ID_X: return "get_first_cta_id_x";
    case ClusterLaunchControlQueryType::GET_FIRST_CTA_ID_Y: return "get_first_cta_id_y";
    case ClusterLaunchControlQueryType::GET_FIRST_CTA_ID_Z: return "get_first_cta_id_z";
  }
  return "";
}

::std::optional<ClusterLaunchControlQueryType> symbolizeClusterLaunchControlQueryType(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ClusterLaunchControlQueryType>>(str)
      .Case("is_canceled", ClusterLaunchControlQueryType::IS_CANCELED)
      .Case("get_first_cta_id_x", ClusterLaunchControlQueryType::GET_FIRST_CTA_ID_X)
      .Case("get_first_cta_id_y", ClusterLaunchControlQueryType::GET_FIRST_CTA_ID_Y)
      .Case("get_first_cta_id_z", ClusterLaunchControlQueryType::GET_FIRST_CTA_ID_Z)
      .Default(::std::nullopt);
}
::std::optional<ClusterLaunchControlQueryType> symbolizeClusterLaunchControlQueryType(uint32_t value) {
  switch (value) {
  case 0: return ClusterLaunchControlQueryType::IS_CANCELED;
  case 1: return ClusterLaunchControlQueryType::GET_FIRST_CTA_ID_X;
  case 2: return ClusterLaunchControlQueryType::GET_FIRST_CTA_ID_Y;
  case 3: return ClusterLaunchControlQueryType::GET_FIRST_CTA_ID_Z;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyDotAccumulateType(DotAccumulateType val) {
  switch (val) {
    case DotAccumulateType::SIGNED: return "signed";
    case DotAccumulateType::UNSIGNED: return "unsigned";
  }
  return "";
}

::std::optional<DotAccumulateType> symbolizeDotAccumulateType(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<DotAccumulateType>>(str)
      .Case("signed", DotAccumulateType::SIGNED)
      .Case("unsigned", DotAccumulateType::UNSIGNED)
      .Default(::std::nullopt);
}
::std::optional<DotAccumulateType> symbolizeDotAccumulateType(uint32_t value) {
  switch (value) {
  case 1: return DotAccumulateType::SIGNED;
  case 0: return DotAccumulateType::UNSIGNED;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyFPRoundingMode(FPRoundingMode val) {
  switch (val) {
    case FPRoundingMode::NONE: return "none";
    case FPRoundingMode::RN: return "rn";
    case FPRoundingMode::RM: return "rm";
    case FPRoundingMode::RP: return "rp";
    case FPRoundingMode::RZ: return "rz";
    case FPRoundingMode::RNA: return "rna";
    case FPRoundingMode::RS: return "rs";
  }
  return "";
}

::std::optional<FPRoundingMode> symbolizeFPRoundingMode(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<FPRoundingMode>>(str)
      .Case("none", FPRoundingMode::NONE)
      .Case("rn", FPRoundingMode::RN)
      .Case("rm", FPRoundingMode::RM)
      .Case("rp", FPRoundingMode::RP)
      .Case("rz", FPRoundingMode::RZ)
      .Case("rna", FPRoundingMode::RNA)
      .Case("rs", FPRoundingMode::RS)
      .Default(::std::nullopt);
}
::std::optional<FPRoundingMode> symbolizeFPRoundingMode(uint32_t value) {
  switch (value) {
  case 0: return FPRoundingMode::NONE;
  case 1: return FPRoundingMode::RN;
  case 2: return FPRoundingMode::RM;
  case 3: return FPRoundingMode::RP;
  case 4: return FPRoundingMode::RZ;
  case 5: return FPRoundingMode::RNA;
  case 6: return FPRoundingMode::RS;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyGridDepActionKind(GridDepActionKind val) {
  switch (val) {
    case GridDepActionKind::wait: return "wait";
    case GridDepActionKind::launch_dependents: return "launch_dependents";
  }
  return "";
}

::std::optional<GridDepActionKind> symbolizeGridDepActionKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<GridDepActionKind>>(str)
      .Case("wait", GridDepActionKind::wait)
      .Case("launch_dependents", GridDepActionKind::launch_dependents)
      .Default(::std::nullopt);
}
::std::optional<GridDepActionKind> symbolizeGridDepActionKind(uint32_t value) {
  switch (value) {
  case 0: return GridDepActionKind::wait;
  case 1: return GridDepActionKind::launch_dependents;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyLdStMatrixEltType(LdStMatrixEltType val) {
  switch (val) {
    case LdStMatrixEltType::B16: return "b16";
    case LdStMatrixEltType::B8: return "b8";
    case LdStMatrixEltType::B8X16_B6X16_P32: return "b8x16.b6x16_p32";
    case LdStMatrixEltType::B8X16_B4X16_P64: return "b8x16.b4x16_p64";
  }
  return "";
}

::std::optional<LdStMatrixEltType> symbolizeLdStMatrixEltType(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<LdStMatrixEltType>>(str)
      .Case("b16", LdStMatrixEltType::B16)
      .Case("b8", LdStMatrixEltType::B8)
      .Case("b8x16.b6x16_p32", LdStMatrixEltType::B8X16_B6X16_P32)
      .Case("b8x16.b4x16_p64", LdStMatrixEltType::B8X16_B4X16_P64)
      .Default(::std::nullopt);
}
::std::optional<LdStMatrixEltType> symbolizeLdStMatrixEltType(uint32_t value) {
  switch (value) {
  case 0: return LdStMatrixEltType::B16;
  case 1: return LdStMatrixEltType::B8;
  case 2: return LdStMatrixEltType::B8X16_B6X16_P32;
  case 3: return LdStMatrixEltType::B8X16_B4X16_P64;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyLoadCacheModifierKind(LoadCacheModifierKind val) {
  switch (val) {
    case LoadCacheModifierKind::CA: return "ca";
    case LoadCacheModifierKind::CG: return "cg";
    case LoadCacheModifierKind::CS: return "cs";
    case LoadCacheModifierKind::LU: return "lu";
    case LoadCacheModifierKind::CV: return "cv";
  }
  return "";
}

::std::optional<LoadCacheModifierKind> symbolizeLoadCacheModifierKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<LoadCacheModifierKind>>(str)
      .Case("ca", LoadCacheModifierKind::CA)
      .Case("cg", LoadCacheModifierKind::CG)
      .Case("cs", LoadCacheModifierKind::CS)
      .Case("lu", LoadCacheModifierKind::LU)
      .Case("cv", LoadCacheModifierKind::CV)
      .Default(::std::nullopt);
}
::std::optional<LoadCacheModifierKind> symbolizeLoadCacheModifierKind(uint32_t value) {
  switch (value) {
  case 0: return LoadCacheModifierKind::CA;
  case 1: return LoadCacheModifierKind::CG;
  case 2: return LoadCacheModifierKind::CS;
  case 3: return LoadCacheModifierKind::LU;
  case 4: return LoadCacheModifierKind::CV;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyMMAB1Op(MMAB1Op val) {
  switch (val) {
    case MMAB1Op::none: return "none";
    case MMAB1Op::xor_popc: return "xor_popc";
    case MMAB1Op::and_popc: return "and_popc";
  }
  return "";
}

::std::optional<MMAB1Op> symbolizeMMAB1Op(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MMAB1Op>>(str)
      .Case("none", MMAB1Op::none)
      .Case("xor_popc", MMAB1Op::xor_popc)
      .Case("and_popc", MMAB1Op::and_popc)
      .Default(::std::nullopt);
}
::std::optional<MMAB1Op> symbolizeMMAB1Op(uint32_t value) {
  switch (value) {
  case 0: return MMAB1Op::none;
  case 1: return MMAB1Op::xor_popc;
  case 2: return MMAB1Op::and_popc;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyMMABlockScaleKind(MMABlockScaleKind val) {
  switch (val) {
    case MMABlockScaleKind::MXF8F6F4: return "mxf8f6f4";
    case MMABlockScaleKind::MXF4: return "mxf4";
    case MMABlockScaleKind::MXF4NVF4: return "mxf4nvf4";
  }
  return "";
}

::std::optional<MMABlockScaleKind> symbolizeMMABlockScaleKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MMABlockScaleKind>>(str)
      .Case("mxf8f6f4", MMABlockScaleKind::MXF8F6F4)
      .Case("mxf4", MMABlockScaleKind::MXF4)
      .Case("mxf4nvf4", MMABlockScaleKind::MXF4NVF4)
      .Default(::std::nullopt);
}
::std::optional<MMABlockScaleKind> symbolizeMMABlockScaleKind(uint32_t value) {
  switch (value) {
  case 0: return MMABlockScaleKind::MXF8F6F4;
  case 1: return MMABlockScaleKind::MXF4;
  case 2: return MMABlockScaleKind::MXF4NVF4;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyMMAFrag(MMAFrag val) {
  switch (val) {
    case MMAFrag::a: return "a";
    case MMAFrag::b: return "b";
    case MMAFrag::c: return "c";
  }
  return "";
}

::std::optional<MMAFrag> symbolizeMMAFrag(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MMAFrag>>(str)
      .Case("a", MMAFrag::a)
      .Case("b", MMAFrag::b)
      .Case("c", MMAFrag::c)
      .Default(::std::nullopt);
}
::std::optional<MMAFrag> symbolizeMMAFrag(uint32_t value) {
  switch (value) {
  case 0: return MMAFrag::a;
  case 1: return MMAFrag::b;
  case 2: return MMAFrag::c;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyMMAIntOverflow(MMAIntOverflow val) {
  switch (val) {
    case MMAIntOverflow::satfinite: return "satfinite";
    case MMAIntOverflow::wrapped: return "wrapped";
  }
  return "";
}

::std::optional<MMAIntOverflow> symbolizeMMAIntOverflow(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MMAIntOverflow>>(str)
      .Case("satfinite", MMAIntOverflow::satfinite)
      .Case("wrapped", MMAIntOverflow::wrapped)
      .Default(::std::nullopt);
}
::std::optional<MMAIntOverflow> symbolizeMMAIntOverflow(uint32_t value) {
  switch (value) {
  case 1: return MMAIntOverflow::satfinite;
  case 0: return MMAIntOverflow::wrapped;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyMMAKind(MMAKind val) {
  switch (val) {
    case MMAKind::f8f6f4: return "f8f6f4";
  }
  return "";
}

::std::optional<MMAKind> symbolizeMMAKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MMAKind>>(str)
      .Case("f8f6f4", MMAKind::f8f6f4)
      .Default(::std::nullopt);
}
::std::optional<MMAKind> symbolizeMMAKind(uint32_t value) {
  switch (value) {
  case 0: return MMAKind::f8f6f4;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyMMALayout(MMALayout val) {
  switch (val) {
    case MMALayout::row: return "row";
    case MMALayout::col: return "col";
  }
  return "";
}

::std::optional<MMALayout> symbolizeMMALayout(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MMALayout>>(str)
      .Case("row", MMALayout::row)
      .Case("col", MMALayout::col)
      .Default(::std::nullopt);
}
::std::optional<MMALayout> symbolizeMMALayout(uint32_t value) {
  switch (value) {
  case 0: return MMALayout::row;
  case 1: return MMALayout::col;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyMMATypes(MMATypes val) {
  switch (val) {
    case MMATypes::f16: return "f16";
    case MMATypes::f32: return "f32";
    case MMATypes::tf32: return "tf32";
    case MMATypes::bf16: return "bf16";
    case MMATypes::s8: return "s8";
    case MMATypes::u8: return "u8";
    case MMATypes::s32: return "s32";
    case MMATypes::s4: return "s4";
    case MMATypes::u4: return "u4";
    case MMATypes::b1: return "b1";
    case MMATypes::f64: return "f64";
    case MMATypes::e4m3: return "e4m3";
    case MMATypes::e5m2: return "e5m2";
    case MMATypes::e3m2: return "e3m2";
    case MMATypes::e2m3: return "e2m3";
    case MMATypes::e2m1: return "e2m1";
  }
  return "";
}

::std::optional<MMATypes> symbolizeMMATypes(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MMATypes>>(str)
      .Case("f16", MMATypes::f16)
      .Case("f32", MMATypes::f32)
      .Case("tf32", MMATypes::tf32)
      .Case("bf16", MMATypes::bf16)
      .Case("s8", MMATypes::s8)
      .Case("u8", MMATypes::u8)
      .Case("s32", MMATypes::s32)
      .Case("s4", MMATypes::s4)
      .Case("u4", MMATypes::u4)
      .Case("b1", MMATypes::b1)
      .Case("f64", MMATypes::f64)
      .Case("e4m3", MMATypes::e4m3)
      .Case("e5m2", MMATypes::e5m2)
      .Case("e3m2", MMATypes::e3m2)
      .Case("e2m3", MMATypes::e2m3)
      .Case("e2m1", MMATypes::e2m1)
      .Default(::std::nullopt);
}
::std::optional<MMATypes> symbolizeMMATypes(uint32_t value) {
  switch (value) {
  case 0: return MMATypes::f16;
  case 1: return MMATypes::f32;
  case 2: return MMATypes::tf32;
  case 9: return MMATypes::bf16;
  case 4: return MMATypes::s8;
  case 3: return MMATypes::u8;
  case 5: return MMATypes::s32;
  case 8: return MMATypes::s4;
  case 7: return MMATypes::u4;
  case 6: return MMATypes::b1;
  case 10: return MMATypes::f64;
  case 11: return MMATypes::e4m3;
  case 12: return MMATypes::e5m2;
  case 13: return MMATypes::e3m2;
  case 14: return MMATypes::e2m3;
  case 15: return MMATypes::e2m1;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyMatchSyncKind(MatchSyncKind val) {
  switch (val) {
    case MatchSyncKind::any: return "any";
    case MatchSyncKind::all: return "all";
  }
  return "";
}

::std::optional<MatchSyncKind> symbolizeMatchSyncKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MatchSyncKind>>(str)
      .Case("any", MatchSyncKind::any)
      .Case("all", MatchSyncKind::all)
      .Default(::std::nullopt);
}
::std::optional<MatchSyncKind> symbolizeMatchSyncKind(uint32_t value) {
  switch (value) {
  case 0: return MatchSyncKind::any;
  case 1: return MatchSyncKind::all;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyMemOrderKind(MemOrderKind val) {
  switch (val) {
    case MemOrderKind::WEAK: return "weak";
    case MemOrderKind::RELAXED: return "relaxed";
    case MemOrderKind::ACQUIRE: return "acquire";
    case MemOrderKind::RELEASE: return "release";
    case MemOrderKind::ACQ_REL: return "acq_rel";
    case MemOrderKind::SC: return "sc";
    case MemOrderKind::MMIO: return "mmio";
    case MemOrderKind::VOLATILE: return "volatile";
  }
  return "";
}

::std::optional<MemOrderKind> symbolizeMemOrderKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MemOrderKind>>(str)
      .Case("weak", MemOrderKind::WEAK)
      .Case("relaxed", MemOrderKind::RELAXED)
      .Case("acquire", MemOrderKind::ACQUIRE)
      .Case("release", MemOrderKind::RELEASE)
      .Case("acq_rel", MemOrderKind::ACQ_REL)
      .Case("sc", MemOrderKind::SC)
      .Case("mmio", MemOrderKind::MMIO)
      .Case("volatile", MemOrderKind::VOLATILE)
      .Default(::std::nullopt);
}
::std::optional<MemOrderKind> symbolizeMemOrderKind(uint32_t value) {
  switch (value) {
  case 0: return MemOrderKind::WEAK;
  case 1: return MemOrderKind::RELAXED;
  case 2: return MemOrderKind::ACQUIRE;
  case 3: return MemOrderKind::RELEASE;
  case 4: return MemOrderKind::ACQ_REL;
  case 5: return MemOrderKind::SC;
  case 6: return MemOrderKind::MMIO;
  case 7: return MemOrderKind::VOLATILE;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyMemScopeKind(MemScopeKind val) {
  switch (val) {
    case MemScopeKind::CTA: return "cta";
    case MemScopeKind::CLUSTER: return "cluster";
    case MemScopeKind::GPU: return "gpu";
    case MemScopeKind::SYS: return "sys";
  }
  return "";
}

::std::optional<MemScopeKind> symbolizeMemScopeKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MemScopeKind>>(str)
      .Case("cta", MemScopeKind::CTA)
      .Case("cluster", MemScopeKind::CLUSTER)
      .Case("gpu", MemScopeKind::GPU)
      .Case("sys", MemScopeKind::SYS)
      .Default(::std::nullopt);
}
::std::optional<MemScopeKind> symbolizeMemScopeKind(uint32_t value) {
  switch (value) {
  case 0: return MemScopeKind::CTA;
  case 1: return MemScopeKind::CLUSTER;
  case 2: return MemScopeKind::GPU;
  case 3: return MemScopeKind::SYS;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyNVVMMemorySpace(NVVMMemorySpace val) {
  switch (val) {
    case NVVMMemorySpace::Generic: return "generic";
    case NVVMMemorySpace::Global: return "global";
    case NVVMMemorySpace::Shared: return "shared";
    case NVVMMemorySpace::Constant: return "constant";
    case NVVMMemorySpace::Local: return "local";
    case NVVMMemorySpace::Tensor: return "tensor";
    case NVVMMemorySpace::SharedCluster: return "shared_cluster";
  }
  return "";
}

::std::optional<NVVMMemorySpace> symbolizeNVVMMemorySpace(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<NVVMMemorySpace>>(str)
      .Case("generic", NVVMMemorySpace::Generic)
      .Case("global", NVVMMemorySpace::Global)
      .Case("shared", NVVMMemorySpace::Shared)
      .Case("constant", NVVMMemorySpace::Constant)
      .Case("local", NVVMMemorySpace::Local)
      .Case("tensor", NVVMMemorySpace::Tensor)
      .Case("shared_cluster", NVVMMemorySpace::SharedCluster)
      .Default(::std::nullopt);
}
::std::optional<NVVMMemorySpace> symbolizeNVVMMemorySpace(uint32_t value) {
  switch (value) {
  case 0: return NVVMMemorySpace::Generic;
  case 1: return NVVMMemorySpace::Global;
  case 3: return NVVMMemorySpace::Shared;
  case 4: return NVVMMemorySpace::Constant;
  case 5: return NVVMMemorySpace::Local;
  case 6: return NVVMMemorySpace::Tensor;
  case 7: return NVVMMemorySpace::SharedCluster;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyPermuteMode(PermuteMode val) {
  switch (val) {
    case PermuteMode::DEFAULT: return "default";
    case PermuteMode::F4E: return "f4e";
    case PermuteMode::B4E: return "b4e";
    case PermuteMode::RC8: return "rc8";
    case PermuteMode::ECL: return "ecl";
    case PermuteMode::ECR: return "ecr";
    case PermuteMode::RC16: return "rc16";
  }
  return "";
}

::std::optional<PermuteMode> symbolizePermuteMode(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<PermuteMode>>(str)
      .Case("default", PermuteMode::DEFAULT)
      .Case("f4e", PermuteMode::F4E)
      .Case("b4e", PermuteMode::B4E)
      .Case("rc8", PermuteMode::RC8)
      .Case("ecl", PermuteMode::ECL)
      .Case("ecr", PermuteMode::ECR)
      .Case("rc16", PermuteMode::RC16)
      .Default(::std::nullopt);
}
::std::optional<PermuteMode> symbolizePermuteMode(uint32_t value) {
  switch (value) {
  case 0: return PermuteMode::DEFAULT;
  case 1: return PermuteMode::F4E;
  case 2: return PermuteMode::B4E;
  case 3: return PermuteMode::RC8;
  case 4: return PermuteMode::ECL;
  case 5: return PermuteMode::ECR;
  case 6: return PermuteMode::RC16;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyPrefetchCacheLevel(PrefetchCacheLevel val) {
  switch (val) {
    case PrefetchCacheLevel::L1: return "L1";
    case PrefetchCacheLevel::L2: return "L2";
  }
  return "";
}

::std::optional<PrefetchCacheLevel> symbolizePrefetchCacheLevel(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<PrefetchCacheLevel>>(str)
      .Case("L1", PrefetchCacheLevel::L1)
      .Case("L2", PrefetchCacheLevel::L2)
      .Default(::std::nullopt);
}
::std::optional<PrefetchCacheLevel> symbolizePrefetchCacheLevel(uint32_t value) {
  switch (value) {
  case 0: return PrefetchCacheLevel::L1;
  case 1: return PrefetchCacheLevel::L2;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyProxyKind(ProxyKind val) {
  switch (val) {
    case ProxyKind::alias: return "alias";
    case ProxyKind::async: return "async";
    case ProxyKind::async_global: return "async.global";
    case ProxyKind::async_shared: return "async.shared";
    case ProxyKind::TENSORMAP: return "tensormap";
    case ProxyKind::GENERIC: return "generic";
  }
  return "";
}

::std::optional<ProxyKind> symbolizeProxyKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ProxyKind>>(str)
      .Case("alias", ProxyKind::alias)
      .Case("async", ProxyKind::async)
      .Case("async.global", ProxyKind::async_global)
      .Case("async.shared", ProxyKind::async_shared)
      .Case("tensormap", ProxyKind::TENSORMAP)
      .Case("generic", ProxyKind::GENERIC)
      .Default(::std::nullopt);
}
::std::optional<ProxyKind> symbolizeProxyKind(uint32_t value) {
  switch (value) {
  case 0: return ProxyKind::alias;
  case 1: return ProxyKind::async;
  case 2: return ProxyKind::async_global;
  case 3: return ProxyKind::async_shared;
  case 4: return ProxyKind::TENSORMAP;
  case 5: return ProxyKind::GENERIC;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyReduxKind(ReduxKind val) {
  switch (val) {
    case ReduxKind::ADD: return "add";
    case ReduxKind::AND: return "and";
    case ReduxKind::MAX: return "max";
    case ReduxKind::MIN: return "min";
    case ReduxKind::OR: return "or";
    case ReduxKind::UMAX: return "umax";
    case ReduxKind::UMIN: return "umin";
    case ReduxKind::XOR: return "xor";
    case ReduxKind::FMIN: return "fmin";
    case ReduxKind::FMAX: return "fmax";
  }
  return "";
}

::std::optional<ReduxKind> symbolizeReduxKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ReduxKind>>(str)
      .Case("add", ReduxKind::ADD)
      .Case("and", ReduxKind::AND)
      .Case("max", ReduxKind::MAX)
      .Case("min", ReduxKind::MIN)
      .Case("or", ReduxKind::OR)
      .Case("umax", ReduxKind::UMAX)
      .Case("umin", ReduxKind::UMIN)
      .Case("xor", ReduxKind::XOR)
      .Case("fmin", ReduxKind::FMIN)
      .Case("fmax", ReduxKind::FMAX)
      .Default(::std::nullopt);
}
::std::optional<ReduxKind> symbolizeReduxKind(uint32_t value) {
  switch (value) {
  case 1: return ReduxKind::ADD;
  case 2: return ReduxKind::AND;
  case 3: return ReduxKind::MAX;
  case 4: return ReduxKind::MIN;
  case 5: return ReduxKind::OR;
  case 6: return ReduxKind::UMAX;
  case 7: return ReduxKind::UMIN;
  case 8: return ReduxKind::XOR;
  case 9: return ReduxKind::FMIN;
  case 10: return ReduxKind::FMAX;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifySaturationMode(SaturationMode val) {
  switch (val) {
    case SaturationMode::NONE: return "none";
    case SaturationMode::SATFINITE: return "satfinite";
  }
  return "";
}

::std::optional<SaturationMode> symbolizeSaturationMode(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<SaturationMode>>(str)
      .Case("none", SaturationMode::NONE)
      .Case("satfinite", SaturationMode::SATFINITE)
      .Default(::std::nullopt);
}
::std::optional<SaturationMode> symbolizeSaturationMode(uint32_t value) {
  switch (value) {
  case 0: return SaturationMode::NONE;
  case 1: return SaturationMode::SATFINITE;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyScaleVecSize(ScaleVecSize val) {
  switch (val) {
    case ScaleVecSize::X1: return "x1";
    case ScaleVecSize::X2: return "x2";
    case ScaleVecSize::X4: return "x4";
  }
  return "";
}

::std::optional<ScaleVecSize> symbolizeScaleVecSize(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ScaleVecSize>>(str)
      .Case("x1", ScaleVecSize::X1)
      .Case("x2", ScaleVecSize::X2)
      .Case("x4", ScaleVecSize::X4)
      .Default(::std::nullopt);
}
::std::optional<ScaleVecSize> symbolizeScaleVecSize(uint32_t value) {
  switch (value) {
  case 0: return ScaleVecSize::X1;
  case 1: return ScaleVecSize::X2;
  case 2: return ScaleVecSize::X4;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifySetMaxRegisterAction(SetMaxRegisterAction val) {
  switch (val) {
    case SetMaxRegisterAction::decrease: return "decrease";
    case SetMaxRegisterAction::increase: return "increase";
  }
  return "";
}

::std::optional<SetMaxRegisterAction> symbolizeSetMaxRegisterAction(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<SetMaxRegisterAction>>(str)
      .Case("decrease", SetMaxRegisterAction::decrease)
      .Case("increase", SetMaxRegisterAction::increase)
      .Default(::std::nullopt);
}
::std::optional<SetMaxRegisterAction> symbolizeSetMaxRegisterAction(uint32_t value) {
  switch (value) {
  case 1: return SetMaxRegisterAction::decrease;
  case 0: return SetMaxRegisterAction::increase;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifySharedSpace(SharedSpace val) {
  switch (val) {
    case SharedSpace::shared_cta: return "cta";
    case SharedSpace::shared_cluster: return "cluster";
  }
  return "";
}

::std::optional<SharedSpace> symbolizeSharedSpace(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<SharedSpace>>(str)
      .Case("cta", SharedSpace::shared_cta)
      .Case("cluster", SharedSpace::shared_cluster)
      .Default(::std::nullopt);
}
::std::optional<SharedSpace> symbolizeSharedSpace(uint32_t value) {
  switch (value) {
  case 0: return SharedSpace::shared_cta;
  case 1: return SharedSpace::shared_cluster;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyShflKind(ShflKind val) {
  switch (val) {
    case ShflKind::bfly: return "bfly";
    case ShflKind::up: return "up";
    case ShflKind::down: return "down";
    case ShflKind::idx: return "idx";
  }
  return "";
}

::std::optional<ShflKind> symbolizeShflKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ShflKind>>(str)
      .Case("bfly", ShflKind::bfly)
      .Case("up", ShflKind::up)
      .Case("down", ShflKind::down)
      .Case("idx", ShflKind::idx)
      .Default(::std::nullopt);
}
::std::optional<ShflKind> symbolizeShflKind(uint32_t value) {
  switch (value) {
  case 0: return ShflKind::bfly;
  case 1: return ShflKind::up;
  case 2: return ShflKind::down;
  case 3: return ShflKind::idx;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTMALoadMode(TMALoadMode val) {
  switch (val) {
    case TMALoadMode::TILE: return "tile";
    case TMALoadMode::IM2COL: return "im2col";
    case TMALoadMode::IM2COL_W: return "im2col_w";
    case TMALoadMode::IM2COL_W_128: return "im2col_w_128";
    case TMALoadMode::TILE_GATHER4: return "tile_gather4";
  }
  return "";
}

::std::optional<TMALoadMode> symbolizeTMALoadMode(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TMALoadMode>>(str)
      .Case("tile", TMALoadMode::TILE)
      .Case("im2col", TMALoadMode::IM2COL)
      .Case("im2col_w", TMALoadMode::IM2COL_W)
      .Case("im2col_w_128", TMALoadMode::IM2COL_W_128)
      .Case("tile_gather4", TMALoadMode::TILE_GATHER4)
      .Default(::std::nullopt);
}
::std::optional<TMALoadMode> symbolizeTMALoadMode(uint32_t value) {
  switch (value) {
  case 0: return TMALoadMode::TILE;
  case 1: return TMALoadMode::IM2COL;
  case 2: return TMALoadMode::IM2COL_W;
  case 3: return TMALoadMode::IM2COL_W_128;
  case 4: return TMALoadMode::TILE_GATHER4;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTMAReduxKind(TMAReduxKind val) {
  switch (val) {
    case TMAReduxKind::ADD: return "add";
    case TMAReduxKind::MAX: return "max";
    case TMAReduxKind::MIN: return "min";
    case TMAReduxKind::INC: return "inc";
    case TMAReduxKind::DEC: return "dec";
    case TMAReduxKind::AND: return "and";
    case TMAReduxKind::OR: return "or";
    case TMAReduxKind::XOR: return "xor";
  }
  return "";
}

::std::optional<TMAReduxKind> symbolizeTMAReduxKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TMAReduxKind>>(str)
      .Case("add", TMAReduxKind::ADD)
      .Case("max", TMAReduxKind::MAX)
      .Case("min", TMAReduxKind::MIN)
      .Case("inc", TMAReduxKind::INC)
      .Case("dec", TMAReduxKind::DEC)
      .Case("and", TMAReduxKind::AND)
      .Case("or", TMAReduxKind::OR)
      .Case("xor", TMAReduxKind::XOR)
      .Default(::std::nullopt);
}
::std::optional<TMAReduxKind> symbolizeTMAReduxKind(uint32_t value) {
  switch (value) {
  case 0: return TMAReduxKind::ADD;
  case 2: return TMAReduxKind::MAX;
  case 1: return TMAReduxKind::MIN;
  case 3: return TMAReduxKind::INC;
  case 4: return TMAReduxKind::DEC;
  case 5: return TMAReduxKind::AND;
  case 6: return TMAReduxKind::OR;
  case 7: return TMAReduxKind::XOR;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTMAStoreMode(TMAStoreMode val) {
  switch (val) {
    case TMAStoreMode::TILE: return "tile";
    case TMAStoreMode::IM2COL: return "im2col";
    case TMAStoreMode::TILE_SCATTER4: return "tile_scatter4";
  }
  return "";
}

::std::optional<TMAStoreMode> symbolizeTMAStoreMode(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TMAStoreMode>>(str)
      .Case("tile", TMAStoreMode::TILE)
      .Case("im2col", TMAStoreMode::IM2COL)
      .Case("tile_scatter4", TMAStoreMode::TILE_SCATTER4)
      .Default(::std::nullopt);
}
::std::optional<TMAStoreMode> symbolizeTMAStoreMode(uint32_t value) {
  switch (value) {
  case 0: return TMAStoreMode::TILE;
  case 1: return TMAStoreMode::IM2COL;
  case 2: return TMAStoreMode::TILE_SCATTER4;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTcgen05CpMulticast(Tcgen05CpMulticast val) {
  switch (val) {
    case Tcgen05CpMulticast::NONE: return "none";
    case Tcgen05CpMulticast::WARPX2_02_13: return "warpx2_02_13";
    case Tcgen05CpMulticast::WARPX2_01_23: return "warpx2_01_23";
    case Tcgen05CpMulticast::WARPX4: return "warpx4";
  }
  return "";
}

::std::optional<Tcgen05CpMulticast> symbolizeTcgen05CpMulticast(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Tcgen05CpMulticast>>(str)
      .Case("none", Tcgen05CpMulticast::NONE)
      .Case("warpx2_02_13", Tcgen05CpMulticast::WARPX2_02_13)
      .Case("warpx2_01_23", Tcgen05CpMulticast::WARPX2_01_23)
      .Case("warpx4", Tcgen05CpMulticast::WARPX4)
      .Default(::std::nullopt);
}
::std::optional<Tcgen05CpMulticast> symbolizeTcgen05CpMulticast(uint32_t value) {
  switch (value) {
  case 0: return Tcgen05CpMulticast::NONE;
  case 1: return Tcgen05CpMulticast::WARPX2_02_13;
  case 2: return Tcgen05CpMulticast::WARPX2_01_23;
  case 3: return Tcgen05CpMulticast::WARPX4;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTcgen05CpShape(Tcgen05CpShape val) {
  switch (val) {
    case Tcgen05CpShape::SHAPE_128x256b: return "shape_128x256b";
    case Tcgen05CpShape::SHAPE_4x256b: return "shape_4x256b";
    case Tcgen05CpShape::SHAPE_128x128b: return "shape_128x128b";
    case Tcgen05CpShape::SHAPE_64x128b: return "shape_64x128b";
    case Tcgen05CpShape::SHAPE_32x128b: return "shape_32x128b";
  }
  return "";
}

::std::optional<Tcgen05CpShape> symbolizeTcgen05CpShape(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Tcgen05CpShape>>(str)
      .Case("shape_128x256b", Tcgen05CpShape::SHAPE_128x256b)
      .Case("shape_4x256b", Tcgen05CpShape::SHAPE_4x256b)
      .Case("shape_128x128b", Tcgen05CpShape::SHAPE_128x128b)
      .Case("shape_64x128b", Tcgen05CpShape::SHAPE_64x128b)
      .Case("shape_32x128b", Tcgen05CpShape::SHAPE_32x128b)
      .Default(::std::nullopt);
}
::std::optional<Tcgen05CpShape> symbolizeTcgen05CpShape(uint32_t value) {
  switch (value) {
  case 0: return Tcgen05CpShape::SHAPE_128x256b;
  case 1: return Tcgen05CpShape::SHAPE_4x256b;
  case 2: return Tcgen05CpShape::SHAPE_128x128b;
  case 3: return Tcgen05CpShape::SHAPE_64x128b;
  case 4: return Tcgen05CpShape::SHAPE_32x128b;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTcgen05CpSrcFormat(Tcgen05CpSrcFormat val) {
  switch (val) {
    case Tcgen05CpSrcFormat::B6x16_P32: return "b6x16_p32";
    case Tcgen05CpSrcFormat::B4x16_P64: return "b4x16_p64";
  }
  return "";
}

::std::optional<Tcgen05CpSrcFormat> symbolizeTcgen05CpSrcFormat(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Tcgen05CpSrcFormat>>(str)
      .Case("b6x16_p32", Tcgen05CpSrcFormat::B6x16_P32)
      .Case("b4x16_p64", Tcgen05CpSrcFormat::B4x16_P64)
      .Default(::std::nullopt);
}
::std::optional<Tcgen05CpSrcFormat> symbolizeTcgen05CpSrcFormat(uint32_t value) {
  switch (value) {
  case 0: return Tcgen05CpSrcFormat::B6x16_P32;
  case 1: return Tcgen05CpSrcFormat::B4x16_P64;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTcgen05FenceKind(Tcgen05FenceKind val) {
  switch (val) {
    case Tcgen05FenceKind::BEFORE_THREAD_SYNC: return "before";
    case Tcgen05FenceKind::AFTER_THREAD_SYNC: return "after";
  }
  return "";
}

::std::optional<Tcgen05FenceKind> symbolizeTcgen05FenceKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Tcgen05FenceKind>>(str)
      .Case("before", Tcgen05FenceKind::BEFORE_THREAD_SYNC)
      .Case("after", Tcgen05FenceKind::AFTER_THREAD_SYNC)
      .Default(::std::nullopt);
}
::std::optional<Tcgen05FenceKind> symbolizeTcgen05FenceKind(uint32_t value) {
  switch (value) {
  case 0: return Tcgen05FenceKind::BEFORE_THREAD_SYNC;
  case 1: return Tcgen05FenceKind::AFTER_THREAD_SYNC;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTcgen05LdStShape(Tcgen05LdStShape val) {
  switch (val) {
    case Tcgen05LdStShape::SHAPE_16X64B: return "shape_16x64b";
    case Tcgen05LdStShape::SHAPE_16X128B: return "shape_16x128b";
    case Tcgen05LdStShape::SHAPE_16X256B: return "shape_16x256b";
    case Tcgen05LdStShape::SHAPE_32X32B: return "shape_32x32b";
    case Tcgen05LdStShape::SHAPE_16X32BX2: return "shape_16x32bx2";
  }
  return "";
}

::std::optional<Tcgen05LdStShape> symbolizeTcgen05LdStShape(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Tcgen05LdStShape>>(str)
      .Case("shape_16x64b", Tcgen05LdStShape::SHAPE_16X64B)
      .Case("shape_16x128b", Tcgen05LdStShape::SHAPE_16X128B)
      .Case("shape_16x256b", Tcgen05LdStShape::SHAPE_16X256B)
      .Case("shape_32x32b", Tcgen05LdStShape::SHAPE_32X32B)
      .Case("shape_16x32bx2", Tcgen05LdStShape::SHAPE_16X32BX2)
      .Default(::std::nullopt);
}
::std::optional<Tcgen05LdStShape> symbolizeTcgen05LdStShape(uint32_t value) {
  switch (value) {
  case 0: return Tcgen05LdStShape::SHAPE_16X64B;
  case 1: return Tcgen05LdStShape::SHAPE_16X128B;
  case 2: return Tcgen05LdStShape::SHAPE_16X256B;
  case 3: return Tcgen05LdStShape::SHAPE_32X32B;
  case 4: return Tcgen05LdStShape::SHAPE_16X32BX2;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTcgen05MMABlockScale(Tcgen05MMABlockScale val) {
  switch (val) {
    case Tcgen05MMABlockScale::DEFAULT: return "default";
    case Tcgen05MMABlockScale::BLOCK16: return "block16";
    case Tcgen05MMABlockScale::BLOCK32: return "block32";
  }
  return "";
}

::std::optional<Tcgen05MMABlockScale> symbolizeTcgen05MMABlockScale(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Tcgen05MMABlockScale>>(str)
      .Case("default", Tcgen05MMABlockScale::DEFAULT)
      .Case("block16", Tcgen05MMABlockScale::BLOCK16)
      .Case("block32", Tcgen05MMABlockScale::BLOCK32)
      .Default(::std::nullopt);
}
::std::optional<Tcgen05MMABlockScale> symbolizeTcgen05MMABlockScale(uint32_t value) {
  switch (value) {
  case 0: return Tcgen05MMABlockScale::DEFAULT;
  case 1: return Tcgen05MMABlockScale::BLOCK16;
  case 2: return Tcgen05MMABlockScale::BLOCK32;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTcgen05MMACollectorBBuffer(Tcgen05MMACollectorBBuffer val) {
  switch (val) {
    case Tcgen05MMACollectorBBuffer::B0: return "b0";
    case Tcgen05MMACollectorBBuffer::B1: return "b1";
    case Tcgen05MMACollectorBBuffer::B2: return "b2";
    case Tcgen05MMACollectorBBuffer::B3: return "b3";
  }
  return "";
}

::std::optional<Tcgen05MMACollectorBBuffer> symbolizeTcgen05MMACollectorBBuffer(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Tcgen05MMACollectorBBuffer>>(str)
      .Case("b0", Tcgen05MMACollectorBBuffer::B0)
      .Case("b1", Tcgen05MMACollectorBBuffer::B1)
      .Case("b2", Tcgen05MMACollectorBBuffer::B2)
      .Case("b3", Tcgen05MMACollectorBBuffer::B3)
      .Default(::std::nullopt);
}
::std::optional<Tcgen05MMACollectorBBuffer> symbolizeTcgen05MMACollectorBBuffer(uint32_t value) {
  switch (value) {
  case 0: return Tcgen05MMACollectorBBuffer::B0;
  case 1: return Tcgen05MMACollectorBBuffer::B1;
  case 2: return Tcgen05MMACollectorBBuffer::B2;
  case 3: return Tcgen05MMACollectorBBuffer::B3;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTcgen05MMACollectorOp(Tcgen05MMACollectorOp val) {
  switch (val) {
    case Tcgen05MMACollectorOp::DISCARD: return "discard";
    case Tcgen05MMACollectorOp::LASTUSE: return "lastuse";
    case Tcgen05MMACollectorOp::FILL: return "fill";
    case Tcgen05MMACollectorOp::USE: return "use";
  }
  return "";
}

::std::optional<Tcgen05MMACollectorOp> symbolizeTcgen05MMACollectorOp(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Tcgen05MMACollectorOp>>(str)
      .Case("discard", Tcgen05MMACollectorOp::DISCARD)
      .Case("lastuse", Tcgen05MMACollectorOp::LASTUSE)
      .Case("fill", Tcgen05MMACollectorOp::FILL)
      .Case("use", Tcgen05MMACollectorOp::USE)
      .Default(::std::nullopt);
}
::std::optional<Tcgen05MMACollectorOp> symbolizeTcgen05MMACollectorOp(uint32_t value) {
  switch (value) {
  case 0: return Tcgen05MMACollectorOp::DISCARD;
  case 1: return Tcgen05MMACollectorOp::LASTUSE;
  case 2: return Tcgen05MMACollectorOp::FILL;
  case 3: return Tcgen05MMACollectorOp::USE;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTcgen05MMAKind(Tcgen05MMAKind val) {
  switch (val) {
    case Tcgen05MMAKind::F8F6F4: return "f8f6f4";
    case Tcgen05MMAKind::I8: return "i8";
    case Tcgen05MMAKind::F16: return "f16";
    case Tcgen05MMAKind::TF32: return "tf32";
  }
  return "";
}

::std::optional<Tcgen05MMAKind> symbolizeTcgen05MMAKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Tcgen05MMAKind>>(str)
      .Case("f8f6f4", Tcgen05MMAKind::F8F6F4)
      .Case("i8", Tcgen05MMAKind::I8)
      .Case("f16", Tcgen05MMAKind::F16)
      .Case("tf32", Tcgen05MMAKind::TF32)
      .Default(::std::nullopt);
}
::std::optional<Tcgen05MMAKind> symbolizeTcgen05MMAKind(uint32_t value) {
  switch (value) {
  case 2: return Tcgen05MMAKind::F8F6F4;
  case 3: return Tcgen05MMAKind::I8;
  case 0: return Tcgen05MMAKind::F16;
  case 1: return Tcgen05MMAKind::TF32;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTcgen05WaitKind(Tcgen05WaitKind val) {
  switch (val) {
    case Tcgen05WaitKind::LOAD: return "load";
    case Tcgen05WaitKind::STORE: return "store";
  }
  return "";
}

::std::optional<Tcgen05WaitKind> symbolizeTcgen05WaitKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Tcgen05WaitKind>>(str)
      .Case("load", Tcgen05WaitKind::LOAD)
      .Case("store", Tcgen05WaitKind::STORE)
      .Default(::std::nullopt);
}
::std::optional<Tcgen05WaitKind> symbolizeTcgen05WaitKind(uint32_t value) {
  switch (value) {
  case 0: return Tcgen05WaitKind::LOAD;
  case 1: return Tcgen05WaitKind::STORE;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTensormapElemtype(TensormapElemtype val) {
  switch (val) {
    case TensormapElemtype::U8: return "u8";
    case TensormapElemtype::U16: return "u16";
    case TensormapElemtype::U32: return "u32";
    case TensormapElemtype::S32: return "s32";
    case TensormapElemtype::U64: return "u64";
    case TensormapElemtype::S64: return "s64";
    case TensormapElemtype::F16: return "f16";
    case TensormapElemtype::F32: return "f32";
    case TensormapElemtype::F32_FTZ: return "f32.ftz";
    case TensormapElemtype::F64: return "f64";
    case TensormapElemtype::BF16: return "bf16";
    case TensormapElemtype::TF32: return "tf32";
    case TensormapElemtype::TF32_FTZ: return "tf32.ftz";
    case TensormapElemtype::B4x16: return "b4x16";
    case TensormapElemtype::B4x16P64: return "b4x16_p64";
    case TensormapElemtype::B6x16P32: return "b6x16_p32";
  }
  return "";
}

::std::optional<TensormapElemtype> symbolizeTensormapElemtype(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TensormapElemtype>>(str)
      .Case("u8", TensormapElemtype::U8)
      .Case("u16", TensormapElemtype::U16)
      .Case("u32", TensormapElemtype::U32)
      .Case("s32", TensormapElemtype::S32)
      .Case("u64", TensormapElemtype::U64)
      .Case("s64", TensormapElemtype::S64)
      .Case("f16", TensormapElemtype::F16)
      .Case("f32", TensormapElemtype::F32)
      .Case("f32.ftz", TensormapElemtype::F32_FTZ)
      .Case("f64", TensormapElemtype::F64)
      .Case("bf16", TensormapElemtype::BF16)
      .Case("tf32", TensormapElemtype::TF32)
      .Case("tf32.ftz", TensormapElemtype::TF32_FTZ)
      .Case("b4x16", TensormapElemtype::B4x16)
      .Case("b4x16_p64", TensormapElemtype::B4x16P64)
      .Case("b6x16_p32", TensormapElemtype::B6x16P32)
      .Default(::std::nullopt);
}
::std::optional<TensormapElemtype> symbolizeTensormapElemtype(uint32_t value) {
  switch (value) {
  case 0: return TensormapElemtype::U8;
  case 1: return TensormapElemtype::U16;
  case 2: return TensormapElemtype::U32;
  case 3: return TensormapElemtype::S32;
  case 4: return TensormapElemtype::U64;
  case 5: return TensormapElemtype::S64;
  case 6: return TensormapElemtype::F16;
  case 7: return TensormapElemtype::F32;
  case 8: return TensormapElemtype::F32_FTZ;
  case 9: return TensormapElemtype::F64;
  case 10: return TensormapElemtype::BF16;
  case 11: return TensormapElemtype::TF32;
  case 12: return TensormapElemtype::TF32_FTZ;
  case 13: return TensormapElemtype::B4x16;
  case 14: return TensormapElemtype::B4x16P64;
  case 15: return TensormapElemtype::B6x16P32;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTensormapField(TensormapField val) {
  switch (val) {
    case TensormapField::GLOBAL_ADDRESS: return "global_address";
    case TensormapField::RANK: return "rank";
    case TensormapField::BOX_DIM: return "box_dim";
    case TensormapField::GLOBAL_DIM: return "global_dim";
    case TensormapField::GLOBAL_STRIDE: return "global_stride";
    case TensormapField::ELEMENT_STRIDE: return "element_stride";
    case TensormapField::ELEMTYPE: return "elemtype";
    case TensormapField::INTERLEAVE_LAYOUT: return "interleave_layout";
    case TensormapField::SWIZZLE_MODE: return "swizzle_mode";
    case TensormapField::SWIZZLE_ATOMICITY: return "swizzle_atomicity";
    case TensormapField::FILL_MODE: return "fill_mode";
  }
  return "";
}

::std::optional<TensormapField> symbolizeTensormapField(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TensormapField>>(str)
      .Case("global_address", TensormapField::GLOBAL_ADDRESS)
      .Case("rank", TensormapField::RANK)
      .Case("box_dim", TensormapField::BOX_DIM)
      .Case("global_dim", TensormapField::GLOBAL_DIM)
      .Case("global_stride", TensormapField::GLOBAL_STRIDE)
      .Case("element_stride", TensormapField::ELEMENT_STRIDE)
      .Case("elemtype", TensormapField::ELEMTYPE)
      .Case("interleave_layout", TensormapField::INTERLEAVE_LAYOUT)
      .Case("swizzle_mode", TensormapField::SWIZZLE_MODE)
      .Case("swizzle_atomicity", TensormapField::SWIZZLE_ATOMICITY)
      .Case("fill_mode", TensormapField::FILL_MODE)
      .Default(::std::nullopt);
}
::std::optional<TensormapField> symbolizeTensormapField(uint32_t value) {
  switch (value) {
  case 0: return TensormapField::GLOBAL_ADDRESS;
  case 1: return TensormapField::RANK;
  case 2: return TensormapField::BOX_DIM;
  case 3: return TensormapField::GLOBAL_DIM;
  case 4: return TensormapField::GLOBAL_STRIDE;
  case 5: return TensormapField::ELEMENT_STRIDE;
  case 6: return TensormapField::ELEMTYPE;
  case 7: return TensormapField::INTERLEAVE_LAYOUT;
  case 8: return TensormapField::SWIZZLE_MODE;
  case 9: return TensormapField::SWIZZLE_ATOMICITY;
  case 10: return TensormapField::FILL_MODE;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTensormapFillMode(TensormapFillMode val) {
  switch (val) {
    case TensormapFillMode::ZERO: return "zero";
    case TensormapFillMode::OOB_NAN: return "oob_nan";
  }
  return "";
}

::std::optional<TensormapFillMode> symbolizeTensormapFillMode(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TensormapFillMode>>(str)
      .Case("zero", TensormapFillMode::ZERO)
      .Case("oob_nan", TensormapFillMode::OOB_NAN)
      .Default(::std::nullopt);
}
::std::optional<TensormapFillMode> symbolizeTensormapFillMode(uint32_t value) {
  switch (value) {
  case 0: return TensormapFillMode::ZERO;
  case 1: return TensormapFillMode::OOB_NAN;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTensormapInterleaveLayout(TensormapInterleaveLayout val) {
  switch (val) {
    case TensormapInterleaveLayout::NO_INTERLEAVE: return "no_interleave";
    case TensormapInterleaveLayout::B16: return "b16";
    case TensormapInterleaveLayout::B32: return "b32";
  }
  return "";
}

::std::optional<TensormapInterleaveLayout> symbolizeTensormapInterleaveLayout(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TensormapInterleaveLayout>>(str)
      .Case("no_interleave", TensormapInterleaveLayout::NO_INTERLEAVE)
      .Case("b16", TensormapInterleaveLayout::B16)
      .Case("b32", TensormapInterleaveLayout::B32)
      .Default(::std::nullopt);
}
::std::optional<TensormapInterleaveLayout> symbolizeTensormapInterleaveLayout(uint32_t value) {
  switch (value) {
  case 0: return TensormapInterleaveLayout::NO_INTERLEAVE;
  case 1: return TensormapInterleaveLayout::B16;
  case 2: return TensormapInterleaveLayout::B32;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTensormapSwizzleAtomicity(TensormapSwizzleAtomicity val) {
  switch (val) {
    case TensormapSwizzleAtomicity::B16: return "b16";
    case TensormapSwizzleAtomicity::B32: return "b32";
    case TensormapSwizzleAtomicity::B32_FLIP_8B: return "b32_flip_b8";
    case TensormapSwizzleAtomicity::B64: return "b64";
  }
  return "";
}

::std::optional<TensormapSwizzleAtomicity> symbolizeTensormapSwizzleAtomicity(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TensormapSwizzleAtomicity>>(str)
      .Case("b16", TensormapSwizzleAtomicity::B16)
      .Case("b32", TensormapSwizzleAtomicity::B32)
      .Case("b32_flip_b8", TensormapSwizzleAtomicity::B32_FLIP_8B)
      .Case("b64", TensormapSwizzleAtomicity::B64)
      .Default(::std::nullopt);
}
::std::optional<TensormapSwizzleAtomicity> symbolizeTensormapSwizzleAtomicity(uint32_t value) {
  switch (value) {
  case 0: return TensormapSwizzleAtomicity::B16;
  case 1: return TensormapSwizzleAtomicity::B32;
  case 2: return TensormapSwizzleAtomicity::B32_FLIP_8B;
  case 3: return TensormapSwizzleAtomicity::B64;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyTensormapSwizzleMode(TensormapSwizzleMode val) {
  switch (val) {
    case TensormapSwizzleMode::NO_SWIZZLING: return "no_swizzling";
    case TensormapSwizzleMode::B32: return "b32";
    case TensormapSwizzleMode::B64: return "b64";
    case TensormapSwizzleMode::B128: return "b128";
    case TensormapSwizzleMode::B96: return "b96";
  }
  return "";
}

::std::optional<TensormapSwizzleMode> symbolizeTensormapSwizzleMode(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TensormapSwizzleMode>>(str)
      .Case("no_swizzling", TensormapSwizzleMode::NO_SWIZZLING)
      .Case("b32", TensormapSwizzleMode::B32)
      .Case("b64", TensormapSwizzleMode::B64)
      .Case("b128", TensormapSwizzleMode::B128)
      .Case("b96", TensormapSwizzleMode::B96)
      .Default(::std::nullopt);
}
::std::optional<TensormapSwizzleMode> symbolizeTensormapSwizzleMode(uint32_t value) {
  switch (value) {
  case 0: return TensormapSwizzleMode::NO_SWIZZLING;
  case 1: return TensormapSwizzleMode::B32;
  case 2: return TensormapSwizzleMode::B64;
  case 3: return TensormapSwizzleMode::B128;
  case 4: return TensormapSwizzleMode::B96;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyVoteSyncKind(VoteSyncKind val) {
  switch (val) {
    case VoteSyncKind::any: return "any";
    case VoteSyncKind::all: return "all";
    case VoteSyncKind::ballot: return "ballot";
    case VoteSyncKind::uni: return "uni";
  }
  return "";
}

::std::optional<VoteSyncKind> symbolizeVoteSyncKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<VoteSyncKind>>(str)
      .Case("any", VoteSyncKind::any)
      .Case("all", VoteSyncKind::all)
      .Case("ballot", VoteSyncKind::ballot)
      .Case("uni", VoteSyncKind::uni)
      .Default(::std::nullopt);
}
::std::optional<VoteSyncKind> symbolizeVoteSyncKind(uint32_t value) {
  switch (value) {
  case 0: return VoteSyncKind::any;
  case 1: return VoteSyncKind::all;
  case 2: return VoteSyncKind::ballot;
  case 3: return VoteSyncKind::uni;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyWGMMAScaleIn(WGMMAScaleIn val) {
  switch (val) {
    case WGMMAScaleIn::one: return "one";
    case WGMMAScaleIn::neg: return "neg";
  }
  return "";
}

::std::optional<WGMMAScaleIn> symbolizeWGMMAScaleIn(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<WGMMAScaleIn>>(str)
      .Case("one", WGMMAScaleIn::one)
      .Case("neg", WGMMAScaleIn::neg)
      .Default(::std::nullopt);
}

} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyWGMMAScaleOut(WGMMAScaleOut val) {
  switch (val) {
    case WGMMAScaleOut::zero: return "zero";
    case WGMMAScaleOut::one: return "one";
  }
  return "";
}

::std::optional<WGMMAScaleOut> symbolizeWGMMAScaleOut(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<WGMMAScaleOut>>(str)
      .Case("zero", WGMMAScaleOut::zero)
      .Case("one", WGMMAScaleOut::one)
      .Default(::std::nullopt);
}
::std::optional<WGMMAScaleOut> symbolizeWGMMAScaleOut(uint32_t value) {
  switch (value) {
  case 0: return WGMMAScaleOut::zero;
  case 1: return WGMMAScaleOut::one;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
namespace mlir::NVVM {

::llvm::StringRef stringifyWGMMATypes(WGMMATypes val) {
  switch (val) {
    case WGMMATypes::f16: return "f16";
    case WGMMATypes::tf32: return "tf32";
    case WGMMATypes::u8: return "u8";
    case WGMMATypes::s8: return "s8";
    case WGMMATypes::b1: return "b1";
    case WGMMATypes::bf16: return "bf16";
    case WGMMATypes::e4m3: return "e4m3";
    case WGMMATypes::e5m2: return "e5m2";
    case WGMMATypes::f32: return "f32";
    case WGMMATypes::s32: return "s32";
  }
  return "";
}

::std::optional<WGMMATypes> symbolizeWGMMATypes(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<WGMMATypes>>(str)
      .Case("f16", WGMMATypes::f16)
      .Case("tf32", WGMMATypes::tf32)
      .Case("u8", WGMMATypes::u8)
      .Case("s8", WGMMATypes::s8)
      .Case("b1", WGMMATypes::b1)
      .Case("bf16", WGMMATypes::bf16)
      .Case("e4m3", WGMMATypes::e4m3)
      .Case("e5m2", WGMMATypes::e5m2)
      .Case("f32", WGMMATypes::f32)
      .Case("s32", WGMMATypes::s32)
      .Default(::std::nullopt);
}
::std::optional<WGMMATypes> symbolizeWGMMATypes(uint32_t value) {
  switch (value) {
  case 0: return WGMMATypes::f16;
  case 1: return WGMMATypes::tf32;
  case 2: return WGMMATypes::u8;
  case 3: return WGMMATypes::s8;
  case 4: return WGMMATypes::b1;
  case 5: return WGMMATypes::bf16;
  case 6: return WGMMATypes::e4m3;
  case 7: return WGMMATypes::e5m2;
  case 8: return WGMMATypes::f32;
  case 9: return WGMMATypes::s32;
  default: return ::std::nullopt;
  }
}


} // namespace mlir::NVVM
