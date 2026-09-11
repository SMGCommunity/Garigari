#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

class Binder {
public:
    void clear();
    TVec3f bind(const TVec3f&);
    Binder(MtxPtr, const TVec3f*, const TVec3f*, f32, f32, u32);
    u8 _0[0x18];
    f32 mRadius;            // 0x18
    u8 _1C[0x1F0 - 0x1C]; // Remaining fields are unrecovered; target allocation size is 0x1F0.
};
