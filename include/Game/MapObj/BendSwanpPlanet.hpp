#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class CollisionObj;

class BendSwanpPlanet : public LiveActor {
public:
    BendSwanpPlanet(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void exeWaitA();
    void exeMoveA();
    void exeWaitB();
    void exeMoveB();
    void exeWaitC();

    /* 0x90 */ CollisionObj** mCollisionObjs;
};
