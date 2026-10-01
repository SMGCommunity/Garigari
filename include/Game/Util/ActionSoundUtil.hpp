#pragma once

#include "Liveactor/Liveactor.hpp"

namespace MR {
    const ActionSoundInfo *getActionSoundInfo(const LiveActor *pActor) NO_INLINE;
    const ActionSoundInfo *fn_80008370(const LiveActor *pActor) NO_INLINE;
    void startActionSound(const LiveActor* pActor, const char* pName, s32 pitch, s32 velocity, s32 volume);
};
