#pragma once

#include <revolution.h>

class HitSensor;

class SensorGroup {
public:
    void add(HitSensor *);
    void remove(HitSensor *);
};
