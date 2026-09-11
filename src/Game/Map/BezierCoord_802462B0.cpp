#include "Map/BezierRail.hpp"
#include "Map/RailPart.hpp"
extern "C" { extern const f32 lbl_807DC628,lbl_807DC5FC; f32 fn_8000E240(const TVec3f*); }
f32 BezierRail::getNearestRailPosCoord(const TVec3f& rPos) const {
    RailPart* part = mRailParts;
    int idx = 0;

    f32 length = part->getTotalLength();
    f32 nearestParam = part->getNearestParam(rPos, lbl_807DC628 / length);

    TVec3f pos;
    part->calcPos(&pos, nearestParam);
    pos.sub(rPos);

    f32 sqrt = fn_8000E240(&pos);

    for (int i = 1; i < static_cast<s32>(_8); i++) {
        part = (mRailParts+i);

        f32 curPartLength = part->getTotalLength();
        f32 curNearParam = part->getNearestParam(rPos, lbl_807DC628 / curPartLength);
        part->calcPos(&pos, curNearParam);

        pos.sub(rPos);
        f32 curSqrt = fn_8000E240(&pos);

        if (curSqrt < sqrt) {
            sqrt = curSqrt;
            idx = i;
            nearestParam = curNearParam;
        }
    }

    f32 val = !idx ? lbl_807DC5FC : _10[idx - 1];
    return (val + (mRailParts+idx)->getLength(lbl_807DC5FC, nearestParam, 10));
}

f32 BezierRail::getRailPosCoord(int idx) const {
    if (!idx) {
        return lbl_807DC5FC;
    }

    if (mIsClosed || idx != static_cast<s32>(mPointNum) - 1) {
        return _10[idx - 1];
    }

    return getTotalLength();
}

void BezierRail::calcCurrentRailCtrlPointIter(JMapInfoIter* pIter, f32 t, bool forward) const {
    int idx = getCurrentCtrlPointIndex(t, forward);
    calcRailCtrlPointIter(pIter, idx);
}

void BezierRail::calcRailCtrlPointIter(JMapInfoIter* pIter, int idx) const {
    pIter->mInfo = _18;
    pIter->mIndex = idx;
}

