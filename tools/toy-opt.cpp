#include "toy/ToyDialect.h"
#include "toy/ToyOps.h"
#include "toy/Transforms/Passes.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinDialect.h"
#include "mlir/IR/DialectRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "mlir/Dialect/Arithmetic/IR/Arithmetic.h"

int main(int argc, char **argv) {
  // Register our Toy dialect and passes.
  toy::registerToyPasses();
  toy::registerToyPassPipelines();

  // Set up the dialect registry.
  mlir::DialectRegistry registry;
  registry.insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::arith::ArithmeticDialect>();

  // Register Toy dialect
  toy::registerToyDialect(registry);

    return asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "Toy optimizer\n", registry));
}
