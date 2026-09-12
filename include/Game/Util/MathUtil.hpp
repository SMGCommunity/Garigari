#pragma once

#include <revolution.h>
#include <JGeometry.hpp>
#include <JMath.hpp>
#include <cmath>

static Vec gZeroVec;

namespace MR {
    void sortSmall(s32, u32 *, s32 *);

    void initAcosTable();

    bool isNearZero(f32, f32);
    bool isNearZero(const TVec3f &, f32);

    f32 lerp(u8, u8, f32);
    f32 lerp(f32, f32, f32);
    //f32 lerp(GXColor, GXColor, f32);
    void sortSmall(long, f32*, long*);
    void sortSmall(long, u32*, long*);
    void PSvecBlend(const TVec3f*, const TVec3f*, f32, f32);
    void vecBlend(const TVec3f&, const TVec3f&, TVec3f*, f32); // DIFFERENT THAN SMG1
    void vecBlendNormal(TVec3f*, const TVec3f&, const TVec3f&, f32);

    f32 vecKillElement(const TVec3f&, const TVec3f&, TVec3f*);
    void makeAxisFrontUp(TVec3f*, TVec3f*, const TVec3f&, const TVec3f&);
    void makeAxisFrontSide(TVec3f*, TVec3f*, const TVec3f&, const TVec3f&);
    void makeAxisUpFront(TVec3f*, TVec3f*, const TVec3f&, const TVec3f&);
    void makeAxisUpSide(TVec3f*, TVec3f*, const TVec3f&, const TVec3f&);
    void makeAxisVerticalZX(TVec3f*, const TVec3f&);
    //void normalize(TVec2f*);
    void normalize(TVec3f*);
    //void normalize(TVec2f*, const TVec2f&);
    void normalize(TVec3f*, const TVec3f&);
    //bool normalizeOrZero(TVec2f*);
    bool normalizeOrZero(TVec3f*);
    bool normalizeOrZero(const TVec3f&, TVec3f*);
    f32 turnVecToVecRadian(TVec3f*, const TVec3f&, const TVec3f&, f32, const TVec3f&);
    f32 turnVecToVecDegree(TVec3f*, const TVec3f&, const TVec3f&, f32, const TVec3f&);
    void rotateVecDegree(TVec3f*, const TVec3f&, f32);
    void rotateVecDegree(TVec3f*, const TVec3f&, const TVec3f&, f32);
    void rotateVecRadian(TVec3f*, const TVec3f&, f32);
    void rotateVecRadian(TVec3f*, const TVec3f&, const TVec3f&, f32);
    f32 diffAngleSigned(const TVec3f&, const TVec3f&, const TVec3f&);

    f32 getInterpolateValue(f32, f32, f32);

    inline f32 sin(f32 x) {
        return JMASinRadian(x);
    }
    inline f32 cos(f32 x) {
        return JMACosRadian(x);
    }
    inline f32 sinDegree(f32 x) {
        return JMASinDegree(x);
    }
    inline f32 cosDegree(f32 x) {
        return JMACosDegree(x);
    }

    inline f32 repeat(f32 value, f32 min, f32 max) {
        return min + (f32)fmod(max + (value - min), max);
    }

    void repeatDegree(f32* value);

    inline f32 repeatDegree(f32 value);
    s32 clamp(s32 val, s32 min, s32 max);
    f32 clamp(f32 val, f32 min, f32 max);
};
