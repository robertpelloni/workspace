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
namespace mlir::sdy {

/// A list of axes that a ManualComputationOp is manual on
class ManualAxesAttr;
/// Named axis in a mesh
class MeshAxisAttr;
/// Mesh of axes and a list of devices
/// A mesh is a list of axes and an optional list of device IDs specifying the
///     device ordering.
/// 
///     If the list of axes is empty
///       - If the `device_ids` is not provided, it is an empty mesh.
///       - If the `device_ids` is provided, it must be a single non-negative
///         integer, we call it a **maximal-sharding mesh**.
/// 
///     If the list of axes is provided
///       - If a device ID list is specified, the product of the axis sizes should
///         match the number of devices.
///       - If a device ID list is not specified, the implicit device ID list is
///         iota(product(axes)). For simplicity, we also disallow specifying a
///         device ID list that is the same as iota(product(axes)); in this case, a
///         device ID list shouldn't be specified.
///       - It is not a maximal-sharding mesh even if the total size of axes is 1.
/// 
///     Here are some examples of meshes:
/// 
///     - An empty mesh represents a placeholder mesh that can be replaced during
///       propagation: <[]>
///     - A mesh without axes list and a single non-negative device ID, which is a
///       maximal-sharding mesh: <[], device_ids=[3]>
///     - A mesh with two axes and implicit device IDs iota(6): <["a"=2, "b"=3]>
///     - A mesh with two axes and explicit device IDs specifying the device
///       ordering: <["a"=3, "b"=2], device_ids=[0, 2, 4, 1, 3, 5]>
/// 
///     **Constraints:**
///     - Elements in `device_ids` should be non-negative.
///     - If `axes` is empty, the size of `device_ids` can be 0 (empty mesh) or 1
///       (maximal-sharding mesh).
///     - If `axes` is not empty,
///         - Elements in `axes` must not have duplicate names.
///         - If `device_ids` is specified, the original `device_ids` is not
///           `iota(product(axis_sizes))` and the sorted `device_ids` is
///           `iota(product(axis_sizes))`.
class MeshAttr;
/// Info about how this sub-axis is derived from the full axis
/// When splitting a full axis into n sub-axes, the axis is reshaped into
///     [k_1,...,k_n], and the ith sub-axis can be expressed by the product of all
///     axis sizes to its left `m=prod(k_1,...,k_(i-1))` (aka pre-size) and size
///     k_i. Therefore, the sub-axis-info attribute holds those two numbers and is
///     denoted as follows: `(m)k` for pre-size m and size k.
/// 
///     **Constraints:**
///     - `pre-size` is at least 1.
///     - `size` is greater than 1.
///     - `pre-size` must divide the size of the full axis, i.e., both `pre-size`
///       and `size` divide the size of the full axis, and the sub-axis doesn't go
///       beyond the full axis.
///     - The size of the sub-axis isn't equal to the size of the corresponding full
///       axis, in which case the full axis should be used instead.
class SubAxisInfoAttr;
/// Reference to either a full axis or a split sub-axis
/// **Constraints:**
///     - `name` must be present in the bound `MeshAttr`.
///     - If `sub_axis_info` is present, it must satisfy the constraints of
///       `SubAxisInfoAttr`.
class AxisRefAttr;
/// Dimension sharding
/// List of axis names to shard a tensor dimension on from major to minor, a
///     boolean indicating whether the dimension can be further sharded, and an
///     optional integer denoting the priority of this dimension sharding, which
///     will respected during sharding propagation. Priorities originate from user
///     sharding annotations and a lower value denotes a higher priority. The
///     highest priority is assumed when the priority is missing in the annotation.
/// 
///     **Constraints:**
///     - Elements in `axes` must satisfy the constraints listed in `AxisRefListAttr`.
///     - If a dimension sharding has a priority:
///       * The priority is greater than or equal to 0.
///       * The dimension has at least one axis if it is closed.
class DimensionShardingAttr;
/// Tensor sharding
/// A tensor sharding is bound to a specific mesh, and can only reference axis
///     names from that mesh. The dimension shardings tell us for each dimension of
///     the tensor, along which axes (or sub-axes) it is sharded from major to
///     minor. All other axes that don’t shard a dimension are either implicitly or
///     explicitly (if they appear in the list of replicated axes) replicated.
/// 
///     Note that no sharding attribute on a tensor is equivalent to a fully open
///     tensor sharding.
/// 
///     The mesh this sharding is bound to can either be specified by a symbol
///     name, referencing a corresponding `MeshOp` symbol, or an inlined `MeshAttr`.
/// 
///     A sharding can have unreduced axes (specified by `unreduced_axes`), meaning
///     the tensor is unreduced along these axes. For example, if the contracting
///     dimension of a matmul is sharded along axis `x` in both the lhs and rhs, the
///     result is unreduced along `x`. Applying an all-reduce on the tensor along
///     the unreduced axes will make the tensor replicated along those axes.
///     However, a tensor with unreduced axes doesn't have to be all-reduced
///     immediately, it can remain unreduced when passed to linear operations like
///     `stablehlo.add` (as long as both lhs and rhs are unreduced) and all-reduced
///     afterwards. We assume the reduction type is sum, other reductions may be
///     supported in the future.
/// 
///     **Constraints:**
///     - Elements in `dim_shardings` must satisfy the constraints listed in
///       `DimensionShardingAttr`.
///     - Elements in `replicated_axes` must satisfy the constraints listed in
///       `AxisRefListAttr`.
///     - Elements in `unreduced_axes` must satisfy the constraints listed in
///       `AxisRefListAttr`.
///     - If the corresponding tensor type isn't a `ShapedType`, the sharding must
///       have rank 0 and no replicated axes.
///     - If it is a `ShapedType`, then:
///       - The tensor should have a rank.
///       - The number of dimension shardings is equal to the rank of the tensor.
///       - Dimensions of size 0 aren't sharded.
///     - There are no duplicate axis-refs or sub-axes that overlap with one another
///       across `dim_shardings`, `replicated_axes`, and `unreduced_axes`.
///     - Items in `replicated_axes` and `unreduced_axes` are ordered w.r.t.
///       `mesh_or_ref` (see `AxisRefAttr::getMeshComparator`).
class TensorShardingAttr;
/// Tensor sharding per operand/result of an op
/// A list of `TensorShardingAttr`s, one for each operand/result of an op.
/// 
///     **Constraints:**
///     - Elements in `shardings` must satisfy the constraints of `TensorShardingAttr`.
class TensorShardingPerValueAttr;
/// List of factor indices for a dimension
/// An empty list indicates that this is a null mapping (this is parsed/printed
///     with `*`), i.e. the dimension isn't mapped to any factors.
/// 
///     **Constraints:**
///     - There is at least one factor index.
///     - Factor indices must be in range [0, `$factor_sizes`).
///     - If there are multiple factors, none of them can have size 1.
///     - No duplicate factor indices.
class DimMappingAttr;
/// Factor mappings for each dimension of a tensor.
/// **Constraints:**
///       - Elements in `dim_mappings` must satisfy the constraints in `DimMappingAttr`.
///       - No duplicate factors indices across dimensions.
class TensorMappingAttr;
/// Specifies how an operation can be partitioned.
/// A sharding rule specifies how an operation can be partitioned according to
///     various properties on the op - any attributes, the shape of operands,
///     the shape of the results, etc. For example:
/// 
///     ```
///     %0 = stablehlo.add %arg0, %arg1 {
///         sdy.sharding_rule = #sdy.op_sharding_rule<
///             ([i, j],[i, j])->([i, j])
///             {i=8, j=8}>
///     } : tensor<8x8xf32>
///     ```
/// 
///     ```
///     %1 = stablehlo.dot_general %arg2, %arg3, contracting_dims = [1] x [0] {
///       sdy.sharding_rule = #sdy.op_sharding_rule<
///           ([i, k],[k, j])->([i, j])
///           {i=8, j=16, k=8}>
///     }: (tensor<8x8xf32>, tensor<8x16xf32>) -> tensor<8x16xf32>
///     ```
/// 
///     Note that we allow factors with size 1 even though they cannot be sharded,
///     this is mainly for completeness as many ops such as pointwise ops have size
///     one dimensions that correspond across operands and results.
/// 
///     **Factor types:**
///     - `reduction_factors` contains the indices of factors requiring reduction,
///       such as the contracting dimensions in a dot operation. These factors can
///       be in operands but not in results.
///     - `need_replication_factors` contains the indices of factors requiring full
///       replication, such as the sorted dimension in a sort operation.
///     - `permutation_factors` contains the indices of factors requiring
///       collective-permute if they are sharded, such as the padding dimensions in
///       a pad operation.
///     - All other factors are considered as pass-through factors, i.e., factors
///       that don't require any communication if sharded in the same way across all
///       tensors that are mapped to them.
/// 
///     `blocked_propagation_factors` contains the factors along which shardings are
///     not allowed to be propagated. It is orthogonal to the factor types. Namely,
///     a blocked-propagation factor can be any of the factor types.
/// 
///     `is_custom_rule` describes whether this is a rule defined by a user. Users
///     can define sharding rules for their custom calls or overwrite the
///     pre-defined sharding rules for the standard operations. A custom rule is
///     always preserved/never removed.
/// 
///     **Constraints:**
///     - Number of operand/result mappings must match the number of
///       operands/results of the op.
///     - There is at least one mapping (can't have a rule for an op with no
///       operands/results).
///     - Rank of each `TensorMappingAttr` matches the rank of the corresponding
///       tensor type.
///     - For each group of factors (`reduction_factors`,
///       `need_replication_factors`, `permutation_factors`):
///       * Elements must be in range [0, `$factor_sizes`].
///       * No duplicate factor indices within each group and across groups.
class OpShardingRuleAttr;
/// List of axis refs
/// **Constraints:**
///     - Elements in `value` must satisfy the constraints of `AxisRefAttr`.
///     - There are no duplicate axis-refs or sub-axes that overlap with one another.
///     - No two adjacent axis-refs are consecutive sub-axes of that same full axis,
///       i.e., they can be merged into one sub-axis or the full axis.
class AxisRefListAttr;
/// List of axis ref lists
class ListOfAxisRefListsAttr;
/// all-to-all parameter
/// A tuple containing the axes and source/target dimensions to perform
///     all-to-all on.
class AllToAllParamAttr;
/// List of all-to-all parameters
class AllToAllParamListAttr;
/// Reference to a particular index of a value edge of type `type`.
class EdgeValueRefAttr;
/// Propagation edge flow details for a specific axis and source.
/// Maps a source value reference to a list of target value references along a particular axis.
class AxisToPropagationDetailsAttr;
/// Per-step propagation metadata.
/// Propagation details for all axes for a single propagation step.
class PropagationOneStepAttr;
/// Propagation edge metadata for all propagation steps.
/// A list of per-axis propagation details for a value, grouped by step index.
class PropagationEdgesAttr;
namespace detail {

struct ManualAxesAttrStorage;

} // namespace detail
class ManualAxesAttr : public ::mlir::Attribute::AttrBase<ManualAxesAttr, ::mlir::Attribute, detail::ManualAxesAttrStorage> {
public:
  using Base::Base;
  auto begin() const { return getValue().begin(); }
  auto end() const { return getValue().end(); }
  bool empty() const { return getValue().empty(); }
  size_t size() const { return getValue().size(); }
  auto &front() const { return getValue().front(); }
  auto &back() const { return getValue().back(); }
  auto &operator[](size_t index) { return getValue()[index]; }
  operator ::llvm::ArrayRef<StringAttr>() const { return getValue(); }
  static constexpr ::llvm::StringLiteral name = "sdy.manual_axes";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static ManualAxesAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<StringAttr> value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"manual_axes"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<StringAttr> getValue() const;
};
namespace detail {

struct MeshAxisAttrStorage;

} // namespace detail
class MeshAxisAttr : public ::mlir::Attribute::AttrBase<MeshAxisAttr, ::mlir::Attribute, detail::MeshAxisAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sdy.mesh_axis";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  using Base::getChecked;
  static MeshAxisAttr get(::mlir::MLIRContext *context, ::llvm::StringRef name, int64_t size);
  static MeshAxisAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::StringRef name, int64_t size);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::StringRef name, int64_t size);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::StringRef name, int64_t size);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mesh_axis"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::StringRef getName() const;
  int64_t getSize() const;
};
namespace detail {

struct MeshAttrStorage;

} // namespace detail
class MeshAttr : public ::mlir::Attribute::AttrBase<MeshAttr, ::mlir::Attribute, detail::MeshAttrStorage> {
public:
  using Base::Base;
  // Returns true if this mesh has no axes or device ids.
  bool empty() const;

