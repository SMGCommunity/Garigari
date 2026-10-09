#pragma once

#include "GameAudio/ActionSoundInfo.hpp"
#include <revolution.h>

class ActorSoundHolder {
public:
    /* 0x00 */ u8 m_00[4];
    /* 0x04 */ ActionSoundInfo* mActionSoundInfo;
};
