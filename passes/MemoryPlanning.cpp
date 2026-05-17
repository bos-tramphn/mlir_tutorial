#include "MemoryPlanning.h"

#include "OpValidation.h"

#include "llvm/Support/raw_ostream.h"

using namespace mlir;

LogicalResult toy::runToyMemoryPlanning(ModuleOp module) {
  ValidationContext context;
  if (failed(validateToyMemoryPlanningInput(module, context))) {
    return failure();
  }

  // TODO(MemoryPlanning): Build TensorInfo list and producer-consumer edges.
  // TODO(MemoryPlanning): Compute tensor lifetimes (start/end by last use).
  // TODO(MemoryPlanning): Compute live-before/live-during/live-after sets.
  // TODO(MemoryPlanning): Implement scheduler/allocation algorithm.
  // TODO(MemoryPlanning): Validate memory constraints from context.txt.
  // TODO(MemoryPlanning): Compute peak memory and print assignment report.

  llvm::outs() << "=== Tensor Memory Reuse Starter ===\n";
  llvm::outs() << "Validated input format for " << context.opInfos.size()
               << " compute ops.\n";
  llvm::outs() << "TODO: implement liveness analysis, scheduling, and memory "
                  "validation algorithm.\n";
  return success();
}
