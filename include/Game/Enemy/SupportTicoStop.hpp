#pragma once

#include "Game/System/NerveExecutor.hpp"

class LiveActor;
class AnimScaleController;

class SupportTicoStop : public NerveExecutor {
public:
    SupportTicoStop(LiveActor*, AnimScaleController*);

    void exeDoNothing();
    void exeTouch();
    void exeEndTouch();

    bool tryTouch();
    bool tryAttachTouch();

    bool isTouching() const;

    inline void resetTouchBools() {
        _15 = _14 = false;
    }
    /* 0x08 */ LiveActor* mHost;
    /* 0x0C */ AnimScaleController* mScaleController;
    /* 0x10 */ s32 _10;
    /* 0x14 */ bool _14;
    /* 0x15 */ bool _15;
    /* 0x16 */ bool mUsePointerTouch;  ///< Does the host use the standard "PointerTouch" effect instead of its own "Touch" effect?
};
