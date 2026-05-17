include "mlir/IR/DialectBase.td"
include "mlir/IR/OpBase.td"

def Toy_Dialect : Dialect {
  let name = "toy";
  let summary = "Toy dialect for tutorial purposes";
  let description = [{
    The Toy dialect is a simple dialect for demonstrating MLIR concepts.
    For tensor-memory-reuse exercises, modules are expected to carry i64
    attributes named:
      toy.slot0_capacity, toy.slot1_capacity, toy.slot2_capacity,
      toy.slot3_capacity, toy.slot4_capacity.
  }];
  let cppNamespace = "::toy";
}
