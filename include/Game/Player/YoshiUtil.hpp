#pragma once

#include <revolution/types.h>

class YoshiLockOnTarget;

namespace YoshiFunction {
    bool tryYoshiEat(YoshiLockOnTarget*);
};  // namespace YoshiFunction

namespace MR {
    bool isMsgYoshiStartTongue(u32);
};  // namespace MR
