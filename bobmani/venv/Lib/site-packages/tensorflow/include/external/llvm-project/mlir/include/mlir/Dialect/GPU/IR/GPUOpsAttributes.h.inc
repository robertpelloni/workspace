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
namespace mlir::gpu {

/// GPU address space
class AddressSpaceAttr;
/// GPU attribute for storing metadata related to a compiled kernel. The
///     attribute contains the name and arguments type of the kernel.
/// 
///     The attribute also contains optional parameters for storing the arguments
///     attributes as well as a dictionary for additional metadata, like occupancy
///     information or other function attributes.
/// 
///     Note: The `arg_attrs` parameter is expected to follow all the constraints
///     imposed by the `mlir::FunctionOpInterface` interface.
/// 
///     Examples:
///     ```mlir
///       #gpu.kernel_metadata<@kernel1, (i32) -> (), arg_attrs = [...],  metadata = {reg_count = 255, ...}>
///       #gpu.kernel_metadata<@kernel2, (i32, f64) -> ()>
///     ```
class KernelMetadataAttr;
/// GPU attribute representing a list of `#gpu.kernel_metadata` attributes. This
///     attribute supports searching kernels by name. All kernels in the table must
///     have an unique name.
/// 
///     Examples:
///     ```mlir
///       // Empty table.
///       #gpu.kernel_table<>
/// 
///       // Table with a single kernel.
///       #gpu.kernel_table<[#gpu.kernel_metadata<kernel0, () -> () >]>
/// 
///       // Table with multiple kernels.
///       #gpu.kernel_table<[
///         #gpu.kernel_metadata<"kernel0", (i32, f32) -> (), metadata = {sgpr_count = 255}>,
///         #gpu.kernel_metadata<"kernel1", (i32) -> ()>
///       ]>
///     ```
class KernelTableAttr;
/// A GPU object attribute glues together a GPU target, the object kind, a
///     binary string with the object, the object properties, and kernel metadata,
///     encapsulating how the object was generated and its properties with the
///     object itself.
/// 
///     There are four object formats:
///     1. `Offload`: represents generic objects not described by the other three
///     formats, and its meaning is target-dependent. For example, on the NVPTX and
///     AMDGPU targets, this format is associated with LLVM bitcode.
///     2. `Assembly`: represents GPU assembly code. For example, in the NVPTX
///     target, assembly is PTX code, which can be JITted at runtime.
///     3. `Binary`: represents executable code for a GPU single architecture. For
///     example, PTX code that was compiled for a specific compute capability. Note
///     that this format is likely to throw an error if there is an architecture
///     mismatch between the compiled and running architecture.
///     4. `Fatbin`: represents a GPU fat binary with executable code for multiple
///     architectures. This format is the default; thus, it gets elided inassembly
///     code.
/// 
///     Object properties are specified through the `properties` dictionary
///     attribute and can be used to define additional information.
/// 
///     Kernel metadata is specified through the `kernels` parameter, and can be
///     used to specify additional information on a kernel by kernel basis.
/// 
///     The target attribute must implement or promise the `TargetAttrInterface`
///     interface.
/// 
///     ```
///       #gpu.object<#rocdl.target, offload = "..."> // An offload object.
///       #gpu.object<#nvvm.target, properties = {O = 3 : i32}, assembly = "..."> // An assembly object with additional properties.
///       #gpu.object<#rocdl.target, bin = "..."> // A binary object.
///       #gpu.object<#nvvm.target, "..."> // A fatbin object.
///       #gpu.object<#nvvm.target, kernels = #gpu.kernel_table<...>, "..."> // An object with a kernel table.
///     ```
class ObjectAttr;
/// This GPU offloading handler selects a single GPU object for embedding. The
///     object is selected based on the `target` parameter, this parameter can be
///     either a number -i.e. selects the ith-target, or the target itself -i.e.
///     searches for the specified target in the object array.
/// 
///     The first object in a `gpu.binary` operation is selected if no target is
///     specified.
class SelectObjectAttr;
/// An attribute that allows defining thread block parallelism for GPU devices.
/// 
///     Thread blocks (aka workgroup) are grouped into a grid described by a 
///     3-dimensional rectangle.
///     This attribute indicates that thread block parallelism is desired.
///     It can be consumed by lowering to generate GPU code.
///     2 modes are supported: (1) 3D mapping mode and (2) linear mapping mode.
/// 
///     #### 3D mapping mode
/// 
///     The 3D block id is simply the 3D index of the block `(bidx, bidy, bidz)`. 
///     If required, predication occurs on a per-dimension basis. This allows 
///     specifying predication on a 3D sub-rectangle of the grid.
/// 
///     #### Linear mapping mode
/// 
///     The linear block id is obtained by linearizing the index of the block. 
///     If required, predication occurs on the linear id. This allows specifying
///     predication on a 1D subset of the (linearized) grid.
/// 
///     For instance, if the basis is denoted as (GX, GY, GZ) and the block id is
///     denoted by (bx, by, bz), the block id is:
///       `linear_id = bx + by * GX + bz * GX * GBY)`.
///     The linear block id is fixed for the duration of a GPU kernel.
///     
///     This linear id mapping attribute indicates a different linearization relation
///     is applied locally to a loop nest. 
///     
///     For instance, if the new basis is denoted as (LBD0, LBD1, LBD2, LBD3) the 
///     block id in the new basis is:
///       ```(linear_id mod LBD0 , 
///           (linear_id / LBD0) mod * LBD1, 
///           (linear_id / (LBD0 * LBD1)) mod LBD2, 
///           (linear_id / (LBD0 * LBD1 * LBD2)) mod LBD3)```.
///     This reinterpretation is only fixed for the duration of a loop nest.
class GPUBlockMappingAttr;
/// An attribute that allows defining warpgroup parallelism for GPU devices.
/// 
///     Threads of proper granularity (e.g. multiple of 
///     "kNumWarpsPerGroup * kWarpSize" on CUDA devices) can be grouped into
///     warpgroups described by a 3-dimensional rectangle. 
///     This attribute indicates that warpgroup parallelism is desired. 
///     It can be consumed by lowering to generate GPU code.
///     2 modes are supported: (1) 3D mapping mode and (2) linear mapping mode.
/// 
///     #### 3D mapping mode
/// 
///     The 3D warpgroup id is simply the adjusted 3D index of the thread 
///     `(tidx / (kNumWarpsPerGroup * kWarpSize), tidy, tidz)`.
///     If required, predication occurs on a per-dimension basis. This allows 
///     specifying predication on a 3D sub-rectangle of the warpgroups.
/// 
///     #### Linear mapping mode
/// 
///     The linear warpgroup id is obtained by linearizing the index of the warpgroup.
///     If required, predication occurs on the linear id. This allows specifying
///     predication on a 1D "kNumWarpsPerGroup * kWarpSize"-aligned subset of the 
///     (linearized) block.
/// 
///     For instance, if the basis is denoted as (BX, BY, BZ) and the thread id is
///     id is denoted by (tx, ty, tz), the linear warpgroup id is:
///       ```linear_id = (tx + ty * BX + tz * BX * BY) 
///                  / (kNumWarpsPerGroup * kWarpSize)```.
///     The linear warpgroup id is fixed for the duration of a GPU kernel.
///     
///     This linear id mapping attribute indicates a different linearization relation
///     is applied locally to a loop nest. 
///     
///     For instance, if the new basis is denoted as (LWGD0, LWGD1, LWGD2, LWGD3) the 
///     warpgroup id in the new basis is:
///       ```(linear_id mod LWGD0 , 
///           (linear_id / LWGD0) mod * LWGD1, 
///           (linear_id / (LWGD0 * LWGD1)) mod LWGD2, 
///           (linear_id / (LWGD0 * LWGD1 * LWGD2)) mod LWGD3)```.
///     This reinterpretation is only fixed for the duration of a loop nest.
class GPUWarpgroupMappingAttr;
/// An attribute that allows defining warp parallelism for GPU devices.
/// 
///     Threads of proper granularity (e.g. multiple of "warp size" on CUDA devices) 
///     can be grouped into warps described by a 3-dimensional rectangle. 
///     This attribute indicates that warp parallelism is desired.
///     It can be consumed by lowering to generate GPU code.
///     2 modes are supported: (1) 3D mapping mode and (2) linear mapping mode.
/// 
///     #### 3D mapping mode
/// 
///     The 3D warp id is simply the adjusted 3D index of the thread 
///     `(tidx / kWarpSize, tidy, tidz)`.
///     If required, predication occurs on a per-dimension basis. This allows 
///     specifying predication on a 3D sub-rectangle of the warpgroups.
/// 
///     #### Linear mapping mode
/// 
///     The linear warp id is obtained by linearizing the index of the warp.
///     If required, predication occurs on the linear id. This allows specifying
///     predication on a 1D "kWarpSize"-aligned subset of the (linearized) block.
/// 
///     For instance, if the basis is denoted as (BX, BY, BZ) and the thread id is
///     id is denoted by (tx, ty, tz), the linear warp id is:
///       `linear_id = (tx + ty * BX + tz * BX * BY) / kWarpSize`.
///     The linear warp id is fixed for the duration of a GPU kernel.
///     
///     This linear id mapping attribute indicates a different linearization relation
///     is applied locally to a loop nest. 
///     
///     For instance, if the new basis is denoted as (LWD0, LWD1, LWD2, LWD3) the 
///     warp id in the new basis is:
///       ```(linear_id mod LWD0 , 
///           (linear_id / LWD0) mod * LWD1, 
///           (linear_id / (LWD0 * LWD1)) mod LWD2, 
///           (linear_id / (LWD0 * LWD1 * LWD2)) mod LWD3)```.
///     This reinterpretation is only fixed for the duration of a loop nest.
class GPUWarpMappingAttr;
/// An attribute that allows defining thread parallelism for GPU devices.
/// 
///     Thread (aka work item) are grouped into a thread blocks described by a 
///     3-dimensional rectangle.
///     This attribute indicates that thread parallelism is desired.
///     It can be consumed by lowering to generate GPU.
/// 
///     #### 3D mapping mode
/// 
///     The 3D thread id is simply the 3D index of the thread `(tidx, tidy, tidz)`. 
///     If required, predication occurs on a per-dimension basis. This allows 
///     specifying predication on a 3D sub-rectangle of the block.
/// 
///     #### Linear mapping mode
/// 
///     The linear thread id is obtained by linearizing the index of the thread. 
///     If required, predication occurs on the linear id. This allows specifying
///     predication on a 1D subset of the (linearized) block.
/// 
///     For instance, if the basis is denoted as (BX, BY, BZ) and the thread id is
///     id is denoted by (tx, ty, tz), the linear thread id is:
///       ```linear_id = (tx + ty * BX + tz * BX * BY)```.
///     The linear thread id is fixed for the duration of a GPU kernel.
///     
///     This linear id mapping attribute indicates a different linearization relation
///     is applied locally to a loop nest. 
///     
///     For instance, if the new basis is denoted as (LTD0, LTD1, LTD2, LTD3) the 
///     thread id in the new basis is:
///       ```(linear_id mod LTD0 , 
///           (linear_id / LTD0) mod * LTD1, 
///           (linear_id / (LTD0 * LTD1)) mod LTD2, 
///           (linear_id / (LTD0 * LTD1 * LTD2)) mod LTD3)```.
///     This reinterpretation is only fixed for the duration of a loop nest.
class GPUThreadMappingAttr;
/// An attribute that allows defining lane parallelism for GPU devices.
/// 
///     It can be consumed by lowering to generate GPU.
/// 
///     #### 3D mapping mode
/// 
///     Unsupported
/// 
///     #### Linear mapping mode
/// 
///     The linear lane id is obtained by linearizing the index of the lane.
///     If required, predication occurs on the linear id. This allows specifying
///     predication on a 1D subset of the (linearized) lanes.
class GPULaneMappingAttr;
/// Attribute describing how to filter the processing units that a region is
///     mapped to. The masking is a bitfield that specifies for each processing
///     unit whether it is active or not.
class GPUMappingMaskAttr;
/// An attribute that allows defining memory hierarchy for GPU devices.
/// 
///     GPU Memory has three memory space, global, workgroup, and private. The global memory
///     is visible to all workitems and workgroups, the workgroup memory is only available for workitems
///     within a workgroup, and private memory is only visible to a single workitem. This attribute indicates
///     that using memory hiearchy is desired. It can be consumed by lowering to
///     move data to a specific address space in GPU code.
class GPUMemorySpaceMappingAttr;
class ParallelLoopDimMappingAttr;
/// a dimension, either 'x', 'y', or 'z'
class DimensionAttr;
/// built-in reduction operations supported by gpu.allreduce.
class AllReduceOperationAttr;
/// Indexing modes supported by gpu.shuffle.
class ShuffleModeAttr;
/// elementwise operation to apply to mma matrix
class MMAElementwiseOpAttr;
/// pruning strategy for 2:4 sparse matrix
class Prune2To4SpMatFlagAttr;
/// transpose mode of sparse matrix supported by sparse tensor ops
class TransposeModeAttr;
/// choose whether spgemm_work_estimation_or_compute does work estimation or compute
class SpGEMMWorkEstimationOrComputeKindAttr;
/// a lane to broadcast from
class BroadcastTypeAttr;
namespace detail {

struct AddressSpaceAttrStorage;

} // namespace detail
class AddressSpaceAttr : public ::mlir::Attribute::AttrBase<AddressSpaceAttr, ::mlir::Attribute, detail::AddressSpaceAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.address_space";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static AddressSpaceAttr get(::mlir::MLIRContext *context, ::mlir::gpu::AddressSpace value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"address_space"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::AddressSpace getValue() const;
};
namespace detail {

struct KernelMetadataAttrStorage;

} // namespace detail
class KernelMetadataAttr : public ::mlir::Attribute::AttrBase<KernelMetadataAttr, ::mlir::Attribute, detail::KernelMetadataAttrStorage> {
public:
  using Base::Base;
  /// Compare two kernels based on the name.
  bool operator<(const KernelMetadataAttr& other) const {
    return getName().getValue() < other.getName().getValue();
  }

