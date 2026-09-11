#pragma once
#pragma once

#include "Util/JMapInfo.hpp"
#include <revolution.h>
#include <JGeometry.hpp>

class RailPart;

class BezierRailPart {
public:
    void set(const TVec3f &, const TVec3f &, const TVec3f &, const TVec3f &);
    void calcPos(TVec3f *, f32) const;
    void calcVelocity(TVec3f *, f32) const;
    f32 getLength(f32, f32, int) const;
    f32 getParam(f32) const;
    f32 getNearestParam(const TVec3f &, f32) const;

    f32 _0[12];            // 0x00: four vector coefficients, scalar storage preserves trivial construction
    f32 mLength;            // 0x30
};

class BezierRail {
public:

    BezierRail(const JMapInfoIter &, const JMapInfo *);

    f32 normalizePos(f32, int) const;
    f32 getPartLength(int) const;
    void calcPos(TVec3f *, f32) const;
    void calcDirection(TVec3f *, f32) const;
    void calcPosDir(TVec3f *, TVec3f *, f32) const;
    f32 getNearestRailPosCoord(const TVec3f &) const;
    f32 getRailPosCoord(int) const;
    void calcCurrentRailCtrlPointIter(JMapInfoIter *, f32, bool) const;
    void calcRailCtrlPointIter(JMapInfoIter *, int) const NO_INLINE;
    void getIncludedSection(const RailPart **, f32 *, f32, int) const;
    int getCurrentCtrlPointIndex(f32, bool) const;

    f32 getTotalLength() const NO_INLINE;

    bool mIsClosed;       // 0x0
    u8 _1;
    u8 _2;
    u8 _3;
    u32 mPointNum;        // 0x4  
    u32 _8;
    RailPart* mRailParts; // 0xC
    f32* _10;
    JMapInfoIter* mIter;  // 0x14
    JMapInfo* _18;
};
