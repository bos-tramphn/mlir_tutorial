#include "MemoryAnalysisPass.h"

#include "toy/ToyOps.h"

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "llvm/ADT/SmallString.h"

using namespace mlir;

namespace {

struct TensorInfo {
  Value value;
  Operation *producer = nullptr;
  int64_t tensorSize = 0;
  SmallVector<Operation *, 4> consumers;
};

struct OpInfo {
  Operation *op = nullptr;
  SmallVector<Value, 4> inputs;
  Value output;
  int64_t tensorSize = 0;
  int64_t workspaceSize = 0;
};

struct SlotInfo {
  StringRef name;
  int64_t capacity = 0;
};

static bool isToyComputeOp(Operation *op) {
  return isa<toy::ConvOp, toy::ReluOp, toy::AddOp, toy::MulOp, toy::SubOp>(op);
}

static SmallVector<Operation *, 16> collectToyComputeOps(ModuleOp module) {
  SmallVector<Operation *, 16> computeOps;
  module.walk([&](Operation *op) {
    if (isToyComputeOp(op)) {
      computeOps.push_back(op);
    }
  });
  return computeOps;
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

  SmallString<64> prefixedName("toy.");
  prefixedName.append(baseAttrName);
  if (auto value = readRequiredI64Attr(module, prefixedName, false);
      succeeded(value)) {
    return value;
  }

  module.emitError() << "missing required slot capacity attribute `"
                     << baseAttrName << "` (or `toy." << baseAttrName << "`)";
  return failure();
}

struct MemoryAnalysisPass
    : public PassWrapper<MemoryAnalysisPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(MemoryAnalysisPass)

  StringRef getArgument() const final { return "toy-tensor-memory-reuse"; }
  StringRef getDescription() const final {
    return "Analyze tensor memory reuse constraints for Toy compute ops";
  }

  void runOnOperation() override {
    ModuleOp module = getOperation();

    SmallVector<OpInfo, 16> opInfos;
    SmallVector<TensorInfo, 32> tensorInfos;
    SmallVector<SlotInfo, 5> slotInfos;
    SmallVector<Operation *, 16> computeOps = collectToyComputeOps(module);

    static constexpr const char *kSlotAttrNames[] = {"slot0_capacity",
                                                      "slot1_capacity",
                                                      "slot2_capacity",
                                                      "slot3_capacity",
                                                      "slot4_capacity"};
    for (const char *slotAttrName : kSlotAttrNames) {
      FailureOr<int64_t> capOr = readRequiredModuleSlotAttr(module, slotAttrName);
      if (failed(capOr)) {
        signalPassFailure();
        return;
      }
      slotInfos.push_back({slotAttrName, *capOr});
    }

    for (Operation *op : computeOps) {
      OpInfo info;
      info.op = op;
      info.inputs.append(op->operand_begin(), op->operand_end());
      if (!op->getResults().empty()) {
        info.output = op->getResult(0);
      }

      FailureOr<int64_t> tensorSizeOr = readRequiredI64Attr(op, "tensor_size");
      FailureOr<int64_t> workspaceSizeOr =
          readRequiredI64Attr(op, "workspace_size");
      if (failed(tensorSizeOr) || failed(workspaceSizeOr)) {
        signalPassFailure();
        return;
      }
      info.tensorSize = *tensorSizeOr;
      info.workspaceSize = *workspaceSizeOr;

      opInfos.push_back(info);
    }

    // TODO: Populate `tensorInfos` and complete producer-consumer extraction.
    // TODO: Add lifetime/live-range analysis and reporting in later steps.
    (void)opInfos;
    (void)tensorInfos;
    (void)slotInfos;
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
