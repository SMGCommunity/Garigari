#include "Game/MapObj/GhostMazePlanetMask.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/CameraUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvGhostMazePlanetMask {
    NEW_NERVE(GhostMazePlanetMaskNrvWait, GhostMazePlanetMask, Wait);
    NEW_NERVE(GhostMazePlanetMaskNrvAppear, GhostMazePlanetMask, Appear);
    NEW_NERVE(GhostMazePlanetMaskNrvDisappear, GhostMazePlanetMask, Disappear);
};  // namespace NrvGhostMazePlanetMask

GhostMazePlanetMask::GhostMazePlanetMask(const char* pName) : LiveActor(pName) {
}

void GhostMazePlanetMask::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    initNerve(GET_NERVE(GhostMazePlanetMask, GhostMazePlanetMaskNrvWait));

    makeActorAppeared();

    MR::initUseStageSwitchReadA(this, rIter);
    MR::initUseStageSwitchReadB(this, rIter);
}

void GhostMazePlanetMask::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Disappear");
        MR::setAllAnimFrameAtEnd(this, "Disappear");
    }

    if (MR::isOnSwitchA(this)) {
        setNerve(GET_NERVE(GhostMazePlanetMask, GhostMazePlanetMaskNrvAppear));
    }
}

void GhostMazePlanetMask::exeAppear() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Appear");
    }

    if (MR::isEventCameraActive()) {
        setNerve(GET_NERVE(GhostMazePlanetMask, GhostMazePlanetMaskNrvDisappear));
    }
}

void GhostMazePlanetMask::exeDisappear() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Disappear");
    }

    if (!MR::isEventCameraActive()) {
        setNerve(GET_NERVE(GhostMazePlanetMask, GhostMazePlanetMaskNrvAppear));
    }
}
