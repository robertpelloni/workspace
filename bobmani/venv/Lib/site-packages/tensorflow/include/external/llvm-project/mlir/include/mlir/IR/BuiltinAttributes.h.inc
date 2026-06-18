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
namespace mlir {

/// An Attribute containing an AffineMap object
/// Syntax:
/// 
///     ```
///     affine-map-attribute ::= `affine_map` `<` affine-map `>`
///     ```
/// 
///     Examples:
/// 
///     ```mlir
///     affine_map<(d0) -> (d0)>
///     affine_map<(d0, d1, d2) -> (d0, d1)>
///     ```
class AffineMapAttr;
/// A collection of other Attribute values
/// Syntax:
/// 
///     ```
///     array-attribute ::= `[` (attribute-value (`,` attribute-value)*)? `]`
///     ```
/// 
///     An array attribute is an attribute that represents a collection of attribute
///     values.
/// 
///     Examples:
/// 
///     ```mlir
///     []
///     [10, i32]
///     [affine_map<(d0, d1, d2) -> (d0, d1)>, i32, "string attribute"]
///     ```
class ArrayAttr;
/// A dense array of integer or floating point elements.
/// A dense array attribute is an attribute that represents a dense array of
///     primitive element types. Contrary to DenseIntOrFPElementsAttr this is a
///     flat unidimensional array which does not have a storage optimization for
///     splat. This allows to expose the raw array through a C++ API as
///     `ArrayRef<T>` for compatible types. The element type must be bool or an
///     integer or float whose bitwidth is a multiple of 8. Bool elements are stored
///     as bytes.
/// 
///     This is the base class attribute. Access to C++ types is intended to be
///     managed through the subclasses `DenseI8ArrayAttr`, `DenseI16ArrayAttr`,
///     `DenseI32ArrayAttr`, `DenseI64ArrayAttr`, `DenseF32ArrayAttr`,
///     and `DenseF64ArrayAttr`.
/// 
///     Syntax:
/// 
///     ```
///     dense-array-attribute ::= `array` `<` (integer-type | float-type)
///                                           (`:` tensor-literal)? `>`
///     ```
///     Examples:
/// 
///     ```mlir
///     array<i8>
///     array<i32: 10, 42>
///     array<f64: 42., 12.>
///     ```
/// 
///     When a specific subclass is used as argument of an operation, the
///     declarative assembly will omit the type and print directly:
/// 
///     ```mlir
///     [1, 2, 3]
///     ```
class DenseArrayAttr;
/// An Attribute containing a dense multi-dimensional array of integer or floating-point values
/// Syntax:
/// 
///     ```
///     tensor-literal ::= integer-literal | float-literal | bool-literal | [] | [tensor-literal (, tensor-literal)* ]
///     dense-intorfloat-elements-attribute ::= `dense` `<` tensor-literal `>` `:`
///                                             ( tensor-type | vector-type )
///     ```
/// 
///     A dense int-or-float elements attribute is an elements attribute containing
///     a densely packed vector or tensor of integer or floating-point values. The
///     element type of this attribute is required to be either an `IntegerType` or
///     a `FloatType`.
/// 
///     Examples:
/// 
///     ```
///     // A splat tensor of integer values.
///     dense<10> : tensor<2xi32>
///     // A tensor of 2 float32 elements.
///     dense<[10.0, 11.0]> : tensor<2xf32>
///     ```
class DenseIntOrFPElementsAttr;
/// An Attribute containing a dense multi-dimensional array of strings
/// Syntax:
/// 
///     ```
///     dense-string-elements-attribute ::= `dense` `<` attribute-value `>` `:`
///                                         ( tensor-type | vector-type )
///     ```
/// 
///     A dense string elements attribute is an elements attribute containing a
///     densely packed vector or tensor of string values. There are no restrictions
///     placed on the element type of this attribute, enabling the use of dialect
///     specific string types.
/// 
///     Examples:
/// 
///     ```
///     // A splat tensor of strings.
///     dense<"example"> : tensor<2x!foo.string>
///     // A tensor of 2 string elements.
///     dense<["example1", "example2"]> : tensor<2x!foo.string>
///     ```
class DenseStringElementsAttr;
/// An Attribute containing a dense multi-dimensional array backed by a resource
/// Syntax:
/// 
///     ```
///     dense-resource-elements-attribute ::=
///       `dense_resource` `<` resource-handle `>` `:` shaped-type
///     ```
/// 
///     A dense resource elements attribute is an elements attribute backed by a
///     handle to a builtin dialect resource containing a densely packed array of
///     values. This class provides the low-level attribute, which should only be
///     interacted with in very generic terms, actual access to the underlying
///     resource data is intended to be managed through one of the subclasses, such
///     as; `DenseBoolResourceElementsAttr`, `DenseUI64ResourceElementsAttr`,
///     `DenseI32ResourceElementsAttr`, `DenseF32ResourceElementsAttr`,
///     `DenseF64ResourceElementsAttr`, etc.
/// 
///     Examples:
/// 
///     ```mlir
///     "example.user_op"() {attr = dense_resource<blob1> : tensor<3xi64> } : () -> ()
/// 
///     {-#
///     dialect_resources: {
///         builtin: {
///           blob1: "0x08000000010000000000000002000000000000000300000000000000"
///         }
///       }
///     #-}
///     ```
class DenseResourceElementsAttr;
/// An dictionary of named Attribute values
/// Syntax:
/// 
///     ```
///     dictionary-attribute ::= `{` (attribute-entry (`,` attribute-entry)*)? `}`
///     ```
/// 
///     A dictionary attribute is an attribute that represents a sorted collection of
///     named attribute values. The elements are sorted by name, and each name must be
///     unique within the collection.
/// 
///     Examples:
/// 
///     ```mlir
///     {}
///     {attr_name = "string attribute"}
///     {int_attr = 10, "string attr name" = "string attribute"}
///     ```
class DictionaryAttr;
/// An Attribute containing a floating-point value
/// Syntax:
/// 
///     ```
///     float-attribute ::= (float-literal (`:` float-type)?)
///                       | (hexadecimal-literal `:` float-type)
///     ```
/// 
///     A float attribute is a literal attribute that represents a floating point
///     value of the specified [float type](#floating-point-types). It can be
///     represented in the hexadecimal form where the hexadecimal value is
///     interpreted as bits of the underlying binary representation. This form is
///     useful for representing infinity and NaN floating point values. To avoid
///     confusion with integer attributes, hexadecimal literals _must_ be followed
///     by a float type to define a float attribute.
/// 
///     Examples:
/// 
///     ```
///     42.0         // float attribute defaults to f64 type
///     42.0 : f32   // float attribute of f32 type
///     0x7C00 : f16 // positive infinity
///     0x7CFF : f16 // NaN (one of possible values)
///     42 : f32     // Error: expected integer type
///     ```
class FloatAttr;
/// An Attribute containing a integer value
/// Syntax:
/// 
///     ```
///     integer-attribute ::= (integer-literal ( `:` (index-type | integer-type) )?)
///                           | `true` | `false`
///     ```
/// 
///     An integer attribute is a literal attribute that represents an integral
///     value of the specified integer or index type. `i1` integer attributes are
///     treated as `boolean` attributes, and use a unique assembly format of either
///     `true` or `false` depending on the value. The default type for non-boolean
///     integer attributes, if a type is not specified, is signless 64-bit integer.
/// 
///     Examples:
/// 
///     ```mlir
///     10 : i32
///     10    // : i64 is implied here.
///     true  // A bool, i.e. i1, value.
///     false // A bool, i.e. i1, value.
///     ```
class IntegerAttr;
/// An Attribute containing an IntegerSet object
/// Syntax:
/// 
///     ```
///     integer-set-attribute ::= `affine_set` `<` integer-set `>`
///     ```
/// 
///     Examples:
/// 
///     ```mlir
///     affine_set<(d0) : (d0 - 2 >= 0)>
///     ```
class IntegerSetAttr;
/// An opaque representation of another Attribute
/// Syntax:
/// 
///     ```
///     opaque-attribute ::= dialect-namespace `<` attr-data `>`
///     ```
/// 
///     Opaque attributes represent attributes of non-registered dialects. These are
///     attribute represented in their raw string form, and can only usefully be
///     tested for attribute equality.
/// 
///     Examples:
/// 
///     ```mlir
///     #dialect<"opaque attribute data">
///     ```
class OpaqueAttr;
/// An opaque representation of a multi-dimensional array
/// Syntax:
/// 
///     ```
///     sparse-elements-attribute ::= `sparse` `<` attribute-value `,`
///                                   attribute-value `>` `:`
///                                   ( tensor-type | vector-type )
///     ```
/// 
///     A sparse elements attribute is an elements attribute that represents a
///     sparse vector or tensor object. This is where very few of the elements are
///     non-zero.
/// 
///     The attribute uses COO (coordinate list) encoding to represent the sparse
///     elements of the elements attribute. The indices are stored via a 2-D tensor
///     of 64-bit integer elements with shape [N, ndims], which specifies the
///     indices of the elements in the sparse tensor that contains non-zero values.
///     The element values are stored via a 1-D tensor with shape [N], that supplies
///     the corresponding values for the indices.
/// 
///     Example:
/// 
///     ```mlir
///     sparse<[[0, 0], [1, 2]], [1, 5]> : tensor<3x4xi32>
/// 
///     // This represents the following tensor:
///     ///  [[1, 0, 0, 0],
///     ///   [0, 0, 5, 0],
///     ///   [0, 0, 0, 0]]
///     ```
class SparseElementsAttr;
/// An Attribute representing a strided layout of a shaped type
/// Syntax:
/// 
///     ```
///     strided-layout-attribute ::= `strided` `<` `[` stride-list `]`
///                                  (`,` `offset` `:` dimension)? `>`
///     stride-list ::= /*empty*/
///                   | dimension (`,` dimension)*
///     dimension ::= decimal-literal | `?`
///     ```
/// 
///     A strided layout attribute captures layout information of the memref type in
///     the canonical form. Specifically, it contains a list of _strides_, one for
///     each dimension. A stride is the number of elements in the linear storage
///     one must step over to reflect an increment in the given dimension. For
///     example, a `MxN` row-major contiguous shaped type would have the strides
///     `[N, 1]`. The layout attribute also contains the _offset_ from the base
///     pointer of the shaped type to the first effectively accessed element,
///     expressed in terms of the number of contiguously stored elements.
/// 
///     Strides must be positive and the offset must be non-negative. Both the
///     strides and the offset may be _dynamic_, i.e. their value may not be known
///     at compile time. This is expressed as a `?` in the assembly syntax and as
///     `ShapedType::kDynamic` in the code. Stride and offset values
///     must satisfy the constraints above at runtime, the behavior is undefined
///     otherwise.
/// 
///     See [Dialects/Builtin.md#memreftype](MemRef type) for more information.
class StridedLayoutAttr;
/// An Attribute containing a string
/// Syntax:
/// 
///     ```
///     string-attribute ::= string-literal (`:` type)?
///     ```
/// 
///     A string attribute is an attribute that represents a string literal value.
/// 
///     Examples:
/// 
///     ```mlir
///     "An important string"
///     "string with a type" : !dialect.string
///     ```
class StringAttr;
/// An Attribute containing a symbolic reference to an Operation
/// Syntax:
/// 
///     ```
///     symbol-ref-attribute ::= symbol-ref-id (`::` symbol-ref-id)*
///     ```
/// 
///     A symbol reference attribute is a literal attribute that represents a named
///     reference to an operation that is nested within an operation with the
///     `OpTrait::SymbolTable` trait. As such, this reference is given meaning by
///     the nearest parent operation containing the `OpTrait::SymbolTable` trait. It
///     may optionally contain a set of nested references that further resolve to a
///     symbol nested within a different symbol table.
/// 
///     **Rationale:** Identifying accesses to global data is critical to
///     enabling efficient multi-threaded compilation. Restricting global
///     data access to occur through symbols and limiting the places that can
///     legally hold a symbol reference simplifies reasoning about these data
///     accesses.
/// 
///     See [`Symbols And SymbolTables`](../SymbolsAndSymbolTables.md) for more
///     information.
/// 
///     Examples:
/// 
///     ```mlir
///     @flat_reference
///     @parent_reference::@nested_reference
///     ```
class SymbolRefAttr;
/// An Attribute containing a Type
/// Syntax:
/// 
///     ```
///     type-attribute ::= type
///     ```
/// 
///     A type attribute is an attribute that represents a
///     [type object](#type-system).
/// 
///     Examples:
/// 
///     ```mlir
///     i32
///     !dialect.type
///     ```
class TypeAttr;
/// An Attribute value of `unit` type
/// Syntax:
/// 
///     ```
///     unit-attribute ::= `unit`
///     ```
/// 
///     A unit attribute is an attribute that represents a value of `unit` type. The
///     `unit` type allows only one value forming a singleton set. This attribute
///     value is used to represent attributes that only have meaning from their
///     existence.
/// 
///     One example of such an attribute could be the `swift.self` attribute. This
///     attribute indicates that a function parameter is the self/context parameter.
///     It could be represented as a [boolean attribute](#boolean-attribute)(true or
///     false), but a value of false doesn't really bring any value. The parameter
///     either is the self/context or it isn't.
/// 
/// 
///     Examples:
/// 
///     ```mlir
///     // A unit attribute defined with the `unit` value specifier.
///     func.func @verbose_form() attributes {dialectName.unitAttr = unit}
/// 
///     // A unit attribute in an attribute dictionary can also be defined without
///     // the value specifier.
///     func.func @simple_form() attributes {dialectName.unitAttr}
///     ```
class UnitAttr;
namespace detail {

struct AffineMapAttrStorage;

} // namespace detail
class AffineMapAttr : public ::mlir::Attribute::AttrBase<AffineMapAttr, ::mlir::Attribute, detail::AffineMapAttrStorage, ::mlir::MemRefLayoutAttrInterface::Trait, ::mlir::OpAsmAttrInterface::Trait> {
public:
  using Base::Base;
  using ValueType = AffineMap;
  AffineMap getAffineMap() const { return getValue(); }

