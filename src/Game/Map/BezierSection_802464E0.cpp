#include "Map/BezierRail.hpp"
#include "Map/RailPart.hpp"
extern "C" { extern const f32 lbl_807DC5FC,lbl_807DC610; f32 fn_8003B8E0(f32,f32,f32); bool isNearZero__2MRFff(f32,f32); }
inline int adjustNextIndex(int index,int count) ALWAYS_INLINE { return (index+1)%count; }
void BezierRail::getIncludedSection(const RailPart** pRailParts, f32* pPos, f32 t, int direction) const {
    f32 pos = normalizePos(t, direction);
    f32 partPos = lbl_807DC5FC;
    s32 idx = -1;

    if (direction > 0) {
        for (s32 i = 0; i < static_cast<s32>(_8); i++) {
            if (!(_10[i] <= pos) || i == static_cast<s32>(_8) - 1) {
                idx = i;

                f32 newPos;
                if (i == 0) {
                    newPos = pos;
                } else {
                    s32 j = i - 1;
                    newPos = pos - _10[j];
                }
                partPos = newPos;
                break;
            }
        }
    } else {
        for (s32 i = static_cast<s32>(_8) - 1; i >= 0; i--) {
            if (i == 0 || (_10[i - 1] < pos && pos <= _10[i])) {
                idx = i;

                f32 newPos;
                if (i == 0) {
                    newPos = pos;
                } else {
                    s32 j = i - 1;
                    newPos = pos - _10[j];
                }
                partPos = newPos;
                break;
            }
        }
    }

    RailPart* part = (mRailParts+idx);
    pRailParts[0] = part;
    *pPos = fn_8003B8E0(partPos, lbl_807DC5FC, part->getTotalLength());
}

int BezierRail::getCurrentCtrlPointIndex(f32 t, bool forward) const {
    f32 pos = normalizePos(t, forward ? 1 : -1);

    if (isNearZero__2MRFff(pos,lbl_807DC610)) {
        return 0;
    }

    f32 totalLength = getTotalLength();
    if (isNearZero__2MRFff(totalLength - pos,lbl_807DC610)) {
        return !mIsClosed ? mPointNum - 1 : 0;
    }

    if (forward) {
        for (int i = 0; i < static_cast<s32>(_8); i++) {
            // this matches but is probably not written like this.
            // other "simple" configurations dont seem to match
            f32 pointCoord = _10[i];
            if (!(pointCoord <= pos)) {
                return i;
            }
        }
    } else {
        for (int i = static_cast<s32>(_8) - 1; i >= 0; i--) {
            f32 f = i > 0 ? _10[i - 1] : lbl_807DC5FC;

            f32 pointCoord = _10[i];
            if (f < pos && pos <= pointCoord) {
                return adjustNextIndex(i, mPointNum);
            }
        }
    }

    return 0;
}

