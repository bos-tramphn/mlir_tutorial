#include "MemoryAnalysisPass.h"
#include "MemoryPlanning.h"

#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"

using namespace mlir;

namespace {

struct MemoryAnalysisPass
    : public PassWrapper<MemoryAnalysisPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(MemoryAnalysisPass)

  StringRef getArgument() const final { return "toy-tensor-memory-reuse"; }
  StringRef getDescription() const final {
    return "Starter pass for tensor memory reuse assignment";
  }

  void runOnOperation() override {
    ModuleOp module = getOperation();
    if (failed(toy::runToyMemoryPlanning(module))) {
      signalPassFailure();
      return;
    }
  }
};

} // namespace

std::unique_ptr<Pass> toy::createToyTensorMemoryReusePass() {
  return std::make_unique<MemoryAnalysisPass>();
}

void toy::detail::registerToyTensorMemoryReusePass() {
  static PassRegistration<MemoryAnalysisPass> pass;
  (void)pass;
}
