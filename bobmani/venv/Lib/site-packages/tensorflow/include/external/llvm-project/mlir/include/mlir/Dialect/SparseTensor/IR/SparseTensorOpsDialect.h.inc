/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SparseTensorOps.td                                                   *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::sparse_tensor {

/// The `SparseTensor` dialect supports all the attributes, types,
///     operations, and passes that are required to make sparse tensor
///     types first class citizens within the MLIR compiler infrastructure.
///     The dialect forms a bridge between high-level operations on sparse
///     tensors types and lower-level operations on the actual sparse storage
///     schemes consisting of positions, coordinates, and values. Lower-level
///     support may consist of fully generated code or may be provided by
///     means of a small sparse runtime support library.
/// 
///     The concept of **treating sparsity as a property, not a tedious
///     implementation detail**, by letting a **sparsifier** generate
///     sparse code automatically was pioneered for linear algebra by [Bik96]
///     in MT1 (see https://www.aartbik.com/sparse.php) and formalized
///     to tensor algebra by [Kjolstad17,Kjolstad20] in the Sparse Tensor
///     Algebra Compiler (TACO) project (see http://tensor-compiler.org).
///     Please note that we started to prefer the term "sparsifier" over
///     the also commonly used "sparse compiler" terminology to refer to
///     such a pass to make it clear that the sparsifier pass is not a
///     separate compiler, but should be an integral part of any compiler
///     pipeline that is built with the MLIR compiler infrastructure
/// 
///     The MLIR implementation [Biketal22] closely follows the "sparse
///     iteration theory" that forms the foundation of TACO.  A rewriting
///     rule is applied to each tensor expression in the Linalg dialect
///     (MLIR's tensor index notation) where the sparsity of tensors is
///     indicated using the per-level level-types (e.g., dense, compressed,
///     singleton) together with a specification of the order on the levels
///     (see [Chou18] for an in-depth discussions and possible extensions
///     to these level-types).  Subsequently, a topologically sorted
///     iteration graph, reflecting the required order on coordinates with
///     respect to the levels of each tensor, is constructed to ensure
///     that all tensors are visited in natural level-coordinate order.
///     Next, iteration lattices are constructed for the tensor expression
///     for every index in topological order.  Each iteration lattice point
///     consists of a conjunction of tensor coordinates together with a tensor
///     (sub)expression that needs to be evaluated for that conjunction.
///     Within the lattice, iteration points are ordered according to
///     the way coordinates are exhausted.  As such these iteration
///     lattices drive actual sparse code generation, which consists of
///     a relatively straightforward one-to-one mapping from iteration
///     lattices to combinations of for-loops, while-loops, and if-statements.
///     Sparse tensor outputs that materialize uninitialized are handled with
///     direct insertions if all parallel loops are outermost or insertions
///     that indirectly go through a 1-dimensional access pattern expansion
///     (a.k.a. workspace) where feasible [Gustavson72,Bik96,Kjolstad19].
/// 
///     * [Bik96] Aart J.C. Bik. Compiler Support for Sparse Matrix Computations.
///     PhD thesis, Leiden University, May 1996.
///     * [Biketal22] Aart J.C. Bik, Penporn Koanantakool, Tatiana Shpeisman,
///     Nicolas Vasilache, Bixia Zheng, and Fredrik Kjolstad. Compiler Support
///     for Sparse Tensor Computations in MLIR. ACM Transactions on Architecture
///     and Code Optimization, June, 2022. See: https://dl.acm.org/doi/10.1145/3544559
///     * [Chou18] Stephen Chou, Fredrik Berg Kjolstad, and Saman Amarasinghe.
///     Format Abstraction for Sparse Tensor Algebra Compilers. Proceedings of
///     the ACM on Programming Languages, October 2018.
///     * [Chou20] Stephen Chou, Fredrik Berg Kjolstad, and Saman Amarasinghe.
///     Automatic Generation of Efficient Sparse Tensor Format Conversion Routines.
///     Proceedings of the 41st ACM SIGPLAN Conference on Programming Language
///     Design and Implementation, June, 2020.
///     * [Gustavson72] Fred G. Gustavson. Some basic techniques for solving
///     sparse systems of linear equations. In Sparse Matrices and Their
///     Applications, pages 41–52. Plenum Press, New York, 1972.
///     * [Kjolstad17] Fredrik Berg Kjolstad, Shoaib Ashraf Kamil, Stephen Chou, David
///     Lugato, and Saman Amarasinghe. The Tensor Algebra Compiler. Proceedings of
///     the ACM on Programming Languages, October 2017.
///     * [Kjolstad19] Fredrik Berg Kjolstad, Peter Ahrens, Shoaib Ashraf Kamil,
///     and Saman Amarasinghe. Tensor Algebra Compilation with Workspaces,
///     Proceedings of the IEEE/ACM International Symposium on Code Generation
///     and Optimization, 2019.
///     * [Kjolstad20] Fredrik Berg Kjolstad. Sparse Tensor Algebra Compilation.
///     PhD thesis, MIT, February, 2020.
class SparseTensorDialect : public ::mlir::Dialect {
  explicit SparseTensorDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~SparseTensorDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("sparse_tensor");
  }

  /// Parse an attribute registered to this dialect.
  ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                   ::mlir::Type type) const override;

  /// Print an attribute registered to this dialect.
  void printAttribute(::mlir::Attribute attr,
                      ::mlir::DialectAsmPrinter &os) const override;

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;

  /// Materialize a single constant operation from a given attribute value with
  /// the desired resultant type.
  ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                         ::mlir::Attribute value,
                                         ::mlir::Type type,
                                         ::mlir::Location loc) override;
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::SparseTensorDialect)
