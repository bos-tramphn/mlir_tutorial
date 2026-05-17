#include "toy/Transforms/Passes.h"

// Toy passes
#include "ToyToLinalgPass.h"

// MLIR core
#include "mlir/Pass/PassManager.h"

// Dialects / ops
#include "mlir/Dialect/Func/IR/FuncOps.h"

// MLIR transforms
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Conversion/SCFToControlFlow/SCFToControlFlow.h"

using namespace mlir;

void toy::registerToyPasses() {
  detail::registerToyShapeInferencePass();
  detail::registerToyCanonicalizePass();
  detail::registerToyDCEPass();
  detail::registerToyCSEPass();
  detail::registerToyConstantFoldPass();
  detail::registerToyToArithPass();
  detail::registerToyToLinalgPass();
  detail::registerToyTensorMemoryReusePass();
}

/* ============================================================
 * Helper: Toy frontend pipeline
 * ============================================================ */
static void buildToyFrontendPipeline(OpPassManager &pm) {
  pm.addPass(toy::createToyShapeInferencePass());
  pm.addPass(toy::createToyCanonicalizePass());
  pm.addNestedPass<func::FuncOp>(toy::createToyDCEPass());
  pm.addNestedPass<func::FuncOp>(toy::createToyCSEPass());
  pm.addNestedPass<func::FuncOp>(toy::createToyConstantFoldPass());
}

/* ============================================================
 * Register pipelines
 * ============================================================ */
void toy::registerToyPassPipelines() {

  // ---------- Frontend-only pipeline ----------
  mlir::PassPipelineRegistration<>(
      "toy-frontend",
      "Toy frontend pipeline (up to constant folding)",
      [](mlir::OpPassManager &pm) {
        buildToyFrontendPipeline(pm);
      });

  // ---------- Full lowering pipeline ----------
  mlir::PassPipelineRegistration<>(
      "toy-to-linalg-pipeline",
      "Toy full pipeline: Toy → Linalg → Bufferized",
      [](mlir::OpPassManager &pm) {

        // Frontend
        buildToyFrontendPipeline(pm);

        // Toy → Linalg
        pm.addNestedPass<func::FuncOp>(toy::createToyToLinalgPass());
      });
}
