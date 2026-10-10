#include "Game/Util/ActionSoundUtil.hpp"

namespace MR {
    const ActionSoundInfo* getActionSoundInfo(const LiveActor* pActor) NO_INLINE {
        const ActorSoundHolder* soundHolder = pActor->mSoundHolder;
        return soundHolder != nullptr ? soundHolder->mActionSoundInfo : nullptr;
    }

    // Does any code reference this? Assuming it's a copy for now...
    const ActionSoundInfo* fn_80008370(const LiveActor* pActor) NO_INLINE {
        const ActorSoundHolder* soundHolder = pActor->mSoundHolder;
        return soundHolder != nullptr ? soundHolder->mActionSoundInfo : nullptr;
    }

    void startActionSound(const LiveActor* pActor, const char* pName, s32 pitch, s32 velocity, s32 volume) {
        const ActionSoundInfo* soundInfo = getActionSoundInfo(pActor);
        if (soundInfo != nullptr) {
            soundInfo->fn_8021F470(pName, pitch, velocity, volume);
        }
    }
}  // namespace MR