  /// Returns the metadata attribute corresponding to `key` or `nullptr`
  /// if missing.
  Attribute getAttr(StringRef key) const {
    DictionaryAttr attrs = getMetadata();
    return attrs ? attrs.get(key) : nullptr;
  }
  template <typename ConcreteAttr>
  ConcreteAttr getAttr(StringRef key) const {
    return llvm::dyn_cast_or_null<ConcreteAttr>(getAttr(key));
  }
  Attribute getAttr(StringAttr key) const {
    DictionaryAttr attrs = getMetadata();
    return attrs ? attrs.get(key) : nullptr;
  }
  template <typename ConcreteAttr>
  ConcreteAttr getAttr(StringAttr key) const {
    return llvm::dyn_cast_or_null<ConcreteAttr>(getAttr(key));
  }

  /// Returns the attribute dictionary at position `index`.
  DictionaryAttr getArgAttrDict(unsigned index) {
    ArrayAttr argArray = getArgAttrs();
    return argArray ? llvm::cast<DictionaryAttr>(argArray[index]) : nullptr;
  }

  /// Return the specified attribute, if present, for the argument at 'index',
  /// null otherwise.
  Attribute getArgAttr(unsigned index, StringAttr name) {
    DictionaryAttr argDict = getArgAttrDict(index);
    return argDict ? argDict.get(name) : nullptr;
  }
  Attribute getArgAttr(unsigned index, StringRef name) {
    DictionaryAttr argDict = getArgAttrDict(index);
    return argDict ? argDict.get(name) : nullptr;
  }

