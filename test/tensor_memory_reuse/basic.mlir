// RUN: toy-opt %s -toy-tensor-memory-reuse

module attributes {
  toy.slot0_capacity = 16 : i64,
  toy.slot1_capacity = 16 : i64,
  toy.slot2_capacity = 16 : i64,
  toy.slot3_capacity = 16 : i64,
  toy.slot4_capacity = 16 : i64
} {
  func.func @basic_memory_reuse(%input: tensor<?xf64>) -> tensor<?xf64> {
    %a = "toy.conv"(%input) {tensor_size = 12 : i64, workspace_size = 4 : i64}
         : (tensor<?xf64>) -> tensor<?xf64>

    %b = "toy.relu"(%a) {tensor_size = 12 : i64, workspace_size = 2 : i64}
         : (tensor<?xf64>) -> tensor<?xf64>

    return %b : tensor<?xf64>
  }
}
