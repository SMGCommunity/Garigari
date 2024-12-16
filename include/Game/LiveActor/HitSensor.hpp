#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

class SensorGroup;
class LiveActor;

class HitSensor {
public:
    HitSensor(u32, u16, f32, LiveActor *);

    bool receiveMessage(u32, HitSensor *);
    void setType(u32);
    bool isType(u32) const;
    void validate();
    void invalidate();
    void validateBySystem();
    void invalidateBySystem();
    void addHitSensor(HitSensor *);

    u32 mType;                  // 0x0
    TVec3f mOffset;             // 0x4
    f32 mRadius;                // 0x10
    u16 mSensorCount;           // 0x14
    u16 mGroupSize;             // 0x16
    HitSensor** mSensors;       // 0x18
    SensorGroup* mSensorGroup;  // 0x1C
    bool mValidBySystem;        // 0x20
    bool mValidByHost;          // 0x21
    LiveActor* mHostActor;      // 0x24
};
