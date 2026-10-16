#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class TicoCoin : public LiveActor {
public:
    TicoCoin(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void initAfterPlacement();
    virtual void makeActorAppeared();
    virtual void control();
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    bool tryCollect();

    void exeAppear();
    void exeRotate();
    void exeCollect();
    void exeDisappear();

    bool isCollectedInStage() const;

    /* 0x90 */ TVec3f _90;
};