  //===------------------------------------------------------------------===//
  // OpAsmAttrInterface Methods
  //===------------------------------------------------------------------===//

  /// Get a name to use when generating an alias for this attribute.
  ::mlir::OpAsmAliasResult getAlias(::llvm::raw_ostream &os) const {
    os << "map";
    return ::mlir::OpAsmAliasResult::OverridableAlias;
  }
  static constexpr ::llvm::StringLiteral name = "builtin.affine_map";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static AffineMapAttr get(AffineMap value);
  AffineMap getValue() const;
};
namespace detail {

struct ArrayAttrStorage;

} // namespace detail
class ArrayAttr : public ::mlir::Attribute::AttrBase<ArrayAttr, ::mlir::Attribute, detail::ArrayAttrStorage> {
public:
  using Base::Base;
    using ValueType = ArrayRef<Attribute>;

    /// Return the element at the given index.
    Attribute operator[](unsigned idx) const {
      assert(idx < size() && "index out of bounds");
      return getValue()[idx];
    }

    /// Support range iteration.
    using iterator = llvm::ArrayRef<Attribute>::iterator;
    iterator begin() const { return getValue().begin(); }
    iterator end() const { return getValue().end(); }
    size_t size() const { return getValue().size(); }
    bool empty() const { return size() == 0; }

