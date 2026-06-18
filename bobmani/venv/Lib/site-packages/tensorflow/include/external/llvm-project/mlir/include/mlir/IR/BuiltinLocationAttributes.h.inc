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

/// A callsite source location
/// Syntax:
/// 
///     ```
///     callsite-location ::= `callsite` `(` location `at` location `)`
///     ```
/// 
///     An instance of this location allows for representing a directed stack of
///     location usages. This connects a location of a `callee` with the location
///     of a `caller`.
/// 
///     Example:
/// 
///     ```mlir
///     loc(callsite("foo" at "mysource.cc":10:8))
///     ```
class CallSiteLoc;
/// A file:line:column source location range
/// Syntax:
/// 
///     ```
///     filelinecol-location ::= string-literal `:` integer-literal `:`
///                              integer-literal
///                              (`to` (integer-literal ?) `:` integer-literal ?)
///     ```
/// 
///     An instance of this location represents a tuple of file, start and end line
///     number, and start and end column number. It allows for the following
///     configurations:
/// 
///     *   A single file line location: `file:line`;
///     *   A single file line col location: `file:line:column`;
///     *   A single line range: `file:line:column to :column`;
///     *   A single file range: `file:line:column to line:column`;
/// 
///     Example:
/// 
///     ```mlir
///     loc("mysource.cc":10:8 to 12:18)
///     ```
class FileLineColRange;
/// A tuple of other source locations
/// Syntax:
/// 
///     ```
///     fusion-metadata ::= `<` attribute-value `>`
///     fused-location ::= `fused` fusion-metadata? `[` (location (`,` location)* )? `]`
///     ```
/// 
///     An instance of a `fused` location represents a grouping of several other
///     source locations, with optional metadata that describes the context of the
///     fusion. There are many places within a compiler in which several constructs
///     may be fused together, e.g. pattern rewriting, that normally result partial
///     or even total loss of location information. With `fused` locations, this is
///     a non-issue.
/// 
///     Example:
/// 
///     ```mlir
///     loc(fused["mysource.cc":10:8, "mysource.cc":22:8])
///     loc(fused<"CSE">["mysource.cc":10:8, "mysource.cc":22:8])
///     ```
class FusedLoc;
/// A named source location
/// Syntax:
/// 
///     ```
///     name-location ::= string-literal (`(` location `)`)?
///     ```
/// 
///     An instance of this location allows for attaching a name to a child location.
///     This can be useful for representing the locations of variable, or node,
///     definitions.
/// 
///     #### Example:
/// 
///     ```mlir
///     loc("CSE"("mysource.cc":10:8))
///     ```
class NameLoc;
/// An opaque source location
/// An instance of this location essentially contains a pointer to some data
///     structure that is external to MLIR and an optional location that can be used
///     if the first one is not suitable. Since it contains an external structure,
///     only the optional location is used during serialization.
/// 
///     #### Example:
/// 
///     ```mlir
///     %0 = "example.operation"() : () -> i32 loc("mysource")
///     %1 = arith.constant 4 : index loc(callsite("mysum" at "mysource.cc":10:8))
///     ```
class OpaqueLoc;
/// An unspecified source location
/// Syntax:
/// 
///     ```
///     unknown-location ::= `?`
///     ```
/// 
///     Source location information is an extremely integral part of the MLIR
///     infrastructure. As such, location information is always present in the IR,
///     and must explicitly be set to unknown. Thus, an instance of the `unknown`
///     location represents an unspecified source location.
/// 
///     Example:
/// 
///     ```mlir
///     loc(?)
///     ```
class UnknownLoc;
namespace detail {

struct CallSiteLocAttrStorage;

} // namespace detail
class CallSiteLoc : public ::mlir::Attribute::AttrBase<CallSiteLoc, ::mlir::LocationAttr, detail::CallSiteLocAttrStorage, ::mlir::AttributeTrait::IsLocation> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.call_site_loc";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static CallSiteLoc get(Location callee, Location caller);
  static CallSiteLoc get(Location name, ArrayRef<Location> frames);
  Location getCallee() const;
  Location getCaller() const;
};
class FileLineColRange : public ::mlir::Attribute::AttrBase<FileLineColRange, ::mlir::LocationAttr, detail::FileLineColRangeAttrStorage, ::mlir::AttributeTrait::IsLocation> {
public:
  using Base::Base;
  ::mlir::StringAttr getFilename() const;
  unsigned getStartLine() const;
  unsigned getStartColumn() const;
  unsigned getEndColumn() const;
  unsigned getEndLine() const;
  static constexpr ::llvm::StringLiteral name = "builtin.file_line_range";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static FileLineColRange get(StringAttr filename);
  static FileLineColRange get(StringAttr filename, unsigned line);
  static FileLineColRange get(StringAttr filename, unsigned line, unsigned column);
  static FileLineColRange get(::mlir::MLIRContext *context, ::llvm::StringRef filename, unsigned start_line, unsigned start_column);
  static FileLineColRange get(::mlir::StringAttr filename, unsigned line, unsigned start_column, unsigned end_column);
  static FileLineColRange get(::mlir::StringAttr filename, unsigned start_line, unsigned start_column, unsigned end_line, unsigned end_column);
  static FileLineColRange get(::mlir::MLIRContext *context, ::llvm::StringRef filename, unsigned start_line, unsigned start_column, unsigned end_line, unsigned end_column);
};
namespace detail {

struct FusedLocAttrStorage;

} // namespace detail
class FusedLoc : public ::mlir::Attribute::AttrBase<FusedLoc, ::mlir::LocationAttr, detail::FusedLocAttrStorage, ::mlir::AttributeTrait::IsLocation> {
public:
  using Base::Base;
  static Location get(ArrayRef<Location> locs, Attribute metadata,
                      MLIRContext *context);
  static Location get(MLIRContext *context, ArrayRef<Location> locs) {
    return get(locs, Attribute(), context);
  }
  static constexpr ::llvm::StringLiteral name = "builtin.fused_loc";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static FusedLoc get(::mlir::MLIRContext *context, ::llvm::ArrayRef<Location> locations, Attribute metadata);
  ::llvm::ArrayRef<Location> getLocations() const;
  Attribute getMetadata() const;
};
namespace detail {

struct NameLocAttrStorage;

} // namespace detail
class NameLoc : public ::mlir::Attribute::AttrBase<NameLoc, ::mlir::LocationAttr, detail::NameLocAttrStorage, ::mlir::AttributeTrait::IsLocation> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.name_loc";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static NameLoc get(StringAttr name, Location childLoc);
  static NameLoc get(StringAttr name);
  StringAttr getName() const;
  Location getChildLoc() const;
};
namespace detail {

struct OpaqueLocAttrStorage;

} // namespace detail
class OpaqueLoc : public ::mlir::Attribute::AttrBase<OpaqueLoc, ::mlir::LocationAttr, detail::OpaqueLocAttrStorage, ::mlir::AttributeTrait::IsLocation> {
public:
  using Base::Base;
  /// Returns an instance of opaque location which contains a given pointer to
  /// an object. The corresponding MLIR location is set to UnknownLoc.
  template <typename T>
  static OpaqueLoc get(T underlyingLocation, MLIRContext *context);

