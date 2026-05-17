#ifndef TOY_MEMORY_PLANNING_H
#define TOY_MEMORY_PLANNING_H

#include "mlir/IR/BuiltinOps.h"
#include "mlir/Support/LogicalResult.h"

namespace toy {

// Implementation entrypoint for assignment work.
// MemoryAnalysisPass.cpp should stay thin and call into this function.
mlir::LogicalResult runToyMemoryPlanning(mlir::ModuleOp module);

} // namespace toy

#endif // TOY_MEMORY_PLANNING_H
