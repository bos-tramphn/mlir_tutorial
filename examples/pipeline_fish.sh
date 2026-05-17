#!/usr/bin/env fish

set SCRIPT_DIR (cd (dirname (status --current-filename)); and pwd)
set PROJECT_ROOT (cd "$SCRIPT_DIR/.."; and pwd)
set BUILD_DIR (if set -q BUILD_DIR; echo $BUILD_DIR; else; echo "$PROJECT_ROOT/build"; end)
set TOY_OPT (if set -q TOY_OPT; echo $TOY_OPT; else; echo "$BUILD_DIR/bin/toy-opt"; end)
set ALT_TOY_OPT "$BUILD_DIR/tools/toy-opt"
set INPUT (if set -q argv[1]; echo $argv[1]; else; echo "$SCRIPT_DIR/intro.toy"; end)

if not test -x "$TOY_OPT"
    if test -x "$ALT_TOY_OPT"
        set TOY_OPT "$ALT_TOY_OPT"
    else
        echo "error: $TOY_OPT (or $ALT_TOY_OPT) is missing. Build the project first." >&2
        exit 1
    end
end

set fish_trace 1
"$TOY_OPT" "$INPUT" \
    --allow-unregistered-dialect \
    --pass-pipeline='builtin.module(toy-frontend)' \
    -mlir-print-ir-after-all
set fish_trace 0