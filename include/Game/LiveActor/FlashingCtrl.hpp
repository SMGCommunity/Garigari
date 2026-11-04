#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class FlashingCtrl : public NameObj {
public:
    FlashingCtrl(LiveActor*, bool);

    virtual void movement();

    void start(int);
    void end();
    s32 getCurrentInterval() const;
    bool isNowFlashing() const NO_INLINE;
    bool isNowOn() const NO_INLINE;
    void updateFlashing();

    /* 0x14 */ LiveActor* mActor;
    /* 0x18 */ bool mToggleDraw;
    /* 0x19 */ bool mIsEnded;
    /* 0x1A */ u8 mOverrideInterval;
    /* 0x1C */ s32 mTimer;
    /* 0x20 */ s32 mFlashStartTime;
    /* 0x24 */ bool mDoBlink;
};
