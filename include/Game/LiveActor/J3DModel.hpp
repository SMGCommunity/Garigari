#pragma once

#include <revolution.h>
// Partial layout verified from LiveActor target accesses.
class J3DModel {
public:
    void setBaseScale(const Vec&) NO_INLINE;
    u8 _0[0x18];
    Vec mBaseScale; // 0x18
    Mtx mBaseTransformMtx; // 0x24
};
