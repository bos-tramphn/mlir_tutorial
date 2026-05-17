#include "ToyToLinalgPass.h"

#include "toy/ToyOps.h"

#include "mlir/Dialect/Arithmetic/IR/Arithmetic.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/IR/AffineMap.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Transforms/DialectConversion.h"

using namespace mlir;
using namespace toy;

namespace {

// TODO: Implement helper function to check if a type is float-like
static bool isFloatLike(Type type) {
  // TODO: Handle ShapedType (tensors)
  // TODO: Handle scalar FloatType
  return false; // Placeholder
}

/// Helper: lower elementwise binary Toy op to linalg.generic
/// This is the core lowering logic that converts Toy operations to Linalg
static LogicalResult lowerPointwiseBinaryOp(
    Operation *op,
    ValueRange inputs,
    PatternRewriter &rewriter,
    function_ref<Value(OpBuilder &, Location, Value, Value)> scalarBuilder) {

  // TODO: Validate that we have exactly 2 inputs (binary operation)
  // If not, return failure()

  // TODO: Get the result type and verify it's a RankedTensorType
  // Hint: Use op->getResult(0).getType().dyn_cast<RankedTensorType>()
  // Also check if the result type is float-like using isFloatLike()
  // If validation fails, return failure()

  // TODO: Get the operation location and tensor rank
  // Hint: Location loc = op->getLoc();
  // Hint: int64_t rank = resultType.getRank();

  // TODO Step 1: Create output tensor using tensor.empty
  // Hint: Use rewriter.create<tensor::EmptyOp>(
  //         loc, resultType.getShape(), resultType.getElementType())

  // TODO Step 2: Create identity indexing maps for inputs and output
  // For elementwise ops, all operands have the same indexing
  // Hint: Use rewriter.getMultiDimIdentityMap(rank) for each map
  // You need 3 maps total: 2 inputs + 1 output
  // Hint: SmallVector<AffineMap, 3> indexingMaps = {...}

  // TODO Step 3: Set all iterator types to "parallel"
  // For elementwise ops, all dimensions are computed independently
  // Hint: SmallVector<mlir::utils::IteratorType, 4> iteratorTypes(
  //         rank, mlir::utils::IteratorType::parallel)

  // TODO Step 4: Create linalg.generic operation
  // This is the main structured operation that will replace the Toy op
  // Hint: auto genericOp = rewriter.create<linalg::GenericOp>(
  //         loc,
  //         resultType,              // result type
  //         inputs,                  // input tensors
  //         ValueRange{initTensor},  // output tensor
  //         indexingMaps,            // how to index each operand
  //         iteratorTypes,           // parallel/reduction iterators
  //         [&](OpBuilder &b, Location loc, ValueRange args) {
  //           // Scalar computation body:
  //           // TODO: Call scalarBuilder to create the scalar computation
  //           // TODO: Yield the result using linalg.yield
  //         });

  // TODO: Replace the original Toy operation with the linalg.generic result
  // Hint: rewriter.replaceOp(op, genericOp.getResult(0))

  // TODO: Return success() when done
  return failure(); // Placeholder
}

/// TODO: Implement pattern to lower toy.add → linalg.generic
struct LowerToyAddPattern : public OpRewritePattern<toy::AddOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(toy::AddOp op,
                                PatternRewriter &rewriter) const override {
    // TODO: Call lowerPointwiseBinaryOp to do the actual lowering
    // Pass the following arguments:
    // 1. op.getOperation() - the operation to lower
    // 2. ValueRange{op.getLhs(), op.getRhs()} - the two operands
    // 3. rewriter - the pattern rewriter
    // 4. A lambda that creates the scalar computation:
    //    [](OpBuilder &b, Location loc, Value lhs, Value rhs) {
    //      return b.create<arith::AddFOp>(loc, lhs, rhs);
    //    }
    // This lambda will be called to generate the body of linalg.generic
    
    return failure(); // Placeholder
  }
};

/// TODO: Implement pattern to lower toy.mul → linalg.generic
struct LowerToyMulPattern : public OpRewritePattern<toy::MulOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(toy::MulOp op,
                                PatternRewriter &rewriter) const override {
    // TODO: Call lowerPointwiseBinaryOp similar to LowerToyAddPattern
    // The only difference: use arith::MulFOp instead of arith::AddFOp
    // in the scalar builder lambda
    
    return failure(); // Placeholder
  }
};

struct ToyToLinalgPass
    : public PassWrapper<ToyToLinalgPass,
                          OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(ToyToLinalgPass)

  StringRef getArgument() const final { return "toy-to-linalg"; }
  StringRef getDescription() const final {
    return "Lower Toy elementwise ops to linalg.generic";
  }

  void getDependentDialects(DialectRegistry &registry) const final {
    registry.insert<
        arith::ArithmeticDialect,
        linalg::LinalgDialect,
        tensor::TensorDialect>();
  }

  void runOnOperation() override {
    // TODO: Create a RewritePatternSet to hold all lowering patterns
    // Hint: RewritePatternSet patterns(&getContext());
    
    // TODO: Add both lowering patterns to the pattern set
    // Hint: patterns.add<LowerToyAddPattern, LowerToyMulPattern>(&getContext());
    
    // TODO: Apply the patterns greedily to transform the IR
    // Hint: Use applyPatternsAndFoldGreedily(getOperation(), std::move(patterns))
    // If it fails, call signalPassFailure()
    
    signalPassFailure(); // Placeholder - remove when implemented
  }
};

} // namespace

std::unique_ptr<mlir::Pass> toy::createToyToLinalgPass() {
  return std::make_unique<ToyToLinalgPass>();
}

void toy::detail::registerToyToLinalgPass() {
  static PassRegistration<ToyToLinalgPass> pass;
  (void)pass;
}
