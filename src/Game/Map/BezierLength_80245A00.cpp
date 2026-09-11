#include "Map/BezierRail.hpp"
extern "C" {
extern const f32 lbl_807DC600,lbl_807DC5FC,lbl_807DC60C,lbl_807DC618,lbl_807DC61C,lbl_807DC620;
double fn_8063D954(double);
f32 PSVECMag(const TVec3f*);
}
inline f32 velocityLength(const BezierRailPart* part,f32 t) ALWAYS_INLINE {
 TVec3f value;part->calcVelocity(&value,t);return PSVECMag(&value);
}
f32 BezierRailPart::getLength(f32 t1, f32 t2, int k) const {
    f32 len1, len2;

    f32 m3 = lbl_807DC600 * (velocityLength(this,t1) + velocityLength(this,t2));

    f32 tDiff = (t2 - t1);
    f32 temp = (1.0f / (k * 2.0));
    f32 delta = tDiff * temp;

    len1 = lbl_807DC5FC;
    len2 = lbl_807DC5FC;

    for (s32 seg = 1; seg <= k; seg++) {
        s32 idxA = ((seg * 2) - 1);
        s32 idxB = (seg * 2);

        f32 tA = t1 + delta * idxA;
        f32 tB = t1 + delta * idxB;

        len1 += velocityLength(this,tA);

        if (seg != k) {
            len2 += velocityLength(this,tB);
        }
    }

    f32 len = fn_8063D954(lbl_807DC61C * static_cast< f32 >((1.0 / 3.0) * delta * ((lbl_807DC618 * len1) + (m3 + (lbl_807DC60C * len2)))));
    f32 rescale = lbl_807DC620;
    len *= rescale;
    return len;
}

