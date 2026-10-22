#pragma once

#include "Game/LiveActor/HitSensor.hpp"
#include "JSystem/JGeometry/TMatrix.hpp"
#include <revolution.h>

class CollisionZone;

class CollisionParts {
public:
    CollisionParts();
    
    void init(const TPos3f&, HitSensor*, const void*, const void*, s32, bool);
    void initWithAutoEqualScale(const TPos3f&, HitSensor*, const void*, const void*, s32, bool);
    void initWithNotUsingScale(const TPos3f&, HitSensor*, const void*, const void*, s32, bool);

    TPos3f* _0;
    s32 mKeeperIndex;
};
