#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

class BezierRailPart {
public:
    inline BezierRailPart(const TVec3f &a1, const TVec3f &a2, const TVec3f &a3, const TVec3f &a4) __attribute__((always_inline)) {
        set(a1, a2, a3, a4);
     }

    void set(const TVec3f &, const TVec3f &, const TVec3f &, const TVec3f &);
    void calcPos(TVec3f *, f32) const;
    void calcVelocity(TVec3f *, f32) const;
    f32 getLength(f32, f32, int) const;
    f32 getParam(f32) const;
    f32 getNearestParam(const TVec3f &, f32) const;

    TVec3f mPoints[4];      // 0x00
    f32 mLength;            // 0x30
};
