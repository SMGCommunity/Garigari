#pragma once

#include <JGeometry.hpp>
#include <revolution.h>

class HitSensor;

class HitSensorInfo {
public:
    HitSensorInfo(const char *, HitSensor *, const TVec3f *, MtxPtr, const TVec3f &, bool);

    void setFollowPos(const TVec3f *);
    void setFollowMtx(MtxPtr);
    void update();
    void doObjCol();

    const char* mSensorName;            // 0x00
    s32 mNameHash;                      // 0x04
    HitSensor* mSensor;                 // 0x08
    TVec3f _C;
    const TVec3f* mFollowPos;           // 0x18
    MtxPtr mFollowMtx;                  // 0x1C
    bool _20;
};
