#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class CollisionObj : public LiveActor {
public:
    CollisionObj(LiveActor* pHost, const char* pName, const char* pCollisionName, HitSensor* pSensor, MtxPtr pMatrix, int movementType);

    virtual void init(const JMapInfoIter& rIter);
    virtual void movement();
    virtual MtxPtr getBaseMtx() const;

    /* 0x90 */ MtxPtr mBaseMtx;
};
