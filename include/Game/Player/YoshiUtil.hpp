#pragma once

#include <revolution/types.h>

class YoshiLockOnTarget;

namespace YoshiFunction {
    bool tryYoshiEat(YoshiLockOnTarget*);
};  // namespace YoshiFunction

namespace MR {
    bool isMsgYoshiStartTongue(u32);
    bool isMsgYoshiLoopTongue(u32);
    bool isMsgYoshiReleaseEaten(u32);
    bool isMsgYoshiCancelEaten(u32);
};  // namespace MR