  // Returns true if this mesh has an axis with the given `axisName`.
  bool hasAxis(StringRef axisName) const;

  // Returns the size of the axis with the given `axisName`.
  //
  // Assumes the axis is present in the mesh.
  int64_t getAxisSize(StringRef axisName) const;

  // Returns the total size of the mesh across all axes, as in the total
  // number of devices.
  int64_t getTotalSize() const;

  // Returns whether this mesh is a maximal-sharding mesh
  //
  // A maximal-sharding mesh is a mesh with an empty axis list and a single
  // device ID.
  bool isMaximal() const;

  // Returns whether this mesh is a maximal-sharding mesh with `deviceId`.
  //
  // A maximal-sharding mesh is a mesh with an empty axis list and a single
  // device ID.
  bool isMaximal(int64_t deviceId) const;

  // Creates a maximal mesh with the given `deviceId`.
  static MeshAttr getMaximal(MLIRContext* ctx, int64_t deviceId);

  // If this mesh is a maximal-sharding mesh, returns the maximal device ID,
  // otherwise, returns std::nullopt.
  //
  // A maximal-sharding mesh is a mesh with an empty axis list and a single
  // device ID.
  std::optional<int64_t> getMaximalDeviceId() const;

  // Returns a comparator that orders axis names w.r.t. their order in this
  // mesh.
  std::function<bool(StringRef lhs, StringRef rhs)> getAxisNameComparator()
  const;

  // Returns a map from axis name to axis size.
  llvm::SmallDenseMap<StringRef, int64_t> getAxisNameToSize() const;

  // Returns true if this mesh is equal to `other` ignoring the device ids
  // depending on `ignoreDeviceIds`.
  bool equals(MeshAttr other, bool ignoreDeviceIds = false) const;
  static constexpr ::llvm::StringLiteral name = "sdy.mesh";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  using Base::getChecked;
  static MeshAttr get(::mlir::MLIRContext *context, mlir::ArrayRef<MeshAxisAttr> axes, mlir::ArrayRef<int64_t> device_ids);
  static MeshAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, mlir::ArrayRef<MeshAxisAttr> axes, mlir::ArrayRef<int64_t> device_ids);
  static MeshAttr get(::mlir::MLIRContext *context, mlir::ArrayRef<MeshAxisAttr> axes);
  static MeshAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, mlir::ArrayRef<MeshAxisAttr> axes);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<MeshAxisAttr> axes, ::llvm::ArrayRef<int64_t> device_ids);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<MeshAxisAttr> axes, ::llvm::ArrayRef<int64_t> device_ids);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mesh"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<MeshAxisAttr> getAxes() const;
  ::llvm::ArrayRef<int64_t> getDeviceIds() const;
};
namespace detail {

struct SubAxisInfoAttrStorage;

} // namespace detail
class SubAxisInfoAttr : public ::mlir::Attribute::AttrBase<SubAxisInfoAttr, ::mlir::Attribute, detail::SubAxisInfoAttrStorage> {
public:
  using Base::Base;
  // Sub-axes of the same full axis are ordered by their pre-size, and then by
  // their size (overlap is only possible for two sub-axes that shard
  // different tensors), e.g. [1(2), 4(2), 4(4)].
  bool operator<(const SubAxisInfoAttr &rhs) const;

