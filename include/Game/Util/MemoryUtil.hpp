#pragma once

#include <JSystem/JKernel/JKRHeap.hpp>
#include <revolution/mem.h>

class JKRExpHeap;
class JKRSolidHeap;

namespace MR {
    JKRHeap* getCurrentHeap();
    JKRExpHeap* getStationedHeapNapa();
    JKRExpHeap* getStationedHeapGDDR3();
    JKRHeap* getHeapNapa(const JKRHeap* pHeap);
    JKRHeap* getHeapGDDR3(const JKRHeap* pHeap);

    /// @brief Copies `size` bytes from `pSrc` to `pDst`.
    /// @param pDst The pointer to the memory to copy to.
    /// @param pSrc The pointer to the memory to copy from.
    /// @param size The number of bytes to copy.
    void copyMemory(void* pDst, const void* pSrc, u32 size);
};  // namespace MR
