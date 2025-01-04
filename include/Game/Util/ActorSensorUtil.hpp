#pragma once

#include <revolution.h>

class LiveActor;
class HitSensor;

namespace MR {
    LiveActor* getSensorHost(const HitSensor *);

    s32 getSensorNum(const LiveActor *);

    void scaleAllSensorRadius(LiveActor *, f32);
};
