#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include "JSystem/JGeometry/TMatrix.hpp"

class PopUpAddTimeAttackTime;

class TimeAttackClock : public LiveActor {
public:
    TimeAttackClock(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void appear();
    virtual void calcAndSetBaseMtx();
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void addTimer();
    void exeWait();
    void exeCollect();

    /* 0x90 */ TPos3f _90;
    /* 0xC0 */ TPos3f _C0;
    /* 0xF0 */ PopUpAddTimeAttackTime* mTimePopup;
    /* 0xF4 */ s32 mTimeToAdd;
};
