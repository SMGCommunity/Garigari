#include <JGeometry/TVec.hpp>
namespace MR { void normalize(TVec3f*); }
extern "C" {
f32 PSVECMag(const Vec*);
f32 PSVECDistance(const Vec*, const Vec*);
void fn_80037060(TVec3f*, const TVec3f*, const TVec3f*);
extern const f32 lbl_807DC6D4;
bool fn_8024C7F0(const TVec3f& point, const TVec3f& origin, const TVec3f& segment, f32 tolerance) {
    f32 length = PSVECMag(&segment);
    TVec3f direction(segment);
    MR::normalize(&direction);
    TVec3f difference;
    fn_80037060(&difference, &point, &origin);
    f32 projection = direction.dot(difference);
    if (projection < lbl_807DC6D4 || projection > length) return false;
    direction.scale(projection);
    return !(PSVECDistance(&direction, &difference) > tolerance);
}
}
