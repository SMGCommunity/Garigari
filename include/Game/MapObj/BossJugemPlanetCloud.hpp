#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class BossJugemPlanetCloud : public LiveActor {
public:
    BossJugemPlanetCloud(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void exeWhite();
    void exeWhiteToGray();
    void exeGray();
    void exeGrayToWhite();
};