  private:
    /// Class for underlying value iterator support.
    template <typename AttrTy>
    class attr_value_iterator final
        : public llvm::mapped_iterator<ArrayAttr::iterator,
                                       AttrTy (*)(Attribute)> {
    public:
      explicit attr_value_iterator(ArrayAttr::iterator it)
          : llvm::mapped_iterator<ArrayAttr::iterator, AttrTy (*)(Attribute)>(
                it, [](Attribute attr) { return ::llvm::cast<AttrTy>(attr); }) {}
      AttrTy operator*() const { return ::llvm::cast<AttrTy>(*this->I); }
    };

  public:
    template <typename AttrTy>
    iterator_range<attr_value_iterator<AttrTy>> getAsRange() const {
      return llvm::make_range(attr_value_iterator<AttrTy>(begin()),
                              attr_value_iterator<AttrTy>(end()));
    }
    template <typename AttrTy,
              typename UnderlyingTy = typename AttrTy::ValueType>
    auto getAsValueRange() const {
      return llvm::map_range(getAsRange<AttrTy>(), [](AttrTy attr) {
        return static_cast<UnderlyingTy>(attr.getValue());
      });
    }
  static constexpr ::llvm::StringLiteral name = "builtin.array";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static ArrayAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<Attribute> value);
  ::llvm::ArrayRef<Attribute> getValue() const;
};
namespace detail {

struct DenseArrayAttrStorage;

} // namespace detail
class DenseArrayAttr : public ::mlir::Attribute::AttrBase<DenseArrayAttr, ::mlir::Attribute, detail::DenseArrayAttrStorage, ::mlir::BlobAttr::Trait> {
public:
  using Base::Base;
  /// Get the number of elements in the array.
  int64_t size() const { return getSize(); }
  /// Return true if there are no elements in the dense array.
  bool empty() const { return !size(); }
  /// BlobAttrInterface method.
  ArrayRef<char> getData() {
    return getRawData();
  }
  static constexpr ::llvm::StringLiteral name = "builtin.dense_array";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static DenseArrayAttr get(::mlir::MLIRContext *context, Type elementType, int64_t size, ::llvm::ArrayRef<char> rawData);
  static DenseArrayAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, Type elementType, int64_t size, ::llvm::ArrayRef<char> rawData);
  static DenseArrayAttr get(Type elementType, unsigned size, ArrayRef<char> rawData);
  static DenseArrayAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, unsigned size, ArrayRef<char> rawData);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, int64_t size, ::llvm::ArrayRef<char> rawData);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, int64_t size, ::llvm::ArrayRef<char> rawData);
  Type getElementType() const;
  int64_t getSize() const;
  ::llvm::ArrayRef<char> getRawData() const;
};
class DenseIntOrFPElementsAttr : public ::mlir::Attribute::AttrBase<DenseIntOrFPElementsAttr, DenseElementsAttr, detail::DenseIntOrFPElementsAttrStorage, ::mlir::TypedAttr::Trait, ::mlir::ElementsAttr::Trait> {
public:
  using Base::Base;
    using DenseElementsAttr::empty;
    using DenseElementsAttr::getNumElements;
    using DenseElementsAttr::getElementType;
    using DenseElementsAttr::getValues;
    using DenseElementsAttr::isSplat;
    using DenseElementsAttr::size;
    using DenseElementsAttr::value_begin;

