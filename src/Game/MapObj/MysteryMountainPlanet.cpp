#include "Game/MapObj/MysteryMountainPlanet.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvMysteryMountainPlanet {
    NEW_NERVE(MysteryMountainPlanetNrvWait, MysteryMountainPlanet, Wait);
    NEW_NERVE(MysteryMountainPlanetNrvBoxVanish, MysteryMountainPlanet, BoxVanish);
    NEW_NERVE(MysteryMountainPlanetNrvCakeVanish, MysteryMountainPlanet, CakeVanish);
    NEW_NERVE(MysteryMountainPlanetNrvWaitVanished, MysteryMountainPlanet, WaitVanished);
};  // namespace NrvMysteryMountainPlanet

MysteryMountainPlanet::MysteryMountainPlanet(const char* pName) : LiveActor(pName) {
}

void MysteryMountainPlanet::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    if (MR::calcDistanceToPlayer(this) < 3000.0f) {
        MR::startAction(this, "CakeVanish");
        MR::setAllAnimFrameAtEnd(this, "CakeVanish");
        initNerve(GET_NERVE(MysteryMountainPlanet, MysteryMountainPlanetNrvWaitVanished));
    } else {
        MR::startAction(this, "BoxVanish");
        MR::setAllAnimFrameAndStop(this, "BoxVanish", 0.0f);
        initNerve(GET_NERVE(MysteryMountainPlanet, MysteryMountainPlanetNrvWait));
    }

    MR::initUseStageSwitchReadA(this, rIter);
    makeActorAppeared();
}

void MysteryMountainPlanet::exeBoxVanish() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "BoxVanish");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(MysteryMountainPlanet, MysteryMountainPlanetNrvCakeVanish));
    }
}

void MysteryMountainPlanet::exeCakeVanish() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "CakeVanish");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(MysteryMountainPlanet, MysteryMountainPlanetNrvWaitVanished));
    }
}

void MysteryMountainPlanet::exeWaitVanished() {
    if (MR::isFirstStep(this)) {
        MR::invalidateClipping(this);
    }
}

void MysteryMountainPlanet::exeWait() {
    if (MR::isValidSwitchA(this) && MR::isOnSwitchA(this)) {
        setNerve(GET_NERVE(MysteryMountainPlanet, MysteryMountainPlanetNrvBoxVanish));
    }
}
