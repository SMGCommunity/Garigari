#include "Game/MapObj/PurpleCoinCompleteWatcher.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/EventUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"

namespace NrvPurpleCoinCompleteWatcher {
    NEW_NERVE(PurpleCoinCompleteWatcherNrvWait, PurpleCoinCompleteWatcher, Wait);
    NEW_NERVE(PurpleCoinCompleteWatcherNrvComplete, PurpleCoinCompleteWatcher, Complete);
};  // namespace NrvPurpleCoinCompleteWatcher

PurpleCoinCompleteWatcher::PurpleCoinCompleteWatcher(const char* pName) : LiveActor(pName) {
}

void PurpleCoinCompleteWatcher::init(const JMapInfoIter& rIter) {
    MR::connectToSceneMapObjMovement(this);

    initNerve(GET_NERVE(PurpleCoinCompleteWatcher, PurpleCoinCompleteWatcherNrvWait));

    MR::invalidateClipping(this);

    MR::initUseStageSwitchWriteA(this, rIter);

    makeActorAppeared();
}

void PurpleCoinCompleteWatcher::exeWait() {
    if (MR::isPurpleCoinNum100()) {
        if (MR::isValidSwitchA(this)) {
            MR::onSwitchA(this);
        }

        setNerve(GET_NERVE(PurpleCoinCompleteWatcher, PurpleCoinCompleteWatcherNrvComplete));
    }
}

void PurpleCoinCompleteWatcher::exeComplete() {
}
