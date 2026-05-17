#ifndef TOY_OP_VALIDATION_H
#define TOY_OP_VALIDATION_H

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Value.h"
#include "mlir/Support/LogicalResult.h"
#include "llvm/ADT/SmallVector.h"

#include <string>

namespace toy {

struct SlotInfo {
  std::string name;
  int64_t capacity = 0;
};

struct OpInfo {
  mlir::Operation *op = nullptr;
  int64_t index = -1;
  std::string opName;
  llvm::SmallVector<mlir::Value, 4> inputs;
  mlir::Value output;
  int64_t tensorSize = 0;
  int64_t workspaceSize = 0;
};

struct ValidationContext {
  llvm::SmallVector<SlotInfo, 5> slots;
  llvm::SmallVector<OpInfo, 16> opInfos;
};

// Baseline input validation for the memory-planning assignment.
// This function validates attributes/op-shapes and fills `context`.
mlir::LogicalResult validateToyMemoryPlanningInput(mlir::ModuleOp module,
                                                   ValidationContext &context);

} // namespace toy

#endif // TOY_OP_VALIDATION_H
