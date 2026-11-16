#pragma once

#include <JSystem/JGeometry/TVec.hpp>
#include <revolution/mtx.h>

class LiveActor;
class YoshiLockOnTarget;

namespace MR {
    YoshiLockOnTarget* createYoshiLockOnTarget(LiveActor*, MtxPtr, const TVec3f&);
};  // namespace MR