  // Returns the pre-size of the next sub-axis (that is minor to this
  // sub-axis), or the size of the full axis if this is the minor-most
  // sub-axis.
  //
  // The next pre-size is equal to `pre-size * size` of this sub-axis.
  int64_t getNextPreSize() const {
    return getPreSize() * getSize();
  }
  static constexpr ::llvm::StringLiteral name = "sdy.sub_axis_info";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static SubAxisInfoAttr get(::mlir::MLIRContext *context, int64_t pre_size, int64_t size);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sub_axis_info"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  int64_t getPreSize() const;
  int64_t getSize() const;
};
namespace detail {

struct AxisRefAttrStorage;

} // namespace detail
class AxisRefAttr : public ::mlir::Attribute::AttrBase<AxisRefAttr, ::mlir::Attribute, detail::AxisRefAttrStorage> {
public:
  using Base::Base;
  // Returns a comparator that orders axis names w.r.t. their order in the
  // given `mesh`.
  static std::function<bool(AxisRefAttr lhs, AxisRefAttr rhs)>
  getMeshComparator(MeshAttr mesh);

  // Returns a comparator that order axis names lexicographically.
  // 1. Compare the axis names lexicographically.
  // 2. For a full-axis and sub-axis with the same name "a" -
  //    "a":(1)x < "a" < "a":(y)z, where y > 1.
  // 3. Sort two sub-axes based on comparator of SubAxisInfoAttr.
  bool operator<(const AxisRefAttr &rhs) const;

  std::string toString() const;

  // Returns the size of this axis or sub-axis.
  int64_t getSize(MeshAttr mesh) const;

  // If this is a sub-axis, returns its pre-size, otherwise returns 1.
  int64_t getSubAxisPreSize() const;

  // If this is a sub-axis, returns its next pre-size (see
  // SubAxisInfoAttr::getNextPreSize), otherwise returns its full size.
  int64_t getNextPreSizeOrFullSize(MeshAttr) const;

  // TODO(b/391138813): consider checking `canCoexist` in `contains`,
  // `prefixOf`, and `suffixOf`, instead of in using methods.

  // Returns whether this axis or sub-axis contains `other`, i.e., this axis
  // or sub-axis is equal to `other` or can be split into multiple sub-axes
  // such that one of them is `other`.
  //
  // For example:
  //  "a", "a":(2)2       -> true
  //  "a":(1)8, "a":(1)4  -> true
  //  "a":(2)16, "a":(4)2 -> true
  //  "a", "a"            -> true
  //  "a":(2)2, "a":(2)2  -> true
  //  "a":(1)4, "a":(2)4  -> false
  //  "a":(2)4, "a":(1)2  -> false
  //  "a", "b":(1)2       -> false
  bool contains(AxisRefAttr other) const;

  // Returns whether this axis or sub-axis strictly contains `other`.
  // "a.strictlyContains(b)" is equivalent to "a.contains(b) && a != b".
  //
  // For example:
  //  "a", "a":(2)2       -> true
  //  "a":(1)8, "a":(1)4  -> true
  //  "a":(2)16, "a":(4)2 -> true
  //  "a", "a"            -> false
  //  "a":(2)2, "a":(2)2  -> false
  //  "a":(1)4, "a":(2)4  -> false
  //  "a":(2)4, "a":(1)2  -> false
  //  "a", "b":(1)2       -> false
  bool strictlyContains(AxisRefAttr other) const;

  // Returns whether this axis or sub-axis is a prefix of `other`, i.e.,
  // `other` is equal to this axis ref or can be split into two sub-axes such
  // that the major one is this sub-axis.
  //
  // For example:
  //  "a":(1)2, "a"      -> true
  //  "a":(2)2, "a":(2)4 -> true
  //  "a", "a"           -> true
  //  "a":(2)4, "a":(2)4 -> true
  //  "a":(1)4, "a":(1)2 -> false
  //  "a":(1)4, "a":(2)8 -> false
  //  "a":(1)2, "b"      -> false
  bool prefixOf(AxisRefAttr other) const;

  // Returns whether this axis or sub-axis is a strict prefix of `other`.
  // "a.strictPrefixOf(b)" is equivalent to "a.prefixOf(b) && a != b".
  //
  // For example:
  //  "a":(1)2, "a"      -> true
  //  "a":(2)2, "a":(2)4 -> true
  //  "a", "a"           -> false
  //  "a":(2)4, "a":(2)4 -> false
  //  "a":(1)4, "a":(1)2 -> false
  //  "a":(1)4, "a":(2)8 -> false
  //  "a":(1)2, "b"      -> false
  bool strictPrefixOf(AxisRefAttr other) const;

  // Returns whether this axis or sub-axis is a suffix of `other`, i.e.,
  // `other` is equal to this axis ref or can be split into two sub-axes such
  // that the minor one is this sub-axis.
  //
  // For example:
  //  "a", "a"           -> true
  //  "a":(2)4, "a"      -> true (size("a") == 8)
  //  "a":(2)4, "a":(1)8 -> true
  //  "a", "b"           -> false
  //  "a", "a":(2)4      -> false
  //  "a":(1)8, "a":(2)4 -> false
  //  "a":(1)2, "a":(2)4 -> false
  //  "a":(1)4, "a"      -> false
  bool suffixOf(AxisRefAttr other, MeshAttr mesh) const;

  // Returns whether this axis or sub-axis is a strict suffix of `other`.
  // "a.strictSuffixOf(b)" is equivalent to "a.suffixOf(b) && a != b".
  //
  // For example:
  //  "a":(2)4, "a"      -> true (size("a") == 8)
  //  "a":(2)4, "a":(1)8 -> true
  //  "a", "a"           -> false
  //  "a", "b"           -> false
  //  "a", "a":(2)4      -> false
  //  "a":(1)8, "a":(2)4 -> false
  //  "a":(1)2, "a":(2)4 -> false
  //  "a":(1)4, "a"      -> false
  bool strictSuffixOf(AxisRefAttr other, MeshAttr mesh) const;

  // Returns whether this axis or sub-axis overlaps with `other`, i.e., they
  // are equal or there is a sub-axis that is contained in both axis refs.
  //
  // For example:
  //  "a", "a":(2)2      -> true
  //  "a":(2)2, "a":(2)2 -> true
  //  "a":(1)4, "a":(2)4 -> true
  //  "a":(2)4, "a":(1)4 -> true
  //  "a":(1)4, "a":(1)2 -> true
  //  "a":(2)8, "a":(4)2 -> true
  //  "a":(1)4, "a":(4)2 -> false
  //  "a":(1)2, "a":(4)2 -> false
  //  "a":(1)4, "b":(2)4 -> false
  bool overlaps(AxisRefAttr other) const;

