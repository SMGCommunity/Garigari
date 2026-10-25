#pragma once

#include "Game/GameAudio/ActionSoundInfo.hpp"
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution.h>

class LiveActor;

class ActorSoundHolder {
public:
    ActorSoundHolder(LiveActor*, s32, const char*, const TVec3f*, const TVec3f&);

    /* 0x00 */ u8 _0[4];
    /* 0x04 */ ActionSoundInfo* mActionSoundInfo;
};
