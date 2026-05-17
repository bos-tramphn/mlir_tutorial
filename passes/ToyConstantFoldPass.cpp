#include "ToyConstantFoldPass.h"

#include "toy/ToyOps.h"

#include "mlir/Dialect/Arithmetic/IR/Arithmetic.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"

using namespace mlir;
using namespace toy;

namespace {

struct ToyConstantFoldPass
    : public mlir::PassWrapper<ToyConstantFoldPass,
                              mlir::OperationPass<mlir::func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(ToyConstantFoldPass)

  mlir::StringRef getArgument() const final { return "toy-constant-fold"; }
  mlir::StringRef getDescription() const final {
    return "Skeleton pass for Toy constant folding";
  }

  void runOnOperation() override {
    mlir::func::FuncOp funcOp = getOperation();
    (void)funcOp;

    // TODO: Match Toy arithmetic ops such as toy.add and toy.mul.
    // TODO: Check whether both operands come from mlir::arith::ConstantOp and
    // read their attribute values.
    // TODO: Compute the folded scalar value (integer or floating point) and
    // create a new mlir::arith::ConstantOp with the result.
    // TODO: Replace the Toy op's uses with the new constant and erase the
    // original Toy op while keeping the traversal stable.
  }
};

} // namespace

std::unique_ptr<mlir::Pass> toy::createToyConstantFoldPass() {
  return std::make_unique<ToyConstantFoldPass>();
}

void toy::detail::registerToyConstantFoldPass() {
  static mlir::PassRegistration<ToyConstantFoldPass> pass;
  (void)pass;
}
