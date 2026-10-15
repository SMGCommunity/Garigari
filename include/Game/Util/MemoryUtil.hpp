#pragma once

#include <JSystem/JKernel/JKRHeap.hpp>
#include <revolution/mem.h>

class JKRExpHeap;
class JKRSolidHeap;

namespace MR {
    class CurrentHeapRestorer {
    public:
        CurrentHeapRestorer(JKRHeap* pHeap);

        ~CurrentHeapRestorer();

    private:
        /* 0x00 */ JKRHeap* _0;
    };

    JKRHeap* getCurrentHeap();
    JKRExpHeap* getStationedHeapNapa();
    JKRExpHeap* getStationedHeapGDDR3();
    JKRHeap* getHeapNapa(const JKRHeap* pHeap);
    JKRHeap* getHeapGDDR3(const JKRHeap* pHeap);
    void becomeCurrentHeap(JKRHeap* pHeap) NO_INLINE;
    bool isEqualCurrentHeap(JKRHeap* pHeap);
    void adjustHeapSize(JKRExpHeap* pHeap);

    /// @brief Copies `size` bytes from `pSrc` to `pDst`.
    /// @param pDst The pointer to the memory to copy to.
    /// @param pSrc The pointer to the memory to copy from.
    /// @param size The number of bytes to copy.
    void copyMemory(void* pDst, const void* pSrc, u32 size);

    /// @brief Fills `size` bytes at `pDst` with `0`.
    /// @param pDst The pointer to the memory to fill.
    /// @param size The number of bytes to fill.
    void zeroMemory(void* pDst, u32 size);
};  // namespace MR