    /// The set of data types that can be iterated by this attribute.
    using ContiguousIterableTypesT = std::tuple<
      // Integer types.
      uint8_t, uint16_t, uint32_t, uint64_t,
      int8_t, int16_t, int32_t, int64_t,
      short, unsigned short, int, unsigned, long, unsigned long,
      std::complex<uint8_t>, std::complex<uint16_t>, std::complex<uint32_t>,
      std::complex<uint64_t>,
      std::complex<int8_t>, std::complex<int16_t>, std::complex<int32_t>,
      std::complex<int64_t>,
      // Float types.
      float, double, std::complex<float>, std::complex<double>
    >;
    using NonContiguousIterableTypesT = std::tuple<
      Attribute,
      // Integer types.
      APInt, bool, std::complex<APInt>,
      // Float types.
      APFloat, std::complex<APFloat>
    >;

    /// Provide a `try_value_begin_impl` to enable iteration within
    /// ElementsAttr.
    template <typename T>
    auto try_value_begin_impl(OverloadToken<T>) const {
      return try_value_begin<T>();
    }

    /// Convert endianess of input ArrayRef for big-endian(BE) machines. All of
    /// the elements of `inRawData` has `type`. If `inRawData` is little endian
    /// (LE), it is converted to big endian (BE). Conversely, if `inRawData` is
    /// BE, converted to LE.
    static void
    convertEndianOfArrayRefForBEmachine(ArrayRef<char> inRawData,
                                        MutableArrayRef<char> outRawData,
                                        ShapedType type);

    /// Convert endianess of input for big-endian(BE) machines. The number of
    /// elements of `inRawData` is `numElements`, and each element has
    /// `elementBitWidth` bits. If `inRawData` is little endian (LE), it is
    /// converted to big endian (BE) and saved in `outRawData`. Conversely, if
    /// `inRawData` is BE, converted to LE.
    static void convertEndianOfCharForBEmachine(const char *inRawData,
                                                char *outRawData,
                                                size_t elementBitWidth,
                                                size_t numElements);

  protected:
    friend DenseElementsAttr;

    /// Constructs a dense elements attribute from an array of raw APFloat
    /// values. Each APFloat value is expected to have the same bitwidth as the
    /// element type of 'type'. 'type' must be a vector or tensor with static
    /// shape.
    ///
    /// If the `values` array only has a single element, then this constructs
    /// splat of that value.
    static DenseElementsAttr getRaw(ShapedType type, size_t storageWidth,
                                    ArrayRef<APFloat> values);

