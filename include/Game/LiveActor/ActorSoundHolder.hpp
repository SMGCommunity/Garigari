#pragma once

#include <JSystem/JGeometry/TVec.hpp>
#include <revolution.h>

class LiveActor;
class ActionSoundInfo;

class ActorSoundHolder {
public:
    ActorSoundHolder(LiveActor*, s32, const char*, const TVec3f*, const TVec3f&);

    /* 0x00 */ u8 _0[4];
    /* 0x04 */ ActionSoundInfo* mActionSoundInfo;
};
