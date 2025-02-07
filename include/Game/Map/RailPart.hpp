#pragma once

#include <JGeometry.hpp>
#include <revolution.h>

class LinearRailPart;
class BezierRailPart;

class RailPart {
public:
    RailPart();

    void init(const TVec3f &, const TVec3f &, const TVec3f &, const TVec3f &);
    void initForBezier(const TVec3f &, const TVec3f &, const TVec3f &, const TVec3f &);
    void calcPos(TVec3f *, f32) const;
    void calcVelocity(TVec3f *, f32) const;
    f32 getLength(f32, f32, int) const;
    f32 getTotalLength() const;
    f32 getParam(f32) const;
    f32 getNearestParam(const TVec3f &, f32) const;

    LinearRailPart* mLinearRailPart;                // 0x00
    BezierRailPart* mBezierRailPart;                // 0x04
};

class LinearRailPart {
public:
    inline LinearRailPart() { }

    void set(const TVec3f &, const TVec3f &);
    f32 getNearestParam(const TVec3f &, f32) const;

    TVec3f mStartPoint;         // 0x00
    TVec3f mStopPoint;          // 0x0C
    f32 mMag;                   // 0x18
};