  // Returns whether `a` and `b` can coexist in the same mesh:
  // * If they overlap, then both overlapping and non-overlapping parts must
  //   be valid axes or sub-axes.
  // * Otherwise, both axes can be used to shard the same tensor.
  //
  // For example:
  //  "a", "b"           -> true
  //  "a", "b":(2)2      -> true
  //  "a", "a"           -> true
  //  "a", "a":(2)2      -> true
  //  "a":(1)2, "a":(4)2 -> true
  //  "a":(1)4, "a":(2)4 -> true
  //  "a":(1)2, "a":(1)3 -> false
  //  "a":(1)2, "a":(3)2 -> false
  //  "a":(1)3, "a":(2)3 -> false
  bool canCoexist(AxisRefAttr other) const;

  // If this axis or sub-axis overlaps with `other`, returns that overlapping
  // axis or sub-axis, otherwise returns `std::nullopt`.
  //
  // If this axis and `other` can't coexist, returns `std::nullopt` (see
  // AxisRefAttr::canCoexist).
  //
  // For example:
  //  "a", "a":(2)2      -> "a":(2)2
  //  "a":(2)2, "a":(2)2 -> "a":(2)2
  //  "a":(1)4, "a":(2)4 -> "a":(2)2
  //  "a":(2)4, "a":(1)4 -> "a":(2)2
  //  "a":(1)4, "a":(1)2 -> "a":(1)2
  //  "a":(2)8, "a":(4)2 -> "a":(4)2
  //  "a":(1)4, "a":(4)2 -> std::nullopt
  //  "a":(1)2, "a":(4)2 -> std::nullopt
  //  "a":(1)4, "b":(2)4 -> std::nullopt
  //  "a":(1)2, "a":(1)3 -> std::nullopt
  //  "a":(3)2, "a":(2)3 -> std::nullopt
  std::optional<AxisRefAttr> getOverlap(AxisRefAttr other) const;

  // If there is no overlap between this axis and `other`, return this axis.
  // Otherwise, return the largest prefix of this axis by removing the
  // overlapping suffix with `other`. Return `std::nullopt` if the prefix does
  // not exist.
  //
  // If this axis and `other` can't coexist, returns `std::nullopt` (see
  // AxisRefAttr::canCoexist).
  //
  // For example:
  //  "a", "a":(2)2      -> "a":(1)2
  //  "a":(1)4, "a":(2)4 -> "a":(1)2
  //  "a":(2)8, "a":(4)2 -> "a":(2)2
  //  "a":(1)4, "a":(4)2 -> "a":(1)4
  //  "a":(1)2, "a":(4)2 -> "a":(1)2
  //  "a":(1)4, "b":(2)4 -> "a":(1)4
  //  "a":(2)2, "a":(2)2 -> std::nullopt
  //  "a":(2)4, "a":(1)4 -> std::nullopt
  //  "a":(1)4, "a":(1)2 -> std::nullopt
  //  "a":(1)2, "a":(3)2 -> std::nullopt
  //  "a":(1)3, "a":(2)3 -> std::nullopt
  std::optional<AxisRefAttr> getPrefixWithoutOverlap(AxisRefAttr other) const;

  // If there is no overlap between this axis and `other`, return this axis.
  // Otherwise, return the largest suffix of this axis by removing the
  // overlapping prefix with `other`. Return `std::nullopt` if the suffix does
  // not exist.
  //
  // If this axis and `other` can't coexist, returns `std::nullopt` (see
  // AxisRefAttr::canCoexist).
  //
  // For example:
  //  "a", "a":(2)2      -> "a":(4)2 (size("a") == 8)
  //  "a":(1)4, "a":(1)2 -> "a":(2)2
  //  "a":(2)8, "a":(4)2 -> "a":(8)2
  //  "a":(1)4, "a":(4)2 -> "a":(1)4
  //  "a":(1)2, "a":(4)2 -> "a":(1)2
  //  "a":(1)4, "b":(2)4 -> "a":(1)4
  //  "a":(2)2, "a":(2)2 -> std::nullopt
  //  "a":(1)4, "a":(2)4 -> std::nullopt
  //  "a":(2)2, "a":(1)4 -> std::nullopt
  //  "a":(2)3, "a":(1)3 -> std::nullopt
  //  "a":(3)2, "a":(1)2 -> std::nullopt
  std::optional<AxisRefAttr> getSuffixWithoutOverlap(
      AxisRefAttr other, MeshAttr mesh) const;

  // Returns the greatest common prefix of this axis and `other`. If the two
  // axes do not have common prefix, return `std::nullopt`.
  //
  // If this axis and `other` can't coexist, returns `std::nullopt` (see
  // AxisRefAttr::canCoexist).
  //
  // For example:
  //  "a", "a"           -> "a"
  //  "a":(1)4, "a"      -> "a":(1)4
  //  "a", "a":(1)4      -> "a":(1)4
  //  "a":(1)2, "a":(1)4 -> "a":(1)2
  //  "a":(2)8, "a":(2)4 -> "a":(2)4
  //  "a", "b"           -> std::nullopt
  //  "a":(1)2, "a":(2)4 -> std::nullopt
  std::optional<AxisRefAttr> getGreatestCommonPrefix(AxisRefAttr other) const;

  // Returns an iterator to the first axis in `orderedAxes` that overlaps with
  // this axis, or `orderedAxes.end()` if there is no such axis.
  //
  // Assumes no two axes in `orderedAxes` overlap.
  ArrayRef<AxisRefAttr>::iterator getFirstOverlapping(
      ArrayRef<AxisRefAttr> orderedAxes) const;

  // Returns whether this axis-ref can be merged with `other`, i.e., they are
  // consecutive sub-axes of the same full axis and this sub-axis is major to
  // `other`.
  //
  // For example:
  //  "a":(2)4, "a":(8)2 -> true
  //  "b":(1)2, "b":(2)4 -> true
  //  "c":(1)2, "c":(4)2 -> false
  //  "d":(2)4, "d":(1)2 -> false
  bool canMerge(AxisRefAttr other) const;

  // Merges this axis-ref with the `other`, assuming `canMerge(other)` is
  // true, i.e., they are consecutive sub-axes of the same full axis and this
  // sub-axis is major to `other`.
  //
  // The mesh is needed for the size of the full axis (see 2nd example below).
  //
  // For example:
  //  "a":(2)4, "a":(8)2 ~> "a":(2)8
  //  "b":(1)2, "b":(2)4 ~> "b"
  AxisRefAttr merge(AxisRefAttr other, MeshAttr mesh) const;
  static constexpr ::llvm::StringLiteral name = "sdy.axis_ref";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static AxisRefAttr get(::mlir::MLIRContext *context, ::llvm::StringRef name, SubAxisInfoAttr sub_axis_info);
  static AxisRefAttr get(::mlir::MLIRContext *context, StringRef name);
  static AxisRefAttr get(::mlir::MLIRContext *context, StringRef name, int64_t pre_size, int64_t size);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"axis_ref"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::StringRef getName() const;
  SubAxisInfoAttr getSubAxisInfo() const;
};
namespace detail {

struct DimensionShardingAttrStorage;

} // namespace detail
class DimensionShardingAttr : public ::mlir::Attribute::AttrBase<DimensionShardingAttr, ::mlir::Attribute, detail::DimensionShardingAttrStorage> {
public:
  using Base::Base;
  ArrayRef<AxisRefAttr>::iterator axis_begin() const {
    return getAxes().begin();
  }
  ArrayRef<AxisRefAttr>::iterator axis_end() const {
    return getAxes().end();
  }

  // Returns true if this dimension sharding has no axes.
  bool emptyAxes() const { return getAxes().empty(); }