    /// Constructs a dense elements attribute from an array of raw APInt values.
    /// Each APInt value is expected to have the same bitwidth as the element
    /// type of 'type'. 'type' must be a vector or tensor with static shape.
    ///
    /// If the `values` array only has a single element, then this constructs
    /// splat of that value.
    static DenseElementsAttr getRaw(ShapedType type, size_t storageWidth,
                                    ArrayRef<APInt> values);

    /// Get or create a new dense elements attribute instance with the given raw
    /// data buffer. 'type' must be a vector or tensor with static shape.
    ///
    /// If the `values` array only has a single element, then this constructs
    /// splat of that value.
    static DenseElementsAttr getRaw(ShapedType type, ArrayRef<char> data);

    /// Overload of the raw 'get' method that asserts that the given type is of
    /// complex type. This method is used to verify type invariants that the
    /// templatized 'get' method cannot.
    static DenseElementsAttr getRawComplex(ShapedType type, ArrayRef<char> data,
                                           int64_t dataEltSize, bool isInt,
                                           bool isSigned);

    /// Overload of the raw 'get' method that asserts that the given type is of
    /// integer or floating-point type. This method is used to verify type
    /// invariants that the templatized 'get' method cannot.
    static DenseElementsAttr getRawIntOrFloat(ShapedType type,
                                              ArrayRef<char> data,
                                              int64_t dataEltSize, bool isInt,
                                              bool isSigned);
  public:
  static constexpr ::llvm::StringLiteral name = "builtin.dense_int_or_fp_elements";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
};
class DenseStringElementsAttr : public ::mlir::Attribute::AttrBase<DenseStringElementsAttr, DenseElementsAttr, detail::DenseStringElementsAttrStorage, ::mlir::TypedAttr::Trait, ::mlir::ElementsAttr::Trait> {
public:
  using Base::Base;
    using DenseElementsAttr::empty;
    using DenseElementsAttr::getNumElements;
    using DenseElementsAttr::getElementType;
    using DenseElementsAttr::getValues;
    using DenseElementsAttr::isSplat;
    using DenseElementsAttr::size;
    using DenseElementsAttr::value_begin;

    /// The set of data types that can be iterated by this attribute.
    using ContiguousIterableTypesT = std::tuple<StringRef>;
    using NonContiguousIterableTypesT = std::tuple<Attribute>;

    /// Provide a `try_value_begin_impl` to enable iteration within
    /// ElementsAttr.
    template <typename T>
    auto try_value_begin_impl(OverloadToken<T>) const {
      return try_value_begin<T>();
    }

  protected:
    friend DenseElementsAttr;

  public:
  static constexpr ::llvm::StringLiteral name = "builtin.dense_string_elements";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static DenseStringElementsAttr get(ShapedType type, ArrayRef<StringRef> values);
};
namespace detail {

struct DenseResourceElementsAttrStorage;

} // namespace detail
class DenseResourceElementsAttr : public ::mlir::Attribute::AttrBase<DenseResourceElementsAttr, ::mlir::Attribute, detail::DenseResourceElementsAttrStorage, ::mlir::TypedAttr::Trait, ::mlir::ElementsAttr::Trait, ::mlir::BlobAttr::Trait> {
public:
  using Base::Base;
  /// BlobAttrInterface method.
  ArrayRef<char> getData();
  static constexpr ::llvm::StringLiteral name = "builtin.dense_resource_elements";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static DenseResourceElementsAttr get(ShapedType type, DenseResourceElementsHandle handle);
  static DenseResourceElementsAttr get(ShapedType type, StringRef blobName, AsmResourceBlob blob);
  ShapedType getType() const;
  DenseResourceElementsHandle getRawHandle() const;
};
namespace detail {

struct DictionaryAttrStorage;

} // namespace detail
class DictionaryAttr : public ::mlir::Attribute::AttrBase<DictionaryAttr, ::mlir::Attribute, detail::DictionaryAttrStorage> {
public:
  using Base::Base;
    using ValueType = ArrayRef<NamedAttribute>;

    /// Construct a dictionary with an array of values that is known to already
    /// be sorted by name and uniqued.
    static DictionaryAttr getWithSorted(MLIRContext *context,
                                        ArrayRef<NamedAttribute> value);

    /// Return the specified attribute if present, null otherwise.
    Attribute get(StringRef name) const;
    Attribute get(StringAttr name) const;

    /// Return the specified named attribute if present, std::nullopt otherwise.
    std::optional<NamedAttribute> getNamed(StringRef name) const;
    std::optional<NamedAttribute> getNamed(StringAttr name) const;

    /// Return whether the specified attribute is present.
    bool contains(StringRef name) const;
    bool contains(StringAttr name) const;

    /// Support range iteration.
    using iterator = llvm::ArrayRef<NamedAttribute>::iterator;
    iterator begin() const;
    iterator end() const;
    bool empty() const { return size() == 0; }
    size_t size() const;

    /// Sorts the NamedAttributes in the array ordered by name as expected by
    /// getWithSorted and returns whether the values were sorted.
    /// Requires: uniquely named attributes.
    static bool sort(ArrayRef<NamedAttribute> values,
                     SmallVectorImpl<NamedAttribute> &storage);

    /// Sorts the NamedAttributes in the array ordered by name as expected by
    /// getWithSorted in place on an array and returns whether the values needed
    /// to be sorted.
    /// Requires: uniquely named attributes.
    static bool sortInPlace(SmallVectorImpl<NamedAttribute> &array);

