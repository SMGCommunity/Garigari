#include "Map/BezierRail.hpp"
#include "Map/RailPart.hpp"
extern "C" {
extern const f32 lbl_807DC5FC,lbl_807DC610;
f32 fn_80040B20(f32,f32);
f32 fn_8003B8E0(f32,f32,f32);
bool isNearZero__2MRFff(f32,f32);
void fn_80245620(TVec3f*,const RailPart*,f32);
}
f32 BezierRail::normalizePos(f32 t, int direction) const {
    if (mIsClosed) {
        f32 pos = fn_80040B20(t, getTotalLength());
        if (direction < 0 && isNearZero__2MRFff(pos,lbl_807DC610)) {
            pos = getTotalLength();
        }
        if (pos < lbl_807DC5FC) {
            pos += getTotalLength();
        }
        return pos;
    } else {
        return fn_8003B8E0(t, lbl_807DC5FC, getTotalLength());
    }
}

f32 BezierRail::getTotalLength() const {
    return _10[_8 - 1];
}

f32 BezierRail::getPartLength(int idx) const {
    return mRailParts[idx].getTotalLength();
}

void BezierRail::calcPos(TVec3f* pOut, f32 t) const {
    const RailPart* part;
    f32 param;

    getIncludedSection(&part, &param, t, 1);
    part->calcPos(pOut, part->getParam(param));
}

void BezierRail::calcDirection(TVec3f* pOut, f32 t) const {
    const RailPart* part;
    f32 param;

    getIncludedSection(&part, &param, t, 1);
    fn_80245620(pOut, part, part->getParam(param));
}

void BezierRail::calcPosDir(TVec3f* pPos, TVec3f* pDir, f32 t) const {
    const RailPart* part;
    f32 param;

    getIncludedSection(&part, &param, t, 1);
    f32 val = part->getParam(param);
    part->calcPos(pPos, val);
    fn_80245620(pDir, part, val);
}