  // Shards this dimension further along `axisName`.
  //
  // Assumes it is it not closed or already sharded on `axisName`.
  //
  // Attributes are immutable, so we can't update the sharding in place and
  // must return a new instance.
  DimensionShardingAttr getSharded(StringRef axisName) const;

  // Returns the sharded size of this dimension,
  // i.e., the product of sharding axis sizes.
  int64_t getShardedSize(MeshAttr mesh) const;

  // Drops the first `N` sharding axes, and keeps `M` sharding axes.
  DimensionShardingAttr sliceShardingAxes(size_t N, size_t M) const;

  // Drops the first `N` sharding axes.
  DimensionShardingAttr dropFrontShardingAxes(size_t N) const;

  // Takes the first `N` sharding axes.
  DimensionShardingAttr takeFrontShardingAxes(size_t N) const;

  // Drops the priority of this dimension sharding, if present.
  DimensionShardingAttr dropPriority() const;

  // Returns the priority of this dimension sharding, if present, or the
  // default priority otherwise.
  int64_t getPriorityOrDefault() const;

  // Builds a closed `DimensionShardingAttr` matching `dimSharding` in axes and priority.
  static DimensionShardingAttr getClosedLike(DimensionShardingAttr sharding);

  // Builds an open `DimensionShardingAttr` matching `dimSharding` in axes and priority.
  static DimensionShardingAttr getOpenLike(DimensionShardingAttr sharding);
  static constexpr ::llvm::StringLiteral name = "sdy.dimension_sharding";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static DimensionShardingAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<AxisRefAttr> axes, bool is_closed, std::optional<int64_t> priority);
  static DimensionShardingAttr get(::mlir::MLIRContext *context, ArrayRef<AxisRefAttr> axes, bool is_closed);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dimension_sharding"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<AxisRefAttr> getAxes() const;
  bool getIsClosed() const;
  std::optional<int64_t> getPriority() const;
};
namespace detail {

struct TensorShardingAttrStorage;

} // namespace detail
class TensorShardingAttr : public ::mlir::Attribute::AttrBase<TensorShardingAttr, ::mlir::Attribute, detail::TensorShardingAttrStorage> {
public:
  using Base::Base;
  int64_t getRank() const {
    return getDimShardings().size();
  }

  DimensionShardingAttr getDimSharding(int64_t dim) const {
    return getDimShardings()[dim];
  }

  bool isClosed(int64_t dim) const {
    return getDimSharding(dim).getIsClosed();
  }

  bool isFullyClosed() const {
    return llvm::all_of(getDimShardings(),
                    [](const DimensionShardingAttr dimSharding) {
                       return dimSharding.getIsClosed();
                    });
  }

  bool isFullyReplicated() const {
    return llvm::all_of(getDimShardings(),
                    [](const DimensionShardingAttr dimSharding) {
                       return dimSharding.emptyAxes();
                    });
  }

  bool isFullyReplicatedAndOpen() const {
    return llvm::all_of(
        getDimShardings(), [](const DimensionShardingAttr dimSharding) {
          return dimSharding.emptyAxes() && !dimSharding.getIsClosed();
        });
  }

  // Returns the mesh `FlatSymbolRefAttr` this sharding references, assuming
  // it doesn't have an inlined `MeshAttr`.
  FlatSymbolRefAttr getMeshSymName() const {
    return mlir::cast<FlatSymbolRefAttr>(getMeshOrRef());
  }

  // Returns the mesh name this sharding references, assuming it doesn't have
  // an inlined `MeshAttr`.
  StringRef getMeshName() const {
    return getMeshSymName().getValue();
  }

  // If this sharding has an inlined `MeshAttr`, returns it, otherwise looks
  // up the mesh symbol with the referenced name in `symbolTable`, and returns
  // its `MeshAttr` if it exists in the table, or nullptr otherwise.
  MeshAttr getMesh(const SymbolTable& symbolTable) const;

  // If this sharding has an inlined `MeshAttr`, returns it, otherwise looks
  // up the mesh symbol with the referenced name in the symbol table of the
  // enclosing module of `op`, and returns its `MeshAttr` if it exists in the
  // table, or nullptr otherwise.
  MeshAttr getMesh(Operation* op) const;

  // Returns true if all dimension shardings are empty and there are no
  // replicated/unreduced axes.
  bool emptyAxes() const;

  // Like `llvm::any_of` but checks the predicate against all dimension
  // sharding and replicated/unreduced `AxisRefAttr`s.
  bool anyOfAxisRef(std::function<bool(AxisRefAttr)> predicate) const;

  // Like `llvm::any_of` but checks the predicate against all dimension
  // sharding and replicated `AxisRefAttr`s.
  bool anyOfDimShardingOrReplicatedAxis(
      std::function<bool(AxisRefAttr)> predicate) const;

  // Like `llvm::for_each` but applies the `callback` against all dimension
  // sharding and replicated/unreduced `AxisRefAttr`s.
  void forEachAxisRef(std::function<void(AxisRefAttr)> callback) const;

  // Returns true if `axisName` or a sub-axis of it is used to shard any
  // dimension or is replicated/unreduced.
  bool isBound(StringRef axisName) const;

  // Returns true if dimension `dim` can be further sharded on the full
  // `axisName`.
  bool canShard(int64_t dim, StringRef axisName) const;

  // Returns true if the tensor can be replicated on the full `axisName`.
  bool canReplicate(StringRef axisName) const;

  // Closes sharding dimensions at the specified dimension indices.
  TensorShardingAttr closeShardingDims(ArrayRef<int64_t> dimIndices) const;

  // Opens sharding dimensions at the specified dimension indices.
  TensorShardingAttr openShardingDims(ArrayRef<int64_t> dimIndices) const;

  // Sets the sharding of dimension `dim`.
  //
  // Assumes `dim < getRank()`.
  //
  // Attributes are immutable, so we can't update the sharding in place and
  // must return a new instance.
  TensorShardingAttr replaceDimSharding(
      int64_t dim, DimensionShardingAttr sharding) const;

  // Sets the replicated axes to `replicatedAxes`.
  //
  // Attributes are immutable, so we can't update the sharding in place and
  // must return a new instance.
  TensorShardingAttr replaceReplicatedAxes(
      ArrayRef<AxisRefAttr> replicatedAxes) const;

  // Sets the unreduced axes to `unreducedAxes`.
  //
  // Attributes are immutable, so we can't update the sharding in place and
  // must return a new instance.
  TensorShardingAttr replaceUnreducedAxes(
      ArrayRef<AxisRefAttr> unreducedAxes) const;

  // Shards dimension `dim` further along `axisName`.
  //
  // Assumes `canShard(dim, axisName)` is true.
  //
  // Attributes are immutable, so we can't update the sharding in place and
  // must return a new instance.
  TensorShardingAttr getSharded(int64_t dim, StringRef axisName) const;

  // Replicates the tensor along `axisName`.
  //
  // Assumes `canReplicate(axisName)` is true. The `mesh` is needed to keep
  // the replicated axes sorted.
  //
  // Attributes are immutable, so we can't update the sharding in place and
  // must return a new instance.
  TensorShardingAttr getReplicated(StringRef axisName, MeshAttr mesh) const;


  // Verifies that this `TensorShardingAttr` is valid w.r.t the given
  // tensor type and mesh.
  //
  // If `type` isn't a `ShapedType`, the sharding must have rank 0
  // and no replicated axes. Otherwise, the `ShapedType` must have a static
  // shape.

