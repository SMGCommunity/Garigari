#include "Game/MapObj/OldFortressCover.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvOldFortressCover {
    NEW_NERVE(OldFortressCoverNrvWait, OldFortressCover, Wait);
    NEW_NERVE(OldFortressCoverNrvOpen, OldFortressCover, Open);
    NEW_NERVE(OldFortressCoverNrvEnd, OldFortressCover, End);
};  // namespace NrvOldFortressCover

OldFortressCover::OldFortressCover(const char* pName) : LiveActor(pName) {
}

void OldFortressCover::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    bool forceClosed = false;
    MR::getJMapInfoArg0NoInit(rIter, &forceClosed);

    MR::initUseStageSwitchReadA(this, rIter);

    if (forceClosed) {
        initNerve(GET_NERVE(OldFortressCover, OldFortressCoverNrvEnd));
    } else {
        initNerve(GET_NERVE(OldFortressCover, OldFortressCoverNrvWait));
    }

    MR::startAction(this, "Move");
    MR::setAllAnimFrameAndStop(this, "Move", 0.0f);

    MR::tryRegisterDemoCast(this, rIter);

    makeActorAppeared();
}

void OldFortressCover::exeWait() {
    if (MR::isValidSwitchA(this) && MR::isOnSwitchA(this)) {
        setNerve(GET_NERVE(OldFortressCover, OldFortressCoverNrvOpen));
    }
}

void OldFortressCover::exeOpen() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Move");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(OldFortressCover, OldFortressCoverNrvEnd));
    }
}

void OldFortressCover::exeEnd() {
}
