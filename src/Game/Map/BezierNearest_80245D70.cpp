#include "Map/BezierRail.hpp"
extern "C" { extern const f32 lbl_807DC5FC,lbl_807DC5F8,lbl_807DC608,lbl_807DC624; }
// Paired-single squared distance, reconstructed from the target's inline helper.
inline f32 squaredDistance(register const TVec3f* a,register const TVec3f* b) ALWAYS_INLINE {
 register f32 pairHead,pairTail,pairResult;
 asm {
  psq_l pairResult,4(a),0,0
  psq_l pairTail,4(b),0,0
  psq_l pairHead,0(a),0,0
  ps_sub pairTail,pairResult,pairTail
  psq_l pairResult,0(b),0,0
  ps_sub pairResult,pairHead,pairResult
  ps_mul pairTail,pairTail,pairTail
  ps_madd pairResult,pairResult,pairResult,pairTail
  ps_sum0 pairResult,pairResult,pairTail,pairTail
 }
 return pairResult;
}
f32 BezierRailPart::getNearestParam(const TVec3f& rPos, f32 delta) const {
    f32 nearestParam = lbl_807DC608;
    f32 nearestMag = lbl_807DC624;

    for (f32 t = lbl_807DC5FC; t <= lbl_807DC5F8; t += delta) {
        TVec3f pos;
        calcPos(&pos, t);
        f32 mag = squaredDistance(&pos,&rPos);
        if (mag < nearestMag) {
            nearestParam = t;
            nearestMag = mag;
        }
    }

    return nearestParam;
}