  //
  // If `checkDivisibility` is true, verifies that each dimension size
  // is divisible by its sharded size.
  mlir::LogicalResult verifyForType(
      Type type, MeshAttr mesh,
      std::function<InFlightDiagnostic(StringRef)> emitError,
      bool checkDivisibility = true);

  // Builds a `TensorShardingAttr` with all dim shardings being empty and
  // closed (cannot be further replicated/sharded).
  static TensorShardingAttr getFullyClosed(
      MLIRContext* context, int64_t rank, Attribute meshOrRef);

  // Builds a `TensorShardingAttr` with all dim shardings being empty and
  // closed (cannot be further replicated/sharded).
  static TensorShardingAttr getFullyClosed(
      MLIRContext* context, int64_t rank, StringRef meshName);

  // Builds a fully closed and replicated `TensorShardingAttr` matching
  // `sharding` in `mesh_or_ref` and rank.
  static TensorShardingAttr getFullyClosedLike(TensorShardingAttr sharding);

  // Builds a `TensorShardingAttr` with all dim shardings being marked closed
  // and matching `sharding` in dim sharding axes, `mesh_or_ref` and rank.
  static TensorShardingAttr getClosedLike(TensorShardingAttr sharding);

  // Builds a `TensorShardingAttr` with all dim shardings being marked open
  // and matching `sharding` in dim sharding axes, `mesh_or_ref` and rank.
  static TensorShardingAttr getOpenLike(TensorShardingAttr sharding);

  // Builds a `TensorShardingAttr` with a closed dim sharding for each axis
  // list in `axesPerDim`.
  static TensorShardingAttr getClosed(
      MLIRContext* context, Attribute meshOrRef,
      ArrayRef<SmallVector<AxisRefAttr>> axesPerDim,
      ArrayRef<AxisRefAttr> unreducedAxes);

  // Builds a `TensorShardingAttr` with all dim shardings being empty and open
  // (can be further sharded).
  static TensorShardingAttr getFullyOpen(
      MLIRContext* context, int64_t rank, Attribute meshOrRef);

  // Builds a `TensorShardingAttr` with all dim shardings being empty and open
  // (can be further sharded).
  static TensorShardingAttr getFullyOpen(
      MLIRContext* context, int64_t rank, StringRef meshName);

  // Builds a fully open and replicated `TensorShardingAttr` matching
  // `sharding` in `mesh_or_ref` and rank.
  static TensorShardingAttr getFullyOpenLike(TensorShardingAttr sharding);

  // Builds a `TensorShardingAttr` with all dim shardings being empty and open/closed.
  static TensorShardingAttr getFullyReplicated(
      MLIRContext* context, int64_t rank, Attribute meshOrRef, bool isClosed);

  // Builds a `TensorShardingAttr` with all dim shardings being empty and openclosed.
  static TensorShardingAttr getFullyReplicated(
      MLIRContext* context, int64_t rank, StringRef meshName, bool isClosed);

  // Gets the local mlir::Type from a global mlir::Type w.r.t. the given mesh
  // and sharding. Assumes that the sharding is valid w.r.t. the mesh and
  // global type. Returns the global mlir::Type if it is not a
  // mlir::ShapedType with a rank.
  //
  // If `allowNonDivisible` is false, returns nullptr if a dimension sharding
  // doesn't divide the corresponding size.
  Type getLocalType(Type globalType, MeshAttr mesh,
                    bool allowNonDivisible = true) const;

  // Gets the local tensor type from a global RankedTensorType w.r.t. the
  // given mesh and sharding. Assumes that the sharding is valid w.r.t. the
  // mesh and tensor type.
  //
  // If `allowNonDivisible` is false, returns nullptr if a dimension sharding
  // doesn't divide the corresponding size.
  RankedTensorType getLocalTensorType(RankedTensorType globalTensorType,
                                      MeshAttr mesh,
                                      bool allowNonDivisible = true) const;

  // Gets the global tensor type from a local RankedTensorType w.r.t. the
  // given mesh and sharding. Assumes that the sharding is valid w.r.t. the
  // mesh and tensor type.
  //
  // NOTE: this doesn't take into account padding. Each dimension of
  // `localTensorType` will be a multiple of the global tensor type returned.
  RankedTensorType getGlobalTensorType(RankedTensorType localTensorType,
                                       MeshAttr mesh) const;

  // Returns true if all dimensions are sharded in the same way and with
  // equal meshes.
  bool isEquivalent(TensorShardingAttr otherSharding) const;
  static constexpr ::llvm::StringLiteral name = "sdy.sharding";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  using Base::getChecked;
  static TensorShardingAttr get(::mlir::MLIRContext *context, ::mlir::Attribute mesh_or_ref, ::llvm::ArrayRef<DimensionShardingAttr> dim_shardings, ::llvm::ArrayRef<AxisRefAttr> replicated_axes, ::llvm::ArrayRef<AxisRefAttr> unreduced_axes);
  static TensorShardingAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Attribute mesh_or_ref, ::llvm::ArrayRef<DimensionShardingAttr> dim_shardings, ::llvm::ArrayRef<AxisRefAttr> replicated_axes, ::llvm::ArrayRef<AxisRefAttr> unreduced_axes);
  static TensorShardingAttr get(::mlir::MLIRContext *context, StringAttr mesh_name, ArrayRef<DimensionShardingAttr> dim_shardings, ArrayRef<AxisRefAttr> replicated_axes, ArrayRef<AxisRefAttr> unreduced_axes);
  static TensorShardingAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, StringAttr mesh_name, ArrayRef<DimensionShardingAttr> dim_shardings, ArrayRef<AxisRefAttr> replicated_axes, ArrayRef<AxisRefAttr> unreduced_axes);
  static TensorShardingAttr get(::mlir::MLIRContext *context, StringRef mesh_name, ArrayRef<DimensionShardingAttr> dim_shardings, ArrayRef<AxisRefAttr> replicated_axes, ArrayRef<AxisRefAttr> unreduced_axes);
  static TensorShardingAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, StringRef mesh_name, ArrayRef<DimensionShardingAttr> dim_shardings, ArrayRef<AxisRefAttr> replicated_axes, ArrayRef<AxisRefAttr> unreduced_axes);
  static ::llvm::LogicalResult verifyInvariantsImpl(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Attribute mesh_or_ref, ::llvm::ArrayRef<DimensionShardingAttr> dim_shardings, ::llvm::ArrayRef<AxisRefAttr> replicated_axes, ::llvm::ArrayRef<AxisRefAttr> unreduced_axes);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Attribute mesh_or_ref, ::llvm::ArrayRef<DimensionShardingAttr> dim_shardings, ::llvm::ArrayRef<AxisRefAttr> replicated_axes, ::llvm::ArrayRef<AxisRefAttr> unreduced_axes);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sharding"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Attribute getMeshOrRef() const;
  ::llvm::ArrayRef<DimensionShardingAttr> getDimShardings() const;
  ::llvm::ArrayRef<AxisRefAttr> getReplicatedAxes() const;
  ::llvm::ArrayRef<AxisRefAttr> getUnreducedAxes() const;
};
namespace detail {

struct TensorShardingPerValueAttrStorage;

} // namespace detail
class TensorShardingPerValueAttr : public ::mlir::Attribute::AttrBase<TensorShardingPerValueAttr, ::mlir::Attribute, detail::TensorShardingPerValueAttrStorage> {
public:
  using Base::Base;
  // Builds a `TensorSharding` for each type in `types`, with all dimension
  // shardings empty and open (can be further sharded).
  static TensorShardingPerValueAttr getFullyOpen(
      MLIRContext* context, TypeRange types, StringRef meshName);

