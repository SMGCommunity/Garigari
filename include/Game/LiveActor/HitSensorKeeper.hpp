#pragma once

#include <JGeometry.hpp>
#include <revolution.h>

class HitSensor;
class HitSensorInfo;
class LiveActor;

class HitSensorKeeper {
public:
    HitSensorKeeper(int);

    HitSensorInfo* add(const char *, u32, u16, f32, LiveActor *, const TVec3f &);
    HitSensorInfo* addCallback(const char *, u32, u16, f32, LiveActor *);
    HitSensor* getSensor(const char *) const;
    void update();
    void doObjCol();
    void clear();
    void validate();
    void invalidate();
    void validateBySystem();
    void invalidateBySystem();
    HitSensorInfo* getNthSensorInfo(int) const;
    HitSensorInfo* getSensorInfo(const char *) const;
    void registHitSensorInfo(HitSensorInfo *);

    int mSensorCount;                       // 0x00
    int mMaxSensorCount;                    // 0x04
    HitSensorInfo** mSensorInfo;            // 0x08
    u32 _C;
    u32 _10;
};
