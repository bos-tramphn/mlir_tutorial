#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR=$(cd -- "$(dirname "${BASH_SOURCE[0]}")" && pwd)
PROJECT_ROOT=$(cd -- "${SCRIPT_DIR}/.." && pwd)
BUILD_DIR=${BUILD_DIR:-"${PROJECT_ROOT}/build"}
TOY_OPT=${TOY_OPT:-"${BUILD_DIR}/bin/toy-opt"}
ALT_TOY_OPT="${BUILD_DIR}/tools/toy-opt"
INPUT=${1:-"${SCRIPT_DIR}/tensor_memory_reuse.ttir"}

if [ ! -x "${TOY_OPT}" ]; then
  if [ -x "${ALT_TOY_OPT}" ]; then
    TOY_OPT="${ALT_TOY_OPT}"
  else
    echo "error: ${TOY_OPT} (or ${ALT_TOY_OPT}) is missing. Build the project first." >&2
    exit 1
  fi
fi

set -x
"${TOY_OPT}" "${INPUT}" \
  -toy-tensor-memory-reuse \
  --mlir-print-op-on-diagnostic
set +x