  // Builds a `TensorSharding` for each type in `types`, with all dimension
  // shardings marked empty and closed (cannot be further sharded).
  static TensorShardingPerValueAttr getFullyClosed(
      MLIRContext* context, TypeRange types, StringRef meshName);

  // Builds an open `TensorSharding` for each type in `types`, but
  // with the sharding at `index` replaced with `sharding`.
  static TensorShardingPerValueAttr getOpenWithShardingAtIndex(
      MLIRContext* context, TypeRange types, int64_t index,
      TensorShardingAttr sharding);

  // Returns whether there are no values.
  bool empty() const { return getShardings().empty(); }

  // Returns the number of values.
  int64_t size() const { return getShardings().size(); }

  bool anyShardingHasUnreducedAxes() const {
    return llvm::any_of(getShardings(), [](TensorShardingAttr sharding) {
      return !sharding.getUnreducedAxes().empty();
    });
  }

  // Returns the sharding of a value at `operandIndex`.
  //
  // Assumes `operandIndex < size()`.
  TensorShardingAttr getSharding(int64_t operandIndex) const {
    assert(operandIndex < size());
    return getShardings()[operandIndex];
  }

  // Sets the sharding of a value at `index`.
  //
  // Assumes `index < size()`.
  //
  // Attributes are immutable, so we can't update the sharding in place and
  // must return a new instance.
  TensorShardingPerValueAttr replaceValueSharding(
      int64_t index, TensorShardingAttr sharding) const;
  static constexpr ::llvm::StringLiteral name = "sdy.sharding_per_value";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static TensorShardingPerValueAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<TensorShardingAttr> shardings);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sharding_per_value"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<TensorShardingAttr> getShardings() const;
};
namespace detail {

struct DimMappingAttrStorage;

} // namespace detail
class DimMappingAttr : public ::mlir::Attribute::AttrBase<DimMappingAttr, ::mlir::Attribute, detail::DimMappingAttrStorage> {
public:
  using Base::Base;
  // Returns whether the given `factorIndex` is the minor-most factor.
  bool isMinorMost(int64_t factorIndex) const {
    return !getFactorIndices().empty() &&
            getFactorIndices().back() == factorIndex;
  }
  static constexpr ::llvm::StringLiteral name = "sdy.dim_mapping";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static DimMappingAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> factor_indices);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dim_mapping"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<int64_t> getFactorIndices() const;
};
namespace detail {

struct TensorMappingAttrStorage;

} // namespace detail
class TensorMappingAttr : public ::mlir::Attribute::AttrBase<TensorMappingAttr, ::mlir::Attribute, detail::TensorMappingAttrStorage> {
public:
  using Base::Base;
  int64_t getRank() const { return getDimMappings().size(); }
  bool empty() const { return getDimMappings().empty(); }

  // Returns true if any of the dimension mappings contains the `factorIndex`.
  bool containsFactor(int64_t factorIndex) const;
  static constexpr ::llvm::StringLiteral name = "sdy.tensor_mapping";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static TensorMappingAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<DimMappingAttr> dim_mappings);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tensor_mapping"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<DimMappingAttr> getDimMappings() const;
};
namespace detail {

struct OpShardingRuleAttrStorage;

} // namespace detail
class OpShardingRuleAttr : public ::mlir::Attribute::AttrBase<OpShardingRuleAttr, ::mlir::Attribute, detail::OpShardingRuleAttrStorage> {
public:
  using Base::Base;
  int64_t getNumFactors() const { return getFactorSizes().size(); }
  int64_t getNumOperands() const { return getOperandMappings().size(); }
  int64_t getNumResults() const { return getResultMappings().size(); }

  int64_t getFactorSize(int64_t factorIndex) const {
    return getFactorSizes()[factorIndex];
  }
  TensorMappingAttr getOperandMapping(int64_t operandNum) const {
    return getOperandMappings()[operandNum];
  }
  TensorMappingAttr getResultMapping(int64_t resultNum) const {
    return getResultMappings()[resultNum];
  }

  bool isCustom() const { return getIsCustomRule(); }

  // Returns the type of the given `factorIndex`.
  FactorType getFactorType(int64_t factorIndex) const;

  // Returns true if the `factorIndex` is a pass-through factor.
  bool isPassThroughFactor(int64_t factorIndex) const;

  // Returns true if the `factorIndex` is a reduction factor.
  bool isReductionFactor(int64_t factorIndex) const;

  // Returns true if the `factorIndex` is a factor requiring full replication.
  bool isNeedReplicationFactor(int64_t factorIndex) const;

  // Returns true if the `factorIndex` is a permutation factor.
  bool isPermutationFactor(int64_t factorIndex) const;

  // Returns true if the `factorIndex` is in `blocked_propagation_factors`. If
  // yes, then shardings are not allowed to be propagated along this factor.
  bool isBlockedPropagationFactor(int64_t factorIndex) const;

  // Returns true if the `factorIndex` is a factor in all non-scalar tensors.
  bool isFactorInAllNonScalarTensors(int64_t factorIndex) const;

  // Returns true if the `factorIndex` is a batching factor, which satisfies:
  // 1. It is a pass-through factor.
  // 2. It is used in all non-scalar tensors.
  bool isBatchingFactor(int64_t factorIndex) const;

  // Returns a vector of tensor indices that are non-scalar, of all operand
  // and result tensors, the operands come before the results.
  SmallVector<int64_t> getNonScalarTensorIndices() const;

  // Returns a vector of batching factor indices.
  SmallVector<int64_t> getBatchingFactors() const;

