# Tensor Memory Reuse Assignment

This is a compiler-style memory planning exercise over a Toy SSA graph.

## Get Started

- Graph input: `examples/assignment_input.mlir`
- Run command: `examples/run_tensor_memory_reuse.sh`
- Pass entry: `-toy-tensor-memory-reuse`

### Reference Operation Graph

| Op  | Expression          |       Type | Output size | Compute size |
| --- | ------------------- | ---------: | ----------: | -----------: |
| op0 | `%a = conv(%input)` |       Conv |          40 |           30 |
| op1 | `%b = relu(%a)`     |       ReLU |          40 |            5 |
| op2 | `%c = conv(%a)`     |       Conv |          30 |           30 |
| op3 | `%d = mul(%c)`      |        Mul |          30 |           10 |
| op4 | `%e = add(%b, %d)`  |        Add |          40 |            8 |
| op5 | `%f = relu(%e)`     |       ReLU |          40 |            5 |
| op6 | `%g = conv(%e)`     |       Conv |          50 |           30 |
| op7 | `%h = sub(%g, %a)`  |        Sub |          50 |            8 |
| op8 | `%i = add(%f, %h)`  |        Add |          50 |            8 |
| op9 | `%j = conv(%i)`     |       Conv |          60 |           30 |

### Reference Slot Capacities

| Slot  | Capacity |
| ----- | -------: |
| slot0 |       60 |
| slot1 |       50 |
| slot2 |       50 |
| slot3 |       40 |
| slot4 |       30 |

Note: `toy.mul` is currently binary in this starter dialect, so the graph input
encodes `mul(%c)` as `toy.mul(%c, %c)`.

The input graph encodes:

- Compute ops: `toy.conv`, `toy.relu`, `toy.add`, `toy.mul`, `toy.sub`
- Per-op attributes:
  - `tensor_size : i64`
  - `workspace_size : i64`
- Module attributes:
  - `toy.slot0_capacity` ... `toy.slot4_capacity` (all `i64`)
  - Note: the pass accepts both `slotN_capacity` and `toy.slotN_capacity`,
    but MLIR module verification typically requires the dialect-prefixed form.

## Your Task

Implement the analysis and reporting in `passes/MemoryPlanning.cpp`.
Keep `passes/MemoryAnalysisPass.cpp` as a thin pass wrapper that calls the implementation entrypoint.

Use this order:

1. Collect compute ops in execution order.
2. Build producer-consumer relationships.
3. Compute tensor lifetimes.
4. Track live tensors before/during/after each op.
5. Plan slot usage for tensors/workspaces.
6. Validate memory constraints.
7. Compute per-op and max peak memory.

## Suggested Validation Loop

1. Build: `ninja -C build toy-passes toy-opt`
2. Run example: `./examples/run_tensor_memory_reuse.sh`
3. Run assignment input: `toy-opt test/assigment_input.mlir -toy-tensor-memory-reuse`
