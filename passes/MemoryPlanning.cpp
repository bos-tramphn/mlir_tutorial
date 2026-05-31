#include "MemoryPlanning.h"

#include "OpValidation.h"
#include <functional>
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/DenseMap.h"
#include <algorithm>
using namespace mlir;

namespace {
  struct TensorInfo {
    mlir::Value value;
    int64_t size = 0;
    int64_t producerIndex = -1;
    llvm::SmallVector<int64_t, 16> consumerIndices;
    int64_t lifetimeStart = -1;
    int64_t lifetimeEnd = -1;
  };

  struct OpLiveness {
    llvm::SmallVector<int64_t, 16> liveBefore;
    llvm::SmallVector<int64_t, 16> liveDuring;
    llvm::SmallVector<int64_t, 16> liveAfter;
  };
}
LogicalResult toy::runToyMemoryPlanning(ModuleOp module) {
  ValidationContext context;
  if (failed(validateToyMemoryPlanningInput(module, context))) {
    return failure();
  }

// DONE(MemoryPlanning): Build TensorInfo list and producer-consumer edges.
llvm::SmallVector<TensorInfo, 16> tensors;
llvm::DenseMap<Value, int64_t> tensorIndexByValue;

for (const OpInfo &opInfo : context.opInfos) {
  // Gather TensorInfo and Producer of Tensor Information
  TensorInfo tensor;
  tensor.value = opInfo.output;
  tensor.size = opInfo.tensorSize;
  tensor.producerIndex = opInfo.index;
  int64_t tensorIndex = static_cast<int64_t>(tensors.size());
  tensorIndexByValue[opInfo.output] = tensorIndex;
  tensors.push_back(std::move(tensor));

  // Gather Consumers of Tensor Information
  for (Value input : opInfo.inputs) {
    auto tensorIt = tensorIndexByValue.find(input);
    if (tensorIt == tensorIndexByValue.end()) {
      continue;
    }

    TensorInfo &producerTensor = tensors[tensorIt->second];
    auto &consumers = producerTensor.consumerIndices;
    if (std::find(consumers.begin(), consumers.end(), opInfo.index) ==
        consumers.end()) {
      consumers.push_back(opInfo.index);
    }
  }
}



  // DONE(MemoryPlanning): Compute tensor lifetimes (start/end by last use).
for (TensorInfo &tensor : tensors) {
    tensor.lifetimeStart = tensor.producerIndex;
    tensor.lifetimeEnd = tensor.producerIndex;
    for (int64_t consumerIndex : tensor.consumerIndices) {
      tensor.lifetimeEnd = std::max(tensor.lifetimeEnd, consumerIndex);
    }
    if (tensor.consumerIndices.empty()) {
      tensor.lifetimeEnd = static_cast<int64_t>(context.opInfos.size()) - 1;
    } // op9
  }

      
  // DONE(MemoryPlanning): Compute live-before/live-during/live-after sets.
llvm::SmallVector<OpLiveness, 16> liveness(context.opInfos.size());
for (size_t opIdx = 0; opIdx < context.opInfos.size(); ++opIdx) {
  for (size_t tensorIndex = 0; tensorIndex < tensors.size(); ++tensorIndex) {
    const TensorInfo &tensor = tensors[tensorIndex];
    const int64_t op = static_cast<int64_t>(opIdx);
    const int64_t tensorIdx = static_cast<int64_t>(tensorIndex);

    if (tensor.lifetimeStart < op && op <= tensor.lifetimeEnd) {
      liveness[opIdx].liveBefore.push_back(tensorIdx);
    }
    if (tensor.lifetimeStart <= op && op <= tensor.lifetimeEnd) {
      liveness[opIdx].liveDuring.push_back(tensorIdx);
    }
    if (tensor.lifetimeStart <= op && op < tensor.lifetimeEnd) {
      liveness[opIdx].liveAfter.push_back(tensorIdx);
    }
  }
}


  // DONE(MemoryPlanning): Implement scheduler/allocation algorithm.
llvm::SmallVector<int64_t, 16> tensorSlotByIndex(tensors.size(), -1);
llvm::SmallVector<int64_t, 16> workspaceSlotByOp(context.opInfos.size(), -1);
auto conflictWithLiveBefore = [&](int64_t slotIndex, int64_t opIdx) {
  for (int64_t liveTensorIdx : liveness[opIdx].liveBefore) {
    if (tensorSlotByIndex[liveTensorIdx] == slotIndex) {
      return true;
      }
    }
    return false;
};
std::function<bool(int64_t)> dfsAllocate = [&](int64_t opIdx) -> bool {
    if (opIdx >= static_cast<int64_t>(context.opInfos.size())) {
      return true;
    }
    const OpInfo &opInfo = context.opInfos[opIdx];
    const TensorInfo &outputTensor = tensors[opIdx];
    for (size_t outputSlot = 0; outputSlot < context.slots.size(); ++outputSlot) {
      if (outputTensor.size > context.slots[outputSlot].capacity) {
        continue;
      }
      for (size_t workspaceSlot = 0; workspaceSlot < context.slots.size(); ++workspaceSlot) {
        if (outputSlot == workspaceSlot) {
          continue;
        }
        if (opInfo.workspaceSize > context.slots[workspaceSlot].capacity) {
          continue;
        }
        if (conflictWithLiveBefore(static_cast<int64_t>(outputSlot), opIdx) ||
            conflictWithLiveBefore(static_cast<int64_t>(workspaceSlot), opIdx)) {
          continue;
        }
        tensorSlotByIndex[opIdx] = static_cast<int64_t>(outputSlot);
        workspaceSlotByOp[opIdx] = static_cast<int64_t>(workspaceSlot);
        if (dfsAllocate(opIdx + 1)) {
          return true;
        }
        tensorSlotByIndex[opIdx] = -1;
        workspaceSlotByOp[opIdx] = -1;
      }
    }
  return false;
  };
if (!dfsAllocate(0)) {
  module.emitError("failed to find a valid memory allocation");
  return failure();
}

  // DONE(MemoryPlanning): Validate memory constraints.
MemoryPlanCandidate candidate;
for (size_t tensorIdx = 0; tensorIdx < tensors.size(); ++tensorIdx) {
    const TensorInfo &tensor = tensors[tensorIdx];
    candidate.tensorPlacements.push_back({tensor.value, tensorSlotByIndex[tensorIdx]});
  }
for (size_t opIdx = 0; opIdx < context.opInfos.size(); ++opIdx) {
    candidate.operationPlacements.push_back({static_cast<int64_t>(opIdx), workspaceSlotByOp[opIdx], tensorSlotByIndex[opIdx]});
  } 

if (failed(validateToyMemorySlotStorage(module, context, candidate))) {
    return failure();
  }
llvm::outs() << "Memory plan validation passed.\n";
  // DONE(MemoryPlanning): Compute peak memory and print assignment report.

int64_t maxPeakMemory = 0;
llvm::SmallVector<int64_t, 16> PeakMemoryOp(context.opInfos.size(), -1);
for (size_t opIdx = 0; opIdx < context.opInfos.size(); ++opIdx) {
    int64_t liveBeforeBytes = 0;
    for (int64_t tensorIdx : liveness[opIdx].liveBefore) {
      liveBeforeBytes += tensors[tensorIdx].size;
    }
    int64_t outputBytes = tensors[opIdx].size;
    int64_t workspaceBytes = context.opInfos[opIdx].workspaceSize;
    int64_t peakDuringOp = liveBeforeBytes + outputBytes + workspaceBytes;
    PeakMemoryOp[opIdx] = peakDuringOp;
    //llvm::outs() << "peak memory = " << PeakMemoryOp[opIdx] << "\n";
    maxPeakMemory = std::max(maxPeakMemory, peakDuringOp);
    
  }

llvm::outs() << "peak memory = " << PeakMemoryOp[0] << "\n";
int64_t totalSlotCapacity = 0;

for (const SlotInfo &slot : context.slots) {
  totalSlotCapacity += slot.capacity;
}
  // Debug print TensorInfo list
llvm::outs() << "=== TensorInfo Debug ===\n";

for (size_t i = 0; i < tensors.size(); ++i) {
  const TensorInfo &tensor = tensors[i];

  llvm::outs() << "tensor " << i
               << ": producer=op" << tensor.producerIndex
               << ", size=" << tensor.size
               << ", lifetime=[" << tensor.lifetimeStart << ", " << tensor.lifetimeEnd << "]"
               << ", consumers=[";
  for (size_t j = 0; j < tensor.consumerIndices.size(); ++j) {
    if (j != 0) {
      llvm::outs() << ", ";
    }
    llvm::outs() << "op" << tensor.consumerIndices[j];
  }

  llvm::outs() << "]\n";
}
llvm::outs() << "=== Liveness Debug ===\n";
for (size_t opIdx = 0; opIdx < liveness.size(); ++opIdx) {
  const OpLiveness &opLive = liveness[opIdx];
  llvm::outs() << "op" << opIdx << ": liveBefore=[";
  for (size_t i = 0; i < opLive.liveBefore.size(); ++i) {
    if (i != 0) {
      llvm::outs() << ", ";
    }
    llvm::outs() << "tensor" << opLive.liveBefore[i];
  }
  llvm::outs() << "], liveDuring=[";
  for (size_t i = 0; i < opLive.liveDuring.size(); ++i) {
    if (i != 0) {
      llvm::outs() << ", ";
    }
    llvm::outs() << "tensor" << opLive.liveDuring[i];
  }
  llvm::outs() << "], liveAfter=[";
  for (size_t i = 0; i < opLive.liveAfter.size(); ++i) {
    if (i != 0) {
      llvm::outs() << ", ";
    }
    llvm::outs() << "tensor" << opLive.liveAfter[i];
  }
  llvm::outs() << "]\n";
}
llvm::outs() << "=== DFS Allocation Result ===\n";

for (size_t opIdx = 0; opIdx < context.opInfos.size(); ++opIdx) {
  llvm::outs() << "op" << opIdx
               << ": output tensor" << opIdx
               << " -> slot" << tensorSlotByIndex[opIdx]
               << ", workspace -> slot" << workspaceSlotByOp[opIdx]
               << ", peak memory = " << PeakMemoryOp[opIdx]
               << "\n";
}
llvm::outs() << "Memory plan validation passed.\n";
llvm::outs() << "Max peak memory = " << maxPeakMemory << "\n";

  llvm::outs() << "=== Tensor Memory Reuse Starter ===\n";
  llvm::outs() << "Validated input format for " << context.opInfos.size()
               << " compute ops.\n";
  llvm::outs() << "TODO: implement liveness analysis, scheduling, and memory "
                  "validation algorithm.\n";

  uint64_t movementTime = 0;
  llvm::outs() << "Total movement time: " << movementTime << "\n";
  return success();
}
