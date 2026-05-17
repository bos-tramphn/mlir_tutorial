#include "ToyToArithPass.h"

#include "toy/ToyOps.h"

#include "mlir/Dialect/Arithmetic/IR/Arithmetic.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

using namespace mlir;
using namespace toy;

namespace {

// TODO: Implement helper function to check if a type is float-like
// Hint: Check if the type (or its element type for shaped types) is a FloatType
static bool isFloatLike(Type type) {
  // TODO: Handle ShapedType (tensors, vectors)
  // - Use type.dyn_cast<ShapedType>() to check if it's a shaped type
  // - If yes, call getElementType() and check if it's FloatType
  // TODO: Handle scalar FloatType
  // - Use type.isa<FloatType>() for scalar floats
  return false; // Placeholder
}

// TODO: Implement pattern to lower toy.add to arith.addf
struct LowerToyAddPattern : public OpRewritePattern<toy::AddOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(toy::AddOp op,
                                PatternRewriter &rewriter) const override {
    // TODO: Get the result type from the operation
    // Hint: Use op.getResult().getType()
    
    // TODO: Verify the result type is float-like using isFloatLike()
    // If not, return failure()
    
    // TODO: Replace the toy.add operation with arith.AddFOp
    // Hint: Use rewriter.replaceOpWithNewOp<arith::AddFOp>(...)
    // Pass: op, resultType, op.getLhs(), op.getRhs()
    
    // TODO: Return success() if replacement succeeds
    return failure(); // Placeholder
  }
};

// TODO: Implement pattern to lower toy.mul to arith.mulf
struct LowerToyMulPattern : public OpRewritePattern<toy::MulOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(toy::MulOp op,
                                PatternRewriter &rewriter) const override {
    // TODO: Get the result type from the operation
    
    // TODO: Verify the result type is float-like
    // If not, return failure()
    
    // TODO: Replace the toy.mul operation with arith.MulFOp
    // Hint: Use rewriter.replaceOpWithNewOp<arith::MulFOp>(...)
    
    // TODO: Return success() if replacement succeeds
    return failure(); // Placeholder
  }
};

struct ToyToArithPass
    : public PassWrapper<ToyToArithPass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(ToyToArithPass)

  StringRef getArgument() const final { return "toy-to-arith"; }
  StringRef getDescription() const final {
    return "Lower Toy arithmetic ops to mlir::arith ops";
  }

  void getDependentDialects(DialectRegistry &registry) const final {
    registry.insert<arith::ArithmeticDialect>();
  }

  void runOnOperation() override {
    // TODO: Get the function operation being transformed
    // Hint: Use getOperation() to get the func::FuncOp
    
    // TODO: Create a RewritePatternSet to hold all lowering patterns
    // Hint: RewritePatternSet patterns(&getContext());
    
    // TODO: Add the lowering patterns to the pattern set
    // Hint: patterns.add<LowerToyAddPattern, LowerToyMulPattern>(&getContext());
    
    // TODO: Apply the patterns greedily to the function
    // Hint: Use applyPatternsAndFoldGreedily(funcOp, std::move(patterns))
    // If it fails, call signalPassFailure()
    
    signalPassFailure(); // Placeholder - remove when implemented
  }
};

} // namespace

std::unique_ptr<mlir::Pass> toy::createToyToArithPass() {
  return std::make_unique<ToyToArithPass>();
}

void toy::detail::registerToyToArithPass() {
  static PassRegistration<ToyToArithPass> pass;
  (void)pass;
}
