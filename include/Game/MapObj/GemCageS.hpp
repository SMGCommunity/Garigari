#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class BreakModel;

class GemCageS : public LiveActor {
public:
    enum ITEM_TYPE {
        ITEM_TYPE_STAR_PIECE = 0,
        ITEM_TYPE_COIN = 1
    };

    GemCageS(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    bool appearItem();

    void exeWait();
    void exeBreak();

    /* 0x90 */ BreakModel* mBreakModel;
    /* 0x94 */ s32 mItemType;
    /* 0x98 */ bool mIsRockCage;
};