  /// Returns an instance of opaque location which contains a given pointer to
  /// an object and an additional MLIR location.
  template <typename T>
  static OpaqueLoc get(T underlyingLocation, Location fallbackLocation) {
    return get(reinterpret_cast<uintptr_t>(underlyingLocation),
               TypeID::get<T>(), fallbackLocation);
  }

  /// Returns a pointer to some data structure that opaque location stores.
  template <typename T> static T getUnderlyingLocation(Location location) {
    assert(isa<T>(location));
    return reinterpret_cast<T>(
        mlir::cast<mlir::OpaqueLoc>(static_cast<LocationAttr>(location))
            .getUnderlyingLocation());
  }

  /// Returns a pointer to some data structure that opaque location stores.
  /// Returns nullptr if provided location is not opaque location or if it
  /// contains a pointer of different type.
  template <typename T>
  static T getUnderlyingLocationOrNull(Location location) {
    return isa<T>(location)
              ? reinterpret_cast<T>(mlir::cast<mlir::OpaqueLoc>(
                                        static_cast<LocationAttr>(location))
                                        .getUnderlyingLocation())
              : T(nullptr);
  }

  /// Checks whether provided location is opaque location and contains a
  /// pointer to an object of particular type.
  template <typename T> static bool isa(Location location) {
    auto opaque_loc =
        mlir::dyn_cast<OpaqueLoc>(static_cast<LocationAttr>(location));
    return opaque_loc && opaque_loc.getUnderlyingTypeID() == TypeID::get<T>();
  }
  static constexpr ::llvm::StringLiteral name = "builtin.opaque_loc";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static OpaqueLoc get(uintptr_t underlyingLocation, TypeID underlyingTypeID, Location fallbackLocation);
  uintptr_t getUnderlyingLocation() const;
  TypeID getUnderlyingTypeID() const;
  Location getFallbackLocation() const;
};
class UnknownLoc : public ::mlir::Attribute::AttrBase<UnknownLoc, ::mlir::LocationAttr, ::mlir::AttributeStorage, ::mlir::AttributeTrait::IsLocation> {
public:
  using Base::Base;
  static UnknownLoc get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "builtin.unknown_loc";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
};

} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::CallSiteLoc)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::FileLineColRange)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::FusedLoc)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NameLoc)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::OpaqueLoc)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::UnknownLoc)

#endif // GET_ATTRDEF_CLASSES

