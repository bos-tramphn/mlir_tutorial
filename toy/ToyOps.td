include "mlir/IR/OpBase.td"
include "mlir/Interfaces/SideEffectInterfaces.td"
include "ToyDialect.td"

class Toy_Op<string mnemonic, list<Trait> traits = []>
    : Op<Toy_Dialect, mnemonic, traits>;

def Toy_AddOp : Toy_Op<"add", [NoSideEffect]> {
  let arguments = (ins AnyType:$lhs, AnyType:$rhs);
  let results = (outs AnyType:$output);
  let summary = "Toy addition op";
  let description = [{
    Adds two tensors elementwise. TODO: constrain shapes and element types.
  }];
}

def Toy_MulOp : Toy_Op<"mul", [NoSideEffect]> {
  let arguments = (ins AnyType:$lhs, AnyType:$rhs);
  let results = (outs AnyType:$output);
  let summary = "Toy multiplication op";
  let description = [{
    Multiplies two tensors elementwise. TODO: define shape inference.
  }];
}
