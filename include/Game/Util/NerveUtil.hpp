#pragma once

#include <revolution/types.h>

class Nerve;
class NerveExecutor;

namespace MR {
    /// @brief Determines if the working nerve action's frame of execution is equal to the given frame value.
    /// @param pExecutor The pointer to the nerve action executor.
    /// @param step The frame value to compare with.
    /// @return `true` if the working frame of execution is equal to `step`, `false` otherwise.
    bool isStep(const NerveExecutor* pExecutor, s32 step);

    /// @brief Determines if the working nerve action's frame of execution is equal to the first frame value.
    /// @param pExecutor The pointer to the nerve action executor.
    /// @return `true` if the working frame of execution is equal to the first frame value, `false` otherwise.
    bool isFirstStep(const NerveExecutor* pExecutor);
    
    /// @brief Determines if the working nerve action's frame of execution is greater than or equal to the given frame value.
    /// @param pExecutor The pointer to the nerve action executor.
    /// @param step The frame value to compare with.
    /// @return `true` if the working frame of execution is greater than or equal to `step`, `false` otherwise.
    bool isGreaterEqualStep(const NerveExecutor* pExecutor, s32 step);
};  // namespace MR
