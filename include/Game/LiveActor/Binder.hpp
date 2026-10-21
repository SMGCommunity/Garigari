#pragma once

#include "Game/Map/HitInfo.hpp"
#include <revolution.h>

class Binder {
public:
    u8 _0[0x18];
    f32 mRadius;  // 0x18
    f32 mOffsetY;
    

    inline bool isBindedGround() const {
        return 0.0f <= _C8;
    }

    HitInfo mGroundInfo;
    f32 _C8;
};
