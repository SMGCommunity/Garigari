#pragma once

#include <revolution.h>

class ActionSoundInfo;

class ActorSoundHolder {
public:
    u8 m_00[4];                          // 0x00
    ActionSoundInfo *mActionSoundInfo;      // 0x04
};