    /// Returns an entry with a duplicate name in `array`, if it exists, else
    /// returns std::nullopt. If `isSorted` is true, the array is assumed to be
    /// sorted else it will be sorted in place before finding the duplicate entry.
    static std::optional<NamedAttribute>
    findDuplicate(SmallVectorImpl<NamedAttribute> &array, bool isSorted);

    /// Return the specified attribute if present and is an instance of
    /// `AttrClass`, null otherwise.
    template<typename AttrClass, typename NameClass>
    AttrClass getAs(NameClass &&name) const {
      return llvm::dyn_cast_or_null<AttrClass>(
               get(std::forward<NameClass>(name)));
    }

  private:
    /// Return empty dictionary.
    static DictionaryAttr getEmpty(MLIRContext *context);

    /// Return empty dictionary. This is a special variant of the above method
    /// that is used by the MLIRContext to cache the empty dictionary instance.
    static DictionaryAttr getEmptyUnchecked(MLIRContext *context);

    /// Allow access to `getEmptyUnchecked`.
    friend MLIRContext;

  public:
  static constexpr ::llvm::StringLiteral name = "builtin.dictionary";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static DictionaryAttr get(::mlir::MLIRContext *context, ArrayRef<NamedAttribute> value = {});
  ::llvm::ArrayRef<NamedAttribute> getValue() const;
};
namespace detail {

struct FloatAttrStorage;

} // namespace detail
class FloatAttr : public ::mlir::Attribute::AttrBase<FloatAttr, ::mlir::Attribute, detail::FloatAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  using ValueType = APFloat;

  /// This function is used to convert the value to a double, even if it loses
  /// precision.
  double getValueAsDouble() const;
  static double getValueAsDouble(APFloat val);
  static constexpr ::llvm::StringLiteral name = "builtin.float";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static FloatAttr get(Type type, const APFloat &value);
  static FloatAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type type, const APFloat &value);
  static FloatAttr get(Type type, double value);
  static FloatAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type type, double value);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type type, ::llvm::APFloat value);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type type, ::llvm::APFloat value);
  ::mlir::Type getType() const;
  ::llvm::APFloat getValue() const;
};
namespace detail {

struct IntegerAttrStorage;

} // namespace detail
class IntegerAttr : public ::mlir::Attribute::AttrBase<IntegerAttr, ::mlir::Attribute, detail::IntegerAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
    using ValueType = APInt;

    /// Return the integer value as a 64-bit int. The attribute must be a
    /// signless integer.
    // TODO: Change callers to use getValue instead.
    int64_t getInt() const;
    /// Return the integer value as a signed 64-bit int. The attribute must be
    /// a signed integer.
    int64_t getSInt() const;
    /// Return the integer value as a unsigned 64-bit int. The attribute must be
    /// an unsigned integer.
    uint64_t getUInt() const;

    /// Return the value as an APSInt which carries the signed from the type of
    /// the attribute.  This traps on signless integers types!
    APSInt getAPSInt() const;

  private:
    /// Return a boolean attribute. This is a special variant of the `get`
    /// method that is used by the MLIRContext to cache the boolean IntegerAttr
    /// instances.
    static BoolAttr getBoolAttrUnchecked(IntegerType type, bool value);

    /// Allow access to `getBoolAttrUnchecked`.
    friend MLIRContext;

  public:
  static constexpr ::llvm::StringLiteral name = "builtin.integer";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static IntegerAttr get(Type type, const APInt &value);
  static IntegerAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type type, const APInt &value);
  static IntegerAttr get(::mlir::MLIRContext *context, const APSInt &value);
  static IntegerAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, const APSInt &value);
  static IntegerAttr get(Type type, int64_t value);
  static IntegerAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type type, int64_t value);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type type, ::llvm::APInt value);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type type, ::llvm::APInt value);
  ::mlir::Type getType() const;
  ::llvm::APInt getValue() const;
};
namespace detail {

struct IntegerSetAttrStorage;

} // namespace detail
class IntegerSetAttr : public ::mlir::Attribute::AttrBase<IntegerSetAttr, ::mlir::Attribute, detail::IntegerSetAttrStorage, ::mlir::OpAsmAttrInterface::Trait> {
public:
  using Base::Base;
  using ValueType = IntegerSet;

  //===------------------------------------------------------------------===//
  // OpAsmAttrInterface Methods
  //===------------------------------------------------------------------===//