  /// Returns a new KernelMetadataAttr that contains `attrs` in the metadata dictionary.
  KernelMetadataAttr appendMetadata(ArrayRef<NamedAttribute> attrs) const;
  static constexpr ::llvm::StringLiteral name = "gpu.kernel_metadata";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  using Base::getChecked;
  static KernelMetadataAttr get(::mlir::MLIRContext *context, StringAttr name, Type function_type, ArrayAttr arg_attrs, DictionaryAttr metadata);
  static KernelMetadataAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, StringAttr name, Type function_type, ArrayAttr arg_attrs, DictionaryAttr metadata);
  static KernelMetadataAttr get(StringAttr name, Type functionType, ArrayAttr argAttrs = nullptr, DictionaryAttr metadata = nullptr);
  static KernelMetadataAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr name, Type functionType, ArrayAttr argAttrs = nullptr, DictionaryAttr metadata = nullptr);
  static KernelMetadataAttr get(FunctionOpInterface kernel, DictionaryAttr metadata = nullptr);
  static KernelMetadataAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, FunctionOpInterface kernel, DictionaryAttr metadata = nullptr);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr name, Type function_type, ArrayAttr arg_attrs, DictionaryAttr metadata);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr name, Type function_type, ArrayAttr arg_attrs, DictionaryAttr metadata);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"kernel_metadata"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  StringAttr getName() const;
  Type getFunctionType() const;
  ArrayAttr getArgAttrs() const;
  DictionaryAttr getMetadata() const;
};
namespace detail {

struct KernelTableAttrStorage;

} // namespace detail
class KernelTableAttr : public ::mlir::Attribute::AttrBase<KernelTableAttr, ::mlir::Attribute, detail::KernelTableAttrStorage> {
public:
  using Base::Base;
  llvm::ArrayRef<KernelMetadataAttr>::iterator begin() const {
    return getKernelTable().begin();
  }
  llvm::ArrayRef<KernelMetadataAttr>::iterator end() const {
    return getKernelTable().end();
  }
  size_t size() const {
    return getKernelTable().size();
  }
  bool empty() const {
    return getKernelTable().empty();
  }

