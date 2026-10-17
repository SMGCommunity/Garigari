#pragma once

#include "Game/Screen/LayoutActor.hpp"

class PopUpAddTimeAttackTime : public LayoutActor {
public:
    PopUpAddTimeAttackTime(const char* pName, f32);

    /* 0x2C - 0x38 */ u8 pad[0x38 - sizeof(LayoutActor)];
};
