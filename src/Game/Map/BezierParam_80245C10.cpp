#include "Map/BezierRail.hpp"
extern "C" {
extern const f32 lbl_807DC600,lbl_807DC5FC,lbl_807DC60C,lbl_807DC618,lbl_807DC61C,lbl_807DC620;
double fn_8063D954(double);
f32 PSVECMag(const TVec3f*);
}
inline f32 velocityLength(const BezierRailPart* part,f32 t) ALWAYS_INLINE {
 TVec3f value;part->calcVelocity(&value,t);return PSVECMag(&value);
}

extern "C" {
extern const f32 lbl_807DC5F8,lbl_807DC614;
f32 fn_8003B8E0(f32,f32,f32);
double __fabs(double);
}
f32 BezierRailPart::getParam(f32 t) const {
    f32 param = t / mLength;
    f32 railLength = getLength(lbl_807DC5FC, param, 10);

    if (__fabs(t - railLength) <= lbl_807DC614) {
        return param;
    }

    f32 length = railLength;
    for (s32 count = 0; count < 5; count++) {
        f32 mag = velocityLength(this,param);
        param = fn_8003B8E0(param + (t - length) / mag, lbl_807DC5FC, lbl_807DC5F8);
        length = getLength(lbl_807DC5FC, param, 10);

        f32 limit = lbl_807DC614;
        if (__fabs(t - length) <= limit) {
            return param;
        }
    }

    if (length < lbl_807DC5FC || lbl_807DC5F8 < param) {
        param = fn_8003B8E0(param, lbl_807DC5FC, lbl_807DC5F8);
    }

    return param;
}

