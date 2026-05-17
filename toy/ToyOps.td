include "mlir/IR/OpBase.td"
include "mlir/Interfaces/SideEffectInterfaces.td"
include "ToyDialect.td"

class Toy_Op<string mnemonic, list<Trait> traits = []>
    : Op<Toy_Dialect, mnemonic, traits>;

def Toy_ConvOp : Toy_Op<"conv", [NoSideEffect]> {
  let arguments = (ins AnyType:$input,
                       DefaultValuedAttr<I64Attr, "0">:$tensor_size,
                       DefaultValuedAttr<I64Attr, "0">:$workspace_size);
  let results = (outs AnyType:$output);
  let summary = "Toy convolution-like compute op";
  let description = [{
    Fake compute op for tensor memory reuse exercises.
    `tensor_size` and `workspace_size` model memory requirements only.
  }];
}

def Toy_ReluOp : Toy_Op<"relu", [NoSideEffect]> {
  let arguments = (ins AnyType:$input,
                       DefaultValuedAttr<I64Attr, "0">:$tensor_size,
                       DefaultValuedAttr<I64Attr, "0">:$workspace_size);
  let results = (outs AnyType:$output);
  let summary = "Toy relu-like compute op";
  let description = [{
    Fake compute op for tensor memory reuse exercises.
    `tensor_size` and `workspace_size` model memory requirements only.
  }];
}

def Toy_AddOp : Toy_Op<"add", [NoSideEffect]> {
  let arguments = (ins AnyType:$lhs, AnyType:$rhs,
                       DefaultValuedAttr<I64Attr, "0">:$tensor_size,
                       DefaultValuedAttr<I64Attr, "0">:$workspace_size);
  let results = (outs AnyType:$output);
  let summary = "Toy addition op";
  let description = [{
    Fake compute op for tensor memory reuse exercises.
    `tensor_size` and `workspace_size` model memory requirements only.
  }];
}

def Toy_MulOp : Toy_Op<"mul", [NoSideEffect]> {
  let arguments = (ins AnyType:$lhs, AnyType:$rhs,
                       DefaultValuedAttr<I64Attr, "0">:$tensor_size,
                       DefaultValuedAttr<I64Attr, "0">:$workspace_size);
  let results = (outs AnyType:$output);
  let summary = "Toy multiplication op";
  let description = [{
    Fake compute op for tensor memory reuse exercises.
    `tensor_size` and `workspace_size` model memory requirements only.
  }];
}

def Toy_SubOp : Toy_Op<"sub", [NoSideEffect]> {
  let arguments = (ins AnyType:$lhs, AnyType:$rhs,
                       DefaultValuedAttr<I64Attr, "0">:$tensor_size,
                       DefaultValuedAttr<I64Attr, "0">:$workspace_size);
  let results = (outs AnyType:$output);
  let summary = "Toy subtraction op";
  let description = [{
    Fake compute op for tensor memory reuse exercises.
    `tensor_size` and `workspace_size` model memory requirements only.
  }];
}
