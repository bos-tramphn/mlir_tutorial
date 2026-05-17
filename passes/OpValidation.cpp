#include "OpValidation.h"

#include "toy/ToyOps.h"

#include "llvm/ADT/SmallString.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinTypes.h"

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

