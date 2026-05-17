# Tensor Memory Reuse Assignment (Starter)

This starter is for a compiler-style memory planning exercise over a Toy SSA graph.

## Starter Input

- Graph file: `examples/tensor_memory_reuse.ttir`
- Run command: `examples/run_tensor_memory_reuse.sh`
- Pass entry: `-toy-tensor-memory-reuse`

### Reference Operation Graph

| Op  | Expression          |       Type | Output size | Compute size |
| --- | ------------------- | ---------: | ----------: | -----------: |
| op0 | `%a = conv(%input)` |       Conv |          40 |           30 |
| op1 | `%b = relu(%a)`     |       ReLU |          40 |            5 |
| op2 | `%c = conv(%a)`     |       Conv |          30 |           30 |
| op3 | `%d = mul(%c)`      |        Mul |          30 |           10 |
| op4 | `%e = add(%b, %d)`  | Add / join |          40 |            8 |
| op5 | `%f = relu(%e)`     |       ReLU |          40 |            5 |
| op6 | `%g = conv(%e)`     |       Conv |          50 |           30 |
| op7 | `%h = sub(%g, %a)`  | Sub / join |          50 |            8 |
| op8 | `%i = add(%f, %h)`  | Add / join |          50 |            8 |
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

Implement analysis/reporting in `passes/MemoryPlanning.cpp`.
`passes/MemoryAnalysisPass.cpp` is the baseline pass wrapper and should stay thin.

Use this order:

1. Collect compute ops in execution order.
2. Build producer-consumer relationships.
3. Compute tensor lifetimes.
4. Track live tensors before/during/after each op.
5. Plan slot usage for tensors/workspaces.
6. Validate memory constraints.
7. Compute per-op and max peak memory.

## Required Output Sections (Template)

Print these section headers in your report, then fill them from your implementation:

1. `Operation List`
2. `Producer-Consumer Edges`
3. `Tensor Lifetime Table`
4. `Live Tensors Before/During/After`
5. `Tensor Slot Assignment`
6. `Workspace Slot Assignment`
7. `Output Slot Per Operation`
8. `Peak Memory Per Operation`
9. `Maximum Peak Memory`
10. `Algorithm Notes`
11. `Optimality Notes`

## Starter Rules

Keep starter files exercise-ready and unsolved.

Do not commit any final solved content such as:

- Completed lifetime table
- Final live-before/during/after answers
- Final tensor-to-slot assignment
- Final workspace-to-slot assignment
- Final peak-memory answer
- Final validity/optimality conclusion for the provided graph

## Suggested Validation Loop

1. Build: `ninja -C build toy-passes toy-opt`
2. Run example: `./examples/run_tensor_memory_reuse.sh`
3. Run starter test: `toy-opt test/tensor_memory_reuse/basic.mlir -toy-tensor-memory-reuse`
