#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class SupportFlushPoint : public LiveActor {
public:
    enum ITEM_TYPE { ITEM_TYPE_STAR_PIECE = -1, ITEM_TYPE_COIN = 0 };

    SupportFlushPoint(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void control();
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void exeAppear();
    void exeHide();
    void exeWait();
    void exeGenerateItem();
    void exeDisappear();

    /* 0x90 */ s32 mItemType;
};
