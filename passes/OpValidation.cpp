#include "OpValidation.h"

#include "toy/ToyOps.h"

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/Support/raw_ostream.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinTypes.h"

#include <algorithm>
#include <string>

using namespace mlir;

namespace {

static bool isComputeOp(Operation *op) {
  return isa<toy::ConvOp, toy::ReluOp, toy::AddOp, toy::MulOp, toy::SubOp>(op);
}

static FailureOr<int64_t> readRequiredI64Attr(Operation *op, StringRef attrName,
                                              bool emitDiagnostic = true) {
  Attribute attr = op->getAttr(attrName);
  if (!attr) {
    if (emitDiagnostic) {
      op->emitError() << "missing required i64 attribute `" << attrName << "`";
    }
    return failure();
  }

  auto intAttr = attr.dyn_cast<IntegerAttr>();
  if (!intAttr) {
    if (emitDiagnostic) {
      op->emitError() << "attribute `" << attrName
                      << "` must be an i64 IntegerAttr";
    }
    return failure();
  }

  const APInt value = intAttr.getValue();
  if (!value.isSignedIntN(64)) {
    if (emitDiagnostic) {
      op->emitError() << "attribute `" << attrName
                      << "` must fit in signed 64-bit integer";
    }
    return failure();
  }
  return value.getSExtValue();
}

static FailureOr<int64_t> readRequiredModuleSlotAttr(ModuleOp module,
                                                     StringRef baseAttrName) {
  if (auto value = readRequiredI64Attr(module, baseAttrName, false);
      succeeded(value)) {
    return value;
  }

  SmallString<64> prefixed("toy.");
  prefixed.append(baseAttrName);
  if (auto value = readRequiredI64Attr(module, prefixed, false);
      succeeded(value)) {
    return value;
  }

  module.emitError() << "missing required slot attribute `" << baseAttrName
                     << "` (or `toy." << baseAttrName << "`)";
  return failure();
}

static LogicalResult validateComputeOpShape(Operation *op) {
  if (op->getNumResults() != 1) {
    op->emitError() << "compute op must produce exactly one result, got "
                    << op->getNumResults();
    return failure();
  }
  if (!op->getResult(0).getType().isa<TensorType>()) {
    op->emitError("compute output must be tensor-typed");
    return failure();
  }
  for (Value input : op->getOperands()) {
    if (!input.getType().isa<TensorType>()) {
      op->emitError("compute input must be tensor-typed");
      return failure();
    }
  }
  return success();
}

static std::string formatValue(Value value) {
  std::string text;
  llvm::raw_string_ostream os(text);
  value.print(os);
  return os.str();
}

static FailureOr<const toy::SlotInfo *>
lookupSlotByIndex(const toy::ValidationContext &context, int64_t slotIndex,
                  Operation *op, StringRef roleName) {
  if (slotIndex < 0 || slotIndex >= static_cast<int64_t>(context.slots.size())) {
    op->emitError() << roleName << " slot index out of range: " << slotIndex;
    return failure();
  }
  return &context.slots[static_cast<size_t>(slotIndex)];
}

static int64_t computeTotalSlotCapacity(const toy::ValidationContext &context) {
  int64_t total = 0;
  for (const toy::SlotInfo &slot : context.slots) {
    total += slot.capacity;
  }
  return total;
}

} // namespace

LogicalResult toy::validateToyMemoryPlanningInput(ModuleOp module,
                                                  ValidationContext &context) {
  context = ValidationContext{};

  static constexpr const char *kSlotAttrs[] = {
      "slot0_capacity", "slot1_capacity", "slot2_capacity", "slot3_capacity",
      "slot4_capacity"};

  for (const char *slotName : kSlotAttrs) {
    FailureOr<int64_t> capacityOr = readRequiredModuleSlotAttr(module, slotName);
    if (failed(capacityOr)) {
      return failure();
    }
    if (*capacityOr <= 0) {
      module.emitError() << "slot capacity must be > 0 for `" << slotName
                         << "`, got " << *capacityOr;
      return failure();
    }
    context.slots.push_back({slotName, *capacityOr});
  }

  SmallVector<Operation *, 16> computeOps;
  module.walk([&](Operation *op) {
    if (isComputeOp(op)) {
      computeOps.push_back(op);
    }
  });
  if (computeOps.empty()) {
    module.emitError("no compute ops found");
    return failure();
  }

  context.opInfos.reserve(computeOps.size());
  for (size_t i = 0; i < computeOps.size(); ++i) {
    Operation *op = computeOps[i];
    if (failed(validateComputeOpShape(op))) {
      return failure();
    }

    FailureOr<int64_t> tensorSizeOr = readRequiredI64Attr(op, "tensor_size");
    FailureOr<int64_t> workspaceSizeOr =
        readRequiredI64Attr(op, "workspace_size");
    if (failed(tensorSizeOr) || failed(workspaceSizeOr)) {
      return failure();
    }
    if (*tensorSizeOr <= 0) {
      op->emitError("`tensor_size` must be > 0");
      return failure();
    }
    if (*workspaceSizeOr < 0) {
      op->emitError("`workspace_size` must be >= 0");
      return failure();
    }

    bool tensorFitsSomeSlot = false;
    bool workspaceFitsSomeSlot = false;
    for (const SlotInfo &slot : context.slots) {
      tensorFitsSomeSlot = tensorFitsSomeSlot || (slot.capacity >= *tensorSizeOr);
      workspaceFitsSomeSlot =
          workspaceFitsSomeSlot || (slot.capacity >= *workspaceSizeOr);
    }
    if (!tensorFitsSomeSlot) {
      op->emitError("no slot can fit `tensor_size`");
      return failure();
    }
    if (!workspaceFitsSomeSlot) {
      op->emitError("no slot can fit `workspace_size`");
      return failure();
    }

    OpInfo info;
    info.op = op;
    info.index = static_cast<int64_t>(i);
    info.opName = op->getName().getStringRef().str();
    info.inputs.append(op->operand_begin(), op->operand_end());
    info.output = op->getResult(0);
    info.tensorSize = *tensorSizeOr;
    info.workspaceSize = *workspaceSizeOr;
    context.opInfos.push_back(std::move(info));
  }

  return success();
}

