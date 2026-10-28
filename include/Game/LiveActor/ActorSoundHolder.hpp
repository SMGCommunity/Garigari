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
    /* 0x08 */ u32 _8;
    /* 0x0C */ u32 _C;
    /* 0x10 */ u32 _10;
};
