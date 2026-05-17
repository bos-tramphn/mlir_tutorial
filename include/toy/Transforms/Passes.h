#ifndef TOY_PASSES_H
#define TOY_PASSES_H

#include "mlir/Pass/Pass.h"
#include <memory>

namespace toy {
std::unique_ptr<mlir::Pass> createToyShapeInferencePass();
std::unique_ptr<mlir::Pass> createToyCanonicalizePass();
std::unique_ptr<mlir::Pass> createToyDCEPass();
std::unique_ptr<mlir::Pass> createToyCSEPass();
std::unique_ptr<mlir::Pass> createToyConstantFoldPass();
std::unique_ptr<mlir::Pass> createToyToArithPass();
std::unique_ptr<mlir::Pass> createToyToLinalgPass();
std::unique_ptr<mlir::Pass> createToyTensorMemoryReusePass();
void registerToyPasses();
void registerToyPassPipelines();

namespace detail {
void registerToyShapeInferencePass();
void registerToyCanonicalizePass();
void registerToyDCEPass();
void registerToyCSEPass();
void registerToyConstantFoldPass();
void registerToyToArithPass();
void registerToyToLinalgPass();
void registerToyTensorMemoryReusePass();
}
}

#endif // TOY_PASSES_H
