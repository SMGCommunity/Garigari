#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class ConstructionLight : public LiveActor {
public:
    ConstructionLight(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void appear();
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void exeNormal();
    void exeBreak();

    /* 0x90 */ bool mSpawnsCoin;
};
