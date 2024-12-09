#pragma once

#include <revolution.h>

class LiveActorFlag {
public:
    LiveActorFlag();

    bool mIsDead;                       // 0x00
    bool mIsNotReleasedAnimFrame;       // 0x01
    bool mIsOnCalcAnim;                 // 0x02
    bool mIsNoCalcView;                 // 0x03
    bool mIsNoEntryDrawBuffer;          // 0x04
    bool mIsOnBind;                     // 0x05
    bool mIsCalcGravity;                // 0x06
    bool mIsClipped;                    // 0x07
    bool mIsClippingInvalid;            // 0x08
};
