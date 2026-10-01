#pragma once

#include <revolution.h>
#include "GameAudio/ActionSoundInfo.hpp"

class ActorSoundHolder {
public:
    u8 m_00[4];                             // 0x00
    ActionSoundInfo *mActionSoundInfo;      // 0x04
};
