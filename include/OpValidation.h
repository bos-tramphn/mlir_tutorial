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

// A candidate assignment produced by a planning implementation.
// One tensor placement is expected per compute-op output value.
struct TensorPlacement {
  mlir::Value tensor;
  int64_t slotIndex = -1;
};

// One operation placement is expected per compute op.
struct OperationPlacement {
  int64_t opIndex = -1;
  int64_t workspaceSlotIndex = -1;
  int64_t outputSlotIndex = -1;
};

struct MemoryPlanCandidate {
  llvm::SmallVector<TensorPlacement, 16> tensorPlacements;
  llvm::SmallVector<OperationPlacement, 16> operationPlacements;
  // Optional. When non-negative, validation checks that this equals the sum of
  // slot-to-slot movement costs over all producer-consumer operands.
  int64_t totalMovementTime = -1;
};

// Baseline input validation for the memory-planning assignment.
// This function validates attributes/op-shapes and fills `context`.
mlir::LogicalResult validateToyMemoryPlanningInput(mlir::ModuleOp module,
                                                   ValidationContext &context);

// Validates slot storage constraints for a candidate memory plan:
// - tensor/workspace capacity checks
// - overlapping tensor lifetime slot conflicts
// - workspace/output conflicts with live tensors
// - per-op peak-vs-budget checks
// - optional total movement time consistency check
mlir::LogicalResult
validateToyMemorySlotStorage(mlir::ModuleOp module,
                             const ValidationContext &context,
                             const MemoryPlanCandidate &candidate);

} // namespace toy

#endif // TOY_OP_VALIDATION_H
