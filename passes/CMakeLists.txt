add_mlir_library(toy-passes SHARED
  ShapeInferencePass.cpp
  CanonicalizePass.cpp
  ToyDCEPass.cpp
  ToyCSEPass.cpp
  ToyConstantFoldPass.cpp
  ToyToArithPass.cpp
  ToyToLinalgPass.cpp
  Passes.cpp
  DEPENDS
  ToyOpsIncGen
  LINK_LIBS PUBLIC
  toy-dialect
  MLIRIR
  MLIRFuncDialect
  MLIRPass
  MLIRTransforms
  MLIRArithmeticDialect
  MLIRLinalgDialect
)

target_include_directories(toy-passes PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/toy
)