  /// Returns the kernel with name `key` or `nullptr` if not present.
  KernelMetadataAttr lookup(StringRef key) const;
  KernelMetadataAttr lookup(StringAttr key) const;
  static constexpr ::llvm::StringLiteral name = "gpu.kernel_table";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  using Base::getChecked;
  static KernelTableAttr get(::mlir::MLIRContext *context, ArrayRef<KernelMetadataAttr> kernels, bool isSorted = false);
  static KernelTableAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ArrayRef<KernelMetadataAttr> kernels, bool isSorted = false);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<KernelMetadataAttr> kernel_table);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<KernelMetadataAttr> kernel_table);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"kernel_table"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<KernelMetadataAttr> getKernelTable() const;
};
namespace detail {

struct ObjectAttrStorage;

} // namespace detail
class ObjectAttr : public ::mlir::Attribute::AttrBase<ObjectAttr, ::mlir::Attribute, detail::ObjectAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.object";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  using Base::getChecked;
  static ObjectAttr get(::mlir::MLIRContext *context, Attribute target, CompilationTarget format, StringAttr object, DictionaryAttr properties, KernelTableAttr kernels);
  static ObjectAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, Attribute target, CompilationTarget format, StringAttr object, DictionaryAttr properties, KernelTableAttr kernels);
  static ObjectAttr get(Attribute target, CompilationTarget format, StringAttr object, DictionaryAttr properties = nullptr, KernelTableAttr kernels = nullptr);
  static ObjectAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Attribute target, CompilationTarget format, StringAttr object, DictionaryAttr properties = nullptr, KernelTableAttr kernels = nullptr);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Attribute target, CompilationTarget format, StringAttr object, DictionaryAttr properties, KernelTableAttr kernels);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Attribute target, CompilationTarget format, StringAttr object, DictionaryAttr properties, KernelTableAttr kernels);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"object"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  Attribute getTarget() const;
  CompilationTarget getFormat() const;
  StringAttr getObject() const;
  DictionaryAttr getProperties() const;
  KernelTableAttr getKernels() const;
};
namespace detail {

struct SelectObjectAttrStorage;

} // namespace detail
class SelectObjectAttr : public ::mlir::Attribute::AttrBase<SelectObjectAttr, ::mlir::Attribute, detail::SelectObjectAttrStorage, ::mlir::gpu::OffloadingTranslationAttrTrait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.select_object";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  using Base::getChecked;
  static SelectObjectAttr get(::mlir::MLIRContext *context, Attribute target);
  static SelectObjectAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, Attribute target);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Attribute target);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Attribute target);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"select_object"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  Attribute getTarget() const;
};
namespace detail {

struct GPUBlockMappingAttrStorage;

} // namespace detail
class GPUBlockMappingAttr : public ::mlir::Attribute::AttrBase<GPUBlockMappingAttr, ::mlir::Attribute, detail::GPUBlockMappingAttrStorage, ::mlir::DeviceMappingAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.block";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static GPUBlockMappingAttr get(::mlir::MLIRContext *context, ::mlir::gpu::MappingId block);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"block"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::MappingId getBlock() const;
  int64_t getMappingId() const;
  bool isLinearMapping() const;
  int64_t getRelativeIndex() const;
};
namespace detail {

struct GPUWarpgroupMappingAttrStorage;

} // namespace detail
class GPUWarpgroupMappingAttr : public ::mlir::Attribute::AttrBase<GPUWarpgroupMappingAttr, ::mlir::Attribute, detail::GPUWarpgroupMappingAttrStorage, ::mlir::DeviceMappingAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.warpgroup";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static GPUWarpgroupMappingAttr get(::mlir::MLIRContext *context, ::mlir::gpu::MappingId warpgroup);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"warpgroup"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::MappingId getWarpgroup() const;
  int64_t getMappingId() const;
  bool isLinearMapping() const;
  int64_t getRelativeIndex() const;
};
namespace detail {

struct GPUWarpMappingAttrStorage;

} // namespace detail
class GPUWarpMappingAttr : public ::mlir::Attribute::AttrBase<GPUWarpMappingAttr, ::mlir::Attribute, detail::GPUWarpMappingAttrStorage, ::mlir::DeviceMappingAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.warp";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static GPUWarpMappingAttr get(::mlir::MLIRContext *context, ::mlir::gpu::MappingId warp);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"warp"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::MappingId getWarp() const;
  int64_t getMappingId() const;
  bool isLinearMapping() const;
  int64_t getRelativeIndex() const;
};
namespace detail {

struct GPUThreadMappingAttrStorage;

} // namespace detail
class GPUThreadMappingAttr : public ::mlir::Attribute::AttrBase<GPUThreadMappingAttr, ::mlir::Attribute, detail::GPUThreadMappingAttrStorage, ::mlir::DeviceMappingAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.thread";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static GPUThreadMappingAttr get(::mlir::MLIRContext *context, ::mlir::gpu::MappingId thread);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"thread"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::MappingId getThread() const;
  int64_t getMappingId() const;
  bool isLinearMapping() const;
  int64_t getRelativeIndex() const;
};
namespace detail {

struct GPULaneMappingAttrStorage;

} // namespace detail
class GPULaneMappingAttr : public ::mlir::Attribute::AttrBase<GPULaneMappingAttr, ::mlir::Attribute, detail::GPULaneMappingAttrStorage, ::mlir::DeviceMappingAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.lane";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static GPULaneMappingAttr get(::mlir::MLIRContext *context, ::mlir::gpu::MappingId lane);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"lane"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::MappingId getLane() const;
  int64_t getMappingId() const;
  bool isLinearMapping() const;
  int64_t getRelativeIndex() const;
};
namespace detail {

struct GPUMappingMaskAttrStorage;

} // namespace detail
class GPUMappingMaskAttr : public ::mlir::Attribute::AttrBase<GPUMappingMaskAttr, ::mlir::Attribute, detail::GPUMappingMaskAttrStorage, ::mlir::DeviceMaskingAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.mask";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static GPUMappingMaskAttr get(::mlir::MLIRContext *context, uint64_t mask);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mask"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  uint64_t getMask() const;
  Value createLogicalLinearMappingId(OpBuilder&builder, Value physicalLinearMappingId) const;
  Value createIsActiveIdPredicate(OpBuilder&builder, Value physicalLinearMappingId) const;
  int64_t getMaxNumPhysicalIds() const;
};
namespace detail {

struct GPUMemorySpaceMappingAttrStorage;

} // namespace detail
class GPUMemorySpaceMappingAttr : public ::mlir::Attribute::AttrBase<GPUMemorySpaceMappingAttr, ::mlir::Attribute, detail::GPUMemorySpaceMappingAttrStorage, ::mlir::DeviceMappingAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.memory_space";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static GPUMemorySpaceMappingAttr get(::mlir::MLIRContext *context, ::mlir::gpu::AddressSpace address_space);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"memory_space"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::AddressSpace getAddressSpace() const;
  int64_t getMappingId() const;
  bool isLinearMapping() const;
  int64_t getRelativeIndex() const;
};
namespace detail {

struct ParallelLoopDimMappingAttrStorage;

} // namespace detail
class ParallelLoopDimMappingAttr : public ::mlir::Attribute::AttrBase<ParallelLoopDimMappingAttr, ::mlir::Attribute, detail::ParallelLoopDimMappingAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.loop_dim_map";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static ParallelLoopDimMappingAttr get(::mlir::MLIRContext *context, ::mlir::gpu::Processor processor, AffineMap map, AffineMap bound);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"loop_dim_map"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::Processor getProcessor() const;
  AffineMap getMap() const;
  AffineMap getBound() const;
};
namespace detail {

struct DimensionAttrStorage;

} // namespace detail
class DimensionAttr : public ::mlir::Attribute::AttrBase<DimensionAttr, ::mlir::Attribute, detail::DimensionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.dim";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static DimensionAttr get(::mlir::MLIRContext *context, ::mlir::gpu::Dimension value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dim"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::Dimension getValue() const;
};
namespace detail {

struct AllReduceOperationAttrStorage;

} // namespace detail
class AllReduceOperationAttr : public ::mlir::Attribute::AttrBase<AllReduceOperationAttr, ::mlir::Attribute, detail::AllReduceOperationAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.all_reduce_op";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static AllReduceOperationAttr get(::mlir::MLIRContext *context, ::mlir::gpu::AllReduceOperation value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"all_reduce_op"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::AllReduceOperation getValue() const;
};
namespace detail {

struct ShuffleModeAttrStorage;

} // namespace detail
class ShuffleModeAttr : public ::mlir::Attribute::AttrBase<ShuffleModeAttr, ::mlir::Attribute, detail::ShuffleModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.shuffle_mode";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static ShuffleModeAttr get(::mlir::MLIRContext *context, ::mlir::gpu::ShuffleMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"shuffle_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::ShuffleMode getValue() const;
};
namespace detail {

struct MMAElementwiseOpAttrStorage;

} // namespace detail
class MMAElementwiseOpAttr : public ::mlir::Attribute::AttrBase<MMAElementwiseOpAttr, ::mlir::Attribute, detail::MMAElementwiseOpAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.mma_element_wise";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static MMAElementwiseOpAttr get(::mlir::MLIRContext *context, ::mlir::gpu::MMAElementwiseOp value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mma_element_wise"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::MMAElementwiseOp getValue() const;
};
namespace detail {

struct Prune2To4SpMatFlagAttrStorage;

} // namespace detail
class Prune2To4SpMatFlagAttr : public ::mlir::Attribute::AttrBase<Prune2To4SpMatFlagAttr, ::mlir::Attribute, detail::Prune2To4SpMatFlagAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.prune_2to4_spmat_flag";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static Prune2To4SpMatFlagAttr get(::mlir::MLIRContext *context, ::mlir::gpu::Prune2To4SpMatFlag value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"prune_2to4_spmat_flag"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::Prune2To4SpMatFlag getValue() const;
};
namespace detail {

struct TransposeModeAttrStorage;

} // namespace detail
class TransposeModeAttr : public ::mlir::Attribute::AttrBase<TransposeModeAttr, ::mlir::Attribute, detail::TransposeModeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.mat_transpose_mode";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static TransposeModeAttr get(::mlir::MLIRContext *context, ::mlir::gpu::TransposeMode value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mat_transpose_mode"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::TransposeMode getValue() const;
};
namespace detail {

struct SpGEMMWorkEstimationOrComputeKindAttrStorage;

} // namespace detail
class SpGEMMWorkEstimationOrComputeKindAttr : public ::mlir::Attribute::AttrBase<SpGEMMWorkEstimationOrComputeKindAttr, ::mlir::Attribute, detail::SpGEMMWorkEstimationOrComputeKindAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.spgemm_work_estimation_or_compute_kind";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static SpGEMMWorkEstimationOrComputeKindAttr get(::mlir::MLIRContext *context, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"spgemm_work_estimation_or_compute_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::SpGEMMWorkEstimationOrComputeKind getValue() const;
};
namespace detail {

struct BroadcastTypeAttrStorage;

} // namespace detail
class BroadcastTypeAttr : public ::mlir::Attribute::AttrBase<BroadcastTypeAttr, ::mlir::Attribute, detail::BroadcastTypeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "gpu.broadcast";
  static constexpr ::llvm::StringLiteral dialectName = "gpu";
  static BroadcastTypeAttr get(::mlir::MLIRContext *context, ::mlir::gpu::BroadcastType value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"broadcast"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::gpu::BroadcastType getValue() const;
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::AddressSpaceAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::KernelMetadataAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::KernelTableAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::ObjectAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SelectObjectAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GPUBlockMappingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GPUWarpgroupMappingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GPUWarpMappingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GPUThreadMappingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GPULaneMappingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GPUMappingMaskAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GPUMemorySpaceMappingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::ParallelLoopDimMappingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::DimensionAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::AllReduceOperationAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::ShuffleModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::MMAElementwiseOpAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::Prune2To4SpMatFlagAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::TransposeModeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::BroadcastTypeAttr)

#endif // GET_ATTRDEF_CLASSES