  bool hasDimensionsWithMultipleFactors() const;
  static constexpr ::llvm::StringLiteral name = "sdy.op_sharding_rule";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static OpShardingRuleAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> factor_sizes, ::llvm::ArrayRef<TensorMappingAttr> operand_mappings, ::llvm::ArrayRef<TensorMappingAttr> result_mappings, ::llvm::ArrayRef<int64_t> reduction_factors, ::llvm::ArrayRef<int64_t> need_replication_factors, ::llvm::ArrayRef<int64_t> permutation_factors, ::llvm::ArrayRef<int64_t> blocked_propagation_factors, bool is_custom_rule);
  static OpShardingRuleAttr get(::mlir::MLIRContext *context, ArrayRef<int64_t> factor_sizes, ArrayRef<TensorMappingAttr> operand_mappings, ArrayRef<TensorMappingAttr> result_mappings, ArrayRef<int64_t> reduction_factors, ArrayRef<int64_t> need_replication_factors, ArrayRef<int64_t> permutation_factors, ArrayRef<int64_t> blocked_propagation_factors);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"op_sharding_rule"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<int64_t> getFactorSizes() const;
  ::llvm::ArrayRef<TensorMappingAttr> getOperandMappings() const;
  ::llvm::ArrayRef<TensorMappingAttr> getResultMappings() const;
  ::llvm::ArrayRef<int64_t> getReductionFactors() const;
  ::llvm::ArrayRef<int64_t> getNeedReplicationFactors() const;
  ::llvm::ArrayRef<int64_t> getPermutationFactors() const;
  ::llvm::ArrayRef<int64_t> getBlockedPropagationFactors() const;
  bool getIsCustomRule() const;
};
namespace detail {

struct AxisRefListAttrStorage;

} // namespace detail
class AxisRefListAttr : public ::mlir::Attribute::AttrBase<AxisRefListAttr, ::mlir::Attribute, detail::AxisRefListAttrStorage> {
public:
  using Base::Base;
  auto begin() const { return getValue().begin(); }
  auto end() const { return getValue().end(); }
  bool empty() const { return getValue().empty(); }
  size_t size() const { return getValue().size(); }
  auto &front() const { return getValue().front(); }
  auto &back() const { return getValue().back(); }
  auto &operator[](size_t index) { return getValue()[index]; }
  operator ::llvm::ArrayRef<AxisRefAttr>() const { return getValue(); }
  static constexpr ::llvm::StringLiteral name = "sdy.axis_ref_list";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static AxisRefListAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<AxisRefAttr> value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"axis_ref_list"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<AxisRefAttr> getValue() const;
};
namespace detail {

struct ListOfAxisRefListsAttrStorage;

} // namespace detail
class ListOfAxisRefListsAttr : public ::mlir::Attribute::AttrBase<ListOfAxisRefListsAttr, ::mlir::Attribute, detail::ListOfAxisRefListsAttrStorage> {
public:
  using Base::Base;
  auto begin() const { return getValue().begin(); }
  auto end() const { return getValue().end(); }
  bool empty() const { return getValue().empty(); }
  size_t size() const { return getValue().size(); }
  auto &front() const { return getValue().front(); }
  auto &back() const { return getValue().back(); }
  auto &operator[](size_t index) { return getValue()[index]; }
  operator ::llvm::ArrayRef<AxisRefListAttr>() const { return getValue(); }
  static constexpr ::llvm::StringLiteral name = "sdy.list_of_axis_ref_lists";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static ListOfAxisRefListsAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<AxisRefListAttr> value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"list_of_axis_ref_lists"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<AxisRefListAttr> getValue() const;
};
namespace detail {

struct AllToAllParamAttrStorage;

} // namespace detail
class AllToAllParamAttr : public ::mlir::Attribute::AttrBase<AllToAllParamAttr, ::mlir::Attribute, detail::AllToAllParamAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sdy.all_to_all_param";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static AllToAllParamAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<AxisRefAttr> axes, int64_t src_dim, int64_t tgt_dim);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"all_to_all_param"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<AxisRefAttr> getAxes() const;
  int64_t getSrcDim() const;
  int64_t getTgtDim() const;
};
namespace detail {

struct AllToAllParamListAttrStorage;

} // namespace detail
class AllToAllParamListAttr : public ::mlir::Attribute::AttrBase<AllToAllParamListAttr, ::mlir::Attribute, detail::AllToAllParamListAttrStorage> {
public:
  using Base::Base;
  bool empty() const { return getValue().empty(); }

  size_t size() const { return getValue().size(); }

  ArrayRef<AllToAllParamAttr>::iterator begin() const { return getValue().begin(); }

  ArrayRef<AllToAllParamAttr>::iterator end() const { return getValue().end(); }

  // Returns true if this parameter list's dimensions overlap with 'other'.
  bool overlaps(AllToAllParamListAttr other) const;

  // Returns a list of parameters that combines this list and `other`, sorted
  // by source dimension. This function assumes that this list and `other`
  // do not have overlapping dimensions, and should only be called after
  // checking `overlaps` is false.
  AllToAllParamListAttr combineAndSort(AllToAllParamListAttr other) const;
  static constexpr ::llvm::StringLiteral name = "sdy.all_to_all_param_list";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static AllToAllParamListAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<AllToAllParamAttr> value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"all_to_all_param_list"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<AllToAllParamAttr> getValue() const;
};
namespace detail {

struct EdgeValueRefAttrStorage;

} // namespace detail
class EdgeValueRefAttr : public ::mlir::Attribute::AttrBase<EdgeValueRefAttr, ::mlir::Attribute, detail::EdgeValueRefAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sdy.edge_value_ref";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static EdgeValueRefAttr get(::mlir::MLIRContext *context, ::mlir::sdy::EdgeNodeType type, int64_t index);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"edge_value_ref"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::sdy::EdgeNodeType getType() const;
  int64_t getIndex() const;
};
namespace detail {

struct AxisToPropagationDetailsAttrStorage;

} // namespace detail
class AxisToPropagationDetailsAttr : public ::mlir::Attribute::AttrBase<AxisToPropagationDetailsAttr, ::mlir::Attribute, detail::AxisToPropagationDetailsAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sdy.axis_to_propagation_details";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  using Base::getChecked;
  static AxisToPropagationDetailsAttr get(::mlir::MLIRContext *context, ::mlir::sdy::AxisRefAttr axis_name, ::mlir::sdy::EdgeValueRefAttr source, ::llvm::ArrayRef<EdgeValueRefAttr> targets);
  static AxisToPropagationDetailsAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::sdy::AxisRefAttr axis_name, ::mlir::sdy::EdgeValueRefAttr source, ::llvm::ArrayRef<EdgeValueRefAttr> targets);
  static ::llvm::LogicalResult verifyInvariantsImpl(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::sdy::AxisRefAttr axis_name, ::mlir::sdy::EdgeValueRefAttr source, ::llvm::ArrayRef<EdgeValueRefAttr> targets);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::sdy::AxisRefAttr axis_name, ::mlir::sdy::EdgeValueRefAttr source, ::llvm::ArrayRef<EdgeValueRefAttr> targets);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"axis_to_propagation_details"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::sdy::AxisRefAttr getAxisName() const;
  ::mlir::sdy::EdgeValueRefAttr getSource() const;
  ::llvm::ArrayRef<EdgeValueRefAttr> getTargets() const;
};
namespace detail {

struct PropagationOneStepAttrStorage;

} // namespace detail
class PropagationOneStepAttr : public ::mlir::Attribute::AttrBase<PropagationOneStepAttr, ::mlir::Attribute, detail::PropagationOneStepAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sdy.propagation_one_step";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  static PropagationOneStepAttr get(::mlir::MLIRContext *context, int64_t step_index, ::llvm::ArrayRef<AxisToPropagationDetailsAttr> axis_entries);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"propagation_one_step"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  int64_t getStepIndex() const;
  ::llvm::ArrayRef<AxisToPropagationDetailsAttr> getAxisEntries() const;
};
namespace detail {

struct PropagationEdgesAttrStorage;

} // namespace detail
class PropagationEdgesAttr : public ::mlir::Attribute::AttrBase<PropagationEdgesAttr, ::mlir::Attribute, detail::PropagationEdgesAttrStorage> {
public:
  using Base::Base;
  auto begin() const { return getValue().begin(); }
  auto end() const { return getValue().end(); }
  bool empty() const { return getValue().empty(); }
  size_t size() const { return getValue().size(); }
  auto &front() const { return getValue().front(); }
  auto &back() const { return getValue().back(); }
  auto &operator[](size_t index) { return getValue()[index]; }
  operator ::llvm::ArrayRef<PropagationOneStepAttr>() const { return getValue(); }
  static constexpr ::llvm::StringLiteral name = "sdy.propagation_edges";
  static constexpr ::llvm::StringLiteral dialectName = "sdy";
  using Base::getChecked;
  static PropagationEdgesAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<PropagationOneStepAttr> value);
  static PropagationEdgesAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<PropagationOneStepAttr> value);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<PropagationOneStepAttr> value);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<PropagationOneStepAttr> value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"propagation_edges"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<PropagationOneStepAttr> getValue() const;
};

} // namespace mlir::sdy
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ManualAxesAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::MeshAxisAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::MeshAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::SubAxisInfoAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::AxisRefAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::DimensionShardingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::TensorShardingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::TensorShardingPerValueAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::DimMappingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::TensorMappingAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::OpShardingRuleAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::AxisRefListAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::ListOfAxisRefListsAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::AllToAllParamAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::AllToAllParamListAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::EdgeValueRefAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::AxisToPropagationDetailsAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::PropagationOneStepAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sdy::PropagationEdgesAttr)

#endif // GET_ATTRDEF_CLASSES

