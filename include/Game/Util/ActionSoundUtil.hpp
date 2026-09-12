#pragma once

#include <revolution.h>

class LiveActor;

namespace MR {
    // getActionSoundInfo

    void startActionSound(const LiveActor* pActor, const char* pName, s32 pitch, s32 velocity, s32 volume);
};