LogicalResult
toy::validateToyMemorySlotStorage(ModuleOp module,
                                  const ValidationContext &context,
                                  const MemoryPlanCandidate &candidate) {
  if (context.opInfos.empty()) {
    module.emitError("internal error: validation context has no compute ops");
    return failure();
  }

  if (candidate.tensorPlacements.size() != context.opInfos.size()) {
    module.emitError()
        << "expected one tensor placement per compute op output (expected "
        << context.opInfos.size() << ", got "
        << candidate.tensorPlacements.size() << ")";
    return failure();
  }
  if (candidate.operationPlacements.size() != context.opInfos.size()) {
    module.emitError() << "expected one operation placement per compute op "
                          "(expected "
                       << context.opInfos.size() << ", got "
                       << candidate.operationPlacements.size() << ")";
    return failure();
  }

  llvm::DenseMap<Operation *, int64_t> opToIndex;
  llvm::DenseMap<Value, int64_t> outputToIndex;
  opToIndex.reserve(context.opInfos.size());
  outputToIndex.reserve(context.opInfos.size());
  for (const OpInfo &opInfo : context.opInfos) {
    opToIndex[opInfo.op] = opInfo.index;
    outputToIndex[opInfo.output] = opInfo.index;
  }

  llvm::SmallVector<int64_t, 16> tensorSlotByProducer(context.opInfos.size(),
                                                       -1);
  for (const TensorPlacement &placement : candidate.tensorPlacements) {
    auto tensorIt = outputToIndex.find(placement.tensor);
    if (tensorIt == outputToIndex.end()) {
      module.emitError()
          << "tensor placement references unknown tensor value "
          << formatValue(placement.tensor);
      return failure();
    }

    const int64_t producerIdx = tensorIt->second;
    const OpInfo &producer = context.opInfos[producerIdx];
    if (tensorSlotByProducer[producerIdx] != -1) {
      producer.op->emitError()
          << "duplicate tensor placement for output "
          << formatValue(placement.tensor);
      return failure();
    }

    FailureOr<const SlotInfo *> slotOr =
        lookupSlotByIndex(context, placement.slotIndex, producer.op, "tensor");
    if (failed(slotOr)) {
      return failure();
    }
    if (producer.tensorSize > (*slotOr)->capacity) {
      producer.op->emitError()
          << "Constraint 1 violated: tensor " << formatValue(placement.tensor)
          << " size " << producer.tensorSize << " exceeds slot `"
          << (*slotOr)->name << "` capacity " << (*slotOr)->capacity;
      return failure();
    }

    tensorSlotByProducer[producerIdx] = placement.slotIndex;
  }
  for (size_t i = 0; i < tensorSlotByProducer.size(); ++i) {
    if (tensorSlotByProducer[i] == -1) {
      context.opInfos[i].op->emitError("missing tensor slot placement for op output");
      return failure();
    }
  }

  llvm::SmallVector<OperationPlacement, 16> opPlacementByIndex(
      context.opInfos.size());
  llvm::SmallVector<char, 16> hasOpPlacement(context.opInfos.size(), 0);
  for (const OperationPlacement &placement : candidate.operationPlacements) {
    if (placement.opIndex < 0 ||
        placement.opIndex >= static_cast<int64_t>(context.opInfos.size())) {
      module.emitError() << "operation placement has out-of-range op index "
                         << placement.opIndex;
      return failure();
    }
    if (hasOpPlacement[placement.opIndex]) {
      module.emitError()
          << "duplicate operation placement for op index " << placement.opIndex;
      return failure();
    }
    hasOpPlacement[placement.opIndex] = 1;
    opPlacementByIndex[placement.opIndex] = placement;
  }
  for (size_t i = 0; i < hasOpPlacement.size(); ++i) {
    if (!hasOpPlacement[i]) {
      module.emitError()
          << "missing operation placement for op index " << i;
      return failure();
    }
  }

  const int64_t totalCapacity = computeTotalSlotCapacity(context);

  // Build tensor lifetimes [producerIndex, lastUseIndex].
  llvm::SmallVector<int64_t, 16> lifetimeEnd(context.opInfos.size(), -1);
  for (size_t i = 0; i < context.opInfos.size(); ++i) {
    const OpInfo &opInfo = context.opInfos[i];
    int64_t end = static_cast<int64_t>(i);
    for (Operation *user : opInfo.output.getUsers()) {
      auto it = opToIndex.find(user);
      if (it != opToIndex.end()) {
        end = std::max(end, it->second);
      } else {
        // Values escaping compute ops remain live conservatively until the end.
        end = std::max(end, static_cast<int64_t>(context.opInfos.size()));
      }
    }
    lifetimeEnd[i] = end;
  }

  // Per-op checks (workspace/output slot range, capacity, and role conflicts).
  for (size_t opIdx = 0; opIdx < context.opInfos.size(); ++opIdx) {
    const OpInfo &opInfo = context.opInfos[opIdx];
    const OperationPlacement &placement = opPlacementByIndex[opIdx];

    FailureOr<const SlotInfo *> workspaceSlotOr = lookupSlotByIndex(
        context, placement.workspaceSlotIndex, opInfo.op, "workspace");
    if (failed(workspaceSlotOr)) {
      return failure();
    }
    FailureOr<const SlotInfo *> outputSlotOr =
        lookupSlotByIndex(context, placement.outputSlotIndex, opInfo.op, "output");
    if (failed(outputSlotOr)) {
      return failure();
    }

    if (opInfo.workspaceSize > (*workspaceSlotOr)->capacity) {
      opInfo.op->emitError()
          << "Constraint 2 violated: workspace size " << opInfo.workspaceSize
          << " exceeds slot `" << (*workspaceSlotOr)->name << "` capacity "
          << (*workspaceSlotOr)->capacity;
      return failure();
    }

    if (placement.outputSlotIndex != tensorSlotByProducer[opIdx]) {
      opInfo.op->emitError()
          << "output slot mismatch: op output is assigned to slot "
          << tensorSlotByProducer[opIdx]
          << " in tensor placement, but operation placement uses slot "
          << placement.outputSlotIndex;
      return failure();
    }

    if (placement.workspaceSlotIndex == placement.outputSlotIndex) {
      opInfo.op->emitError()
          << "workspace slot and output slot cannot be the same during one op";
      return failure();
    }

    int64_t liveBeforeBytes = 0;
    for (size_t t = 0; t < context.opInfos.size(); ++t) {
      const int64_t producer = static_cast<int64_t>(t);
      const bool liveDuringThisOp =
          producer <= static_cast<int64_t>(opIdx) &&
          static_cast<int64_t>(opIdx) <= lifetimeEnd[t];
      if (!liveDuringThisOp) {
        continue;
      }

      const bool isCurrentOutput = (t == opIdx);
      if (!isCurrentOutput) {
        liveBeforeBytes += context.opInfos[t].tensorSize;

        if (tensorSlotByProducer[t] == placement.workspaceSlotIndex) {
          opInfo.op->emitError()
              << "Constraint 4 violated: workspace slot "
              << placement.workspaceSlotIndex
              << " overlaps live tensor " << formatValue(context.opInfos[t].output);
          return failure();
        }
        if (tensorSlotByProducer[t] == placement.outputSlotIndex) {
          opInfo.op->emitError()
              << "Constraint 5 violated: output slot "
              << placement.outputSlotIndex
              << " overlaps live tensor " << formatValue(context.opInfos[t].output);
          return failure();
        }
      }
    }

    const int64_t peakDuringOp =
        liveBeforeBytes + opInfo.tensorSize + opInfo.workspaceSize;
    if (peakDuringOp > totalCapacity) {
      opInfo.op->emitError()
          << "Constraint 9 violated: peak memory " << peakDuringOp
          << " exceeds total slot capacity " << totalCapacity;
      return failure();
    }
  }

  // Cross-op overlap check for persistent tensors (Constraint 3).
  for (size_t i = 0; i < context.opInfos.size(); ++i) {
    for (size_t j = i + 1; j < context.opInfos.size(); ++j) {
      const bool overlap = static_cast<int64_t>(i) <= lifetimeEnd[j] &&
                           static_cast<int64_t>(j) <= lifetimeEnd[i];
      if (!overlap) {
        continue;
      }
      if (tensorSlotByProducer[i] == tensorSlotByProducer[j]) {
        context.opInfos[j].op->emitError()
            << "Constraint 3 violated: overlapping tensors "
            << formatValue(context.opInfos[i].output) << " [" << i << ", "
            << lifetimeEnd[i] << "] and "
            << formatValue(context.opInfos[j].output) << " [" << j << ", "
            << lifetimeEnd[j] << "] share slot index "
            << tensorSlotByProducer[i];
        return failure();
      }
    }
  }

  return success();
}
