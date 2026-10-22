#pragma once

#include "Game/LiveActor/HitSensor.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>
#include <revolution.h>

class CollisionZone;

class CollisionParts {
public:
    CollisionParts();

    void init(const TPos3f&, HitSensor*, const void*, const void*, s32, bool);
    void addToBelongZone();
    void removeFromBelongZone();
    void resetAllMtx(const TPos3f&);
    void resetAllMtx();
    void setMtx(const TPos3f&);
    void setMtx();
    void updateMtx();
    void initWithAutoEqualScale(const TPos3f&, HitSensor*, const void*, const void*, s32, bool);
    void initWithNotUsingScale(const TPos3f&, HitSensor*, const void*, const void*, s32, bool);
    void updateBoundingSphereRange();
    void updateBoundingSphereRange(TVec3f);

    TPos3f* _0;
    bool _CC;
    bool _CD;
    bool _CE;
    f32 _D8;
    s32 mKeeperIndex;
};