  /// Get a name to use when generating an alias for this attribute.
  ::mlir::OpAsmAliasResult getAlias(::llvm::raw_ostream &os) const {
    os << "set";
    return ::mlir::OpAsmAliasResult::OverridableAlias;
  }
  static constexpr ::llvm::StringLiteral name = "builtin.integer_set";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static IntegerSetAttr get(IntegerSet value);
  IntegerSet getValue() const;
};
namespace detail {

struct OpaqueAttrStorage;

} // namespace detail
class OpaqueAttr : public ::mlir::Attribute::AttrBase<OpaqueAttr, ::mlir::Attribute, detail::OpaqueAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.opaque";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static OpaqueAttr get(StringAttr dialect, StringRef attrData, Type type);
  static OpaqueAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr dialect, StringRef attrData, Type type);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr dialectNamespace, ::llvm::StringRef attrData, ::mlir::Type type);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr dialectNamespace, ::llvm::StringRef attrData, ::mlir::Type type);
  StringAttr getDialectNamespace() const;
  ::llvm::StringRef getAttrData() const;
  ::mlir::Type getType() const;
};
namespace detail {

struct SparseElementsAttrStorage;

} // namespace detail
class SparseElementsAttr : public ::mlir::Attribute::AttrBase<SparseElementsAttr, ::mlir::Attribute, detail::SparseElementsAttrStorage, ::mlir::TypedAttr::Trait, ::mlir::ElementsAttr::Trait> {
public:
  using Base::Base;
    /// The set of data types that can be iterated by this attribute.
    // FIXME: Realistically, SparseElementsAttr could use ElementsAttr for the
    // value storage. This would mean dispatching to `values` when accessing
    // values. For now, we just add the types that can be iterated by
    // DenseElementsAttr.
    using NonContiguousIterableTypesT = std::tuple<
      Attribute,
      // Integer types.
      APInt, bool, uint8_t, uint16_t, uint32_t, uint64_t,
      int8_t, int16_t, int32_t, int64_t,
      short, unsigned short, int, unsigned, long, unsigned long,
      std::complex<APInt>, std::complex<uint8_t>, std::complex<uint16_t>,
      std::complex<uint32_t>, std::complex<uint64_t>, std::complex<int8_t>,
      std::complex<int16_t>, std::complex<int32_t>, std::complex<int64_t>,
      // Float types.
      APFloat, float, double,
      std::complex<APFloat>, std::complex<float>, std::complex<double>,
      // String types.
      StringRef
    >;
    using ElementsAttr::Trait<SparseElementsAttr>::getValues;
    using ElementsAttr::Trait<SparseElementsAttr>::value_begin;

    template <typename T>
    using iterator =
        llvm::mapped_iterator<typename decltype(llvm::seq<ptrdiff_t>(0, 0))::iterator,
                              std::function<T(ptrdiff_t)>>;

    /// Provide a `try_value_begin_impl` to enable iteration within
    /// ElementsAttr.
    template <typename T>
    FailureOr<iterator<T>> try_value_begin_impl(OverloadToken<T>) const;

  private:
    /// Get a zero APFloat for the given sparse attribute.
    APFloat getZeroAPFloat() const;

    /// Get a zero APInt for the given sparse attribute.
    APInt getZeroAPInt() const;

    /// Get a zero attribute for the given sparse attribute.
    Attribute getZeroAttr() const;

    /// Utility methods to generate a zero value of some type 'T'. This is used
    /// by the 'iterator' class.
    /// Get a zero for a given attribute type.
    template <typename T>
    std::enable_if_t<std::is_base_of<Attribute, T>::value, T>
    getZeroValue() const {
      return ::llvm::cast<T>(getZeroAttr());
    }
    /// Get a zero for an APInt.
    template <typename T>
    std::enable_if_t<std::is_same<APInt, T>::value, T>
    getZeroValue() const {
      return getZeroAPInt();
    }
    template <typename T>
    std::enable_if_t<std::is_same<std::complex<APInt>, T>::value, T>
    getZeroValue() const {
      APInt intZero = getZeroAPInt();
      return {intZero, intZero};
    }
    /// Get a zero for an APFloat.
    template <typename T>
    std::enable_if_t<std::is_same<APFloat, T>::value, T>
    getZeroValue() const {
      return getZeroAPFloat();
    }
    template <typename T>
    std::enable_if_t<std::is_same<std::complex<APFloat>, T>::value, T>
    getZeroValue() const {
      APFloat floatZero = getZeroAPFloat();
      return {floatZero, floatZero};
    }

    /// Get a zero for an C++ integer, float, StringRef, or complex type.
    template <typename T>
    std::enable_if_t<std::numeric_limits<T>::is_integer ||
                         DenseElementsAttr::is_valid_cpp_fp_type<T>::value ||
                         std::is_same<T, StringRef>::value ||
                         (detail::is_complex_t<T>::value &&
                          !llvm::is_one_of<T, std::complex<APInt>,
                                           std::complex<APFloat>>::value),
                     T>
    getZeroValue() const {
      return T();
    }

    /// Flatten, and return, all of the sparse indices in this attribute in
    /// row-major order.
    SmallVector<ptrdiff_t> getFlattenedSparseIndices() const;

  public:
  static constexpr ::llvm::StringLiteral name = "builtin.sparse_elements";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static SparseElementsAttr get(ShapedType type, DenseElementsAttr indices, DenseElementsAttr values);
  static SparseElementsAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ShapedType type, DenseElementsAttr indices, DenseElementsAttr values);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ShapedType type, DenseIntElementsAttr indices, DenseElementsAttr values);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ShapedType type, DenseIntElementsAttr indices, DenseElementsAttr values);
  ShapedType getType() const;
  DenseIntElementsAttr getIndices() const;
  DenseElementsAttr getValues() const;
};
namespace detail {

struct StridedLayoutAttrStorage;

} // namespace detail
class StridedLayoutAttr : public ::mlir::Attribute::AttrBase<StridedLayoutAttr, ::mlir::Attribute, detail::StridedLayoutAttrStorage, ::mlir::MemRefLayoutAttrInterface::Trait> {
public:
  using Base::Base;
  /// Print the attribute to the given output stream.
  void print(raw_ostream &os) const;

