#pragma once

#include "Game/LiveActor/LiveActor.hpp"

namespace MR {
    const ActionSoundInfo* getActionSoundInfo(const LiveActor* pActor) NO_INLINE;
    const ActionSoundInfo* fn_80008370(const LiveActor* pActor) NO_INLINE;
    void startActionSound(const LiveActor* pActor, const char* pName, s32 pitch = -1, s32 velocity = -1, s32 volume = -1);
};  // namespace MR
