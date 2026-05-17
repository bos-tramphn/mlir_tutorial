#ifndef TOY_MEMORY_ANALYSIS_PASS_H
#define TOY_MEMORY_ANALYSIS_PASS_H

#include "mlir/Pass/Pass.h"
#include <memory>

namespace toy {

std::unique_ptr<mlir::Pass> createToyTensorMemoryReusePass();

namespace detail {
void registerToyTensorMemoryReusePass();
}

} // namespace toy

#endif // TOY_MEMORY_ANALYSIS_PASS_H