  /// Returns true if this layout is static, i.e. the strides and offset all
  /// have a known value > 0.
  bool hasStaticLayout() const;
  static constexpr ::llvm::StringLiteral name = "builtin.strided_layout";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  using ::mlir::MemRefLayoutAttrInterface::Trait<StridedLayoutAttr>::isIdentity;
  static StridedLayoutAttr get(::mlir::MLIRContext *context, int64_t offset, ::llvm::ArrayRef<int64_t> strides);
  static StridedLayoutAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, int64_t offset, ::llvm::ArrayRef<int64_t> strides);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int64_t offset, ::llvm::ArrayRef<int64_t> strides);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int64_t offset, ::llvm::ArrayRef<int64_t> strides);
  int64_t getOffset() const;
  ::llvm::ArrayRef<int64_t> getStrides() const;
  ::mlir::AffineMap getAffineMap() const;
  ::llvm::LogicalResult verifyLayout(::llvm::ArrayRef<int64_t> shape, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  ::llvm::LogicalResult getStridesAndOffset(::llvm::ArrayRef<int64_t> shape, ::llvm::SmallVectorImpl<int64_t>&strides, int64_t&offset) const;
};
class StringAttr : public ::mlir::Attribute::AttrBase<StringAttr, ::mlir::Attribute, detail::StringAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
    using ValueType = StringRef;

    /// If the value of this string is prefixed with a dialect namespace,
    /// returns the dialect corresponding to that namespace if it is loaded,
    /// nullptr otherwise. For example, the string `llvm.fastmathflags` would
    /// return the LLVM dialect, assuming it is loaded in the context.
    Dialect *getReferencedDialect() const;

    /// Enable conversion to StringRef.
    operator StringRef() const { return getValue(); }

    /// Returns the underlying string value
    StringRef strref() const { return getValue(); }

    /// Convert the underling value to an std::string.
    std::string str() const { return getValue().str(); }

    /// Return a pointer to the start of the string data.
    const char *data() const { return getValue().data(); }

    /// Return the number of bytes in this string.
    size_t size() const { return getValue().size(); }

    /// Return whether the string is empty.
    bool empty() const { return getValue().empty(); }

    /// Iterate over the underlying string data.
    StringRef::iterator begin() const { return getValue().begin(); }
    StringRef::iterator end() const { return getValue().end(); }

    /// Compare the underlying string value to the one in `rhs`.
    int compare(StringAttr rhs) const {
      if (*this == rhs)
        return 0;
      return getValue().compare(rhs.getValue());
    }

  private:
    /// Return an empty StringAttr with NoneType type. This is a special variant
    /// of the `get` method that is used by the MLIRContext to cache the
    /// instance.
    static StringAttr getEmptyStringAttrUnchecked(MLIRContext *context);
    friend MLIRContext;
  public:
  static constexpr ::llvm::StringLiteral name = "builtin.string";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static StringAttr get(const Twine &bytes, Type type);
  static StringAttr get(::mlir::MLIRContext *context, const Twine &bytes);
  static StringAttr get(::mlir::MLIRContext *context);
  ::llvm::StringRef getValue() const;
  ::mlir::Type getType() const;
};
namespace detail {

struct SymbolRefAttrStorage;

} // namespace detail
class SymbolRefAttr : public ::mlir::Attribute::AttrBase<SymbolRefAttr, ::mlir::Attribute, detail::SymbolRefAttrStorage> {
public:
  using Base::Base;
  static SymbolRefAttr get(MLIRContext *ctx, StringRef value,
                           ArrayRef<FlatSymbolRefAttr> nestedRefs);
  /// Convenience getters for building a SymbolRefAttr with no path, which is
  /// known to produce a FlatSymbolRefAttr.
  static FlatSymbolRefAttr get(StringAttr value);
  static FlatSymbolRefAttr get(MLIRContext *ctx, StringRef value);

  /// Convenience getter for buliding a SymbolRefAttr based on an operation
  /// that implements the SymbolTrait.
  static FlatSymbolRefAttr get(Operation *symbol);

  /// Returns the name of the fully resolved symbol, i.e. the leaf of the
  /// reference path.
  StringAttr getLeafReference() const;
  static constexpr ::llvm::StringLiteral name = "builtin.symbol_ref";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static SymbolRefAttr get(StringAttr rootReference, ArrayRef<FlatSymbolRefAttr> nestedReferences);
  StringAttr getRootReference() const;
  ::llvm::ArrayRef<FlatSymbolRefAttr> getNestedReferences() const;
};
namespace detail {

struct TypeAttrStorage;

} // namespace detail
class TypeAttr : public ::mlir::Attribute::AttrBase<TypeAttr, ::mlir::Attribute, detail::TypeAttrStorage> {
public:
  using Base::Base;
  using ValueType = Type;static constexpr ::llvm::StringLiteral name = "builtin.type";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static TypeAttr get(Type type);
  Type getValue() const;
};
class UnitAttr : public ::mlir::Attribute::AttrBase<UnitAttr, ::mlir::Attribute, ::mlir::AttributeStorage> {
public:
  using Base::Base;
  static UnitAttr get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "builtin.unit";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
};

} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::AffineMapAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ArrayAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::DenseArrayAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::DenseIntOrFPElementsAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::DenseStringElementsAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::DenseResourceElementsAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::DictionaryAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::FloatAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::IntegerAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::IntegerSetAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::OpaqueAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::SparseElementsAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::StridedLayoutAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::StringAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::SymbolRefAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::UnitAttr)

#endif // GET_ATTRDEF_CLASSES

