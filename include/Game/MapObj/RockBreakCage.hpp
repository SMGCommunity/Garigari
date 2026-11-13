#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class BreakModel;

class RockBreakCage : public LiveActor {
public:
    RockBreakCage(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void kill();
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void exeWait();
    void exeBreak();
    void exeCrack();

    /* 0x90 */ s32 mRemainingHits;
    /* 0x94 */ BreakModel* mBreakModel;
    /* 0x98 */ const char* mObjectName;
};
