#include "Game/Util/ActionSoundUtil.hpp"

#include "Game/GameAudio/ActionSoundInfo.hpp"
#include "Game/LiveActor/ActorSoundHolder.hpp"

namespace MR {
    const ActionSoundInfo* getActionSoundInfo(const LiveActor* pActor) {
        const ActorSoundHolder* soundHolder = pActor->mSoundHolder;
        return soundHolder != nullptr ? soundHolder->mActionSoundInfo : nullptr;
    }

    // Only used in this TU
    const ActionSoundInfo* fn_80008370(const LiveActor* pActor) {
        const ActorSoundHolder* soundHolder = pActor->mSoundHolder;
        return soundHolder != nullptr ? soundHolder->mActionSoundInfo : nullptr;
    }

    void startActionSound(const LiveActor* pActor, const char* pName, s32 pitch, s32 velocity, s32 volume) {
        const ActionSoundInfo* soundInfo = getActionSoundInfo(pActor);
        if (soundInfo != nullptr) {
            soundInfo->fn_8021F470(pName, pitch, velocity, volume);
        }
    }
    
    void startActionSoundState0(const LiveActor* pActor, const char* pName, s32 pitch, s32 velocity, s32 volume) {
        const ActionSoundInfo* soundInfo = fn_80008370(pActor);
        if (soundInfo != nullptr) {
            soundInfo->fn_8021F490(0, pName, pitch, velocity, volume);
        }
    }

    void startActionSoundState1(const LiveActor* pActor, const char* pName, s32 pitch, s32 velocity, s32 volume) {
        const ActionSoundInfo* soundInfo = fn_80008370(pActor);
        if (soundInfo != nullptr) {
            soundInfo->fn_8021F490(1, pName, pitch, velocity, volume);
        }
    }
    
    void startActionSoundState2(const LiveActor* pActor, const char* pName, s32 pitch, s32 velocity, s32 volume) {
        const ActionSoundInfo* soundInfo = fn_80008370(pActor);
        if (soundInfo != nullptr) {
            soundInfo->fn_8021F490(2, pName, pitch, velocity, volume);
        }
    }
    
    void fn_80008510(const LiveActor* pActor, const char* pName, u32 a1) {
        const ActionSoundInfo* soundInfo = getActionSoundInfo(pActor);
        if (soundInfo != nullptr) {
            soundInfo->fn_8021F5A0(pName, a1);
        }
    }
    
    void fn_80008560(const LiveActor* pActor, const char* pName) {
        const ActionSoundInfo* soundInfo = getActionSoundInfo(pActor);
        if (soundInfo != nullptr) {
            soundInfo->fn_8021F630(pName);
        }
    }
}  // namespace MR
