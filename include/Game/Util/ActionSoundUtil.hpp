#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class ActionSoundInfo;

namespace MR {
    const ActionSoundInfo* getActionSoundInfo(const LiveActor* pActor) NO_INLINE;
    const ActionSoundInfo* fn_80008370(const LiveActor* pActor) NO_INLINE;
    void startActionSound(const LiveActor* pActor, const char* pName, s32 pitch = -1, s32 velocity = -1, s32 volume = -1);
    void startActionSoundState0(const LiveActor* pActor, const char* pName, s32 pitch = -1, s32 velocity = -1,
                                s32 volume = -1);  // TODO: rename and verify arguments
    void startActionSoundState1(const LiveActor* pActor, const char* pName, s32 pitch = -1, s32 velocity = -1,
                                s32 volume = -1);  // TODO: rename and verify arguments
    void startActionSoundState2(const LiveActor* pActor, const char* pName, s32 pitch = -1, s32 velocity = -1,
                                s32 volume = -1);  // TODO: rename and verify arguments
    void fn_80008510(const LiveActor* pActor, const char* pName, u32 a1); // TODO: name function and verify argument a1
    void fn_80008560(const LiveActor* pActor, const char* pName);
};  // namespace MR
