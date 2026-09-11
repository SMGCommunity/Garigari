#pragma once

#include <revolution.h>

class HitSensor;

class SensorGroup {
public:
    SensorGroup(int, const char*);
    void add(HitSensor *);
    void remove(HitSensor *);
    void clear() const;

    s32 mCapacity; // 0x0
    s32 mSensorCount; // 0x4
    HitSensor** mSensors; // 0x8
};
