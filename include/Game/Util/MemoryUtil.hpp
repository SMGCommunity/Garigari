#pragma once

#include <JSystem/JKernel/JKRHeap.hpp>
#include <revolution/mem.h>

class JKRExpHeap;
class JKRSolidHeap;

namespace MR {
    JKRHeap* getHeapNapa(const JKRHeap* pHeap);
    JKRHeap* getHeapGDDR3(const JKRHeap* pHeap);
};  // namespace MR
