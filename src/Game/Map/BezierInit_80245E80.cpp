#define JMAP_INLINE_ITER_COPY
#include "Map/BezierRail.hpp"
#include "Map/RailPart.hpp"
#include "Util/JMapUtil.hpp"
#include "Util/StringUtil.hpp"
extern "C" { extern const char lbl_807CFAF0[1],lbl_806964C8[],lbl_806964D0[]; extern const f32 lbl_807DC5FC; }
inline void getCsvDataStr(const char** out,const JMapInfo* info,const char* key,s32 index) ALWAYS_INLINE {
 int field=info->searchItemInfo(key);
 if(field>=0)info->getValueFast(index,field,out);
}
inline int adjustNextIndex(int index,int count) ALWAYS_INLINE { return (index+1)%count; }
BezierRail::BezierRail(const JMapInfoIter& rIter, const JMapInfo* pInfo) {
    _18 = const_cast<JMapInfo*>(pInfo);
    mIter = new JMapInfoIter(rIter);

    const char* closedValue = lbl_807CFAF0;
    const JMapInfo* info = rIter.mInfo;

    getCsvDataStr(&closedValue, info, lbl_806964C8, rIter.mIndex);
    mIsClosed = MR::isEqualString(closedValue, lbl_806964D0);

    mPointNum = pInfo->getLength();

    _8 = mPointNum - 1;
    if (mIsClosed) {
        _8++;
    }

    f32 pointCoord = lbl_807DC5FC;
    f32 railStartCoord = lbl_807DC5FC;

    mRailParts = new RailPart[_8];
    _10 = new f32[_8];

    for (int i = 0; i < static_cast<s32>(_8); i++) {
        JMapInfoIter iterPoint1 = JMapInfoIter(pInfo, i);
        JMapInfoIter iterPoint2 = JMapInfoIter(pInfo, adjustNextIndex(i, mPointNum));

        TVec3f point1;
        TVec3f point2;
        TVec3f point1Ctrl;
        TVec3f point2Ctrl;

        MR::getRailPointPos0(iterPoint1, &point1);
        MR::getRailPointPos2(iterPoint1, &point1Ctrl);
        MR::getRailPointPos1(iterPoint2, &point2Ctrl);
        MR::getRailPointPos0(iterPoint2, &point2);

        mRailParts[i].init(point1, point1Ctrl, point2Ctrl, point2);

        // this is the strangest way to do this calculation I have ever seen
        f32 railEndCoord = railStartCoord;
        f32 prevPointCoord = pointCoord;
        f32 railLength = mRailParts[i].getTotalLength();
        railEndCoord += railLength;
        pointCoord += railEndCoord;
        railEndCoord -= pointCoord - prevPointCoord;
        _10[i] = pointCoord;
        railStartCoord = railEndCoord;
    }
}
