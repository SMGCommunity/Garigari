#pragma once

#include "Liveactor/Liveactor.hpp"
#include <revolution.h>

extern void fn_8021F470(const ActionSoundInfo *pSoundInfo, const char *pName, s32 pitch, s32 velocity, s32 volume);

namespace MR {
    const ActionSoundInfo *getActionSoundInfo(const LiveActor *pActor) NO_INLINE;
    const ActionSoundInfo *fn_80008370(const LiveActor *pActor) NO_INLINE;
    void startActionSound(const LiveActor* pActor, const char* pName, s32 pitch, s32 velocity, s32 volume);
};
